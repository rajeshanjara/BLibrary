#include "StdAfx.h"
#include "windows.h"
#include "DatabaseImpl.h"

namespace DataBase
{
    /*input param, total rows count, row value, column name*/
static int callback(void * pIn_Param, int argc, char **argv, char **azColName)
{
    RecordSet* pRecordSet = (RecordSet*) pIn_Param;
    if( NULL == pRecordSet )
    {
        // Invalid case
    }

    Record Colrecord, row;
    int i;
    for(i=0; i<argc; i++)
    {
        char* ptr = new char[255];
        memset( ptr, 0, 255 );
        if (azColName[i] != 0)
            memcpy( ptr, azColName[i], strlen(azColName[i]));
        Colrecord.add( i, ptr );
        ptr = new char[255];
        //store value
        memset( ptr, 0, 255 );
        if( argv[i] != 0 )
            memcpy( ptr, argv[i], strlen(argv[i]));
        row.add( i, ptr );
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    pRecordSet->setColumnHeader( Colrecord );
    pRecordSet->add( 0, row );


    printf("\n");
    return 0;
}

typedef int (*Sqlite3_open)( const char *filename,   /* Database filename (UTF-8) */
							 sqlite3 **ppDb          /* OUT: SQLite db handle */);
typedef char (*Sqlite3_errmsg)( sqlite3* );
typedef int (*Sqlite3_exec)(  sqlite3*,                                  /* An open database */
							  const char *sql,                           /* SQL to be evaluated */
							  int (*callback)(void*,int,char**,char**),  /* Callback function */
							  void *,                                    /* 1st argument to callback */
							  char **errmsg                              /* Error msg written here */);

typedef int (*Sqlite3_close)(sqlite3*);
typedef void (*Sqlite3_free)(void*);

Sqlite3_open sqlite3_open;
Sqlite3_errmsg sqlite3_errmsg;
Sqlite3_exec sqlite3_exec;
Sqlite3_close sqlite3_close;
Sqlite3_free sqlite3_free;

/*Record class*/
template<class T>
void Record::add( int Id, T value )
{
    m_ItemsMap[Id] = (void*) value;
}


int Record::getInt(int nIndex_i){
    int val = -1;
    if( nIndex_i > -1 && nIndex_i + 1 <= m_ItemsMap.size())
    {
        void* pVal = (m_ItemsMap[nIndex_i]);
        char* fptr = (char*) pVal;
        val = atoi(fptr);
    }
    return val;
}
char* Record::getString(int nIndex_i){
    char* ptr = 0;
    if( nIndex_i > -1 && nIndex_i + 1 <= m_ItemsMap.size())
    {
        void* pVal = (m_ItemsMap[nIndex_i]);
        ptr = (char*) pVal;
    }
    return ptr;
}
float Record::getReal(int nIndex_i){
    float val = 0;
    if( nIndex_i > -1 && nIndex_i + 1 <= m_ItemsMap.size())
    {
        void* pVal = (m_ItemsMap[nIndex_i]);
        float* fptr = (float*) pVal;
        val = *fptr;
    }
    return val;
}
byte* Record::getBinary(int nIndex_i){
    byte* val = 0;
    if( nIndex_i > -1 && nIndex_i + 1 <= m_ItemsMap.size())
    {
        void* pVal = (m_ItemsMap[nIndex_i]);
        val = (byte*) pVal;
    }
    return val;
}



/*Ends Record class*/

/* RecordSet class*/

void RecordSet::add( int nIndex, Record& value )
{
    int count = m_RecordsMap.size();
    m_RecordsMap[count] = value;
}

Record RecordSet::getRow(int nRowIndex_i)
{
    if( !m_RecordsMap.empty())
    {
        return m_RecordsMap[nRowIndex_i];
    }
    Record rc;
    return rc;
}


void RecordSet::setColumnHeader(Record& record)
{
    m_ColumnTypes = record;
}

/* Ends RecordSet class*/






DatabaseImpl::DatabaseImpl(void)
{
}


DatabaseImpl::~DatabaseImpl(void)
{
}

bool DatabaseImpl::Connect( const char* pszDBName_i )
{
    char *zErrMsg = 0;
    int rc;
	m_hSQLiteModule = LoadLibrary( "sqlite3.dll" );
	if( 0 == m_hSQLiteModule )
	{
		return false;
	}

    sqlite3_open =  (Sqlite3_open) GetProcAddress( m_hSQLiteModule, "sqlite3_open" ) ;

    rc = sqlite3_open("file:filedb", &m_hConnection);
    if( rc ){
		sqlite3_errmsg =  (Sqlite3_errmsg) GetProcAddress( m_hSQLiteModule, "sqlite3_errmsg" ) ;
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_hConnection));
      sqlite3_close(m_hConnection);
      return( true);
    }

    return true;
}

bool DatabaseImpl::Execute( const char* pszQuery_i )
{
    m_RecordSet.clear();
    char *zErrMsg = 0;
    int rc;
    sqlite3_exec =  (Sqlite3_exec) GetProcAddress( m_hSQLiteModule, "sqlite3_exec" ) ;
    rc = sqlite3_exec( m_hConnection, pszQuery_i, &callback, (void*) &m_RecordSet, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free = (Sqlite3_free) GetProcAddress( m_hSQLiteModule, "sqlite3_free" ) ;
      sqlite3_free(zErrMsg);
    }

    return true;
}

bool DatabaseImpl::Disconnect()
{
    sqlite3_close = (Sqlite3_close) GetProcAddress( m_hSQLiteModule, "sqlite3_close" ) ;
    sqlite3_close( m_hConnection );

    return true;
}


Record DatabaseImpl::getColumnTypes( const char* pTableName_i )
{
    char query[255] = {0};
    Record record;
    sprintf( query, "PRAGMA table_info(%s);", pTableName_i );
    if( Execute( query ))
    {
        if( m_RecordSet.count() > 0 )
        {
            record = m_RecordSet.getRow( 0 );
            return record;
        }
    }
    return record;
}
}