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
    USES_CONVERSION;
    m_stBooksDetails.name = W2A(str);
    GetDlgItem( IDC_AUTHOR_EDIT)->GetWindowText( str );
    m_stBooksDetails.author = W2A(str);
    GetDlgItem( IDC_PUBLISHER_EDIT )->GetWindowText( str );
    m_stBooksDetails.publisher = W2A(str);
    GetDlgItem(IDC_EDIT4)->GetWindowText(str);
    m_stBooksDetails.year = W2A(str);
    GetDlgItem(IDC_EDIT5)->GetWindowText(str);
    m_stBooksDetails.edition = W2A(str);
    GetDlgItem(IDC_EDIT6)->GetWindowText(str);
    m_stBooksDetails.address = W2A(str);
    CDialogEx::OnOK();
}
