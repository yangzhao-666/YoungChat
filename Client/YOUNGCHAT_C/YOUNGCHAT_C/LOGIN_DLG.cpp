// LOGIN_DLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YOUNGCHAT_C.h"
#include "LOGIN_DLG.h"
#include "afxdialogex.h"


// LOGIN_DLG �Ի���

IMPLEMENT_DYNAMIC(LOGIN_DLG, CDialogEx)

LOGIN_DLG::LOGIN_DLG(CWnd* pParent)
	: CDialogEx(LOGIN_DLG::IDD, pParent), m_User(_T(""))
{
	//��ʼ��IP
	m_IPadd = ntohl(inet_addr("127.0.0.1"));
}

LOGIN_DLG::~LOGIN_DLG()
{}

void LOGIN_DLG::DoDataExchange(CDataExchange* pDX)//�ñ����Ϳؼ�����һ��
{
	CDialogEx::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IPADDR, m_IPadd);
	DDX_Text(pDX, IDC_USER, m_User);
}


BEGIN_MESSAGE_MAP(LOGIN_DLG,CDialogEx)
	ON_BN_CLICKED(IDOK,&LOGIN_DLG::OnClickedLog)
	ON_BN_CLICKED(IDCANCEL,&LOGIN_DLG::OnClickedExit)
END_MESSAGE_MAP()

void LOGIN_DLG::OnClickedLog()
{
	UpdateData();
	if(m_User.IsEmpty())
	{
		AfxMessageBox(_T("�û�������Ϊ��"));
		return;
	}
	if(m_IPadd==0)
	{
		AfxMessageBox(_T("IP��ַ����Ϊ��"));
		return;
	}
	Socket_Client* Socket = theApp.GetSocket();//private�����޷�������Ҫ����public����
	IN_ADDR add;
	add.S_un.S_addr = htonl(m_IPadd);//wincosk.h�ж���ĺ꣬htonl��������ת�����޷��ų����ε������ֽ�˳��
	CString IP(inet_ntoa(add));//inet_ntoa��һ��ʮ���������ֽ���ת��Ϊ���ʮ����IP��ʽ���ַ���
	if(!Socket->Connect(IP.GetBuffer(0),8989))
	{
		AfxMessageBox(_T("���ӷ�����ʧ��"));
		return;
	}
	Socket->m_user_name = m_User;
	char* m_buff = new char[m_User.GetLength()+1];
	memset(m_buff,0,m_User.GetLength());
	if(WChar2MByte(m_User.GetBuffer(0), m_buff, m_User.GetLength()+1))
		Socket->OnLogIn(m_buff, m_User.GetLength()+1);
	delete m_buff;
	CDialogEx::OnOK();
}
void LOGIN_DLG::OnClickedExit()
{
	Socket_Client* m_Sock = theApp.GetSocket();
	m_Sock->Close();
	CDialogEx::OnCancel();
}

BOOL LOGIN_DLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(0);
	((CEdit*)GetDlgItem(IDC_PWD))->SetWindowTextW(_T("123123"));
	return TRUE; 
}

BOOL LOGIN_DLG::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(n<nlen)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}