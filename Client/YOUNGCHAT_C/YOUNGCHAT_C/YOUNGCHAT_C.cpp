
// YOUNGCHAT_C.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "YOUNGCHAT_C.h"
#include "YOUNGCHAT_CDlg.h"
#include "Socket_Client.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYOUNGCHAT_CApp

BEGIN_MESSAGE_MAP(CYOUNGCHAT_CApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CYOUNGCHAT_CApp ����

CYOUNGCHAT_CApp::CYOUNGCHAT_CApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CYOUNGCHAT_CApp ����

CYOUNGCHAT_CApp theApp;


// CYOUNGCHAT_CApp ��ʼ��

BOOL CYOUNGCHAT_CApp::InitInstance()
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
	if(!AfxSocketInit())
	{
		AfxMessageBox(_T("Socket���ʼ��ʧ��"));
		return false;
	}
	m_Socket = new Socket_Client();
	if(!m_Socket)
	{
		AfxMessageBox(_T("socketδ���䵽�ڴ浼��ʧ��"));
		return false;
	}
	if(!m_Socket->Create())
	{
		AfxMessageBox(_T("�����׽���ʧ��"));
		return false;
	}

	
	LOGIN_DLG* pLogoinDlg;
	pLogoinDlg = new LOGIN_DLG();
	
	if(pLogoinDlg->DoModal()==IDCANCEL)
	{
		//����¼
		delete pLogoinDlg;
		m_Socket->Close();
		return false;
	}
	else
	{
		delete pLogoinDlg;
	}

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CYOUNGCHAT_CDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CYOUNGCHAT_CApp::ExitInstance()
{
	if(m_Socket)//����Կ���ҵ����䣬����ը�ˣ�Ȼ��Կ������
	{
		delete m_Socket;//ը����
		m_Socket = NULL;//��Կ��
	}
	return CWinApp::ExitInstance();
}

Socket_Client* CYOUNGCHAT_CApp::GetSocket()
{
	return m_Socket;
}