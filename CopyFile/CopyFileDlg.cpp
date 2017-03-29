
// CopyFileDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CopyFile.h"
#include "CopyFileDlg.h"
#include "afxdialogex.h"

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


// CCopyFileDlg 대화 상자




CCopyFileDlg::CCopyFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCopyFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopyFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCopyFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_ORG, &CCopyFileDlg::OnBnClickedButtonOrg)
    ON_BN_CLICKED(IDC_BUTTON_DST, &CCopyFileDlg::OnBnClickedButtonDst)
    ON_BN_CLICKED(IDOK, &CCopyFileDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_LIST, &CCopyFileDlg::OnBnClickedButtonList)
    ON_WM_SIZE()
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CCopyFileDlg 메시지 처리기

BOOL CCopyFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	if ( CheckCommandParameter() )
	{
		exit(0);
	}

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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
    CString strLog = TEXT("경로 목록 파일은 '로그에 출력할 문자열', '원본경로', '대상경로'가 컴마(,)로 구분된 Text 파일 입니다.");
    SetDlgItemText(IDC_EDIT_LOG, strLog);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCopyFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCopyFileDlg::OnPaint()
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
HCURSOR CCopyFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCopyFileDlg::OnBnClickedButtonOrg()
{
    CString strPath;
    GetDlgItemText(IDC_EDIT_ORG, strPath);

    if ( strPath.Trim().IsEmpty() ) {
        strPath.Format(TEXT("C:\\"));
    }

    ITEMIDLIST  *pidlBrowse;
    TCHAR       pszPathname[MAX_PATH];

    _tcscpy_s(pszPathname, MAX_PATH, strPath);

    BROWSEINFO  BrInfo;
    memset(&BrInfo, 0x00, sizeof(BrInfo));
    BrInfo.hwndOwner = this->GetSafeHwnd();
    BrInfo.pidlRoot = NULL;
    BrInfo.pszDisplayName = pszPathname;
    BrInfo.lpszTitle = _T("원본 경로");
    BrInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    BrInfo.lParam = (LPARAM)pszPathname;

    pidlBrowse = ::SHBrowseForFolder(&BrInfo);
    if(pidlBrowse != NULL)
    {
        // 선택된 폴더 경로얻음
        SHGetPathFromIDList(pidlBrowse, pszPathname);

        strPath.Format(pszPathname);
        strPath.Trim();
        SetDlgItemText(IDC_EDIT_ORG, strPath);
    }
}


void CCopyFileDlg::OnBnClickedButtonDst()
{
    CString strPath;
    GetDlgItemText(IDC_EDIT_DST, strPath);

    if ( strPath.Trim().IsEmpty() ) {
        strPath.Format(TEXT("C:\\"));
    }

    ITEMIDLIST  *pidlBrowse;
    TCHAR       pszPathname[MAX_PATH];

    _tcscpy_s(pszPathname, MAX_PATH, strPath);

    BROWSEINFO  BrInfo;
    memset(&BrInfo, 0x00, sizeof(BrInfo));
    BrInfo.hwndOwner = this->GetSafeHwnd();
    BrInfo.pidlRoot = NULL;
    BrInfo.pszDisplayName = pszPathname;
    BrInfo.lpszTitle = _T("대상 경로");
    BrInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    BrInfo.lParam = (LPARAM)pszPathname;

    pidlBrowse = ::SHBrowseForFolder(&BrInfo);
    if(pidlBrowse != NULL)
    {
        // 선택된 폴더 경로얻음
        SHGetPathFromIDList(pidlBrowse, pszPathname);

        strPath.Format(pszPathname);
        strPath.Trim();
        SetDlgItemText(IDC_EDIT_DST, strPath);
    }
}

int CCopyFileDlg::GetFileList(CString strOrgPath, CStringArray &listFile)
{
    int nCount = 0;

    CString strPattern;
    strPattern.Format(TEXT("%s\\*.*"), strOrgPath);

    WIN32_FIND_DATA         findFileData = {0,};

    HANDLE hFind = FindFirstFile(strPattern, &findFileData);
    if ( hFind == INVALID_HANDLE_VALUE) return -1;

    if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
    {
        nCount++;
        listFile.Add( findFileData.cFileName );
    }

    while (FindNextFile(hFind, &findFileData))
    {
        if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
            !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
            !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
            !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
        {
            nCount++;
            listFile.Add( findFileData.cFileName );
        }
    }

    FindClose(hFind);

    return nCount;
}

CString CCopyFileDlg::FormatErrorMessage(DWORD ErrorCode)
{
    TCHAR   *pMsgBuf = NULL;
    DWORD   nMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>(&pMsgBuf), 0, NULL);
    if (!nMsgLen)
        return _T("FormatMessage fail");
    CString sMsg(pMsgBuf, nMsgLen);
    LocalFree(pMsgBuf);
    return sMsg;
}

