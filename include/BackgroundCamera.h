/**
*  @file    ARCamera.h
*  @author  Christoph Göttert
*  @version 0.1
*/

#ifndef _BACKGROUNDCAMERA_H_
#define _BACKGROUNDCAMERA_H_

#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osg/Geode>
#include <osg/Geometry>
#include <opencv2/opencv.hpp>

class BackgroundCamera {
	public:
		BackgroundCamera();
		void update(cv::Mat frame);
		osg::Geode* createCameraPlane(int textureWidth, int textureHeight);
		osg::Camera* createCamera(int textureWidth, int textureHeight);

	protected:
		osg::ref_ptr<osg::Image> img;
};

#endif
