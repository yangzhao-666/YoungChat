#pragma once
#include "afxsock.h"

// CServerSocket

class CServerSocket : public CSocket
{
	

public:
	CServerSocket(void);
	~CServerSocket(void);
	CPtrList m_listSockets;//保存链接客户端的链表
	virtual void OnAccept(int nErrorCode);

protected:
	
};


