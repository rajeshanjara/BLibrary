
// BLibraryDlg.h : header file
//

#pragma once
#include "LibraryMgr.h"
#include "afxcmn.h"
#include "ListViewer.h"

// CBLibraryDlg dialog
class CBLibraryDlg : public CDialogEx
{
// Construction
public:
	CBLibraryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BLIBRARY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();

    LibraryMgr m_LibraryMgr;
    ListViewer m_BooksListCtrl;
    
};
