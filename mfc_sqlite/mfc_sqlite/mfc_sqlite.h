
// mfc_sqlite.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cmfc_sqliteApp:
// �� Ŭ������ ������ ���ؼ��� mfc_sqlite.cpp�� �����Ͻʽÿ�.
//

class Cmfc_sqliteApp : public CWinApp
{
public:
	Cmfc_sqliteApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_sqliteApp theApp;