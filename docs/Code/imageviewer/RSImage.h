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

// ���ݴ洢��ʽö�����ͣ�BSQ-�����μ���洢��BIL-����Ϊ����洢��BIP-����Ԫ����洢
enum INTERLEAVE_TYPE {BSQ,BIP,BIL};

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
//	void	Display(int nRedBand=0, int nGrnBand=1, int nBluBand=2);		//��ʾͼ�� Add by 2017.12.11

	//--------------- ������������ȡͼ������ֵ --------------------//
	inline int	GetBands() const {return m_nBands;}
	inline int	GetLines() const {return m_nLines;}
	inline int GetSamples() const {return m_nSamples;}
	inline DataType*** GetDataBuffer() const {return m_pppData;}
	inline bool	IsOpen() const { return (NULL != m_pppData ? true : false);}

protected:
	// ���ļ�
	bool	ReadMetaData(const char* lpstrMetaFilePath);	//Ԫ�����ļ�
	bool	InitBuffer(void);								//��ʼ���ڴ�
	bool	ReadImgData(const char* lpstrImgFilePath);		//��ͼ���ļ�

protected:
	//--------------------- ��Ա���� --------------------------//
	DataType***		m_pppData;		//ָ���¼��ά�����׵�ַ
	int				m_nBands;		//������
	int				m_nLines;		//����
	int				m_nSamples;		//����
	INTERLEAVE_TYPE m_eInterleave;	//���ݴ洢����BSQ/BIL/BIP
	short       m_nDataType;		//��������
};

#endif	//#ifndef _RS_IMAGE_H_INC_
