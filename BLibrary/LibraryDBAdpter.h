#pragma once

#include "../sqlite/DatabaseIF.h"
using namespace DataBase;

class LibraryDBAdpter
{
public:
	LibraryDBAdpter(void);
	~LibraryDBAdpter(void);
    bool openDB(char* pDbName_i = NULL);
    bool disconnect();
    bool executeQuery( char* pQuery_i );
    RecordSet getRecrdSet()
    {
        return m_SqLiteIF.getRecordSet();
    }

    std::string getErrorMsg()
    {
        return m_SqLiteIF.getErrorMsg();
    }

private:
    DatabaseIF m_SqLiteIF;
};

