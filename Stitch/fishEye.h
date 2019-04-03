#pragma once

#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

namespace cinoCV
{
    //use MEI model calib camere internal
    struct Parameters
    {
        double m_xi;
        double m_k1;
        double m_k2;
        double m_p1;
        double m_p2;
        double m_gamma1;
        double m_gamma2;
        double m_u0;
        double m_v0;

        int fw;
        int fh;

        bool readFromYamlFile(std::string filename)
        {
            cv::FileStorage fs(filename, cv::FileStorage::READ);

            if (!fs.isOpened())
            {
                return false;
            }

            fw = fs["image_width"];
            fh = fs["image_height"];

            cv::FileNode n = fs["mirror_parameters"];
            m_xi = static_cast<double>(n["xi"]);

            n = fs["distortion_parameters"];
            m_k1 = static_cast<double>(n["k1"]);
            m_k2 = static_cast<double>(n["k2"]);
            m_p1 = static_cast<double>(n["p1"]);
            m_p2 = static_cast<double>(n["p2"]);

            n = fs["projection_parameters"];
            m_gamma1 = static_cast<double>(n["gamma1"]);
            m_gamma2 = static_cast<double>(n["gamma2"]);
            m_u0 = static_cast<double>(n["u0"]);
            m_v0 = static_cast<double>(n["v0"]);
        }
        
    };

    //Apply distortion to input point (from the normalised plane)
    void distortion(cv::Point2d p_u, cv::Point2d &d_u, Parameters param);

    //Projects an undistorted 2D point p_u to the image plane
    void undistToPlane(cv::Point2d p_u, Parameters param, cv::Point2d &p, bool bDistortion);

    //Lifts a point from the image plane to the unit sphere
    void liftSphere(cv::Point2d p2d, cv::Point3d &p3d, Parameters param, bool bDistortion);

    //Project a 3D point (x,y,z) to the image plane in (u,v)
    void spaceToPlane(cv::Point3d p3d, Parameters param, cv::Point2d &p2d, bool bDistortion);

    /////////////////////////////////////////////////////////////////////////////////////////
    //fish eye info
    struct VARS
    {
        int fishwidth;
        int fishheight;    // Fisheye input image dimensions
        int outwidth;
        int outheight;                // Dimension of the output equirectangular image
        int fishcenterx;
        int fishcentery; // Centre of the fisheye circle in the image
        int fishradius;              // The radius of the fisheye circle in the image
        double fishfov;              // Fisheye field of view
        int antialias;
    };

    bool findFishPixel(double latitude, double longitude, Parameters param, cv::Mat T, VARS vars, int *u, int *v, double *fu, double *fv);

    //fish eye image to pano 
    void fish2Sphere(cv::Mat feImg, cv::Mat T, Parameters param, int imgNum, int ow, int fov, std::string dstPath);
}