
// MsgBox2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMsgBox2App:
// �� Ŭ������ ������ ���ؼ��� MsgBox2.cpp�� �����Ͻʽÿ�.
//

class CMsgBox2App : public CWinApp
{
public:
	CMsgBox2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMsgBox2App theApp;