// FileSystemDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "mfc_sqlite.h"
#include "FileSystemDlg.h"
#include "afxdialogex.h"
#include "mfc_sqliteDlg.h"


// CFileSystemDlg ��ȭ �����Դϴ�.

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


// CFileSystemDlg �޽��� ó�����Դϴ�.


BOOL CFileSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ListFiles.DeleteAllItems();

	m_ListFiles.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	m_ListFiles.InsertColumn(0, _T("���� ���"), LVCFMT_LEFT, 700, -1);

	Cmfc_sqliteDlg *sqliteDlg = (Cmfc_sqliteDlg*)AfxGetMainWnd();

	// �ں��� ��µǾ ��� ���� ����
	// for (unsigned int i = 0; i < sqliteDlg->vSelectedList.size(); i++)
	for (int i = sqliteDlg->vSelectedList.size() - 1; i >= 0; i--)
	{
		m_ListFiles.InsertItem(0, sqliteDlg->vSelectedList[i]);
	}

	// Cmfc_sqliteDlg::vSelectedList
	// delete[] sqliteDlg;

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

// -- sqlite �м�
// ---- apk_file_info ���� -- file_path, file_index
// ---- apk_file_data ���� -- file_inex, file_length, file_data, file_index
// select files: sqliteDlg->vSelectedList



// void CFileSystemDlg::OnBnClickedOk()
// {
// 	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.



// 	CDialogEx::OnOK();
// }


BOOL CFileSystemDlg::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialogEx::DestroyWindow();
}
