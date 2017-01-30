/**
*  @file    VirtualCamera.cpp
*  @author  Christoph Göttert
*  @version 0.1
*/

#include "VirtualCamera.h"

VirtualCamera::VirtualCamera(	osg::ref_ptr<osg::Camera> cam)
{
	camera = cam;
	// Initial Values
	camera->setProjectionMatrixAsPerspective(40., 1., 1., 100. );
}

void VirtualCamera::updatePosition(double r, double p, double h, double x, double y, double z)
{
	osg::Matrixd myCameraMatrix;

	// Update Rotation
	rotation.makeRotate(
		osg::DegreesToRadians(r), osg::Vec3(0,1,0), // roll
		osg::DegreesToRadians(p), osg::Vec3(1,0,0) , // pitch
		osg::DegreesToRadians(h), osg::Vec3(0,0,1) ); // heading

	// Update Translation
	translation.makeTranslate(x, y, z);
	myCameraMatrix = rotation * translation;
	osg::Matrixd i = myCameraMatrix.inverse(myCameraMatrix);
	camera->setViewMatrix(i*osg::Matrix::rotate(-(osg::PI_2),1,0,0));
}
