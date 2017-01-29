cmake_minimum_required(VERSION 2.8.7)
project(osg_ar_demo)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake/")

FIND_PACKAGE(OpenGL)
FIND_PACKAGE(OpenCV REQUIRED)
find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText)

# Also add some useful compiler flag
set(CMAKE_CXX_FLAGS
   "${CMAKE_CXX_FLAGS} -msse4.1 -msse3 -msse2 -msse -march=native -O3 -std=c++0x"
)

set(SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/main.cpp
  ${PROJECT_SOURCE_DIR}/include/ARCamera.cpp
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${OPENSCENEGRAPH_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(osg_ar_demo main.cpp ${SOURCE_FILES})
target_link_libraries(osg_ar_demo ${OpenCV_LIBS} ${OPENSCENEGRAPH_LIBRARIES})
