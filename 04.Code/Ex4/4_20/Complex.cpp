/*****************************************************************************
 * File��Complex.cpp                                                         *
 * Description���������ʵ��                                                       *
 * Author: Wang hongping 2016.11.14                                          *
 *****************************************************************************/

#include "Complex.h"
#include <cmath>

///���캯��
complex::complex(float r, float i)
{
    m_fr = r;
    m_fi = i;
}

///�������캯��
complex::complex(const complex& c)
{
    m_fr = c.m_fr;
    m_fi = c.m_fi;
}


/**************************************************************************
 *                       ���������                                      *
 **************************************************************************/
/// + ����
complex complex::operator+(const complex& c)
{
    return complex(m_fr+c.m_fr, m_fi+c.m_fi);
}

/// - ����
complex complex::operator-(const complex& c)
{
    return complex(m_fr-c.m_fr, m_fi-c.m_fi);
}

/// * ����
complex complex::operator*(const complex& c)
{
    return complex(m_fr*c.m_fr-m_fi*c.m_fi, m_fr*c.m_fi+m_fi*c.m_fr);
}

/// / ����
complex complex::operator/(const complex& c)
{
    float   t;
    t = c.m_fr*c.m_fr + c.m_fi*c.m_fi; //norm

    return complex((c.m_fr*m_fr + c.m_fi*m_fi)/t, (c.m_fr*m_fi - c.m_fi*m_fr)/t);
}

/// �������������
ostream& operator<<(ostream& os, const complex& c)    ///ע������Ķ���
{
    os << c.m_fr;

    if (fabs(c.m_fi) > 1e-12)
        os << (c.m_fi>1e-12 ? "+" : "") << c.m_fi << "i";

    return os;
}

/// �������������
istream& operator>>(istream& is, const complex& c)
{
    is >> c.m_fr >> c.m_fi;
    return is;
}

