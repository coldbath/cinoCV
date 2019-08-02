#pragma once

#include "geoCommon.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

namespace cino
{
    void getFacePara_3D(cv::Point3f pt1, cv::Point3f pt2, cv::Point3f pt3, FacePara_3D &face);

    float distPoint2Line_3D(cv::Point3f ptLine1, cv::Point3f ptLine2, cv::Point3f pt);
}