CString CCopyFileDlg::getFileInfo(CString filePath)
{
    HANDLE hFind = 0;
    WIN32_FIND_DATA FindFileData = {0,};

    hFind = FindFirstFile(filePath, &FindFileData);
    if ( hFind == INVALID_HANDLE_VALUE ) return TEXT("");

    FindClose(hFind);

    // Convert the last-write time to local time.
    SYSTEMTIME stUTC={0,}, stLocal={0,};
    FileTimeToSystemTime(&FindFileData.ftLastWriteTime, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    // Build a string showing the date and time.
    CString szDate;

    szDate.Format(TEXT("%04d/%02d/%02d  %02d:%02d")
        , stLocal.wYear, stLocal.wMonth, stLocal.wDay
        , stLocal.wHour, stLocal.wMinute);

    return szDate; 
}

int CCopyFileDlg::copyFileFolderToFolder(CString strTitle, CString strOrgPath, CString strDstPath, CString &log)
{
    // 원본에서 목록을 구한다.
    CStringArray listFileOrg;
    int nCountOrg = GetFileList(strOrgPath, listFileOrg);

    // 대상에서 목록을 구한다.
    CStringArray listFileDst;
    int nCountDst = GetFileList(strDstPath, listFileDst);

    // 대상 목록에서 원본 목록과 같은 것이 있으면 복사한다.
    for(int d=0; d<listFileDst.GetCount(); d++)
    {
        int status = 0; // 0:pass, 1:copy success, 2: copy fail
        CString dstFile;
        CString srcFile;

        dstFile.Format(TEXT("%s\\%s"), strDstPath, listFileDst.GetAt(d));

        for(int o=0; o<listFileOrg.GetCount(); o++)
        {
            if ( listFileOrg.GetAt(o).Compare( listFileDst.GetAt(d) ) == 0 )
            {
                srcFile.Format(TEXT("%s\\%s"), strOrgPath, listFileOrg.GetAt(o));

                //if ( CopyFile(srcFile, dstFile, FALSE) )
				if ( 1 )
                {
                    status = 1;
                } else 
                {
                    status = 2;
                }
                break;
            }
        }

        CString line;
        CString info;
        info = getFileInfo(dstFile);
        switch(status)
        {
        case 1:  
            line.Format(TEXT("[%s]\t %s \t %s \t %s\r\n"), TEXT("Success"), strTitle, info, listFileDst.GetAt(d)); 
            break;
        case 2:  
            line.Format(TEXT("[%s]\t %s \t %s \t %s - (%d)%s")
                     , TEXT("Fail"), strTitle, info, listFileDst.GetAt(d)
                     , GetLastError(), FormatErrorMessage(GetLastError())); 
            break;
        default: 
            line.Format(TEXT("[%s]\t %s \t %s \t %s\r\n"), TEXT("Pass"), strTitle, info, listFileDst.GetAt(d)); 
            break;
        }

        log.Append(line);
    }

    return listFileDst.GetCount();
}

BOOL CCopyFileDlg::isExistFile(CString filename)
{
   WIN32_FIND_DATA         findFileData = {0,};

    HANDLE hFind = FindFirstFile(filename, &findFileData);
    if ( hFind == INVALID_HANDLE_VALUE) return FALSE;
    FindClose(FindClose);

    if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
    {
        return TRUE;
    }

    return FALSE;
}

BOOL CCopyFileDlg::isExistDir(CString dirname)
{
   WIN32_FIND_DATA         findFileData = {0,};

    HANDLE hFind = FindFirstFile(dirname, &findFileData);
    if ( hFind == INVALID_HANDLE_VALUE) return FALSE;
    FindClose(FindClose);

    if((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
    {
        return TRUE;
    }

    return FALSE;
}

void CCopyFileDlg::OnBnClickedOk()
{
	CString strLog;
    CString strListfile;
    GetDlgItemText(IDC_EDIT_LIST, strListfile);
    if ( isExistFile(strListfile) ) 
	{
		CopyFromConfig(strListfile, strLog, NULL, NULL);
    } 
    else 
    {
        CString strOrgPath;
        GetDlgItemText(IDC_EDIT_ORG, strOrgPath);
        strOrgPath.Trim();

        if ( strOrgPath.IsEmpty() ) {
            MessageBox(TEXT("원본 경로를 입력하세요"));
            return;
        }

        CString strDstPath;
        GetDlgItemText(IDC_EDIT_DST, strDstPath);
        strDstPath.Trim();

        if ( strDstPath.IsEmpty() ) {
            MessageBox(TEXT("대상 경로를 입력하세요"));
            return;
        }

        copyFileFolderToFolder(NULL, strOrgPath, strDstPath, strLog);
    }

	SetDlgItemText(IDC_EDIT_LOG, TEXT(""));
	SetDlgItemText(IDC_EDIT_LOG, strLog);
}


void CCopyFileDlg::OnBnClickedButtonList()
{
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL);

    if( IDOK == dlg.DoModal() )
    {
        SetDlgItemText(IDC_EDIT_LIST, dlg.GetPathName());
    }
}


void CCopyFileDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    CEdit* pWndLog = (CEdit*)GetDlgItem(IDC_EDIT_LOG);


    if ( pWndLog && pWndLog->GetSafeHwnd())
    {
        RECT rectLog = {0,};
//        RECT rectDlg = {0,};

        pWndLog->GetWindowRect(&rectLog);
//        GetWindowRect(&rectDlg);

        pWndLog->SetWindowPos(NULL, 20, 160, cx-30, cy-170, SWP_NOZORDER);
    }
}


void CCopyFileDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    lpMMI->ptMinTrackSize.x = 640; //가로
    lpMMI->ptMinTrackSize.y = 580; // 세로

    CDialogEx::OnGetMinMaxInfo(lpMMI);
}


