// Socket_Client.cpp : 实现文件
//

#include "stdafx.h"
#include "YOUNGCHAT_C.h"
#include "Socket_Client.h"
#include "YOUNGCHAT_CDlg.h"

// Socket_Client

Socket_Client::Socket_Client()
	:m_user_name(_T(""))
{
}

Socket_Client::~Socket_Client()
{
}
void Socket_Client::OnReceive(int nErrorCode)
{
	HEAD header;
	char *m_head = NULL;
	m_head = new char[sizeof(header)];
	memset(m_head,0,sizeof(header));
	Receive(m_head,sizeof(header));
	header.type = ((LPHEAD)m_head)->type;
	header.content_len = ((LPHEAD)m_head)->content_len;
	delete m_head;
	m_head = NULL;
	
	char *m_buff;
	m_buff = new char[header.content_len];
	if(!m_buff)
	{
		AfxMessageBox(_T("内存不足"));
		return;
	}
	memset(m_buff,0,sizeof(char)*header.content_len);
	if(header.content_len!=Receive(m_buff,header.content_len))
	{
		AfxMessageBox(_T("接收数据有误"));
		delete m_buff;
		return;
	}
	switch (header.type)
	{
	case MSG_UPDATE:
		{
			CString text(m_buff);
			((CYOUNGCHAT_CDlg*)(AfxGetApp()->GetMainWnd()))->UpdateInfo(text);
		}
		break;
	case MSG_SEND:
		{
			CString text(m_buff);
			((CYOUNGCHAT_CDlg*)(AfxGetApp()->GetMainWnd()))->UpdateMSG(text);
			break;
		}
	default:
		break;
	}
	delete m_buff;
	CSocket::OnReceive(nErrorCode);
}
BOOL Socket_Client::SendMSG(LPSTR buff,int len)
{
	HEAD header;
	header.type = MSG_SEND;
	header.content_len = len;
	if(Send(&header,sizeof(header))==SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送头部失败"));
		return FALSE;
	};
	if(Send(buff,len)==SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送数据部分失败"));
		return FALSE;
	};
	return TRUE;
}
BOOL Socket_Client::OnLogIn(LPSTR buff,int len)
{
	HEAD header;
	header.type = MSG_LOGOIN;
	header.content_len = len;
	int _nSnd= 0;
	if((_nSnd = Send((char*)&header, sizeof(header)))==SOCKET_ERROR)
		return false;
	if((_nSnd = Send(buff, len))==SOCKET_ERROR)
		return false;

	return TRUE;
}
// Socket_Client 成员函数
