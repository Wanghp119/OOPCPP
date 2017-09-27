// RSImageView.cpp : CRSImageView ���ʵ��
//

#include "stdafx.h"
#include "RSImage.h"

#include "RSImageDoc.h"
#include "RSImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRSImageView

IMPLEMENT_DYNCREATE(CRSImageView, CView)

BEGIN_MESSAGE_MAP(CRSImageView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CRSImageView ����/����

CRSImageView::CRSImageView()
{
	// TODO: �ڴ˴���ӹ������
	m_dDispRate = 1.;	//��ʾ����
	m_iX0 = m_iY0 = 0;	//ͼ��ƫ�Ƶ�λ��

	// ��ʼ����ʾ����
	m_ptrRedBuff = NULL;
	m_ptrGrnBuff = NULL;
	m_ptrBluBuff = NULL;
	m_nXBuffSize = 0;
	m_nYBuffSize = 0;
	memset(m_nRgbList, 0, sizeof(int)*3);

	memset(&m_oBitmap, 0, sizeof(BITMAP));
	m_ptRGBBitmap = NULL;
	m_nBitmapWidth = 0;
	m_nBitmapHeight = 0;
}

CRSImageView::~CRSImageView()
{
	ReleaseBuff();
}

BOOL CRSImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

void CRSImageView::OnInitialUpdate()
{
	//1. ��ʼ����ʾ����
	InitDispPara();

	//2. ��ʼ����ʾ����
	InitDispBuffer();

	//3. ������ʾλͼ
	GenDispBitmap();

	OnUpdate(NULL, 0, NULL);
}

//��ʼ����ʾ����
bool CRSImageView::InitDispPara()
{
	CRSImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc == NULL)
		return false;

	GDALDataset*	ptrDS = pDoc->GetDS();
	if (ptrDS == NULL)
		return false;

	CRect	rectWnd;
	GetClientRect(&rectWnd);

	m_iRasXSize = ptrDS->GetRasterXSize();
	m_iRasYSize = ptrDS->GetRasterYSize();

	m_dDispRate = min((1.*rectWnd.Width())/m_iRasXSize, (1.*rectWnd.Height())/m_iRasYSize);
	m_iX0 = m_iY0 = 0;

	// ��ʼ��RGB���
	if (ptrDS->GetRasterCount() >= 3)
	{
		m_nRgbList[0] = 1;
		m_nRgbList[1] = 2;
		m_nRgbList[2] = 3;
		m_eDispType = DT_Color;			//��ʾ����
		m_eEnhanceStyle = ES_Normal;	//��ǿ��ʽ

	}
	else
	{
		m_nRgbList[0] = m_nRgbList[1] = m_nRgbList[2] = 1;
		m_eDispType = DT_Gray;			//��ʾ����
		m_eEnhanceStyle = ES_Normal;	//��ǿ��ʽ
	}

	return true;
}

bool CRSImageView::InitDispBuffer()
{
	CRSImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc == NULL)	return false;

	GDALDataset*	ptrDS = pDoc->GetDS();
	if (ptrDS == NULL)	return false;

	m_nXBuffSize = int(m_iRasXSize * m_dDispRate + 0.5);
	m_nYBuffSize = int(m_iRasYSize * m_dDispRate + 0.5);

	m_ptrRedBuff = CPLMalloc(GDALGetDataTypeSize(GDT_Float32) * m_nXBuffSize * m_nYBuffSize);
	m_ptrGrnBuff = CPLMalloc(GDALGetDataTypeSize(GDT_Float32) * m_nXBuffSize * m_nYBuffSize);
	m_ptrBluBuff = CPLMalloc(GDALGetDataTypeSize(GDT_Float32) * m_nXBuffSize * m_nYBuffSize);
	
	GDALRasterBand*	pBand = ptrDS->GetRasterBand(m_nRgbList[0]);
	if (pBand != NULL)
		pBand->RasterIO(GF_Read, 0, 0, m_iRasXSize, m_iRasYSize, m_ptrRedBuff, m_nXBuffSize, m_nYBuffSize, GDT_Float32, 0, 0);

	pBand = ptrDS->GetRasterBand(m_nRgbList[1]);
	if (pBand != NULL)
		pBand->RasterIO(GF_Read, 0, 0, m_iRasXSize, m_iRasYSize, m_ptrGrnBuff, m_nXBuffSize, m_nYBuffSize, GDT_Float32, 0, 0);

	pBand = ptrDS->GetRasterBand(m_nRgbList[2]);
	if (pBand != NULL)
		pBand->RasterIO(GF_Read, 0, 0, m_iRasXSize, m_iRasYSize, m_ptrBluBuff, m_nXBuffSize, m_nYBuffSize, GDT_Float32, 0, 0);	
	
	return true;
}

//3. ������ʾλͼ
bool CRSImageView::GenDispBitmap()
{
	if (m_nBitmapHeight < m_nYBuffSize || m_nBitmapWidth < m_nXBuffSize)
	{
		if (m_ptRGBBitmap)	delete[] m_ptRGBBitmap;
		m_ptRGBBitmap = NULL;
		m_nBitmapWidth = m_nBitmapHeight = 0;
	}

	if (m_ptRGBBitmap == NULL)
	{
		m_nBitmapWidth = m_nXBuffSize; 
		m_nBitmapHeight = m_nYBuffSize;

		m_ptRGBBitmap = new BYTE[4*m_nBitmapWidth * m_nBitmapHeight];
		memset(m_ptRGBBitmap, 0, sizeof(BYTE)*4*m_nBitmapWidth*m_nBitmapHeight);
	}

	if (m_ptRGBBitmap == NULL)
		return false;

	m_oBitmap.bmBits = (LPVOID)m_ptRGBBitmap;
	m_oBitmap.bmBitsPixel = 24;
	m_oBitmap.bmHeight = m_nBitmapHeight;
	m_oBitmap.bmWidth = m_nBitmapWidth;
	m_oBitmap.bmWidthBytes = ((((24 * m_nBitmapWidth) + 31) / 32) * 4);

	for (int i=0; i<m_nXBuffSize; i++)
	{
		for (int j=0; j<m_nYBuffSize; j++)
		{
			m_ptRGBBitmap[i*3*m_nBitmapWidth+j+0] = (unsigned char)((float*)m_ptrRedBuff)[i*m_nXBuffSize+j];
			m_ptRGBBitmap[i*3*m_nBitmapWidth+j+1] = (unsigned char)((float*)m_ptrGrnBuff)[i*m_nXBuffSize+j];
			m_ptRGBBitmap[i*3*m_nBitmapWidth+j+2] = (unsigned char)((float*)m_ptrBluBuff)[i*m_nXBuffSize+j];
		}
	}

	return true;
}


void CRSImageView::ReleaseBuff()
{
	if (m_ptrRedBuff)
	{
		CPLFree(m_ptrRedBuff);
		m_ptrRedBuff = NULL;
	}

	if (m_ptrGrnBuff)
	{
		CPLFree(m_ptrGrnBuff);
		m_ptrGrnBuff = NULL;
	}

	if (m_ptrBluBuff)
	{
		CPLFree(m_ptrBluBuff);
		m_ptrBluBuff = NULL;
	}

	m_nXBuffSize = 0;
	m_nYBuffSize = 0;

	// 
	if (m_ptRGBBitmap)
	{
		delete m_ptRGBBitmap;
		m_ptRGBBitmap = NULL;
	}
	m_nBitmapWidth = 0;
	m_nBitmapHeight = 0;
}

// CRSImageView ����
void CRSImageView::OnDraw(CDC* pDC)
{
	CRSImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	DrawRaster(pDC);
}


void CRSImageView::DrawRaster(CDC* pDC)
{
	if (m_oBitmap.bmBits == NULL)
		return;

	HBITMAP hOldBmp;
	CDC		memdc;

	memdc.CreateCompatibleDC(pDC);

	hOldBmp = (HBITMAP)memdc.SelectObject(&m_oBitmap);

	//��ʾͼƬ
	pDC->BitBlt(0, 0, m_nBitmapWidth, m_nBitmapHeight, &memdc, 0, 0, SRCCOPY);

	memdc.SelectObject(hOldBmp);
}

// CRSImageView ��ӡ

BOOL CRSImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CRSImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CRSImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CRSImageView ���

#ifdef _DEBUG
void CRSImageView::AssertValid() const
{
	CView::AssertValid();
}

void CRSImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRSImageDoc* CRSImageView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRSImageDoc)));
	return (CRSImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CRSImageView ��Ϣ�������
