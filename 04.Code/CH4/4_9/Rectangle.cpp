#include "Rectangle.h"
#include <iostream>

using namespace std;

/// ���캯��
Rectangle::Rectangle(int xmin, int xmax, int ymin, int ymax)
    : m_ptLeftUp(xmin, ymin), m_ptRightBottom(xmax, ymax)
{

}

/// ���캯��
Rectangle::Rectangle(const Point& ptLu, const Point& ptRb)
    : m_ptLeftUp(ptLu), m_ptRightBottom(ptRb)
{

}

/// �������캯��
Rectangle::Rectangle(const Rectangle& rect)
    : m_ptLeftUp(rect.m_ptLeftUp), m_ptRightBottom(rect.m_ptRightBottom)
{

}
