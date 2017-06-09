// ListViewer.cpp : implementation file
//

#include "stdafx.h"
#include "BLibrary.h"
#include "ListViewer.h"
#include "ImageManager.h"

// ListViewer

IMPLEMENT_DYNAMIC(ListViewer, CListCtrl)

ListViewer::ListViewer() : m_bColumnsCreated( false )
{
    createimagelist();
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
        CreateHeader(/*m_RecordSet.getColumHeader()*/);
        m_bColumnsCreated = true;
    }
    // Fill rows
    DeleteAllItems();
    // Clear image list
    m_myImageList.DeleteImageList();
    createimagelist();

    for (int i = 0; i < m_RecordSet.count(); ++i)
    {
        Record& record = m_RecordSet.getRow(i);
        FillRows( record );
    }

}


void ListViewer::FillRows(Record row)
{
    // Icon
    int id = row.getInt(0);
    USES_CONVERSION;
    WCHAR wstr[10] = { 0 };
    int index = InsertItem(0, NULL, id - 1);
    SetColumnWidth(0, 35);

    // id
    SetItemText(index, 1, (LPCTSTR)_itow(id, wstr, 10));

    // name
    const char* ptrName = row.getString(1);
    LPCWSTR lptrName = A2W(ptrName);
    SetItemText(index, 2, (LPCTSTR)lptrName);

    // author
    const char* ptrAuthor = row.getString(2);
    LPCWSTR lptrAuthor = A2W(ptrAuthor);
    SetItemText(index, 3, (LPCTSTR)lptrAuthor);

    const char *ptr = row.getString(3);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 4, (LPCTSTR)lptrAuthor);

    ptr = row.getString(4);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 5, (LPCTSTR)lptrAuthor);

    ptr = row.getString(5);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 6, (LPCTSTR)lptrAuthor);

    ptr = row.getString(6);
    lptrAuthor = A2W(ptr);
    SetItemText(index, 7, (LPCTSTR)lptrAuthor);

    AddImage(row);
}


void ListViewer::createimagelist()
{
    SIZE size = ImageManager::instance().getImageDimension(ICON);
    m_myImageList.Create(size.cx, size.cy, ILC_COLOR24 | ILC_MASK, 8, 1);
}


void ListViewer::AddImage(Record& row)
{
    BLimage<icon> iconimage;
    const char* ptrName = row.getString(7);
    if (ImageManager::instance().loadImage(ptrName, iconimage))
    {
        HBITMAP hbitmap = iconimage.getbitmap();
        CBitmap bm;
        bm.Attach(hbitmap);
        m_myImageList.Add(&bm, RGB(255, 255, 255));
        CImageList* pValid = SetImageList(&m_myImageList, LVSIL_SMALL);
        pValid = SetImageList(&m_myImageList, LVSIL_NORMAL);
    }
}


void ListViewer::CreateHeader(/*Record columns*/)
{
    /*InsertColumn( 0, _T(""), LVCFMT_LEFT, 0);
    for (int i = 0; i < (int)columns.size(); ++i)
    {
        const char* ptr = columns.getString(i);
        USES_CONVERSION;
        LPCWSTR lptr = A2W(ptr);
        InsertColumn(i + 1, (LPCTSTR) lptr, LVCFMT_LEFT, 90);
    }*/

    InsertColumn(0, _T(" "), LVCFMT_LEFT, 32);
    CString csColumn(_T(""));
    for (int i = 0; i < sizeof(BOOK_TBL_COLUMS)/ sizeof(BOOK_TBL_COLUMS[0]); ++i)
    {
        csColumn = BOOK_TBL_COLUMS[i];
        InsertColumn(i + 1, csColumn, LVCFMT_LEFT, 90);
    }
}
