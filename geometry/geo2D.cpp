#include "geo2D.h"

namespace cino
{
    void getLinePara_2D(cv::Point2f pt1, cv::Point2f pt2, LinePara_2D &line)
    {
        double m = 0;

        m = pt2.x - pt1.x;

        float k, b;

        if(0 == m)
        {
            k = 10000.0;
            b = pt1.y - k * pt1.x;
        }
        else
        {
            k = (pt2.y - pt1.y) / (pt2.x - pt1.x);
            b = pt1.y - k * pt1.x;
        }

        line.A = -1.0f;
        line.B = k;
        line.C = b;
    }

    bool getCross_2D(cv::Point2f pt1, cv::Point2f pt2, cv::Point2f pt3, cv::Point2f pt4, cv::Point2f &crossPt)
    {
        LinePara_2D line1, line2;

        getLinePara_2D(pt1, pt2, line1);
        getLinePara_2D(pt3, pt4, line2);

        return getCross_2D(line1, line2, crossPt);
    }

    bool getCross_2D(LinePara_2D line1, LinePara_2D line2, cv::Point2f &crossPt)
    {
        float k1, k2, b1, b2;

        k1 = -line1.B / line1.A;
        k2 = -line2.B / line2.A;

        b1 = -line1.C / line1.A;
        b2 = -line2.C / line2.A;

        if(fabs(k1 - k2) > 0.5f)
        {
            crossPt.x = (b2 - b1) / (k1 - k2);
            crossPt.y = k1*crossPt.x + b1;
            
            return true;
        }
        else
        {
            return false;
        }
    }

    float distPoint2Line_2D(cv::Point2f pt, LinePara_2D line)
    {
        return fabs((line.A*pt.x + line.B*pt.y + line.C) / sqrt(line.A*line.A + line.B*line.B));
    }

} // namespace cino
