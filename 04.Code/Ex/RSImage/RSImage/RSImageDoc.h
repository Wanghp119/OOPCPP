// RSImageDoc.h : CRSImageDoc ��Ľӿ�
//


#pragma once


class CRSImageDoc : public CDocument
{
protected: // �������л�����
	CRSImageDoc();
	DECLARE_DYNCREATE(CRSImageDoc)

// ����
public:
	GDALDataset* GetDS() {return m_ptrDS;}
	GDALDataset*	GetDataset() { return m_poDataset; }

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);

	virtual void DeleteContents();

// ʵ��
public:
	virtual ~CRSImageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GDALDataset*	m_ptrDS;
	GDALDataset*	m_poDataset;	//Dataset

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


