#ifndef _COMMON_H_
#define _COMMON_H_

#include "stdafx.h"
#include <string>
using namespace std;
typedef struct BOOKS_INFO_tag
{
    int id;
	string name;
	string author;
	string publisher;
	string year;
    string edition;
    string address;
    string filepath;
}BOOKS_INFO_t;


class Utils
{
public:
    static BOOL copyfile(LPCTSTR lpszSrc, LPCTSTR lpszDest)
    {
        return CopyFile(lpszSrc, lpszDest, FALSE);
    }
};

#endif // _COMMON_H_