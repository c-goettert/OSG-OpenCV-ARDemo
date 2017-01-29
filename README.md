# OSG-OpenCV-ARDemo
Very basic project which might server as a template for augmented reality scenes using OpenSceneGraph for 3D Visualisation and OpenCV to grab webcam frames for the background.

![screen](https://cloud.githubusercontent.com/assets/7591624/22407163/62cecc90-e661-11e6-8bf1-58cca94bc41d.jpg)

*Note: The model was just placed nice "manually" by moving the camera, this project does not contain any real AR-Functionality (e.g. markers or tracking).*

# Requirements
* Cmake
* OpenCV
* OpenSceneGraph
* to see the sample model, you need OpenSceneGraph-Data set to OSG_FILE_PATH (see this [link](http://trac.openscenegraph.org/projects/osg/wiki/Support/GettingStarted))

# Install
* Switch to project directory:
`cd ~/OSG-OpenCV-ARDemo`
* Create build folder:
`mkdir build`
`cd build/`
* Make project:
`cmake ..`
* Compile:
`make`
* finally, to run the code use:
`./osg_ar_demo`

# Remarks
The implementation might not be optimal in performance, defining an own `osg::ImageStream` might be better. If you have any enhancements, feel free to contribute.
