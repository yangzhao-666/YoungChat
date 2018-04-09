
// YOUNGCHAT_S.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "ServerSocket.h"

// CYOUNGCHAT_SApp:
// 有关此类的实现，请参阅 YOUNGCHAT_S.cpp
//

class CYOUNGCHAT_SApp : public CWinApp
{
public:
	CYOUNGCHAT_SApp();

// 重写
public:
	CServerSocket *GetServerSocket() const;
	CServerSocket *m_iSocket;
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();//退出时清理
// 实现

	DECLARE_MESSAGE_MAP()
};

extern CYOUNGCHAT_SApp theApp;