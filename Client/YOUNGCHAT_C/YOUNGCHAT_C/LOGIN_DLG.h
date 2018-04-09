#pragma once


// LOGIN_DLG 对话框

class LOGIN_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(LOGIN_DLG)

public:
	LOGIN_DLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LOGIN_DLG();

// 对话框数据
	enum { IDD = IDD_LOGIN  };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedLog();
	afx_msg void OnClickedExit();
	virtual BOOL OnInitDialog();
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	DWORD m_IPadd;
	CString m_User;
};