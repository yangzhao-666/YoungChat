#pragma once
const int MSG_LOGOIN = 0x01; //登录
const int MSG_SEND = 0x11;   //发送消息
const int MSG_CLOSE = 0x02;  //退出
const int MSG_UPDATE = 0x21; //更信息

// Socket_Client 命令目标

class Socket_Client : public CSocket
{
public:
	Socket_Client();
	virtual ~Socket_Client();
public:
	BOOL OnLogIn(LPSTR buff,int len);//LPSTR = Char*
	BOOL SendMSG(LPSTR buff,int len);
	virtual void OnReceive(int nErrorCode);
	CString m_user_name;
	typedef struct HEAD
	{
		int type;
		int content_len;
	}*LPHEAD;
};


