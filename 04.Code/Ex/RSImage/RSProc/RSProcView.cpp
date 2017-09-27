// RSProcView.cpp : CRSProcView ���ʵ��
//

#include "stdafx.h"
#include "RSProc.h"

#include "RSProcDoc.h"
#include "RSProcView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRSProcView

IMPLEMENT_DYNCREATE(CRSProcView, CView)

BEGIN_MESSAGE_MAP(CRSProcView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CRSProcView ����/����

CRSProcView::CRSProcView()
{
	// TODO: �ڴ˴���ӹ������

}

CRSProcView::~CRSProcView()
{
}

BOOL CRSProcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CRSProcView ����

void CRSProcView::DrawImage(CDC* pDC, CRSImage* pImage)
{
	if (pImage == NULL)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRSImage::DataType***	pppData = pImage->GetDataBuffer();
	if (pppData != NULL)
	{
		int	nLines = pImage->GetLines();
		int nSamples = pImage->GetSamples();
		int	nBands = pImage->GetBands();

		int	x, y;
		int	iRed, iGreen, iBlue;
		iRed = min(nBands-1,0);
		iGreen = min(nBands-1,1);
		iBlue = min(nBands-1, 2);
		for (x=0; x<nLines; ++x)
		{
			for (y=0; y<nSamples; ++y)
			{
				pDC->SetPixel(y, x, RGB(pppData[iRed][x][y], pppData[iGreen][x][y], pppData[iBlue][x][y]));
			}
		}
	}
}

void CRSProcView::OnDraw(CDC* pDC)
{
	CRSProcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (m_pDispImage != NULL)
		DrawImage(pDC, m_pDispImage);
}


// CRSProcView ��ӡ

BOOL CRSProcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CRSProcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CRSProcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CRSProcView ���

#ifdef _DEBUG
void CRSProcView::AssertValid() const
{
	CView::AssertValid();
}

void CRSProcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRSProcDoc* CRSProcView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRSProcDoc)));
	return (CRSProcDoc*)m_pDocument;
}
#endif //_DEBUG


// CRSProcView ��Ϣ�������
void CRSProcView::OnMouseMove(UINT nFlags, CPoint point)
{
	CRSProcDoc* pDoc = GetDocument();
	if (!pDoc)	return;

	if (!pDoc->GetImage().IsOpen())
		return;

	CMainFrame*	pFrm = (CMainFrame*)AfxGetMainWnd();
	if (pFrm != NULL)
	{
		CString	strTxt;
		strTxt.Format("x:%d,y:%d", point.x, point.y);
		pFrm->SetPaneText(ID_INDICATOR_COORD, strTxt);
	}
}