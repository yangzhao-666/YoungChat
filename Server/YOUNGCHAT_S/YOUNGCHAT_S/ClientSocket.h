#pragma once
#include "afxsock.h"
#include "stdafx.h"
const int MSG_LOGIN = 0x01;
const int MSG_SEND = 0x11;
const int MSG_CLOSE = 0x02;
const int MSG_UPDATE = 0x21;

// CClientSocket

class CClientSocket : public CSocket
{
	

public:
	CClientSocket(CPtrList* pList);
	virtual ~CClientSocket(void);
	CPtrList* m_pList;
	CString m_strName;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void OnLogIn(char *buff,int nLen);
	void OnMSGTrans(char *buff,int nLen);
	CString UpdateServerLog();
	void UpdateAllUser(CString strUserInfo);
	BOOL Char2Byte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	typedef struct Header
	{
		int type;
		int nContentLen;
	}HEADER,*LPHEADER;

protected:

};


