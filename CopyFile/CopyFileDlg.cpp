
// CopyFileDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CopyFile.h"
#include "CopyFileDlg.h"
#include "afxdialogex.h"

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


// CCopyFileDlg ��ȭ ����




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


// CCopyFileDlg �޽��� ó����

BOOL CCopyFileDlg::OnInitDialog()
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
    CString strLog = TEXT("��� ��� ������ '�α׿� ����� ���ڿ�', '�������', '�����'�� �ĸ�(,)�� ���е� Text ���� �Դϴ�.");
    SetDlgItemText(IDC_EDIT_LOG, strLog);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCopyFileDlg::OnPaint()
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
    BrInfo.lpszTitle = _T("���� ���");
    BrInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    BrInfo.lParam = (LPARAM)pszPathname;

    pidlBrowse = ::SHBrowseForFolder(&BrInfo);
    if(pidlBrowse != NULL)
    {
        // ���õ� ���� ��ξ���
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
    BrInfo.lpszTitle = _T("��� ���");
    BrInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    BrInfo.lParam = (LPARAM)pszPathname;

    pidlBrowse = ::SHBrowseForFolder(&BrInfo);
    if(pidlBrowse != NULL)
    {
        // ���õ� ���� ��ξ���
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

int CCopyFileDlg::copyFileFolderToFolder(CString strTitle, CString strOrgPath, CString strDstPath)
{
    CString strLog;

    GetDlgItemText(IDC_EDIT_LOG, strLog);

    // �������� ����� ���Ѵ�.
    CStringArray listFileOrg;
    int nCountOrg = GetFileList(strOrgPath, listFileOrg);

    // ��󿡼� ����� ���Ѵ�.
    CStringArray listFileDst;
    int nCountDst = GetFileList(strDstPath, listFileDst);

    // ��� ��Ͽ��� ���� ��ϰ� ���� ���� ������ �����Ѵ�.
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

                if ( CopyFile(srcFile, dstFile, FALSE) )
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

        strLog.Append(line);
    }

    SetDlgItemText(IDC_EDIT_LOG, strLog);

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
    SetDlgItemText(IDC_EDIT_LOG, TEXT(""));

    CString strListfile;
    GetDlgItemText(IDC_EDIT_LIST, strListfile);
    if ( isExistFile(strListfile) ) {
        CStdioFile cf;
        CString strLine;

        cf.Open(strListfile, CFile::modeRead);
        while(cf.ReadString(strLine))
        {
            CString strTitle;
            CString strOrgPath;
            CString strDstPath;

            AfxExtractSubString(strTitle, strLine, 0, ',');
            AfxExtractSubString(strOrgPath, strLine, 1, ',');
            AfxExtractSubString(strDstPath, strLine, 2, ',');

            strTitle.Trim();
            strOrgPath.Trim();
            strDstPath.Trim();

            if ( strTitle.IsEmpty() || strOrgPath.IsEmpty() || strDstPath.IsEmpty() )
            {
                CString strLog;
                GetDlgItemText(IDC_EDIT_LOG, strLog);
                strLog.AppendFormat(TEXT("ERR List File\t%s,%s,%s"), strTitle, strOrgPath, strDstPath);
                SetDlgItemText(IDC_EDIT_LOG, strLog);
            }

            copyFileFolderToFolder(strTitle, strOrgPath, strDstPath);
        }
    } 
    else 
    {
        CString strOrgPath;
        GetDlgItemText(IDC_EDIT_ORG, strOrgPath);
        strOrgPath.Trim();

        if ( strOrgPath.IsEmpty() ) {
            MessageBox(TEXT("���� ��θ� �Է��ϼ���"));
            return;
        }

        CString strDstPath;
        GetDlgItemText(IDC_EDIT_DST, strDstPath);
        strDstPath.Trim();

        if ( strDstPath.IsEmpty() ) {
            MessageBox(TEXT("��� ��θ� �Է��ϼ���"));
            return;
        }

        copyFileFolderToFolder(NULL, strOrgPath, strDstPath);
    }
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
    lpMMI->ptMinTrackSize.x = 640; //����
    lpMMI->ptMinTrackSize.y = 580; // ����

    CDialogEx::OnGetMinMaxInfo(lpMMI);
}
