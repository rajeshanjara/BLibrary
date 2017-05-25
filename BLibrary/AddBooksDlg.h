#pragma once
#include "common.h"

// AddBooksDlg dialog

class AddBooksDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddBooksDlg)

public:
	AddBooksDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddBooksDlg();
    void GetBooksDetails( BOOKS_INFO_t& stBook_o )
    {
        stBook_o = m_stBooksDetails;
    }

    void clear()
    {
        m_stBooksDetails.id = -1;
        m_stBooksDetails.name.clear();
        m_stBooksDetails.author.clear();
        m_stBooksDetails.publisher.clear();
    }

// Dialog Data
	enum { IDD = IDD_ADDBOOKSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
    BOOKS_INFO_t m_stBooksDetails;
public:
    afx_msg void OnBnClickedCancel2();
    afx_msg void OnBnClickedOk2();
    afx_msg void OnBnClickedBrowseImg();
};
