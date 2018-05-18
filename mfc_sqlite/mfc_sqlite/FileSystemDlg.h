#pragma once
#include "afxcmn.h"


// CFileSystemDlg 대화 상자입니다.

class CFileSystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileSystemDlg)

public:
	CFileSystemDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFileSystemDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FILESYSTEM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListFiles;
	virtual BOOL OnInitDialog();
//	afx_msg void OnBnClickedOk();
	virtual BOOL DestroyWindow();
};
