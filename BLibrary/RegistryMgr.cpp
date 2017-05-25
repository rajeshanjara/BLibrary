#include "stdafx.h"
#include "RegistryMgr.h"
#include <winreg.h>

RegistryMgr::RegistryMgr()
{
}


RegistryMgr::~RegistryMgr()
{
}


bool RegistryMgr::readRegistry(LPCTSTR lpcszKey, CString& csValue)
{
    HKEY keyHandle;
    char rgValue[1024];
    char fnlRes[1024];
    DWORD size1;
    DWORD Type;

    if( RegOpenKeyEx(HKEY_CURRENT_USER,
        L"SOFTWARE\\BLibrary\\status", 0,
        KEY_QUERY_VALUE, &keyHandle ) == ERROR_SUCCESS )
    {
        size1 = 1023;
        RegQueryValueEx( keyHandle, L"ProductStatus", NULL, &Type,
                        (LPBYTE)rgValue, &size1);
        csValue = rgValue;
        sprintf(fnlRes, "Product ID of your Windows system is:: %s", rgValue);
    }
    else
    {
        strcpy(fnlRes, "Couldn't access system information!");
        return false;
    }

    RegCloseKey(keyHandle);
    return true;
}


bool RegistryMgr::readRegistry(LPCTSTR lpcszKey, DWORD& dwValue)
{
    HKEY keyHandle;
    char rgValue[1024];
    char fnlRes[1024];
    DWORD size1;
    DWORD Type;
        if (RegOpenKeyEx(HKEY_CURRENT_USER,
            L"SOFTWARE\\BLibrary\\status", 0,
            KEY_QUERY_VALUE, &keyHandle) == ERROR_SUCCESS)
        {
            size1 = 1023;
            RegQueryValueEx(keyHandle, L"ProductStatus", NULL, &Type,
                (LPBYTE)rgValue, &size1);
            dwValue = atoi(rgValue);
            sprintf(fnlRes, "Product ID of your Windows system is:: %s", rgValue);
        }
        else {
            strcpy(fnlRes, "Couldn't access system information!");
            return false;
        }

        RegCloseKey(keyHandle);
        return true;
}


bool RegistryMgr::writeRegistry(LPCTSTR lpcszKey, LPCTSTR value)
{
    HKEY hk;
    DWORD dwDisp;
    TCHAR dwData[40];
    RegCreateKeyEx(HKEY_CURRENT_USER,
        L"SOFTWARE\\BLibrary\\status",
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &hk,
        &dwDisp);

    RegSetValueEx(hk,
        L"ProductStatus",
        0,
        REG_DWORD,
        (PBYTE)&dwData,
        sizeof(PDWORD));
    RegCloseKey(hk);
    return true;
}

bool RegistryMgr::writeRegistry(LPCTSTR lpcszKey, DWORD dvalue)
{
    HKEY hk;
    DWORD dwDisp;
    TCHAR dwData[40];
    AfxMessageBox(_T("sgdsdgs"));
    RegCreateKeyEx(HKEY_CURRENT_USER,
        L"SOFTWARE\\BLibrary\\status",
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &hk,
        &dwDisp);

    swprintf( dwData, L"%d", dvalue );

    RegSetValueEx(hk,
        L"ProductStatus",
        0,
        REG_DWORD,
        (PBYTE)&dwData,
        sizeof(PDWORD));
    RegCloseKey(hk);
    return true;
}