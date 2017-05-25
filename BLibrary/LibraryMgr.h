#pragma once
#include "common.h"
#include "BookValidator.h"
#include "LibraryDBAdpter.h"
class LibraryMgr
{
public:
	LibraryMgr(void);
	~LibraryMgr(void);
    bool init();
    void addBook( BOOKS_INFO_t& book )
    {
        BookValidator validator;
      //  validator.BookExists(book);
        char* pquery = query::InsertValues(book);
        m_adapter.executeQuery( pquery );
    }

    bool fetchBooks()
    {
        char* ptr = query::fetchBookTable();
        m_adapter.executeQuery( ptr );
        return true;
    }

    RecordSet getRecordSet()
    {
        return m_adapter.getRecrdSet();
    }

private:
    LibraryDBAdpter m_adapter;
};

