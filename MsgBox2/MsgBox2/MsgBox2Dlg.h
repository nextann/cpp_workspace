
// MsgBox2Dlg.h : ��� ����
//

#pragma once


// CMsgBox2Dlg ��ȭ ����
class CMsgBox2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMsgBox2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MSGBOX2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strResult;
	afx_msg void OnClickedButtonYn();
	afx_msg void OnClickedButtonOc();
	afx_msg void OnClickedButtonExit();
};
