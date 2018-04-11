// 7-5View.cpp : CMy75View ���ʵ��
//

#include "stdafx.h"
#include "7-5.h"

#include "7-5Doc.h"
#include "7-5View.h"

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy75View

IMPLEMENT_DYNCREATE(CMy75View, CView)

BEGIN_MESSAGE_MAP(CMy75View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SHAPE_DISPLAY, &CMy75View::OnShapeDisplay)
	ON_COMMAND(ID_SHAPE_TEST, &CMy75View::OnShapeTest)
//	ON_COMMAND(WM_INITIALUPDATE, &CMy75View::OnInitUpdate)
END_MESSAGE_MAP()

// CMy75View ����/����

CMy75View::CMy75View()
{
	// TODO: �ڴ˴���ӹ������
}

CMy75View::~CMy75View()
{	
}

void CMy75View::OnInitUpdate()
{
	CView::OnInitialUpdate();
}

BOOL CMy75View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy75View ����

void CMy75View::OnDraw(CDC* pDC)
{
	pDC->TextOut(10, 10, "Shape Demo.");

	CMy75Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	list<CShape*>::iterator	iter;
	for (iter = pDoc->m_lstShape.begin(); iter!=pDoc->m_lstShape.end(); ++iter)
	{
		(*iter)->Draw(pDC);
	}
}

// CMy75View ��ӡ

BOOL CMy75View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy75View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy75View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy75View ���

#ifdef _DEBUG
void CMy75View::AssertValid() const
{
	CView::AssertValid();
}

void CMy75View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy75Doc* CMy75View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy75Doc)));
	return (CMy75Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy75View ��Ϣ�������

void CMy75View::OnShapeDisplay()
{
	CMy75Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
	pDoc->m_lstShape.push_back(new CCircle(10, 100, 100));
	pDoc->m_lstShape.push_back(new CCircle(50, 200, 200));
	pDoc->m_lstShape.push_back(new CRectangle(500,300, 600, 400));
	pDoc->m_lstShape.push_back(new CRectangle(30, 20, 100,50));

	Invalidate();
}

void CMy75View::OnShapeTest()
{
	// TODO: �ڴ���������������
	AfxMessageBox("Hello World!");
}
