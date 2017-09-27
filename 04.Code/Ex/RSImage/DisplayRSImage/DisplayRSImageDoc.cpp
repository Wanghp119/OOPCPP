// DisplayRSImageDoc.cpp : CDisplayRSImageDoc ���ʵ��
//

#include "stdafx.h"
#include "DisplayRSImage.h"

#include "DisplayRSImageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDisplayRSImageDoc

IMPLEMENT_DYNCREATE(CDisplayRSImageDoc, CDocument)

BEGIN_MESSAGE_MAP(CDisplayRSImageDoc, CDocument)
END_MESSAGE_MAP()


// CDisplayRSImageDoc ����/����

CDisplayRSImageDoc::CDisplayRSImageDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_poDataset = NULL;
}

CDisplayRSImageDoc::~CDisplayRSImageDoc()
{
}

BOOL CDisplayRSImageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

//===================================================//
// ����DeleteContents()�����������Դ
//===================================================//
void CDisplayRSImageDoc::DeleteContents()
{
	// ���û���ӿ�
	CDocument::DeleteContents();

	// �ر����ݼ�
	if (m_poDataset)
	{
		delete m_poDataset;
		m_poDataset = NULL;
	}
}

//==========================================================//
// ����OnOpenDocument�ӿڣ����ڴ����ݼ�					//
//==========================================================//
BOOL CDisplayRSImageDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// ���û��ຯ��
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// �����ݼ�
	USES_CONVERSION;	//֧��unicode
	m_poDataset = (GDALDataset*)GDALOpen(lpszPathName, GA_ReadOnly);
	if (m_poDataset == NULL)
	{
		AfxMessageBox(_T("Open Image File Failed!!"));

		return FALSE;
	}

	//----------------- ͼ������ô��ʾ���� ? ----------------------//
	// MFC ��һ���׻��ƣ���֪ͨ��ͼ�����ƣ���Ҫ���ľ�������ͼ��OnDraw()
	// �ӿ�����д��Ӧ�Ļ���ͼ����뼴�ɡ�
	//=============================================================//

	return TRUE;
}


// CDisplayRSImageDoc ���л�

void CDisplayRSImageDoc::Serialize(CArchive& ar)
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


// CDisplayRSImageDoc ���

#ifdef _DEBUG
void CDisplayRSImageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDisplayRSImageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDisplayRSImageDoc ����
