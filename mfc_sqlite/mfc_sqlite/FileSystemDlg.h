#pragma once
#include "afxcmn.h"


// CFileSystemDlg ��ȭ �����Դϴ�.

class CFileSystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileSystemDlg)

public:
	CFileSystemDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFileSystemDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FILESYSTEM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListFiles;
	virtual BOOL OnInitDialog();
//	afx_msg void OnBnClickedOk();
	virtual BOOL DestroyWindow();
};
