
// mfc_sqliteDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"

#include <vector>
#include <algorithm>
#include "afxwin.h"
typedef struct HuaweiFile
{
	CString strFileIndex;
	CString strFilePath;
	CString strFileData;
	long numFileLength;
} HUAWEIFILE;
// using namespace std;

// Cmfc_sqliteDlg 대화 상자
class Cmfc_sqliteDlg : public CDialogEx
{
// 생성입니다.
public:
	Cmfc_sqliteDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~Cmfc_sqliteDlg();
// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFC_SQLITE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListBackup(NMHDR *pNMHDR, LRESULT *pResult);
	// afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOpen();
	CListCtrl m_ListDB;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString m_strGlobalPath;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	std::vector<CString> vSelectedList;
	virtual BOOL DestroyWindow();
	void CreateFileSystem(CString strDBFile);
	LPCTSTR GetInstallRootDir();
	BOOL _CreateDirectory(LPCTSTR lpszPath);
	void _CreateFile(CString strFilePath, const char* cFileIndex, const char* cAcquisitionFilePath);
	void _CreateFile(LPCTSTR lpszPath, const char * chData, int nbufSize);
};
