#include "StdAfx.h"
#include "DatabaseIF.h"
namespace DataBase
{
DatabaseIF::DatabaseIF(void)
{
    m_pDatabaseImpl = new DatabaseImpl;
}

DatabaseIF::~DatabaseIF(void)
{
    delete m_pDatabaseImpl;
}

bool DatabaseIF::Connect( const char* pszDBName_i )
{
    return m_pDatabaseImpl->Connect( pszDBName_i );
}

bool DatabaseIF::Execute( const char* pszQuery_i )
{
    return m_pDatabaseImpl->Execute( pszQuery_i );
}

bool DatabaseIF::Disconnect()
{
    return m_pDatabaseImpl->Disconnect();
}
}