
// mfc_sqliteDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "mfc_sqlite.h"
#include "mfc_sqliteDlg.h"
#include "afxdialogex.h"
#include "sqlite/CppSQLite3.h"
#include <windows.h>
#include <string>
#include "FileSystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfc_sqliteDlg ��ȭ ����



Cmfc_sqliteDlg::Cmfc_sqliteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc_sqliteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strGlobalPath = _T("");
}

Cmfc_sqliteDlg::~Cmfc_sqliteDlg()
{
	CoUninitialize();
}

void Cmfc_sqliteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DBTABLE, m_ListDB);
}

BEGIN_MESSAGE_MAP(Cmfc_sqliteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DBTABLE, &Cmfc_sqliteDlg::OnLvnItemchangedListBackup)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &Cmfc_sqliteDlg::OnBnClickedOpen)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK, &Cmfc_sqliteDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cmfc_sqliteDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Cmfc_sqliteDlg �޽��� ó����

BOOL Cmfc_sqliteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ListDB.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	m_ListDB.InsertColumn(0, _T("���� ���"), LVCFMT_LEFT, 700, -1);


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void Cmfc_sqliteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cmfc_sqliteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR Cmfc_sqliteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void Cmfc_sqliteDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	*pResult = 0;
//}


void Cmfc_sqliteDlg::OnLvnItemchangedListBackup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


//void Cmfc_sqliteDlg::OnBnClickedButton1()
//{
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//}


void Cmfc_sqliteDlg::OnBnClickedOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[] = "DB ���� (*.db)|*.db|All Files (*.*)|*.*||";

	// CFileDialog dlg(TRUE, _T("*.db"), _T("db"), OFN_HIDEREADONLY, szFilter);
	// CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, (CString)szFilter);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, (CString)szFilter);
	DWORD MAXFILE = 2562; // 2562 is the max

	TCHAR* pc = new TCHAR[MAXFILE];
	pc[0] = NULL;
	pc[MAXFILE - 1] = NULL;
	
	dlg.m_ofn.nMaxFile = MAXFILE;
	dlg.m_ofn.lpstrFile = pc;
	// dlg.m_ofn.lpstrFile[0] = NULL;


	if (IDOK == dlg.DoModal())
	{
		m_ListDB.DeleteAllItems();

		// CString pathName = dlg.GetPathName();
		POSITION pos = dlg.GetStartPosition();

		if (pos)
		{
			// CString pathName;
			// pathName = _T("");
			do
			{
				/*
				pathName += dlg.GetNextPathName(pos);
				pathName += "\n";
				*/

				m_ListDB.InsertItem(0, dlg.GetNextPathName(pos));
				// UpdateData(FALSE);

			} while (pos);
			// MessageBox(_T("HELLO WORLD"));
			// MessageBox(pathName);
			//MessageBox(pathName.GetLength());
		}
		// MessageBox(pathName);
	}

	// release file names buffer
	delete[] pc;
	
}


void Cmfc_sqliteDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_ListDB.DeleteAllItems();

	CDialog::OnDropFiles(hDropInfo);

	// UINT i = 0; // drag & drop �� ����, ������ ���� ����
	int i = 0;
	// ��ӵ� ������ ����
	// UINT uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	int uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	TCHAR buffer[MAX_PATH]; // drag&drop �� ����, ������ ������ ����

	// MessageBox(_T());
	// CString temp(uCount);

	// �ں��� ��µǾ ��� ���� ���� 
	for (i = 0; i < uCount; i++)
	// for (i = uCount - 1; i >= 0; i--)
	{
		DragQueryFile(hDropInfo, i, buffer, MAX_PATH);
		// m_strGlobalPath.Format(_T("%s"), buffer);
		m_ListDB.InsertItem(0, buffer);
	}


	CDialogEx::OnDropFiles(hDropInfo);
}


void Cmfc_sqliteDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���� �� ���
	// vector<CString> vSelectedList;
	vSelectedList.clear();

	// int count = m_ListDB.GetSelectedCount();
	POSITION pos = m_ListDB.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		MessageBox(_T("No Items Selected!!\nPlease Select an item."));
	}
	else
	{
		while (pos)
		{
			int nItem = m_ListDB.GetNextSelectedItem(pos);

			CString strItem = m_ListDB.GetItemText(nItem, 0);

			vSelectedList.push_back(strItem);
		}

		// TODO: -- File System ���� �޼ҵ� ���⿡ �߰�
		CreateFileSystem(vSelectedList[0]);

		// FileSystemDlg â ���� -- ���ý� â�� ���� �ȴٴ� conditional
		CFileSystemDlg filesysDlg;
		filesysDlg.DoModal();

		filesysDlg.DestroyWindow();
	}

	// CDialogEx::OnOK();
}


void Cmfc_sqliteDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


BOOL Cmfc_sqliteDlg::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialogEx::DestroyWindow();
}


