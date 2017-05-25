// sqlite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "DatabaseIF.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
    using namespace DataBase;
    DatabaseIF* pDatabaseIF = new DatabaseIF();
    pDatabaseIF->Connect( "file:filedb" );
    char * pstatements = "drop table mytable;";
    pDatabaseIF->Execute( pstatements );
    pstatements = "Create table mytable( name varchar2(10))";
    pDatabaseIF->Execute( pstatements );
    pstatements = "insert into mytable values('rajesh');";
    pDatabaseIF->Execute( pstatements );
    pstatements = "select * from mytable";
    pDatabaseIF->Execute( pstatements );
    pDatabaseIF->Disconnect();

    int x;
    std::cin>>x;
    return 0;
}

