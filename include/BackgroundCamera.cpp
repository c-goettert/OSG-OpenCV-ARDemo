/**
*  @file    ARCamera.cpp
*  @author  Christoph Göttert
*  @version 0.1
*/

#include "BackgroundCamera.h"

BackgroundCamera::BackgroundCamera() {
		// Create OSG Image from CV Mat
		img = new osg::Image;
}

void BackgroundCamera::update(cv::Mat frame)
{
	img->setImage(frame.cols, frame.rows, 3,
			GL_RGB, GL_BGR, GL_UNSIGNED_BYTE,
			(uchar*)(frame.data),
			osg::Image::AllocationMode::NO_DELETE, 1);
	img->dirty();
}

osg::Geode* BackgroundCamera::createCameraPlane(int textureWidth, int textureHeight)
{
	// CREATE PLANE TO DRAW TEXTURE
	osg::ref_ptr<osg::Geometry> quadGeometry = osg::createTexturedQuadGeometry(osg::Vec3(0.0f,0.0f,0.0f),
										osg::Vec3(textureWidth,0.0f,0.0f),
										osg::Vec3(0.0,textureHeight,0.0),
										0.0f,
										1.0f,
										1.0f,
										0.0f);
	// PUT PLANE INTO NODE
	osg::ref_ptr<osg::Geode> quad = new osg::Geode;
	quad->addDrawable(quadGeometry);
	// DISABLE SHADOW / LIGHTNING EFFECTS
	int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
	quad->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL), values );
	quad->getOrCreateStateSet()->setMode( GL_LIGHTING, values );

	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setTextureSize( textureWidth, textureHeight);
	texture->setFilter(osg::Texture::MIN_FILTER , osg::Texture::LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER , osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	texture->setResizeNonPowerOfTwoHint(false);

	texture->setImage(img);

	// Apply texture to quad
	osg::ref_ptr<osg::StateSet> stateSet = quadGeometry->getOrCreateStateSet();
	stateSet->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

	return quad.release();
}

osg::Camera* BackgroundCamera::createCamera(int textureWidth,int textureHeight)
{
	osg::ref_ptr<osg::Geode> quad = createCameraPlane(textureWidth, textureHeight);
	//Bind texture to the quadGeometry, then use the following camera:
	osg::Camera* camera = new osg::Camera;
  // CAMERA SETUP
	camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
	// use identity view matrix so that children do not get (view) transformed
	camera->setViewMatrix(osg::Matrix::identity());
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setClearColor( osg::Vec4(0.f, 0.f, 0.f, 1.0) );
	camera->setProjectionMatrixAsOrtho( 0.f, textureWidth, 0.f, textureHeight, 1.0, 500.f );
	// set resize policy to fixed
	camera->setProjectionResizePolicy(osg::Camera::ProjectionResizePolicy::FIXED);
	// we don't want the camera to grab event focus from the viewers main camera(s).
	camera->setAllowEventFocus(false);
	// only clear the depth buffer
	camera->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//camera->setViewport( 0, 0, screenWidth, screenHeight );
	camera->setRenderOrder( osg::Camera::NESTED_RENDER );
	camera->addChild(quad);
	return camera;
}
