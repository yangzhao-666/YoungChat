#pragma once


// LOGIN_DLG �Ի���

class LOGIN_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(LOGIN_DLG)

public:
	LOGIN_DLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LOGIN_DLG();

// �Ի�������
	enum { IDD = IDD_LOGIN  };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedLog();
	afx_msg void OnClickedExit();
	virtual BOOL OnInitDialog();
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	DWORD m_IPadd;
	CString m_User;
};