// RSProcDoc.h : CRSProcDoc ��Ľӿ�
//


#pragma once

#include "RSImage.h"

class CRSProcDoc : public CDocument
{
protected: // �������л�����
	CRSProcDoc();
	DECLARE_DYNCREATE(CRSProcDoc)

// ����
public:

// ����
public:
	const CRSImage&	GetImage() const { return m_oImage;}

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();

// ʵ��
public:
	virtual ~CRSProcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRSImage	m_oImage;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


