
// YOUNGCHAT_C.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Socket_Client.h"
#include "LOGIN_DLG.h"
// CYOUNGCHAT_CApp:
// �йش����ʵ�֣������ YOUNGCHAT_C.cpp
//

class CYOUNGCHAT_CApp : public CWinApp
{
public:
	CYOUNGCHAT_CApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
private:
	Socket_Client* m_Socket;
public:
	Socket_Client* GetSocket();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYOUNGCHAT_CApp theApp;