
// CopyFileDlg.h : 헤더 파일
//

#pragma once

// CCopyFileDlg 대화 상자
class CCopyFileDlg : public CDialogEx
{
// 생성입니다.
public:
	CCopyFileDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COPYFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    BOOL isExistFile(CString filename);
    BOOL isExistDir(CString dirname);
    int copyFileFolderToFolder(CString strTitle, CString strOrgPath, CString strDstPath, CString &log);
    CString FormatErrorMessage(DWORD ErrorCode);
    CString getFileInfo(CString filePath);

	BOOL CheckCommandParameter();
	void CopyFromConfig(CString &config, CString &log, LPCTSTR parentSrc, LPCTSTR parentDst);

public:
    afx_msg void OnBnClickedButtonOrg();
    afx_msg void OnBnClickedButtonDst();
    afx_msg void OnBnClickedOk();

    int GetFileList(CString strOrgPath, CStringArray &listFile);
    afx_msg void OnBnClickedButtonList();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
