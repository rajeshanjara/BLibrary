// ListViewer.cpp : implementation file
//
#pragma warning (disable:4005)

#include "stdafx.h"
#include "BLibrary.h"
#include "ListViewer.h"
#include "ImageManager.h"

// ListViewer

IMPLEMENT_DYNAMIC(ListViewer, CListCtrl)

ListViewer::ListViewer() : m_bColumnsCreated( false )
{
    createimagelist();
    m_pThumbnailView = new ThumbnailView;
    m_pThumbnailView->SetOwner(this);
    m_pThumbnailView->CreateEx( WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        AfxRegisterWndClass(NULL,0,0,0), L"",
        WS_POPUP | WS_BORDER, 0, 0, 100, 100, NULL, NULL);
    m_pThumbnailView->SetLayeredWindowAttributes(RGB(0,0,0), 255*0.8, LWA_ALPHA);
}


ListViewer::~ListViewer()
{

}

BEGIN_MESSAGE_MAP(ListViewer, CListCtrl)
    ON_WM_CONTEXTMENU()
    ON_WM_MOUSEMOVE()
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


void ListViewer::OnRButtonDown(UINT nFlags, CPoint point)
{
        UINT uFlags;
    int htItem = HitTest(point, &uFlags);
    if ((htItem != NULL) && (uFlags & TVHT_ONITEM)) {
       // Select(htItem, TVGN_DROPHILITE);
    }
}


void ListViewer::OnContextMenu(CWnd* pWnd, CPoint point)
{
    UINT uFlags;
    CPoint ptTree = point;
    ScreenToClient(&ptTree);
    int htItem = HitTest(ptTree, &uFlags);
    if ( htItem >=0 && (uFlags & TVHT_ONITEM)) {
        ShowPopupMenu( point );
    }
    else
        CListCtrl::OnContextMenu(pWnd, point);
}


void ListViewer::ShowPopupMenu( CPoint& point )
{
    if (point.x == -1 && point.y == -1){
        //keystroke invocation
        CRect rect;
        GetClientRect(rect);
        ClientToScreen(rect);
        point = rect.TopLeft();
        point.Offset(5, 5);
    }
    CMenu menu;
    VERIFY(menu.LoadMenu(IDR_MENU1));
    CMenu* pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);
    CWnd* pWndPopupOwner = this;
    while (pWndPopupOwner->GetStyle() & WS_CHILD)
        pWndPopupOwner = pWndPopupOwner->GetParent();
    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
        pWndPopupOwner);
}

void ListViewer::OnMouseMove(UINT nFlags, CPoint point)
{
   int Index = HitTest(point);
   CRect rect;
   GetItemRect( Index, &rect, LVIR_ICON  );
   if(  rect.PtInRect( point))
   {
       ClientToScreen(&point);
       BLimage<thumbnail> iconimage;
       m_pThumbnailView->MoveWindow(point.x, point.y, iconimage.getimagesize().cx, iconimage.getimagesize().cy);
       CString itemtext = GetItemText(Index, 1);
       int Id = _wtoi(itemtext);
       const char* ptrName = NULL;
       for (int i = 0; i < m_RecordSet.count(); ++i)
       {
           if (Id == m_RecordSet.getRow(i).getInt(0))
           {
               // Get the image path
               ptrName = m_RecordSet.getRow(i).getString(7);
           }
       }

       // Need to optimize creating imaged at evey mouse move
       if (ImageManager::instance().loadImage(ptrName, iconimage))
       {
           HBITMAP hbitmap = iconimage.getbitmap();
           CDC* pDC = m_pThumbnailView->GetDC();
           HDC hDC = CreateCompatibleDC(pDC->m_hDC);
           HBITMAP Old = (HBITMAP) ::SelectObject( hDC, (HBITMAP) hbitmap);
           BitBlt(pDC->m_hDC, 0, 0, iconimage.getimagesize().cx, iconimage.getimagesize().cy,
               hDC, 0, 0, SRCCOPY);
           ::SelectObject(hDC, (HBITMAP) Old);
           DeleteObject(hbitmap);
           DeleteObject(hDC);
           m_pThumbnailView->ReleaseDC(pDC);
       }

       m_pThumbnailView->ShowWindow(SW_SHOW);
   }
   else
   {
       m_pThumbnailView->ShowWindow(SW_HIDE);
   }

    CListCtrl::OnMouseMove(nFlags, point);
}
