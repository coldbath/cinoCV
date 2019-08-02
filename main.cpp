#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "util/matrixCompute.h"

int main()
{
    double a[9] = {0}, b[9] = {0};

    a[0] = 1;
    a[4] = 1;
    a[8] = 1;

    b[0] = 1;
    b[4] = 1;
    b[8] = 1;

    double c[9] = {0};

    cino::matrixAdd3x3(a, b, c);

    cino::matrixPrint3x3(c);

    return 0;
}