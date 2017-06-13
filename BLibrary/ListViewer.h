#pragma once
#include "common.h"
#include "../sqlite/DatabaseIF.h"
#include "ThumbnailView.h"

using namespace DataBase;

// ListViewer

class ListViewer : public CListCtrl
{
	DECLARE_DYNAMIC(ListViewer)

public:
	ListViewer();
	virtual ~ListViewer();
    void setRecordSet(RecordSet);
    void refresh();
    void CreateHeader(/*Record columns*/);
    void FillRows(Record row);
    void createimagelist();
    void AddImage(Record& row);

protected:
    //{{AFX_MSG(CMyTreeView)
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    afx_msg void OnContextMenu(CWnd*, CPoint point);
    void ShowPopupMenu( CPoint& point );

private:
    RecordSet m_RecordSet;
    bool m_bColumnsCreated;
    CImageList m_myImageList;
    ThumbnailView* m_pThumbnailView;
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


