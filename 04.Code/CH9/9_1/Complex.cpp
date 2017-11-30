#include "Complex.h"

// ���캯��
CComplex::CComplex(double r, double i) : m_dblReal(r), m_dblImage(i)
{
}

// ��������
CComplex::~CComplex(void)
{
}

CComplex	//��������
CComplex::operator-()
{
	return CComplex(-m_dblReal, -m_dblImage);
}

bool	// < ����
CComplex::operator<(const CComplex& c)
{
	if (m_dblReal < c.m_dblReal && m_dblImage < c.m_dblImage)
		return true;
	return false;
}


// ���������
ostream& operator<<(ostream& os, const CComplex& c)
{
	os << c.m_dblReal << (c.m_dblImage>0.0 ? "+" : "");
	os << c.m_dblImage << "i";

	return os;
}

// ���������
istream& operator>>(istream& is, CComplex& c)
{
	is >> c.m_dblReal >> c.m_dblImage;
	return is;
}