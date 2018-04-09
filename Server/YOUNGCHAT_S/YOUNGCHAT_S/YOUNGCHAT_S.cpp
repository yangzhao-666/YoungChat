
// YOUNGCHAT_S.cpp : 定义应用程序的类行为。
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


// CYOUNGCHAT_SApp 构造

CYOUNGCHAT_SApp::CYOUNGCHAT_SApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CYOUNGCHAT_SApp 对象

CYOUNGCHAT_SApp theApp;


// CYOUNGCHAT_SApp 初始化

BOOL CYOUNGCHAT_SApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//对socket库进行初始化
	if(!AfxSocketInit())
	{
		AfxMessageBox(_T("Socket 库初始化失败"));
		return false;
	}

	//创建服务器socket对象
	m_iSocket = new CServerSocket();
	if(!m_iSocket)
	{
		AfxMessageBox(_T("Server socket 初始化失败"));
		return false;
	}

	//创建套接字
	if(!m_iSocket->Create(8989))
	{
		AfxMessageBox(_T("Server socket 创建失败"));
		return false;
		m_iSocket->Close();
		return false;
	}

	//监听
	if(!m_iSocket->Listen())
	{
		AfxMessageBox(_T("Server socket监听失败"));
		return false;
		m_iSocket->Close();
		return false;
	}
	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CYOUNGCHAT_SDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
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
