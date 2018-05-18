// FileSystemDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "mfc_sqlite.h"
#include "FileSystemDlg.h"
#include "afxdialogex.h"
#include "mfc_sqliteDlg.h"


// CFileSystemDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFileSystemDlg, CDialogEx)

CFileSystemDlg::CFileSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileSystemDlg::IDD, pParent)
{

}

CFileSystemDlg::~CFileSystemDlg()
{
}

void CFileSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILESYSTEM, m_ListFiles);
}


BEGIN_MESSAGE_MAP(CFileSystemDlg, CDialogEx)
//	ON_BN_CLICKED(IDOK, &CFileSystemDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileSystemDlg 메시지 처리기입니다.


BOOL CFileSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ListFiles.DeleteAllItems();

	m_ListFiles.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	m_ListFiles.InsertColumn(0, _T("파일 경로"), LVCFMT_LEFT, 700, -1);

	Cmfc_sqliteDlg *sqliteDlg = (Cmfc_sqliteDlg*)AfxGetMainWnd();

	// 뒤부터 출력되어서 출력 순서 변경
	// for (unsigned int i = 0; i < sqliteDlg->vSelectedList.size(); i++)
	for (int i = sqliteDlg->vSelectedList.size() - 1; i >= 0; i--)
	{
		m_ListFiles.InsertItem(0, sqliteDlg->vSelectedList[i]);
	}

	// Cmfc_sqliteDlg::vSelectedList
	// delete[] sqliteDlg;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// -- sqlite 분석
// ---- apk_file_info 참조 -- file_path, file_index
// ---- apk_file_data 참조 -- file_inex, file_length, file_data, file_index
// select files: sqliteDlg->vSelectedList



// void CFileSystemDlg::OnBnClickedOk()
// {
// 	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.



// 	CDialogEx::OnOK();
// }


BOOL CFileSystemDlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::DestroyWindow();
}