BOOL CCopyFileDlg::CheckCommandParameter()
{
	// 아규먼트가 없는 경우, Dialog를 띄운다.
	if(__argc == 1) 
		return FALSE;

	CString keyConfig("-c"), keyLog("-l"), keySrc("-s"), keyDst("-d");
	CString configFilename;
	CString logFilename;
	CString srcParentDir;
	CString dstParentDir;
	CString log;

	bool isError = false;

	for(int i=1; i<__argc; i++)
	{
		if(keyConfig.CompareNoCase(__targv[i]) == 0)
		{
			configFilename = __targv[++i];
		}
		else if(keyLog.CompareNoCase(__targv[i]) == 0)
		{
			logFilename = __targv[++i];
		}
		else if(keySrc.CompareNoCase(__targv[i]) == 0)
		{
			srcParentDir = __targv[++i];
		}
		else if(keyDst.CompareNoCase(__targv[i]) == 0)
		{
			dstParentDir = __targv[++i];
		}
		else
		{
			log.AppendFormat(TEXT("Unknown parameter [%s]\r\n"), __targv[i]);
			isError = true;
		}
	}

	if (configFilename.IsEmpty() == true && isExistFile(configFilename) == FALSE)
	{
		log.AppendFormat(TEXT("Config file [%s] Not found\r\n"), configFilename);
		isError = true;
	}


	if ( isError == true )
	{
		log.AppendFormat(TEXT("\r\n"));
		log.AppendFormat(TEXT("Used>\r\n"));
		log.AppendFormat(TEXT("> $s [option]\r\n"), __targv[0]);
		log.AppendFormat(TEXT("\r\n[option]\r\n"));
		log.AppendFormat(TEXT("\t-c : config file"));
		log.AppendFormat(TEXT("\t-l : log file"));
		log.AppendFormat(TEXT("\t-s : source parent directory"));
		log.AppendFormat(TEXT("\t-d : destination parent directory"));
		log.AppendFormat(TEXT("\r\n"));
		log.AppendFormat(TEXT("ex> %s -c list.cfg -l secure.log -s c:\\secure_bin -d d:\\secure_package\\binary"), __targv[0]);
	}
	else 
	{
		CopyFromConfig(configFilename, log, srcParentDir, dstParentDir);
	}

	if ( logFilename.IsEmpty() == false )
	{
		CStdioFile cf;

		cf.Open(logFilename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
		cf.WriteString(log);
		cf.Close();
	}
	else
	{

	}

	
	_tprintf(log);

	return TRUE;
}

void CCopyFileDlg::CopyFromConfig(CString &config, CString &log, LPCTSTR parentSrc, LPCTSTR parentDst)
{
    CStdioFile cf;
    CString strLine;

    cf.Open(config, CFile::modeRead);
    while(cf.ReadString(strLine))
    {
        CString strTitle;
        CString strOrgPath;
        CString strDstPath;
		CString strBuf;

		if(strLine.TrimLeft().GetAt(0) == '#') continue;

        AfxExtractSubString(strTitle, strLine, 0, ',');
        AfxExtractSubString(strOrgPath, strLine, 1, ',');
        AfxExtractSubString(strDstPath, strLine, 2, ',');

        strTitle.Trim();
        strOrgPath.Trim();
        strDstPath.Trim();

		if(strOrgPath.IsEmpty() == false && parentSrc!=NULL && parentSrc[0]!=NULL)
		{
			strBuf.Format(TEXT("%s\\%s"), parentSrc, strOrgPath);
			strOrgPath.Format(TEXT("%s"), strBuf); 
		}

		if(strDstPath.IsEmpty() == false && parentDst!=NULL && parentDst[0]!=NULL)
		{
			strBuf.Format(TEXT("%s\\%s"), parentDst, strDstPath);
			strDstPath.Format(TEXT("%s"), strBuf);
		}

        if ( strTitle.IsEmpty() || strOrgPath.IsEmpty() || strDstPath.IsEmpty() )
        {
            log.AppendFormat(TEXT("ERR List File\t%s,%s,%s"), strTitle, strOrgPath, strDstPath);
        }

        copyFileFolderToFolder(strTitle, strOrgPath, strDstPath, log);
    }
}