
// CopyFile.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCopyFileApp:
// �� Ŭ������ ������ ���ؼ��� CopyFile.cpp�� �����Ͻʽÿ�.
//

class CCopyFileApp : public CWinApp
{
public:
	CCopyFileApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCopyFileApp theApp;