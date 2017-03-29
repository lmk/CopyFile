
// CopyFileDlg.h : ��� ����
//

#pragma once

// CCopyFileDlg ��ȭ ����
class CCopyFileDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCopyFileDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COPYFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
