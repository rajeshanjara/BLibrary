#pragma once
#include "common.h"
#include "BookValidator.h"
#include "LibraryDBAdpter.h"
#include "ImageManager.h"

class LibraryMgr
{
public:
	LibraryMgr(void);
	~LibraryMgr(void);
    bool init();
    void addBook( BOOKS_INFO_t& book )
    {
        book.filepath = ImageManager::instance().RelocateImages(book.filepath.c_str());
        BookValidator validator;
        char* pquery = query::InsertValues(book);
        m_adapter.executeQuery( pquery );
    }

    bool fetchBooks()
    {
        char* ptr = query::fetchBookTable();
        return m_adapter.executeQuery( ptr );
    }

    RecordSet getRecordSet()
    {
        return m_adapter.getRecrdSet();
    }

    std::string getErrorMsg()
    {
        return m_adapter.getErrorMsg();
    }

private:
    LibraryDBAdpter m_adapter;
};

