#pragma once
#include "common.h"
#include "LibraryDBAdpter.h"

class query
{
public:
    static char* InsertValues( BOOKS_INFO_t& book )
    {
        char* ptr = new char[255];
        memset( ptr, 0, 255 );
        sprintf( ptr, "INSERT INTO booktbl VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s');", book.name.c_str(), book.author.c_str(), book.publisher.c_str(), book.year.c_str(), book.edition.c_str(), book.address.c_str());
        return ptr;
    }

    static char* createBookTable()
    {
        return "CREATE TABLE booktbl( id integer PRIMARY KEY AUTOINCREMENT, name text, author text, publisher text, year text, edition text, address text);";
    }

    static char* dropBookTable()
    {
        return "DROP TABLE booktbl;";
    }

    static char* fetchBookTable()
    {
        return "select * from booktbl;";
    }
};

class BookValidator
{
public:
	BookValidator(void);
	~BookValidator(void);
    void BookExists( BOOKS_INFO_t book )
    {
        LibraryDBAdpter adapter;
        adapter.openDB("");
        char* pquery = query::InsertValues(book);
        adapter.executeQuery( pquery );
    }
};

