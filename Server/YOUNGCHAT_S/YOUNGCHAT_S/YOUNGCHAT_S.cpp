
// YOUNGCHAT_S.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "YOUNGCHAT_S.h"
#include "YOUNGCHAT_SDlg.h"
#include "Afxsock.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYOUNGCHAT_SApp

BEGIN_MESSAGE_MAP(CYOUNGCHAT_SApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CYOUNGCHAT_SApp ����

CYOUNGCHAT_SApp::CYOUNGCHAT_SApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CYOUNGCHAT_SApp ����

CYOUNGCHAT_SApp theApp;


// CYOUNGCHAT_SApp ��ʼ��

BOOL CYOUNGCHAT_SApp::InitInstance()
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

	//��socket����г�ʼ��
	if(!AfxSocketInit())
	{
		AfxMessageBox(_T("Socket ���ʼ��ʧ��"));
		return false;
	}

	//����������socket����
	m_iSocket = new CServerSocket();
	if(!m_iSocket)
	{
		AfxMessageBox(_T("Server socket ��ʼ��ʧ��"));
		return false;
	}

	//�����׽���
	if(!m_iSocket->Create(8989))
	{
		AfxMessageBox(_T("Server socket ����ʧ��"));
		return false;
		m_iSocket->Close();
		return false;
	}

	//����
	if(!m_iSocket->Listen())
	{
		AfxMessageBox(_T("Server socket����ʧ��"));
		return false;
		m_iSocket->Close();
		return false;
	}
	CWinApp::InitInstance();


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

	CYOUNGCHAT_SDlg dlg;
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

int CYOUNGCHAT_SApp::ExitInstance()
{
	if(m_iSocket)
	{
		delete m_iSocket;
		m_iSocket = NULL;
	}
	return CWinApp::ExitInstance();
}
CServerSocket* CYOUNGCHAT_SApp::GetServerSocket() const
{
	ASSERT(m_iSocket);
	return m_iSocket;
}
