#include "geo3D.h"

namespace cino
{
    void getFacePara_3D(cv::Point3f pt1, cv::Point3f pt2, cv::Point3f pt3, FacePara_3D &face)
    {
        face.A = (pt3.y-pt1.y)*(pt3.z-pt1.z) - (pt2.z-pt1.z)*(pt3.y-pt1.y);
        face.B = (pt3.x-pt1.x)*(pt2.z-pt1.z) - (pt2.x-pt1.x)*(pt3.z-pt1.z);
        face.C = (pt2.x-pt1.x)*(pt3.y-pt1.y) - (pt3.x-pt1.x)*(pt2.y-pt1.y);
        face.D = -(face.A*pt1.x + face.B*pt1.y + face.C*pt1.z);
    }

    float distPoint2Line_3D(cv::Point3f ptLine1, cv::Point3f ptLine2, cv::Point3f pt)
    {
        float ab = sqrt(pow((ptLine1.x - ptLine2.x), 2.0) + pow((ptLine1.y - ptLine2.y), 2.0) + pow((ptLine1.z - ptLine2.z), 2.0));
        float as = sqrt(pow((ptLine1.x - pt.x), 2.0) + pow((ptLine1.y - pt.y), 2.0) + pow((ptLine1.z - pt.z), 2.0));
        float bs = sqrt(pow((pt.x - ptLine2.x), 2.0) + pow((pt.y - ptLine2.y), 2.0) + pow((pt.z - ptLine2.z), 2.0));
        
        float cos_A = (pow(as, 2.0) + pow(ab, 2.0) - pow(bs, 2.0)) / (2 * ab*as);
        float sin_A = sqrt(1 - pow(cos_A, 2.0));

        return as*sin_A; 
    }

    float distPoint2Face_3D(cv::Point3f pt, FacePara_3D face)
    {
        return fabs((face.A*pt.x + face.B*pt.y + face.C*pt.z + face.D) / sqrt(face.A*face.A + face.B*face.B + face.C*face.C));
    }
} // namespace cino



 