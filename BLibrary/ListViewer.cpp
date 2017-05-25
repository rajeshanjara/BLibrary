// ListViewer.cpp : implementation file
//

#include "stdafx.h"
#include "BLibrary.h"
#include "ListViewer.h"


// ListViewer

IMPLEMENT_DYNAMIC(ListViewer, CListCtrl)

ListViewer::ListViewer() : m_bColumnsCreated( false )
{

}

ListViewer::~ListViewer()
{
}

BEGIN_MESSAGE_MAP(ListViewer, CListCtrl)
END_MESSAGE_MAP()

void ListViewer::setRecordSet(RecordSet recordset)
{
    m_RecordSet = recordset;
}

void ListViewer::refresh()
{
    // check for isdirty
    if (!m_bColumnsCreated)
    {
        CreateHeader(m_RecordSet.getColumHeader());
        m_bColumnsCreated = true;
    }
    // Fill rows
    DeleteAllItems();
    for (int i = 0; i < m_RecordSet.count(); ++i)
    {
        FillRows(m_RecordSet.getRow(i));
    }

}


void ListViewer::FillRows(Record row)
{
    // id
    int id = row.getInt(0);
    USES_CONVERSION;
    WCHAR wstr[10] = { 0 };
    int index = InsertItem(0, _itow( id, wstr, 10));
        

    // name
    char* ptrName = row.getString(1);
    LPCTSTR lptrName = A2W(ptrName);
    SetItemText(index, 1, lptrName);

    // author
    char* ptrAuthor = row.getString(2);
    LPCTSTR lptrAuthor = A2W(ptrAuthor);
    SetItemText(index, 2, lptrAuthor);

    char *ptr = row.getString(3);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 3, lptrAuthor);

    ptr = row.getString(4);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 4, lptrAuthor);

    ptr = row.getString(5);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 5, lptrAuthor);

    ptr = row.getString(6);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 6, lptrAuthor);
}

void ListViewer::CreateHeader(Record columns)
{
    for (int i = 0; i < (int)columns.size(); ++i)
    {
        char* ptr = columns.getString(i);
        USES_CONVERSION;
        LPCTSTR lptr = A2W(ptr);
        InsertColumn(i, (LPCTSTR) lptr, LVCFMT_LEFT, 90);
    }
}