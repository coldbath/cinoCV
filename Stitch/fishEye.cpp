#include "fishEye.h"

#include <iostream>
#include <fstream>
#include <math.h>

#define PI 3.1415926

inline int getIndex(int x, int y, int w)
{
    return y * w + x;
}

namespace cinoCV
{
    void distortion(cv::Point2d p_u, cv::Point2d &d_u, Parameters param)
    {
        double k1 = param.m_k1;
        double k2 = param.m_k2;
        double p1 = param.m_p1;
        double p2 = param.m_p2;

        double mx2_u, my2_u, mxy_u, rho2_u, rad_dist_u;

        mx2_u = p_u.x * p_u.x;
        my2_u = p_u.y * p_u.y;
        mxy_u = p_u.x * p_u.y;

        rho2_u = mx2_u + my2_u;
        rad_dist_u = k1 * rho2_u + k2 * rho2_u * rho2_u;

        d_u.x = p_u.x * rad_dist_u + 2.0 * p1 * mxy_u + p2 * (rho2_u + 2.0 * mx2_u);
        d_u.y = p_u.y * rad_dist_u + 2.0 * p2 * mxy_u + p1 * (rho2_u + 2.0 * my2_u);          
    }

    void liftSphere(cv::Point2d p2d, cv::Point3d &p3d, Parameters param, bool bDistortion)
    {
        double mx_d, my_d,mx2_d, mxy_d, my2_d, mx_u, my_u;
        double rho2_d, rho4_d, radDist_d, Dx_d, Dy_d, inv_denom_d;
        double lambda;

        double m_inv_K11 = 1.0 / param.m_gamma1;
        double m_inv_K13 = -1 * param.m_u0 / param.m_gamma1;
        double m_inv_K22 = 1.0 / param.m_gamma2;
        double m_inv_K23 = -1 * param.m_v0 / param.m_gamma2;

        mx_d = m_inv_K11 * p2d.x + m_inv_K13;
        my_d = m_inv_K22 * p2d.y + m_inv_K23;

        if (bDistortion)
        {
            int n = 6;

            cv::Point2d d_u;

            distortion(cv::Point2d(mx_d, my_d), d_u, param);

            // Approximate value
            mx_u = mx_d - d_u.x;
            my_u = my_d - d_u.y;

            for (int i = 1; i < n; ++i)
            {
                distortion(cv::Point2d(mx_u, my_u), d_u, param);
                mx_u = mx_d - d_u.x;
                my_u = my_d - d_u.y;
            }
        }
        else
        {
            mx_u = mx_d;
            my_u = my_d;
        }
        
        // Lift normalised points to the sphere (inv_hslash)
        double xi = param.m_xi;
        if (xi == 1.0)
        {
            lambda = 2.0 / (mx_u * mx_u + my_u * my_u + 1.0);
            p3d.x = lambda * mx_u;
            p3d.y = lambda * my_u;
            p3d.z = lambda - 1.0f;
        }
        else
        {
            lambda = (xi + sqrt(1.0 + (1.0 - xi * xi) * (mx_u * mx_u + my_u * my_u))) / (1.0 + mx_u * mx_u + my_u * my_u);
            p3d.x = lambda * mx_u;
            p3d.y = lambda * my_u;
            p3d.z = lambda - xi;
        }
    }

    void spaceToPlane(cv::Point3d p3d, Parameters param, cv::Point2d &p2d, bool bDistortion)
    {
        cv::Point2d p_u, p_d;
        
        // Project points to the normalised plane
        double z = p3d.z + param.m_xi * sqrt(p3d.x * p3d.x + p3d.y * p3d.y + p3d.z * p3d.z);

        p_u.x = p3d.x / z;
        p_u.y = p3d.y / z;

        if (bDistortion)
        {
            // Apply distortion
            cv::Point2d d_u;
            distortion(p_u, d_u, param);
            p_d = p_u + d_u;
        }
        else
        {
            p_d = p_u;
        }

        p2d.x = param.m_gamma1 * p_d.x + param.m_u0;
        p2d.y = param.m_gamma2 * p_d.y + param.m_v0;
    }

    void undistToPlane(cv::Point2d p_u, Parameters param, cv::Point2d &p, bool bDistortion)
    {
        cv::Point2d p_d;

        if (bDistortion)
        {
            // Apply distortion
            cv::Point2d d_u;
            distortion(p_u, d_u, param);
            p_d = p_u + d_u;
        }
        else
        {
            p_d = p_u;
        }

        
        // Apply generalised projection matrix
        p.x = param.m_gamma1 * p_d.x + param.m_u0;
        p.y = param.m_gamma2 * p_d.y + param.m_v0;
    }

