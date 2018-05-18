
// mfc_sqliteDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// Cmfc_sqliteDlg 대화 상자



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


// Cmfc_sqliteDlg 메시지 처리기

BOOL Cmfc_sqliteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ListDB.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	m_ListDB.InsertColumn(0, _T("파일 경로"), LVCFMT_LEFT, 700, -1);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cmfc_sqliteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cmfc_sqliteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void Cmfc_sqliteDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//}


void Cmfc_sqliteDlg::OnLvnItemchangedListBackup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


//void Cmfc_sqliteDlg::OnBnClickedButton1()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


void Cmfc_sqliteDlg::OnBnClickedOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szFilter[] = "DB 파일 (*.db)|*.db|All Files (*.*)|*.*||";

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ListDB.DeleteAllItems();

	CDialog::OnDropFiles(hDropInfo);

	// UINT i = 0; // drag & drop 된 파일, 폴더의 갯수 저장
	int i = 0;
	// 드롭된 파일의 갯수
	// UINT uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	int uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	TCHAR buffer[MAX_PATH]; // drag&drop 된 파일, 폴더의 절대경로 저장

	// MessageBox(_T());
	// CString temp(uCount);

	// 뒤부터 출력되어서 출력 순서 변경 
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 선택 된 목록
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

		// TODO: -- File System 구성 메소드 여기에 추가
		CreateFileSystem(vSelectedList[0]);

		// FileSystemDlg 창 실행 -- 선택시 창이 실행 된다는 conditional
		CFileSystemDlg filesysDlg;
		filesysDlg.DoModal();

		filesysDlg.DestroyWindow();
	}

	// CDialogEx::OnOK();
}


void Cmfc_sqliteDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL Cmfc_sqliteDlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

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
				AfxMessageBox(_T("CreateFileSystem[1]: 티렉토리 생성 실패"));

			if (strcmp(cFileIndex, "-1") != 0)
				_CreateFile(strFileFullPath, cFileIndex, cAcquisitionFilePath);

			queryResult.nextRow();
		}
	}
	catch (CppSQLite3Exception& e)
	{
		AfxMessageBox((CString)e.errorMessage());
		OutputDebugString(_T("CreateFileSystem[1]: 디비 오픈 실패"));
	}
}


// 현재 경로 찾기
LPCTSTR Cmfc_sqliteDlg::GetInstallRootDir()
{
	static TCHAR s_szInstallRootDir[MAX_PATH] = { 0x00, };

	if (0 == _tcslen(s_szInstallRootDir))
	{
		// s_szInstallRootDir 는 실행경로 파일까지 포함한다.
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

// 폴더 만들기
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


// 파일 읽고 쓰기
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
		OutputDebugString(_T("_CreateFile[3]: 디비 오픈 실패"));
	}
}

// 파일 읽고 쓰기
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
