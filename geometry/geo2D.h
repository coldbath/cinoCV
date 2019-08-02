#pragma once

#include "geoCommon.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

namespace cino
{
    void getLinePara_2D(cv::Point2f pt1, cv::Point2f pt2, LinePara_2D &line);

    bool getCross_2D(cv::Point2f pt1, cv::Point2f pt2, cv::Point2f pt3, cv::Point2f pt4, cv::Point2f &crossPt);
    bool getCross_2D(LinePara_2D line1, LinePara_2D line2, cv::Point2f &crossPt);

    float distPoint2Line_2D(cv::Point2f pt, LinePara_2D line);

    void getFacePara_3D(cv::Point3f pt1, cv::Point3f pt2, cv::Point3f pt3, FacePara_3D &face);
}