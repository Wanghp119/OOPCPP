// MyAppDoc.cpp : CMyAppDoc ���ʵ��
//

#include "stdafx.h"
#include "MyApp.h"

#include "MyAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyAppDoc

IMPLEMENT_DYNCREATE(CMyAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyAppDoc, CDocument)
END_MESSAGE_MAP()


// CMyAppDoc ����/����

CMyAppDoc::CMyAppDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMyAppDoc::~CMyAppDoc()
{
}

BOOL CMyAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMyAppDoc ���л�

void CMyAppDoc::Serialize(CArchive& ar)
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


// CMyAppDoc ���

#ifdef _DEBUG
void CMyAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyAppDoc ����
