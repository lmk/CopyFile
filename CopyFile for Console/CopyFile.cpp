// CopyFile for Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CopyFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

bool appMain(int argc, TCHAR* argv[]);
bool IsExistFile(CString filename);
void CopyFromConfig(CString &config, CString &log, LPCTSTR parentSrc, LPCTSTR parentDst);
CString GetStateLog(CString strTitle, int status, CString dstFile, CString dstText);
int CopyFileFolderToFolder(CString strTitle, CString strOrgPath, CString strDstPath, CString &log);
int GetFileList(CString strOrgPath, CStringArray &listFile);
CString GetFileInfo(CString filePath);
CString FormatErrorMessage(DWORD ErrorCode, CString &sMsg);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			if (appMain(argc, argv) == true)
			{
				nRetCode = 0;
			}
			else 
			{
				nRetCode = 1;

				_tprintf(TEXT("\n"));
				_tprintf(TEXT("Used>\n"));
				_tprintf(TEXT("> %s [option]\n"), argv[0]);
				_tprintf(TEXT("\n[option]\n"));
				_tprintf(TEXT("\t-c : config file\n"));
				_tprintf(TEXT("\t-l : log file\n"));
				_tprintf(TEXT("\t-s : source parent directory\n"));
				_tprintf(TEXT("\t-d : destination parent directory\n"));
				_tprintf(TEXT("\n"));
				_tprintf(TEXT("ex> %s -c list.cfg -l secure.log -s c:\\secure_bin -d d:\\secure_package\\binary\n"), argv[0]);
			}
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

bool appMain(int argc, TCHAR* argv[])
{
	if(argc == 1) return false;

	CString keyConfig("-c"), keyLog("-l"), keySrc("-s"), keyDst("-d");
	CString configFilename;
	CString logFilename;
	CString srcParentDir;
	CString dstParentDir;
	CString log;

	bool isError = false;

	for(int i=1; i<argc; i++)
	{
		if(keyConfig.CompareNoCase(argv[i]) == 0)
		{
			configFilename = argv[++i];
		}
		else if(keyLog.CompareNoCase(argv[i]) == 0)
		{
			logFilename = argv[++i];
		}
		else if(keySrc.CompareNoCase(argv[i]) == 0)
		{
			srcParentDir = argv[++i];
		}
		else if(keyDst.CompareNoCase(argv[i]) == 0)
		{
			dstParentDir = argv[++i];
		}
		else
		{
			log.AppendFormat(TEXT("Unknown parameter [%s]\n"), argv[i]);
			isError = true;
		}
	}

	if (configFilename.IsEmpty() == true && IsExistFile(configFilename) == false)
	{
		log.AppendFormat(TEXT("Config file [%s] Not found\n"), configFilename);
		isError = true;
	}

	if ( isError == true ) return false;

	CopyFromConfig(configFilename, log, srcParentDir, dstParentDir);

	if ( logFilename.IsEmpty() == false )
	{
		CStdioFile cf;

		cf.Open(logFilename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
		cf.WriteString(log);
		cf.Close();
	}

	_tprintf(log);

	return true;
}

bool IsExistFile(CString filename)
{
   WIN32_FIND_DATA         findFileData = {0,};

    HANDLE hFind = FindFirstFile(filename, &findFileData);
    if ( hFind == INVALID_HANDLE_VALUE) return false;
    FindClose(FindClose);

    if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
        !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
    {
        return true;
    }

    return false;
}

void CopyFromConfig(CString &config, CString &log, LPCTSTR parentSrc, LPCTSTR parentDst)
{
    CStdioFile cf;
    CString strLine;

    cf.Open(config, CFile::modeRead);
    while(cf.ReadString(strLine))
    {
        CString strTitle;
        CString strOrgPath;
        CString strDstPath;
		CString strDstText;
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
			strDstText.Format(TEXT("%s"), strDstPath);
			strBuf.Format(TEXT("%s\\%s"), parentDst, strDstPath);
			strDstPath.Format(TEXT("%s"), strBuf);
		}

        if ( strTitle.IsEmpty() || strOrgPath.IsEmpty() || strDstPath.IsEmpty() )
        {
            log.AppendFormat(TEXT("ERR List File\t%s,%s,%s"), strTitle, strOrgPath, strDstPath);
        }

		if ( IsExistFile(strDstPath) == true )
		{
			int status = 0; // 0:pass, 1:copy success, 2: copy fail
            if ( CopyFile(strOrgPath, strDstPath, FALSE) )
            {
                status = 1;
            } else 
            {
                status = 2;
            }

			CString line = GetStateLog(strTitle, status, strDstPath, strDstText);
			log.Append(line);
		}
		else 
		{
			CopyFileFolderToFolder(strTitle, strOrgPath, strDstPath, log);
		}
    }
}

// 0:pass, 1:copy success, 2: copy fail
CString GetStateLog(CString strTitle, int status, CString dstFile, CString dstText)
{
    CString line;
    CString info = GetFileInfo(dstFile);
	CString errMsg;
    switch(status)
    {
    case 1:  
        line.Format(TEXT("[%s]\t %s \t %s \t %s\r\n"), TEXT("Success"), strTitle, info, dstText); 
        break;
    case 2:  
		FormatErrorMessage(GetLastError(), errMsg);
        line.Format(TEXT("[%s]\t %s \t %s \t %s - %s")
                    , TEXT("Fail"), strTitle, info, dstText
                    , errMsg ); 
        break;
    default: 
        line.Format(TEXT("[%s]\t %s \t %s \t %s\r\n"), TEXT("Pass"), strTitle, info, dstText); 
        break;
    }

    return line;
}

int CopyFileFolderToFolder(CString strTitle, CString strOrgPath, CString strDstPath, CString &log)
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

        CString line = GetStateLog(strTitle, status, dstFile, listFileDst.GetAt(d));
        log.Append(line);
    }

    return listFileDst.GetCount();
}

int GetFileList(CString strOrgPath, CStringArray &listFile)
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

CString GetFileInfo(CString filePath)
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

CString FormatErrorMessage(DWORD ErrorCode, CString& sMsg)
{
    TCHAR   *pMsgBuf = NULL;
    DWORD   nMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, ErrorCode, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        reinterpret_cast<LPTSTR>(&pMsgBuf), 0, NULL);
    if (!nMsgLen)
	{
        sMsg.Format(TEXT("(%d)"), ErrorCode);
	}
	else
	{
		sMsg.Format(TEXT("(%d) %s"), ErrorCode, pMsgBuf );
	}
	
    LocalFree(pMsgBuf);
    return sMsg;
}