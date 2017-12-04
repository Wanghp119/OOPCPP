// RSProcView.cpp : CRSProcView ���ʵ��
//

#include "stdafx.h"
#include "RSProc.h"

#include "RSProcDoc.h"
#include "RSProcView.h"

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

void CRSProcView::OnDraw(CDC* pDC)
{
	CRSProcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRSImage::DataType***	pppData = pDoc->GetImage().GetDataBuffer();
	if (pppData != NULL)
	{
		int	nLines = pDoc->GetImage().GetLines();
		int nSamples = pDoc->GetImage().GetSamples();
		int	nBands = pDoc->GetImage().GetBands();

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
