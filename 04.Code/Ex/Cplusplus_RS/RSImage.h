#ifndef _RSIMAGE_H_INCLUDED_
#define _RSIMAGE_H_INCLUDED_

#include <string>
using namespace std;

class RSImage
{
public:
	RSImage();	//ȱʡ���캯��
	RSImage(int nx, int ny, int nz, int nDataType, int nSotreType, void* ptData);	//���ع��캯��
	RSImage(RSImage& img);	//�������캯��
	~RSImage();	//��������
	
public:
	bool	Open(const string strPath);
	void	Close();
	bool	Save(const string strDstPath) const;
	long	GetStatistics(double* pdfMean, double* pdfStd, double* pdfMax, double* pdfMin) const;
	long	GetHist(double* pdfHist, int* pnCount) const;
	void	Rotate(double dfAngle);
	void	Zoom(double dfScale);
	void	Filter(int nKernelSize, double* pdfKernel);

protected:
	

private:
	string	m_strPath;
	int		m_nX;
	int		m_nY;
	int		m_nBand;
	int		m_nDataType;
	int		m_nStoreType;
	void*	m_ptData;
};
#endif	//_RSIMAGE_H_INCLUDED_