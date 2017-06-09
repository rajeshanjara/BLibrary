// AddBooksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BLibrary.h"
#include "AddBooksDlg.h"
#include "afxdialogex.h"
#include <atlbase.h>

// AddBooksDlg dialog

IMPLEMENT_DYNAMIC(AddBooksDlg, CDialogEx)

AddBooksDlg::AddBooksDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddBooksDlg::IDD, pParent)
{

}

AddBooksDlg::~AddBooksDlg()
{
}

void AddBooksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddBooksDlg, CDialogEx)
    ON_BN_CLICKED(IDCANCEL2, &AddBooksDlg::OnBnClickedCancel2)
    ON_BN_CLICKED(IDOK2, &AddBooksDlg::OnBnClickedOk2)
    ON_BN_CLICKED(IDC_BROWSE_IMG, &AddBooksDlg::OnBnClickedBrowseImg)
END_MESSAGE_MAP()


// AddBooksDlg message handlers


void AddBooksDlg::OnBnClickedCancel2()
{
    CDialogEx::OnCancel();
}

// add books
void AddBooksDlg::OnBnClickedOk2()
{
    clear();
    CString str;
    GetDlgItem( IDC_NAME_EDIT )->GetWindowText( str );
    LPWSTR pstr = (LPWSTR)(LPCTSTR)str;
    USES_CONVERSION;
    m_stBooksDetails.name = W2A(pstr);
    GetDlgItem( IDC_AUTHOR_EDIT)->GetWindowText( str );
    pstr = (LPWSTR)(LPCTSTR)str;
    m_stBooksDetails.author = W2A(pstr);
    GetDlgItem( IDC_PUBLISHER_EDIT )->GetWindowText( str );
    pstr = (LPWSTR)(LPCTSTR)str;
    m_stBooksDetails.publisher = W2A(pstr);
    GetDlgItem(IDC_EDIT4)->GetWindowText(str);
    pstr = (LPWSTR)(LPCTSTR)str;
    m_stBooksDetails.year = W2A(pstr);
    GetDlgItem(IDC_EDIT5)->GetWindowText(str);
    pstr = (LPWSTR)(LPCTSTR)str;
    m_stBooksDetails.edition = W2A(pstr);
    GetDlgItem(IDC_EDIT6)->GetWindowText(str);
    pstr = (LPWSTR)(LPCTSTR)str;
    m_stBooksDetails.address = W2A(pstr);
    GetDlgItem(IDC_EDIT7)->GetWindowText(str);
    pstr = (LPWSTR)(LPCTSTR)str;
    m_stBooksDetails.filepath = W2A(pstr);
    CDialogEx::OnOK();
}


void AddBooksDlg::OnBnClickedBrowseImg()
{
    CFileDialog cfd(TRUE, _T("jpg"), _T("JPEG Images"), OFN_FILEMUSTEXIST,
        _T("Photo Files (*.jpg)|*.jpg|*.PNG||"), this);
    cfd.DoModal();
    CString str = cfd.GetFolderPath() + _T( "\\" ) +cfd.GetFileName();
    USES_CONVERSION;
    LPWSTR pstr = (LPWSTR)(LPCTSTR)str;
    m_stBooksDetails.filepath = W2A(pstr);
    GetDlgItem(IDC_EDIT7)->SetWindowText(str);
}
