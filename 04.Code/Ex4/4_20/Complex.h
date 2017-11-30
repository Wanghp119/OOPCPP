/******************************************************************************
 * Description�������࣬���ڸ����ļ�����                                  *
 * File��complex.h                                                            *
 * Author: Wang hongping 2016.11.14                                           *
 ******************************************************************************/

#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#include <iostream>
using namespace std;

/// ����
class complex
{
public:
    complex(float r=0.0f, float i=0.0f);    ///���캯��
    complex(const complex& c);              ///���ƹ��캯��
public:
    complex operator+(const complex& c);    ///���������
    complex operator-(const complex& c);
    complex operator*(const complex& c);
    complex operator/(const complex& c);

    friend ostream& operator<<(ostream& os, const complex& c);    ///�������������
    friend istream& operator>>(istream& is, const complex& c);

private:
    float   m_fr;   ///ʵ��
    float   m_fi;   ///�鲿
};


#endif // COMPLEX_H_INCLUDED
