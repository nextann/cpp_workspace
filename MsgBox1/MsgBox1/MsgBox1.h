
// MsgBox1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMsgBox1App:
// �� Ŭ������ ������ ���ؼ��� MsgBox1.cpp�� �����Ͻʽÿ�.
//

class CMsgBox1App : public CWinApp
{
public:
	CMsgBox1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMsgBox1App theApp;