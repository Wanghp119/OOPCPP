#ifndef POOL_H
#define POOL_H
#include <string>
#include "Circle.h"
using namespace std;
//class Circle;

class Pool
{
public:
    Pool();
    virtual ~Pool();

    float getPrice();

protected:

private:
    Circle  m_oSwimmingCircle;
    Circle  m_oFenceCircle;
    float   m_fFencePrice;		//Χ������35/m
    float   m_fRoadPrice;		//�������� 20/m2
};

#endif // POOL_H
