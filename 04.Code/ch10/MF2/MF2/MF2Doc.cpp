// MF2Doc.cpp : CMF2Doc ���ʵ��
//

#include "stdafx.h"
#include "MF2.h"

#include "MF2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMF2Doc

IMPLEMENT_DYNCREATE(CMF2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMF2Doc, CDocument)
END_MESSAGE_MAP()


// CMF2Doc ����/����

CMF2Doc::CMF2Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CMF2Doc::~CMF2Doc()
{
}

BOOL CMF2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMF2Doc ���л�

void CMF2Doc::Serialize(CArchive& ar)
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


// CMF2Doc ���

#ifdef _DEBUG
void CMF2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMF2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMF2Doc ����
