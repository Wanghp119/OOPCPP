// MF2View.cpp : CMF2View ���ʵ��
//

#include "stdafx.h"
#include "MF2.h"

#include "MF2Doc.h"
#include "MF2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMF2View

IMPLEMENT_DYNCREATE(CMF2View, CView)

BEGIN_MESSAGE_MAP(CMF2View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMF2View ����/����

CMF2View::CMF2View()
{
	// TODO: �ڴ˴���ӹ������

}

CMF2View::~CMF2View()
{
}

BOOL CMF2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMF2View ����

void CMF2View::OnDraw(CDC* /*pDC*/)
{
	CMF2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMF2View ��ӡ

BOOL CMF2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMF2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMF2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMF2View ���

#ifdef _DEBUG
void CMF2View::AssertValid() const
{
	CView::AssertValid();
}

void CMF2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMF2Doc* CMF2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMF2Doc)));
	return (CMF2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMF2View ��Ϣ�������
