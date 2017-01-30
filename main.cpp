
/**
*  @file    main.cpp
*  @author  Christoph Göttert
*  @version 0.1
*/

#include <iostream>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

#include "BackgroundCamera.h"
#include "VirtualCamera.h"

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
	viewer.setUpViewInWindow(50,50,screenWidth,screenHeight);

	// Main Camera
	osg::ref_ptr<osg::Camera>  camera = viewer.getCamera();
	VirtualCamera* vCamera = new VirtualCamera(camera);

	// Background-Camera (OpenCV Feed)
 	BackgroundCamera bgCamera;
 	osg::Camera* backgroundCamera = bgCamera.createCamera(textureWidth, textureHeight);

	// Load Truck Model as Example Scene
	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("dumptruck.osgt");

	// Create new group node
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::Node* background = backgroundCamera;
	osg::Node* foreground = scene.get();
	background->getOrCreateStateSet()->setRenderBinDetails(1,"RenderBin");
	foreground->getOrCreateStateSet()->setRenderBinDetails(2,"RenderBin");
	group->addChild(background);
	group->addChild(foreground);
	background->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	foreground->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);

  // Add the groud to the viewer
  viewer.setSceneData(group.get());

	double angleRoll( 0. );
	while (!viewer.done())
	{
		// Refresh Background Image
		cv::Mat frame;
		cap >> frame;
		bgCamera.update(frame);

		angleRoll += 0.5;
		// Update Virtual Camera (these Coordinates should be determined by some AR-Framework/Functionality)
		// They are just updated for demonstration purposes..
		// Position Parameters: Roll, Pitch, Heading, X, Y, Z
		vCamera->updatePosition(angleRoll,0,0,  0, -100, 0);
		//osg::notify(osg::WARN)<<"Angle: "<<  angleRoll <<std::endl;
		viewer.frame();
	}
	return 0;
}
