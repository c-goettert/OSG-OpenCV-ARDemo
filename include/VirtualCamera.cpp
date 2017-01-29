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

void VirtualCamera::updateTranslation(double x, double y, double z)
{
	translation.makeTranslate(x, y, z);
	camera->setViewMatrix( rotation * translation );
}

void VirtualCamera::updateRotation(double x, double y, double z)
{
	rotation.makeRotate(
	  osg::DegreesToRadians(x), osg::Vec3(0,1,0), // roll
	  osg::DegreesToRadians(y), osg::Vec3(1,0,0) , // pitch
	  osg::DegreesToRadians(z), osg::Vec3(0,0,1) ); // heading
	camera->setViewMatrix( rotation * translation );
}