void Cmfc_sqliteDlg::CreateFileSystem(CString strDBFile)
{
	CppSQLite3DB CSdb;
	// CString strFilePath, strFileFullPath, strFileName;
	// DWORD dwFile_Length;
	// const char* cFileIndex;
	const char* cAcquisitionFilePath;
	CT2A asciiPath(strDBFile, CP_UTF8);
	cAcquisitionFilePath = asciiPath.m_psz;
	try
	{
		CSdb.open(cAcquisitionFilePath);
		CppSQLite3Query queryResult = CSdb.execQuery("SELECT file_path, file_index FROM apk_file_info order by file_index;");
		while (!queryResult.eof())
		{
			CString strFilePath = (CString)queryResult.fieldValue(0);
			const char* cFileIndex  = queryResult.fieldValue(1);

			CString strFileFullPath;
			strFileFullPath.Format(_T("%s\\%s"), GetInstallRootDir(), strFilePath);

			if (!_CreateDirectory(strFileFullPath))
				AfxMessageBox(_T("CreateFileSystem[1]: Ƽ���丮 ���� ����"));

			if (strcmp(cFileIndex, "-1") != 0)
				_CreateFile(strFileFullPath, cFileIndex, cAcquisitionFilePath);

			queryResult.nextRow();
		}
	}
	catch (CppSQLite3Exception& e)
	{
		AfxMessageBox((CString)e.errorMessage());
		OutputDebugString(_T("CreateFileSystem[1]: ��� ���� ����"));
	}
}


// ���� ��� ã��
LPCTSTR Cmfc_sqliteDlg::GetInstallRootDir()
{
	static TCHAR s_szInstallRootDir[MAX_PATH] = { 0x00, };

	if (0 == _tcslen(s_szInstallRootDir))
	{
		// s_szInstallRootDir �� ������ ���ϱ��� �����Ѵ�.
		if (GetModuleFileName(NULL, s_szInstallRootDir, MAX_PATH) == 0)
			return NULL; // throw FMException (FME_TRACE_INFO, FME_INVALID_PARAM, _T("GetModuleFileName Failed."));

		CString szTemp = s_szInstallRootDir;
		szTemp.Replace(_T('/'), _T('\\'));
		int nRFirstBackslashPos = szTemp.ReverseFind(_T('\\'));
		if (nRFirstBackslashPos < 1)
			return NULL; // throw FMException(FME_TRACE_INFO, FME_INVALID_PARAM, _T("GetModuleFileName Failed. [s_szInstallRootDir=%s]"), s_szInstallRootDir);

		_tcscpy_s(s_szInstallRootDir, MAX_PATH, szTemp.Left(nRFirstBackslashPos + 1));
	}

	return s_szInstallRootDir;
}

// ���� �����
BOOL Cmfc_sqliteDlg::_CreateDirectory(LPCTSTR lpszPath)
{
	TCHAR szPathBuffer[MAX_PATH];

	size_t len = _tcslen(lpszPath);

	for (size_t i = 0; i < len; i++)
	{
		szPathBuffer[i] = *(lpszPath + i);
		if (szPathBuffer[i] == _T('\\') || szPathBuffer[i] == _T('/'))
		{
			szPathBuffer[i + 1] = NULL;
			if (!PathFileExists(szPathBuffer))
			{
				if (!::CreateDirectory(szPathBuffer, NULL))
				{
					if (GetLastError() != ERROR_ALREADY_EXISTS)
						return FALSE;
				}
			}
		}
	}
	return TRUE;
}


// ���� �а� ����
void Cmfc_sqliteDlg::_CreateFile(CString strFilePath, const char* cFileIndex, const char* cAcquisitionFilePath)
{
	CppSQLite3DB CSdb;
	CString strFileFullPath, strFileName;
	// DWORD dwFile_Length;
	const char *cDataIndex, *cFileIndex_data, *cBlobData, *cBlobSize;

	CStdioFile file;

	try
	{
		CSdb.open(cAcquisitionFilePath);
		CppSQLite3Query queryResult = CSdb.execQuery("SELECT data_index, file_index, file_length, file_data FROM apk_file_data;");
		while (!queryResult.eof())
		{
			cDataIndex      = queryResult.fieldValue(0);
			cFileIndex_data = queryResult.fieldValue(1);
			cBlobSize       = queryResult.fieldValue(2);
			cBlobData       = queryResult.fieldValue(3);

			if (strcmp(cFileIndex, cFileIndex_data) == 0)
				_CreateFile(strFilePath, cBlobData, atoi(cBlobSize));

			queryResult.nextRow();
		}

	}
	catch (CppSQLite3Exception& e)
	{
		AfxMessageBox((CString)e.errorMessage());
		OutputDebugString(_T("_CreateFile[3]: ��� ���� ����"));
	}
}

// ���� �а� ����
void Cmfc_sqliteDlg::_CreateFile(LPCTSTR lpszPath, const char * chData, int nbufSize)
{
	CStdioFile file;
	if (file.Open(lpszPath, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate | CFile::typeBinary))
	{
		file.SeekToEnd();
		file.Write(chData, nbufSize);
		file.Close();
	}
}
