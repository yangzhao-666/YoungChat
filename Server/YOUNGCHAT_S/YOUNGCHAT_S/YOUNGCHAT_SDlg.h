
// YOUNGCHAT_SDlg.h : ͷ�ļ�
//

#pragma once


// CYOUNGCHAT_SDlg �Ի���
class CYOUNGCHAT_SDlg : public CDialogEx
{
// ����
public:
	CYOUNGCHAT_SDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void DisplayLog(CString &strInfo);
	void UpdateUserInfo(CString strUserInfo);

// �Ի�������
	enum { IDD = IDD_YOUNGCHAT_S_DIALOG };

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
};
