
// YOUNGCHAT_CDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YOUNGCHAT_C.h"
#include "YOUNGCHAT_CDlg.h"
#include "afxdialogex.h"
#include "Socket_Client.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CYOUNGCHAT_CDlg �Ի���



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


// CYOUNGCHAT_CDlg ��Ϣ�������

BOOL CYOUNGCHAT_CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���������ô���


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYOUNGCHAT_CDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		AfxMessageBox(_T("�������ݲ���Ϊ��"));
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
	//�˳�
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