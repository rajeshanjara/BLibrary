#pragma once
#include "DatabaseImpl.h"
namespace DataBase
{
class DatabaseIF
{
public:
    DatabaseIF(void);
    ~DatabaseIF(void);

    bool Connect( const char* pszDBName_i );
    bool Execute( const char* pszQuery_i );
    RecordSet getRecordSet()
    {
        return m_pDatabaseImpl->getRecordSet();
    }
    bool Disconnect();

private:
    DatabaseImpl* m_pDatabaseImpl;
};
}
