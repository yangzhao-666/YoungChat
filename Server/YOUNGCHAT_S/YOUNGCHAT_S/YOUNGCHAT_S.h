
// YOUNGCHAT_S.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ServerSocket.h"

// CYOUNGCHAT_SApp:
// �йش����ʵ�֣������ YOUNGCHAT_S.cpp
//

class CYOUNGCHAT_SApp : public CWinApp
{
public:
	CYOUNGCHAT_SApp();

// ��д
public:
	CServerSocket *GetServerSocket() const;
	CServerSocket *m_iSocket;
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();//�˳�ʱ����
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYOUNGCHAT_SApp theApp;