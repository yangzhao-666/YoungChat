
// YOUNGCHAT_CDlg.h : ͷ�ļ�
//

#pragma once
#include "Socket_Client.h"
#include "afxwin.h"

// CYOUNGCHAT_CDlg �Ի���
class CYOUNGCHAT_CDlg : public CDialogEx
{
// ����
public:
	CYOUNGCHAT_CDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YOUNGCHAT_C_DIALOG };
	void UpdateMSG(CString &text);
	void UpdateInfo(CString Info);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
