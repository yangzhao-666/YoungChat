#pragma once
const int MSG_LOGOIN = 0x01; //��¼
const int MSG_SEND = 0x11;   //������Ϣ
const int MSG_CLOSE = 0x02;  //�˳�
const int MSG_UPDATE = 0x21; //����Ϣ

// Socket_Client ����Ŀ��

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


