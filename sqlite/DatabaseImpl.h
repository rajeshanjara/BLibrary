#ifndef _DATABASE_IMPL_H_
#define _DATABASE_IMPL_H_

#include "sqlite3.h"
#include "windows.h"
#include <map>

namespace DataBase
{
    typedef char DATA_TYPE;
    typedef DATA_TYPE* DATA_TYPE_PTR;
    const DATA_TYPE SQLITE_TYPES[][10] =
    {
        {"INTEGER"}, {"REAL"}, {"BLOB"}, {"TEXT"}
    };

    /* contains a single row of table result*/
    class Record
    {
    public:
        template<class T>
        void add( int Id, T value );
        size_t size() { return m_ItemsMap.size(); }
        int getInt(int nIndex_i);
        char* getString(int nIndex_i);
        float getReal(int nIndex_i);
        byte* getBinary(int nIndex_i);

    private:
        
        std::map<int, void*> m_ItemsMap;
    };


    class RecordSet
    {
    public:
        void add( int nIndex, Record& value );
        Record getRow(int nRowIndex_i);
        Record getColumHeader() { return m_ColumnTypes; }
        void setColumnHeader(Record& record);
        DATA_TYPE_PTR getColumnType( int nColumnId);
        int count()
        {
            return (int) m_RecordsMap.size();
        }
        void clear()
        {
            m_RecordsMap.clear();
        }

    private:
        std::map<int, Record> m_RecordsMap;
        Record m_ColumnTypes;
    };

class DatabaseImpl
{
public:
    DatabaseImpl(void);
    ~DatabaseImpl(void);

    bool Connect( const char* pszDBName_i );
    bool Execute( const char* pszQuery_i );
    bool Disconnect();
    RecordSet getRecordSet()
    {
        return m_RecordSet;
    }
    Record getColumnTypes( const char* pTableName_i );

private:

    sqlite3* m_hConnection;
    HMODULE m_hSQLiteModule;
    RecordSet m_RecordSet;
};
}

#endif

