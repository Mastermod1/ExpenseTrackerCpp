#pragma once

#include <Database.hpp>
#include <sqlite3.h>

namespace tracker::database
{
class SqlDatabase : public Database
{
public:
    SqlDatabase();
    
    bool insert(const std::string& values);
    bool insert(const datatypes::Row& row);
    void printWhole();
    datatypes::ContainerWrapper<datatypes::Row>* select();
    int countSelectedRows();
    bool isTableAvaiable();
    
private:
    sqlite3* db;
    bool isTableGood = false;
    std::string tableName = "EXPENSES";
    std::string databaseFileName = "data.db";
};
}  // namespace tracker::database
