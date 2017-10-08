#include "TriFunc.h"
#include <cmath>

const double EPLISON = 1.e-6;

bool IsValidTriangle(double a, double b, double c)
{
    if ((a+b-c)<EPLISON || (a+c-b)<EPLISON || (b+c-a)<EPLISON)
        return false;

    return true;
}

/// �����ܳ�
double GetPerimeter(double a, double b, double c)
{
    double dPerimeter = 0.0f;
    if (IsValidTriangle(a, b, c))
    {
        dPerimeter = (a+b+c);
    }

    return dPerimeter;
}

/// �������
double GetArea(double a, double b, double c)
{
    double  dArea = 0.0f;
    double  S = (a+b+c)/2;

    if (IsValidTriangle(a, b, c))
    {
        dArea = sqrt(S*(s-a)*(s-b)*(s-c));
    }

    return dArea;
}

/// ����Ƕ�
double GetAngle(double a, double b, double c, int which)
{
    // cosa = (a*a+b*b-c*c)/(a*b);

}
