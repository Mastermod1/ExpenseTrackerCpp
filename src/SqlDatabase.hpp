#pragma once

#include <Database.hpp>
#include <Sqlite3/Sqlite3Wrapper.hpp>

namespace tracker::database {
class SqlDatabase : public Database {
   public:
    SqlDatabase();

    bool insert(const std::string& values) override;
    bool insert(const datatypes::Row& row);
    void printWhole() override;
    datatypes::ContainerWrapper<datatypes::Row>* select() override;
    int countSelectedRows();
    bool isTableAvaiable();

   private:
    sqlite3_wrapper::Sqlite3Wrapper db;
    bool isTableGood = false;
    std::string tableName = "EXPENSES";
    std::string databaseFileName = "data.db";
};
}  // namespace tracker::database
