// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "YOUNGCHAT_S.h"
#include "ClientSocket.h"
#include "YOUNGCHAT_SDlg.h"

// CClientSocket




CClientSocket::CClientSocket(CPtrList* pList):m_pList(pList),m_strName(_T(""))
{

}

CClientSocket::~CClientSocket(void)
{
}
void CClientSocket::OnReceive(int nErrorCode)
{
	HEADER head;
	int nlen = sizeof HEADER;
	char *pHead = NULL;
	pHead =	new char[nlen];
	if(!pHead)
	{
		TRACE0("CClientSocket::OnReceive 内存不足");
		return;
	}
	memset(pHead,0,sizeof(char)*nlen);//memset是按照字节替换的，所以一共nlen个char，需要nlen*sizeof char
	Receive(pHead,nlen);
	head.type = ((LPHEADER)pHead)->type;
	head.nContentLen = ((LPHEADER)pHead)->nContentLen;
	delete pHead;
	pHead = NULL;
	//接收数据内容
	pHead = new char[head.nContentLen];
	if(!pHead)
	{
		TRACE0("CClientSocket::OnReceive 内存不足");
		return;
	}
	if(Receive(pHead,head.nContentLen) != head.nContentLen)//接收到的内容大小和头部所描述大小不一致
	{
		AfxMessageBox(_T("接收数据有误"));
		delete pHead;
		return;
	}
	switch (head.type)
	{
	case MSG_LOGIN:
		OnLogIn(pHead,head.nContentLen);
		break;
	case MSG_SEND:
		OnMSGTrans(pHead,head.nContentLen);
		break;
	default:
		break;
	}
delete pHead;
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int ErrorCode)
{
	CTime time;
	time = CTime::GetCurrentTime();
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S  ");
	strTime = strTime + this->m_strName + _T("离开...\r\n");
	((CYOUNGCHAT_SDlg*)theApp.GetMainWnd())->DisplayLog(strTime);
	m_pList->RemoveAt(m_pList->Find(this));
	CString str = this->UpdateServerLog();
	this->UpdateAllUser(str);
	this->Close();
	delete this;
	CSocket::OnClose(ErrorCode);

}

void CClientSocket::OnLogIn(char* buff,int nlen)
{
	CTime time;
	time = CTime::GetCurrentTime();
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S  ");
	CString strTemp(buff);
	strTime = strTime + strTemp + _T("登入...\r\n");

	((CYOUNGCHAT_SDlg*)theApp.GetMainWnd())->DisplayLog(strTime);
	m_strName = strTemp;
	CString str = this->UpdateServerLog();
	this->UpdateAllUser(str);
}

void CClientSocket::OnMSGTrans(char* buff,int nlen)
{
	HEADER head;
	head.type = MSG_SEND;
	head.nContentLen = nlen;
	POSITION ps = m_pList->GetHeadPosition();
	if(ps != NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		pTemp->Send(&head,sizeof HEADER);
		pTemp->Send(buff,nlen);
	}
}

void CClientSocket::UpdateAllUser(CString strUserInfo)
{
	HEADER _head;
	 _head.type = MSG_UPDATE;
	 _head.nContentLen = strUserInfo.GetLength()+1;
	 char *pSend = new char[_head.nContentLen];
	 memset(pSend, 0, _head.nContentLen*sizeof(char));
	if( !Char2Byte(strUserInfo.GetBuffer(0), pSend, _head.nContentLen))
	{
		AfxMessageBox(_T("字符转换失败"));
		delete pSend;
		return;
	}
	POSITION ps = m_pList->GetHeadPosition();
	while(ps!=NULL)
	{
		 CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		 //发送协议头
		 pTemp->Send((char*)&_head, sizeof(_head));
		 pTemp->Send(pSend,_head.nContentLen );
	}	
	 
	delete pSend;
 
}

CString CClientSocket::UpdateServerLog()  
 {  
     CString strUserInfo = _T("");  
       
     POSITION ps = m_pList->GetHeadPosition();  
  
     while(ps!=NULL)  
     {  
         CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);  
         strUserInfo += pTemp->m_strName + _T("#");  
     }  
    ((CYOUNGCHAT_SDlg*)theApp.GetMainWnd())->UpdateUserInfo(strUserInfo);  
  
    return strUserInfo;  
 }  

// CClientSocket 消息处理程序


BOOL CClientSocket::Char2Byte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}