
// YOUNGCHAT_CDlg.h : 头文件
//

#pragma once
#include "Socket_Client.h"
#include "afxwin.h"

// CYOUNGCHAT_CDlg 对话框
class CYOUNGCHAT_CDlg : public CDialogEx
{
// 构造
public:
	CYOUNGCHAT_CDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YOUNGCHAT_C_DIALOG };
	void UpdateMSG(CString &text);
	void UpdateInfo(CString Info);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedSend();
	CString m_Send;
	afx_msg void OnClickedCancel();
	BOOL Char2Byte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
};
