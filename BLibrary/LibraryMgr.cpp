#include "StdAfx.h"
#include "LibraryMgr.h"
#include "LibraryDBAdpter.h"
#include "RegistryMgr.h"
LibraryMgr::LibraryMgr(void)
{
}


LibraryMgr::~LibraryMgr(void)
{
    m_adapter.disconnect();
}

bool LibraryMgr::init()
{
    // init db
    RegistryMgr mgr;
    DWORD dwValue = 0;
    mgr.readRegistry(_T("ProductStatus"), dwValue);
    if (dwValue == 1)
    {
        m_adapter.openDB("");
    }
    else
    {
        // new App
        mgr.writeRegistry(_T("ProductStatus"), 1 );
        m_adapter.openDB("");
        char* ptr = NULL;
        // Remove old table if exists
        ptr = query::dropBookTable();
        m_adapter.executeQuery( ptr );
        ptr = query::createBookTable();
        m_adapter.executeQuery(ptr);
    }
    return true;
}
