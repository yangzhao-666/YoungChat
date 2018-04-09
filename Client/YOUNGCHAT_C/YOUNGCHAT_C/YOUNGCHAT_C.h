
// YOUNGCHAT_C.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "Socket_Client.h"
#include "LOGIN_DLG.h"
// CYOUNGCHAT_CApp:
// 有关此类的实现，请参阅 YOUNGCHAT_C.cpp
//

class CYOUNGCHAT_CApp : public CWinApp
{
public:
	CYOUNGCHAT_CApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
private:
	Socket_Client* m_Socket;
public:
	Socket_Client* GetSocket();
// 实现

	DECLARE_MESSAGE_MAP()
};

extern CYOUNGCHAT_CApp theApp;