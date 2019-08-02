#pragma once
#include <iostream>

namespace cino
{
    //==============3x3==============
    //3x3 multi a const num
    void matrixMulti3xConst(double coe, double *a, double *b);

    //3x3 multi 3x3
    void matrixMulti3x3(double *a, double *b, double *c);

    //3x3 add 3x3
    void matrixAdd3x3(double *a, double *b, double *c);

    void matrixPrint3x3(double *a);

    //==============4x4==============
    //4x4 multi a const num
    void matrixMulti4xConst(double coe, double *a, double *b);

    void matrixMulti4x4(double *a, double *b, double *c);

    void matrixAdd4x4(double *a, double *b, double *c);

    void matrixPrint4x4(double *a);
} // namespace cino
