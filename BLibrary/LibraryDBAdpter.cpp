#include "StdAfx.h"
#include "LibraryDBAdpter.h"


LibraryDBAdpter::LibraryDBAdpter(void)
{
}


LibraryDBAdpter::~LibraryDBAdpter(void)
{
    m_SqLiteIF.Disconnect();
}

bool LibraryDBAdpter::openDB(char* pDbName_i /* = NULL */)
{
    return m_SqLiteIF.Connect( pDbName_i );
}

bool LibraryDBAdpter::disconnect()
{
    return m_SqLiteIF.Disconnect();
}

bool LibraryDBAdpter::executeQuery( char* pQuery_i )
{
    return m_SqLiteIF.Execute(pQuery_i);
}
