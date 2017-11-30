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
	ON_COMMAND(ID_SHAPE_TEST, &CMy75View::OnShapeTest)
	ON_COMMAND(ID_C_C1, &CMy75View::OnCC1)
END_MESSAGE_MAP()

// CMy75View ����/����

CMy75View::CMy75View()
{
	// TODO: �ڴ˴���ӹ������
}

CMy75View::~CMy75View()
{

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
	CMy75Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (pDoc->m_ptShapeAry != NULL)
	{
		for (int i=0; i<pDoc->m_nShapeCount; i++)
		{
			if (pDoc->m_ptShapeAry[i])
			{
				pDoc->m_ptShapeAry[i]->Draw(pDC);

				pDoc->m_ptShapeAry[i]->DrawInfo(pDC);
			}
		}
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


void CMy75View::OnShapeTest()
{
	// TODO: �ڴ���������������
	AfxMessageBox("Hello World!");
}

void CMy75View::OnCC1()
{
	// TODO: �ڴ���������������
	AfxMessageBox("C++");
}
