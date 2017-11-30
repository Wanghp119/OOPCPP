// RSProcDoc.cpp : CRSProcDoc ���ʵ��
//

#include "stdafx.h"
#include "RSProc.h"

#include "RSProcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRSProcDoc

IMPLEMENT_DYNCREATE(CRSProcDoc, CDocument)

BEGIN_MESSAGE_MAP(CRSProcDoc, CDocument)
END_MESSAGE_MAP()


// CRSProcDoc ����/����

CRSProcDoc::CRSProcDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CRSProcDoc::~CRSProcDoc()
{
}

BOOL CRSProcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}


BOOL CRSProcDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
//	return CDocument::OnOpenDocument(lpszPathName);

	DeleteContents();
	SetModifiedFlag();  // dirty during de-serialize

	if (!m_oImage.Open(lpszPathName))
		return FALSE;

	SetModifiedFlag(FALSE);     // start off with unmodified

	return TRUE;
}

void CRSProcDoc::DeleteContents()
{
	m_oImage.Close();

	CDocument::DeleteContents();
}

// CRSProcDoc ���л�

void CRSProcDoc::Serialize(CArchive& ar)
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


// CRSProcDoc ���

#ifdef _DEBUG
void CRSProcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRSProcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRSProcDoc ����
