#pragma once
#include <string>
using namespace std;

// �������з�ʽö��
enum eInterleave{BSQ,BIL,BIP};

class CRSImage
{
public:
	CRSImage(void);
	~CRSImage(void);

	// Methods
	void doOpen();	//���ļ�
	void doDisplay();	//��ʾͼ��
protected:
	string getMetaDataPath(const char*);	//��ͼ���ļ�·��-->Ԫ�����ļ�·��
	bool ReadMetaData(const char*);			//��ȡԪ�����ļ�
	bool NewImageArray();					//��������
	bool ReadImageData(const char*);		//��ȡͼ���ļ�.img to ����
	bool ReadBsqImage(const char*);			//��ȡBSQ
	bool ReadBilImage(const char*);			//��ȡBIL
	bool ReadBipImage(const char*);			//��ȡBIP
	void Close();							//�ر��ļ����ͷ��ڴ�

	void DrawImage(int, int, int);			//����ͼ��
private:
	int		m_nSamples;
	int		m_nLines;
	int		m_nBands;
	eInterleave		m_eInterleave;
	int		m_nDataType;    
	unsigned char***	m_pppData;
};

