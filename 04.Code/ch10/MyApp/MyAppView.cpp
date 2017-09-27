// MyAppView.cpp : CMyAppView ���ʵ��
//

#include "stdafx.h"
#include "MyApp.h"

#include "MyAppDoc.h"
#include "MyAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyAppView

IMPLEMENT_DYNCREATE(CMyAppView, CView)

BEGIN_MESSAGE_MAP(CMyAppView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMyAppView ����/����

CMyAppView::CMyAppView()
{
	// TODO: �ڴ˴���ӹ������

}

CMyAppView::~CMyAppView()
{
}

BOOL CMyAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyAppView ����

void CMyAppView::OnDraw(CDC* /*pDC*/)
{
	CMyAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMyAppView ��ӡ

BOOL CMyAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMyAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMyAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMyAppView ���

#ifdef _DEBUG
void CMyAppView::AssertValid() const
{
	CView::AssertValid();
}

void CMyAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyAppDoc* CMyAppView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyAppDoc)));
	return (CMyAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyAppView ��Ϣ�������
