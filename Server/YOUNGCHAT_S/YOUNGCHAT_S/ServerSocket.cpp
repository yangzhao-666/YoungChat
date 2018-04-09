// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "YOUNGCHAT_S.h"
#include "ServerSocket.h"
#include "ClientSocket.h"


// CServerSocket



CServerSocket::CServerSocket(void)
{

}

CServerSocket::~CServerSocket(void)
{
}
void CServerSocket::OnAccept(int nErrorCode)
{
	CClientSocket* theClient = new CClientSocket(&m_listSockets);
	if(!theClient)
	{
		AfxMessageBox(_T("内存不足，连接失败"));
		return;
	}
	Accept(*theClient);//???
	m_listSockets.AddTail(theClient);//???
	CSocket::OnAccept(nErrorCode);
}





// CServerSocket 消息处理程序


