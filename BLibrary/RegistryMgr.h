#pragma once
class RegistryMgr
{
public:
    RegistryMgr();
    ~RegistryMgr();
    bool readRegistry(LPCTSTR lpcszKey, CString& );
    bool readRegistry(LPCTSTR lpcszKey, DWORD&);
    bool writeRegistry(LPCTSTR lpcszKey, LPCTSTR value);
    bool writeRegistry(LPCTSTR lpcszKey, DWORD dvalue);
};