    bool findFishPixel(double latitude, double longitude, Parameters param, cv::Mat T, VARS vars, int *u, int *v, double *fu, double *fv)
    {
        int k;
        cv::Point3d p;
        double theta, phi, r;

        //p is the ray from the camera position into the scene
        p.x = cos(latitude) * sin(longitude);
        p.y = cos(latitude) * cos(longitude);
        p.z = sin(latitude);
    
        if(std::isnan(p.x) || std::isnan(p.y) || std::isnan(p.z))
            return false;

        // Apply transformation
        cv::Mat rotation = (cv::Mat_<double>(3,3) << T.at<double>(0,0), T.at<double>(0,1), T.at<double>(0,2),
                                                    T.at<double>(1,0), T.at<double>(1,1), T.at<double>(1,2),
                                                    T.at<double>(2,0), T.at<double>(2,1), T.at<double>(2,2));

        cv::Mat translation = (cv::Mat_<double>(3,1) <<T.at<double>(0,3), T.at<double>(1,3), T.at<double>(2,3));

        cv::Mat sphPt = (cv::Mat_<double>(3,1) << p.x, p.y, p.z);

        //rotation and translation for camera dirction
        sphPt = rotation * sphPt + translation;

        p.x = sphPt.at<double>(0, 0);
        p.y = sphPt.at<double>(1, 0);
        p.z = sphPt.at<double>(2, 0);

        //calculate fisheye polar coordinates
        theta = atan2(p.z, p.x); //-pi ... pi
        phi = atan2(sqrt(p.x*p.x + p.z*p.z), p.y);//0 ... fov
        r = phi / vars.fishfov;//0 ... 1

        if (r > 1)
            return false;

        //determine the u,v coordinate
        *fu = vars.fishcenterx + r * vars.fishradius * cos(theta);
        *u = *fu;
        *fu /= vars.fishwidth;

        cv::Point3d p3d;
        cv::Point2d p2d;

        *fv = vars.fishcentery  + r * vars.fishradius * sin(theta);
        *v = *fv;
        *fv /= vars.fishheight;

        p2d.x = *u;
        p2d.y = *v;

        liftSphere(p2d, p3d, param, true);
        spaceToPlane(p3d, param, p2d, false);

        *u = p2d.x;
        *v = p2d.y;

        if(*u < 0 || *u >= vars.fishwidth || *fu >= 1 || *fu < 0)
            return false;

        if(*v < 0 || *v >= vars.fishheight || *fv >= 1 || *fv < 0)
            return false;
        
        return true;
    }

    void fish2Sphere(cv::Mat feImg, cv::Mat T, Parameters param, int imgNum, int ow, int fov, std::string dstPath)
    {
        ow = 2 * (ow / 2); //ensure ow is even
        int oh = ow / 2;

        cv::Mat sphere;
        sphere.create(oh, ow, CV_8UC3);

        int fw, fh; 
        fw = feImg.cols;
        fh = feImg.rows;

        VARS vars;
        vars.fishwidth = param.fw;
        vars.fishheight = param.fh;
        vars.fishcenterx = param.m_u0;
        vars.fishcentery = param.m_v0;

        vars.outwidth = ow;
        vars.outheight = oh;
        
        vars.fishradius = vars.fishwidth / 2;
        vars.fishfov = fov * PI / 180 / 2;
        vars.antialias = 1;

        int rsum, gsum, bsum;
        int ai, aj;
        int index;

        int u, v;
        double z, x, y, fu, fv;
        double latitude, longitude;

        int i, j;
        for (j = 0;j<vars.outheight;j++) 
        {
            for (i = 0;i<vars.outwidth;i++) 
            {
                // Normalised coordinates
                x = 2 * i / (double)vars.outwidth - 1; // -1 to 1
                y = 2 * j / (double)vars.outheight - 1; // -1 to 1
                
                longitude = x * PI;     // -pi <= x < pi
                latitude = y * PI/2;     // -pi/2 <= y < pi/2

                if (findFishPixel(latitude,longitude, param, T, vars, &u, &v, &fu, &fv))
                {
                    for(size_t k = 0; k < 3; k++)
                    {
                        *(sphere.data + 3 * (j * vars.outwidth + i) + k) = *(feImg.data + 3 * (v * vars.fishwidth + u) + k);
                    }
                }
                else
                {
                    for(size_t k = 0; k < 3; k++)
                    {
                        *(sphere.data + 3 * (j * vars.outwidth + i) + k) = 0;
                    }
                }
            }

        }

         cv::imwrite(dstPath, sphere);
    }

}//end of namespace
