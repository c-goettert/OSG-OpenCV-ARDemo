/**
*  @file    VirtualCamera.h
*  @author  Christoph Göttert
*  @version 0.1
*/

#ifndef _VIRTUALCAMERA_H_
#define _VIRTUALCAMERA_H_

#include <osg/Camera>

class VirtualCamera {
	public:
		VirtualCamera(osg::ref_ptr<osg::Camera> cam);
		void updateTranslation(double x, double y, double z);
		void updateRotation(double x, double y, double z);

	protected:
		double angle;
		osg::Matrix rotation;
		osg::Matrix translation;
		osg::ref_ptr<osg::Camera> camera;
};

#endif
