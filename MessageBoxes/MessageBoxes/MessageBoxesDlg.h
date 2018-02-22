
// MessageBoxesDlg.h : ��� ����
//

#pragma once


// CMessageBoxesDlg ��ȭ ����
class CMessageBoxesDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMessageBoxesDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MESSAGEBOXES_DIALOG };

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
	afx_msg void OnClickedButtonMfc();
	afx_msg void OnClickedButtonExit();
	afx_msg void OnClickedButtonYn();
	afx_msg void OnClickedButtonAri();
	afx_msg void OnClickedButtonOc();
	afx_msg void OnClickedButtonOk();
	afx_msg void OnClickedButtonRc();
	afx_msg void OnClickedButtonYnc();
};
