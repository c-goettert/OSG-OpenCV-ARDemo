/**
*  @file    ARCamera.h
*  @author  Christoph Göttert
*  @version 0.1
*/

#ifndef _ARCAMERA_H_
#define _ARCAMERA_H_

#include <iostream>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osg/Shader>
#include <osgGA/StateSetManipulator>

#include <opencv2/opencv.hpp>

class ARCamera {
	public:
		ARCamera();
		void update(cv::Mat frame);
		osg::Geode* createCameraPlane(int textureWidth, int textureHeight);
		osg::Camera* createCamera(int textureWidth, int textureHeight);

	protected:
		osg::ref_ptr<osg::Image> img;
};

#endif
