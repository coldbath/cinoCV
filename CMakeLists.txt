CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(cinoCV)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# set(CMAKE_BUILD_TYPE "Release")

FIND_PACKAGE(OpenCV REQUIRED)

ADD_EXECUTABLE(out main.cpp util/matrixCompute.cpp geometry/geoCommon.h geometry/geo2D.cpp geometry/geo3D.cpp)
TARGET_LINK_LIBRARIES(out ${OpenCV_LIBS})


set(CMAKE_BUILD_TYPE "Debug")