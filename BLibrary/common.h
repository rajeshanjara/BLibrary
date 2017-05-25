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
}BOOKS_INFO_t;


#endif // _COMMON_H_