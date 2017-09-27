// DisplayRSImage.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "DisplayRSImage.h"
#include "MainFrm.h"

#include "DisplayRSImageDoc.h"
#include "DisplayRSImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDisplayRSImageApp

BEGIN_MESSAGE_MAP(CDisplayRSImageApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CDisplayRSImageApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CDisplayRSImageApp::OnFileOpen)	//ӳ��򿪲˵�����Ϣ������
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CDisplayRSImageApp ����

CDisplayRSImageApp::CDisplayRSImageApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDisplayRSImageApp ����

CDisplayRSImageApp theApp;


// CDisplayRSImageApp ��ʼ��

BOOL CDisplayRSImageApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDisplayRSImageDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CDisplayRSImageView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// GDAL ʹ�õ�����
	GDALAllRegister();

	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
	return TRUE;
}

//-----------------------------------------------//
// ���ļ�����Ϣ������
//-----------------------------------------------//
void CDisplayRSImageApp::OnFileOpen()
{
	/*	�������
	->1. CWinApp::OnFileOpen(); 
	ENSURE(m_pDocManager != NULL);
	m_pDocManager->OnFileOpen();

	->2.CDocManager::OnFileOpen();
	[���ļ��Ի���]
	// prompt the user (with all document templates)
	CString newName;
	if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
		return; // open cancelled
	
	[����OpenDocumentFile]
	AfxGetApp()->OpenDocumentFile(newName);
	// if returns NULL, the user has already been alerted
	*/

	//-------------------------------------------------------------//
	// ��д���ļ��Ի���
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL, 0);

	dlgFile.m_ofn.lpstrFilter = "Ӱ���ļ�(*.tif;*.img;*.pix;*.jpg;*.bmp;*.png)\0*.tif;*.img;*.pix;*.jpg;*.bmp;*.png\0�����ļ�(*.*)\0*.*\0";
	dlgFile.m_ofn.lpstrTitle = _T("��ң��Ӱ���ļ�...");

	if (dlgFile.DoModal() == IDOK)
	{
		OpenDocumentFile(dlgFile.GetPathName());	// ���ĵ�
	}

//	CWinApp::OnFileOpen();
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CDisplayRSImageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CDisplayRSImageApp ��Ϣ�������

