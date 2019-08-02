#include "matrixCompute.h"

namespace cino
{
    void matrixMulti3xConst(double coe, double *a, double *b)
    {
        for (int i = 0; i < 9; i++)
        {
            b[i] = a[i] * coe;
        }
    }

    void matrixMulti3x3(double *a, double *b, double *c)
    {
        c[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
        c[1] = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
        c[2] = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];

        c[3] = a[3] * b[0] + a[4] * b[3] + a[5] * b[6];
        c[4] = a[3] * b[1] + a[4] * b[4] + a[5] * b[7];
        c[5] = a[3] * b[2] + a[4] * b[5] + a[5] * b[8];

        c[6] = a[6] * b[0] + a[7] * b[3] + a[8] * b[6];
        c[7] = a[6] * b[1] + a[7] * b[4] + a[8] * b[7];
        c[8] = a[6] * b[2] + a[7] * b[5] + a[8] * b[8];
    }

    void matrixAdd3x3(double *a, double *b, double *c)
    {
        c[0] = a[0] + b[0];
        c[1] = a[1] + b[1];
        c[2] = a[2] + b[2];

        c[3] = a[3] + b[3];
        c[4] = a[4] + b[4];
        c[5] = a[5] + b[5];

        c[6] = a[6] + b[6];
        c[7] = a[7] + b[7];
        c[8] = a[8] + b[8];
    }

    void matrixPrint3x3(double *a)
    {
        std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
        std::cout << a[3] << " " << a[4] << " " << a[5] << std::endl;
        std::cout << a[6] << " " << a[7] << " " << a[8] << std::endl;
    }

    void matrixMulti4xConst(double coe, double *a, double *b)
    {
        for (int i = 0; i < 16; i++)
        {
            b[i] = a[i] * coe;
        }
    }

    void matrixMulti4x4(double *a, double *b, double *c)
    {
        c[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
        c[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
        c[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
        c[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];

        c[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
        c[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
        c[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
        c[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];

        c[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
        c[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
        c[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
        c[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];

        c[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
        c[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
        c[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
        c[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];
    }

    void matrixAdd4x4(double *a, double *b, double *c)
    {
        double *res = new double[16];

        res[0] = a[0] * b[0];
        res[1] = a[1] * b[1];
        res[2] = a[2] * b[2];
        res[3] = a[3] * b[3];

        res[4] = a[4] * b[4];
        res[5] = a[5] * b[5];
        res[6] = a[6] * b[6];
        res[7] = a[7] * b[7];

        res[8] = a[8] * b[8];
        res[9] = a[9] * b[9];
        res[10] = a[10] * b[10];
        res[11] = a[11] * b[11];

        res[12] = a[12] * b[12];
        res[13] = a[13] * b[13];
        res[14] = a[14] * b[14];
        res[15] = a[15] * b[15];
    }

    void matrixPrint4x4(double *a)
    {
        std::cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << std::endl;
        std::cout << a[4] << " " << a[5] << " " << a[6] << " " << a[7] << std::endl;
        std::cout << a[8] << " " << a[9] << " " << a[10] << " " << a[11] << std::endl;
        std::cout << a[12] << " " << a[13] << " " << a[14] << " " << a[15] << std::endl;
    }

} // namespace cino