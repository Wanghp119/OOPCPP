/************************************************************************/
/*                        class CRSImage                                */
/* Author: Wang Hongping												*/
/* Purpose: Reomte sensing image data									*/
/* Modify List:															*/
/* 2016.12.10 - Create it.												*/
/* 2017.12.11 - Add function to Display image in console window 		*/
/************************************************************************/
#ifndef _RS_IMAGE_H_INC_
#define _RS_IMAGE_H_INC_

// NULL define
#ifndef NULL
#define NULL 0
#endif	//#ifndef NULL

#include <QImage>
#include <QByteArray>

// ���ݴ洢��ʽö�����ͣ�BSQ-�����μ���洢��BIL-����Ϊ����洢��BIP-����Ԫ����洢
enum INTERLEAVE_TYPE {BSQ,BIP,BIL};

typedef enum EnhanceDisplayType
{
  EDT_Normal = 0
  , EDT_Linear = 1
//  , EDT_Equalization = 2
}EDT;

// class CRSImage - Remote Sensing image
class CRSImage
{
public:
	typedef unsigned char	DataType;	//typedef �����������ͱ���

	//------------------- ����/�������� -----------------------//
	CRSImage();
	CRSImage(const CRSImage& img);
	~CRSImage();

	//-------------------------- Operations ------------------------------//
	bool	Open(const char* lpstrPath);	//���ļ��������ļ�·������ȡ���ݵ��ڴ����
	bool	Save(const char* lpstrPath);	//�����ļ��������ļ�·����д���ݵ�Ӳ��
	void	Close();						//�ر�ͼ�񣬳�ʼ������
	void	PrintInfo();					//��ӡ��Ϣ
	int		CalcStatistics();				//����ͳ�������Բ���Ϊ��λ
	int		Histogram();					//ֱ��ͼ
	void	Rotate(float fAngle);			//��תͼ��
	void	Zoom(float fZoom);				//����ͼ��
	void	Filter(double* dFilterKernel, int nSize);	//ͼ���˲�
//	void	Display(int nRedBand=0, int nGrnBand=1, int nBluBand=2);    //��ʾͼ�� Add by 2017.12.11
    QImage  toQImage(int iR=0, int iG=0, int iB=0, EDT eDispType=EDT_Normal); //Transform to QImage

    void    normalImage(int iR, int iG, int iB);
    void    linearImage(int iR, int iG, int iB);

	//--------------- ������������ȡͼ������ֵ --------------------//
	inline int	GetBands() const {return m_nBands;}
	inline int	GetLines() const {return m_nLines;}
	inline int GetSamples() const {return m_nSamples;}
//	inline DataType*** GetDataBuffer() const {return m_pppData;}
    inline DataType** GetDataBuffer() const {return m_ppData;}
    inline bool	IsOpen() const { return (NULL != m_ppData ? true : false);}

protected:
	// ���ļ�
	bool	ReadMetaData(const char* lpstrMetaFilePath);	//Ԫ�����ļ�
	bool	InitBuffer(void);								//��ʼ���ڴ�
	bool	ReadImgData(const char* lpstrImgFilePath);		//��ͼ���ļ�

protected:
	//--------------------- ��Ա���� --------------------------//
//	DataType***		m_pppData;		//ָ���¼��ά�����׵�ַ
    DataType**      m_ppData;       //2D Image Matrix
	int				m_nBands;		//������
	int				m_nLines;		//����
	int				m_nSamples;		//����
	INTERLEAVE_TYPE m_eInterleave;	//���ݴ洢����BSQ/BIL/BIP
	short       m_nDataType;		//��������
//    unsigned char*  m_pDispBuff;   //Display Buffer to QImage
    QByteArray      m_aryDispBuff;  //Display Buffer to QImage
};

#endif	//#ifndef _RS_IMAGE_H_INC_
