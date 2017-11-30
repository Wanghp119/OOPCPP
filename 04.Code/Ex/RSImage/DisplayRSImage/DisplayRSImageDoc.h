// DisplayRSImageDoc.h : CDisplayRSImageDoc ��Ľӿ�
//


#pragma once


class CDisplayRSImageDoc : public CDocument
{
protected: // �������л�����
	CDisplayRSImageDoc();
	DECLARE_DYNCREATE(CDisplayRSImageDoc)

// ����
public:
	GDALDataset*	GetDataset() { return m_poDataset; }	//����դ�����ݶ���

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CDisplayRSImageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GDALDataset*	m_poDataset;	//դ�����ݾ��

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};