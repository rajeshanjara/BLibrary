#pragma once
#include "common.h"
#include "../sqlite/DatabaseIF.h"
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
	DECLARE_MESSAGE_MAP()

private:
    RecordSet m_RecordSet;
    bool m_bColumnsCreated;
    CImageList m_myImageList;
};


