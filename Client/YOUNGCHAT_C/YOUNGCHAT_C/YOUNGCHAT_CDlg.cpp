
// YOUNGCHAT_CDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YOUNGCHAT_C.h"
#include "YOUNGCHAT_CDlg.h"
#include "afxdialogex.h"
#include "Socket_Client.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CYOUNGCHAT_CDlg 对话框



CYOUNGCHAT_CDlg::CYOUNGCHAT_CDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYOUNGCHAT_CDlg::IDD, pParent),m_Send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYOUNGCHAT_CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CONTENT, m_Send);
	DDX_Control(pDX, IDC_VS1, VS_1);
}

BEGIN_MESSAGE_MAP(CYOUNGCHAT_CDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CYOUNGCHAT_CDlg::OnClickedSend)
	ON_BN_CLICKED(IDCANCEL, &CYOUNGCHAT_CDlg::OnClickedCancel)
END_MESSAGE_MAP()


// CYOUNGCHAT_CDlg 消息处理程序

BOOL CYOUNGCHAT_CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//滚动条配置代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYOUNGCHAT_CDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CYOUNGCHAT_CDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CYOUNGCHAT_CDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CYOUNGCHAT_CDlg::UpdateInfo(CString Info)
{
	CString strTmp;
	CListBox* pBox = (CListBox*)GetDlgItem(IDC_ONLINE);
	pBox->ResetContent();
	while(!Info.IsEmpty())
	{
		int n = Info.Find('#');
		if(n==-1)
			break;
		strTmp = Info.Left(n);
		pBox->AddString(strTmp);
		Info = Info.Right(Info.GetLength()-n-1);
	}
}
void CYOUNGCHAT_CDlg::UpdateMSG(CString& MSG)
{
	((CEdit*)GetDlgItem(IDC_LOG))->ReplaceSel(MSG);
}

void CYOUNGCHAT_CDlg::OnClickedSend()
{
	UpdateData();
	if(m_Send.IsEmpty())
	{
		AfxMessageBox(_T("发送内容不能为空"));
		return;
	}
	CString tmp;
	CTime time = CTime::GetCurrentTime();
	tmp = time.Format("%H:%M:%S");
	m_Send = theApp.GetSocket()->m_user_name+_T("   ")+tmp+_T("\r\n")+m_Send+_T("\r\n");

	char* m_buff = new char[m_Send.GetLength()*2];
	memset(m_buff, 0, m_Send.GetLength()*2);
	Char2Byte(m_Send.GetBuffer(0), m_buff, m_Send.GetLength()*2);
	theApp.GetSocket()->SendMSG(m_buff, m_Send.GetLength()*2);

	delete m_buff;

	m_Send.Empty();
	UpdateData(0);
}
void CYOUNGCHAT_CDlg::OnClickedCancel()
{
	//退出
	CDialogEx::OnCancel();
}

BOOL CYOUNGCHAT_CDlg::Char2Byte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}