// DisplayRSImageView.cpp : CDisplayRSImageView ���ʵ��
//

#include "stdafx.h"
#include "DisplayRSImage.h"

#include "DisplayRSImageDoc.h"
#include "DisplayRSImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDisplayRSImageView
IMPLEMENT_DYNCREATE(CDisplayRSImageView, CScrollView)

BEGIN_MESSAGE_MAP(CDisplayRSImageView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_MESSAGE_VOID(WM_INITIALUPDATE, CDisplayRSImageView::OnInitialUpdate)
END_MESSAGE_MAP()

// CDisplayRSImageView ����/����

CDisplayRSImageView::CDisplayRSImageView()
{
	// TODO: �ڴ˴���ӹ������
	m_pbyRGB = NULL;
	m_pRBuff = NULL;
	m_pGBuff = NULL;
	m_pBBuff = NULL;
	m_nBuffWidth = NULL;
	m_nBuffHeight = NULL;
	m_nRGBWidth = 0;
	m_nRGBHeight = 0;
	m_dRatio = 1.0f;
	m_nRBandIdx = m_nGBandIdx = m_nBBandIdx = 0;
	m_hBitmap = NULL;
	memset(&m_bitmap, 0, sizeof(m_bitmap));
}

CDisplayRSImageView::~CDisplayRSImageView()
{
	if (m_pbyRGB) { delete m_pbyRGB; m_pbyRGB = NULL; }
	if (m_pRBuff) { CPLFree(m_pRBuff);m_pRBuff = NULL; }
	if (m_pGBuff) { CPLFree(m_pGBuff);	m_pGBuff = NULL; }
	if (m_pBBuff) { CPLFree(m_pGBuff);	m_pGBuff = NULL; }

	if (m_hBitmap) { DeleteObject(m_hBitmap); m_hBitmap = NULL; }
}

BOOL CDisplayRSImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CDisplayRSImageView ����

void CDisplayRSImageView::OnDraw(CDC* pDC)
{
	CDisplayRSImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// ��ʾͼ����Ϣ
	DrawImgInfo(pDC);

	// ����ͼ��
	DrawImage(pDC);
}


//----------------------------------------------------------//
// ��λͼ���Ƶ����ڣ�����ֻ�ǻ��ƶ��ѡ�						//
//----------------------------------------------------------//
void CDisplayRSImageView::DrawImage(CDC* pDC)
{
	if (m_pbyRGB == NULL)	return;

	//Preparing Bitmap Info
	BITMAPINFO bmInfo;
	memset(&bmInfo.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
	bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biWidth = m_bitmap.bmWidth;
	bmInfo.bmiHeader.biHeight = m_bitmap.bmHeight;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biBitCount = 24;

	// ��ͼ
	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, 0, 0, 0, m_bitmap.bmHeight, m_pbyRGB, &bmInfo, DIB_RGB_COLORS);
}

/************************************************************************/
/* Name: InitBuffer()                                                   */
/* Parameter: double dRatio - ��ʾ����									*/
/* return: bool - true/success, false/failed							*/
/* Description: ��ʼ����ʾ���棬�򻯳ɸ�����ʾ����������Ҫȡ�����ݷ�Χ, */
/*              ��ȡӰ�����ݣ�Ȼ�����Bitmap�ڴ档                      */
/************************************************************************/
bool CDisplayRSImageView::InitBuffer(double dRatio)
{
	// �ͷ����е��ڴ�
	if (m_pbyRGB) { delete m_pbyRGB; m_pbyRGB = NULL; }
	if (m_pRBuff) { CPLFree(m_pRBuff);m_pRBuff = NULL; }
	if (m_pGBuff) { CPLFree(m_pGBuff);	m_pGBuff = NULL; }
	if (m_pBBuff) { CPLFree(m_pGBuff);	m_pGBuff = NULL; }

	// ���ݼ�
	CDisplayRSImageDoc*	pDoc = GetDocument();
	if (pDoc == NULL)	return false;

	GDALDataset*	poDataset = pDoc->GetDataset();
	if (poDataset == NULL)	return false;

	// ���ݷ�Χ
	int		nRasterXSize = poDataset->GetRasterXSize();
	int		nRasterYSize = poDataset->GetRasterYSize();
	int		nBandCount = poDataset->GetRasterCount();
	RECT	rectView;

	// Ĭ�ϳ�ʼ��������
	if (m_nRBandIdx<1 || m_nGBandIdx<1 || m_nBBandIdx<1)
	{
		m_nRBandIdx = 1;
		m_nGBandIdx = nBandCount<3 ? 1 : 2;
		m_nBBandIdx = nBandCount<3 ? 1 : 3;
	}

	// ���ݿͻ�����С��������Buffer��Χ
	GetClientRect(&rectView);
	if (dRatio < 1e-6)
	{
		m_dRatio = min(1., (rectView.right - rectView.left) / (nRasterXSize * 1.));
		m_dRatio = min(m_dRatio, (rectView.bottom - rectView.top) / (nRasterYSize * 1.));
	}
	else
	{
		m_dRatio = dRatio;
	}

	m_nBuffWidth = (int)ceil(nRasterXSize * m_dRatio);
	m_nBuffHeight = (int)ceil(nRasterYSize * m_dRatio);

	// ���仺��
	m_pRBuff = CPLMalloc(GDALGetDataTypeSize(GDT_Float32)*m_nBuffHeight*m_nBuffWidth);
	m_pGBuff = CPLMalloc(GDALGetDataTypeSize(GDT_Float32)*m_nBuffHeight*m_nBuffWidth);
	m_pBBuff = CPLMalloc(GDALGetDataTypeSize(GDT_Float32)*m_nBuffHeight*m_nBuffWidth);

	// Bitmap�Ĵ�С
	m_nRGBWidth = (m_nBuffWidth * 24L + 31L) / 32L * 4;
	m_nRGBHeight = m_nBuffHeight;

	// ����Bitmap���ݴ洢��Ԫ
	m_pbyRGB = new BYTE[m_nRGBWidth*m_nRGBHeight];
	memset(m_pbyRGB, 0, m_nRGBWidth*m_nRGBHeight);

	if (!m_pRBuff || !m_pGBuff || !m_pBBuff || !m_pbyRGB)
		return false;

	// ���Bitmap
	m_bitmap.bmBits = (LPVOID)m_pbyRGB;
	m_bitmap.bmBitsPixel = 24;
	m_bitmap.bmHeight = m_nBuffHeight;
	m_bitmap.bmPlanes = 0;
	m_bitmap.bmType = 0;
	m_bitmap.bmWidth = m_nBuffWidth;
	m_bitmap.bmWidthBytes = m_nRGBWidth;

	return true;
}

/************************************************************************/
/* Name: ReadRaster                                                     */
/* Description: ��ȡ���ݣ�������Bitmapλͼ��Ϊ������׼����				*/
/************************************************************************/
void CDisplayRSImageView::ReadRaster()
{
	CDisplayRSImageDoc*	pDoc = GetDocument();
	if (pDoc == NULL)	return;

	GDALDataset*	poDataset = pDoc->GetDataset();
	if (poDataset == NULL)	return;

	int		nRasterXSize = poDataset->GetRasterXSize();
	int		nRasterYSize = poDataset->GetRasterYSize();
	int		nBandCount = poDataset->GetRasterCount();
	GDALRasterBand*	poBand = NULL;

	// Raster IO R,G,B
	poBand = poDataset->GetRasterBand(m_nRBandIdx);
	poBand->RasterIO(GF_Read, 0, 0, nRasterXSize, nRasterYSize, m_pRBuff, m_nBuffWidth, m_nBuffHeight, GDT_Float32, 0, 0);

	// Raster IO
	if (m_nGBandIdx == m_nRBandIdx)
		memcpy(m_pGBuff, m_pRBuff, m_nBuffHeight*m_nBuffWidth*GDALGetDataTypeSize(GDT_Float32));
	else
	{
		poBand = poDataset->GetRasterBand(m_nGBandIdx);
		poBand->RasterIO(GF_Read, 0, 0, nRasterXSize, nRasterYSize, m_pGBuff, m_nBuffWidth, m_nBuffHeight, GDT_Float32, 0, 0);
	}

	// Raster IO
	if (m_nBBandIdx == m_nRBandIdx)
		memcpy(m_pBBuff, m_pRBuff, m_nBuffHeight*m_nBuffWidth*GDALGetDataTypeSize(GDT_Float32));
	else
	{
		poBand = poDataset->GetRasterBand(m_nBBandIdx);
		poBand->RasterIO(GF_Read, 0, 0, nRasterXSize, nRasterYSize, m_pBBuff, m_nBuffWidth, m_nBuffHeight, GDT_Float32, 0, 0);
	}

	// Buffer
	float*	ptrR = (float*)m_pRBuff;
	float*	ptrB = (float*)m_pBBuff;
	float*	ptrG = (float*)m_pGBuff;
	BYTE*	ptrbyRGB = NULL;

	// ���Bitmap
	for (int i = 0; i<m_nBuffHeight; ++i)
	{
		ptrbyRGB = m_pbyRGB + i*m_nRGBWidth;
		for (int j = 0; j<m_nBuffWidth; ++j)
		{
			*ptrbyRGB++ = ptrB[(m_nBuffHeight - i - 1)*m_nBuffWidth + j];
			*ptrbyRGB++ = ptrG[(m_nBuffHeight - i - 1)*m_nBuffWidth + j];
			*ptrbyRGB++ = ptrR[(m_nBuffHeight - i - 1)*m_nBuffWidth + j];
		}
	}

	if (m_hBitmap) { DeleteObject(m_hBitmap); m_hBitmap = NULL; }
	m_hBitmap = CreateBitmapIndirect(&m_bitmap);
}

/************************************************************************/
/* ����ͼ�����Ϣ��For Test                                             */
/************************************************************************/
void CDisplayRSImageView::DrawImgInfo(CDC* pDC)
{
	USES_CONVERSION;

	CDisplayRSImageDoc*	pDoc = GetDocument();
	GDALDataset* poDataset = pDoc->GetDataset();
	if (poDataset == NULL)
		return;

	pDC->TextOut(10, 10, poDataset->GetDescription());
}

// CDisplayRSImageView ��ӡ

BOOL CDisplayRSImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDisplayRSImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDisplayRSImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CDisplayRSImageView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CDisplayRSImageView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CDisplayRSImageView ��Ϣ�������
void CDisplayRSImageView::OnInitialUpdate()
{
	if (InitBuffer())
		ReadRaster();

	CScrollView::OnInitialUpdate();
}

// CDisplayRSImageView ���
#ifdef _DEBUG
void CDisplayRSImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDisplayRSImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDisplayRSImageDoc* CDisplayRSImageView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDisplayRSImageDoc)));
	return (CDisplayRSImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CDisplayRSImageView ��Ϣ�������
