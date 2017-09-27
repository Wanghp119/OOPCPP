// RSImageDoc.cpp : CRSImageDoc ���ʵ��
//

#include "stdafx.h"
#include "RSImage.h"

#include "RSImageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRSImageDoc

IMPLEMENT_DYNCREATE(CRSImageDoc, CDocument)

BEGIN_MESSAGE_MAP(CRSImageDoc, CDocument)
END_MESSAGE_MAP()


// CRSImageDoc ����/����

CRSImageDoc::CRSImageDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_ptrDS = NULL;
}

CRSImageDoc::~CRSImageDoc()
{
}

BOOL CRSImageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

// Override Open Document for Raster
BOOL CRSImageDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	DeleteContents();
	SetModifiedFlag();  // dirty during de-serialize

	// ��ͼ��
	m_ptrDS = (GDALDataset*)GDALOpen(lpszPathName, GA_ReadOnly);
	if (m_ptrDS == NULL)	return FALSE;
	
	SetModifiedFlag(FALSE);     // start off with unmodified

	return TRUE;
}


// CRSImageDoc ���л�

void CRSImageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

// ���أ��ر�ͼ��
void CRSImageDoc::DeleteContents()
{
	if (m_ptrDS)
	{
		GDALClose(m_ptrDS);
		m_ptrDS = NULL;
	}

	CDocument::DeleteContents();
}

// CRSImageDoc ���

#ifdef _DEBUG
void CRSImageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRSImageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRSImageDoc ����
