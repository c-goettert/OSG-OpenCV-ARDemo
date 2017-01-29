
/**
*  @file    main.cpp
*  @author  Christoph Göttert
*  @version 0.1
*/

#include <iostream>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osg/Shader>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

#include "ARCamera.h"

int main( int argc, char** argv )
{
	 int screenWidth,screenHeight,textureWidth,textureHeight;
	 screenWidth = 640;
	 screenHeight = 480;

	 textureWidth = 640;
	 textureHeight = 480;

	 // OPENCV STUFF
	 // OpenCV Webcam
	 cv::VideoCapture cap(0);

	 if(!cap.isOpened())
	 {
			 std::cout << "Webcam cannot open!\n";
			 return 0;
	 }

	// OSG STUFF
	// Create viewer
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("dumptruck.osgt");
	osg::ref_ptr<osg::Group> group = new osg::Group;
	viewer.setUpViewInWindow(50,50,screenWidth,screenHeight);
	ARCamera arCamera;
	cv::Mat frame = cvLoadImage("../image2.jpg", 1);
	// Update the Frame for the camera manually
	arCamera.update(frame);

	// First add Model to group
	// group->addChild(scene.get());
	// then ad HUD
	osg::Camera* camera = arCamera.createCamera(textureWidth, textureHeight);
  group->addChild(camera);

  // set the scene to render
  viewer.setSceneData(group.get());
	// Start Viewer
	while (!viewer.done())
	{
		// Refresh Background Image
		cv::Mat frame;
		cap >> frame;
		arCamera.update(frame);
		// osg::Matrix rot;
		// rot.makeRotate( angle, osg::Vec3( 1., 0., 0. ) );
		// angle += 0.01;
		// // Set the view matrix (the concatenation of the rotation and
		// // translation matrices).
		// viewer.getCamera()->setViewMatrix( rot * trans );
		// // Draw the next frame.
		viewer.frame();
	}
	return 0;
}
