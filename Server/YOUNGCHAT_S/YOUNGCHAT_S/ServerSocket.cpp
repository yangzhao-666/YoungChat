// ServerSocket.cpp : ʵ���ļ�
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
		AfxMessageBox(_T("�ڴ治�㣬����ʧ��"));
		return;
	}
	Accept(*theClient);//???
	m_listSockets.AddTail(theClient);//???
	CSocket::OnAccept(nErrorCode);
}





// CServerSocket ��Ϣ�������


