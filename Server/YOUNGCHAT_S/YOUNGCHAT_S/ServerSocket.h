#pragma once
#include "afxsock.h"

// CServerSocket

class CServerSocket : public CSocket
{
	

public:
	CServerSocket(void);
	~CServerSocket(void);
	CPtrList m_listSockets;//�������ӿͻ��˵�����
	virtual void OnAccept(int nErrorCode);

protected:
	
};


