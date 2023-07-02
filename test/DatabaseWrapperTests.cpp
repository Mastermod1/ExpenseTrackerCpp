#include <gtest/gtest.h>
#include <iostream>
#include <sqlite3.h>

namespace tracker::ut
{
class Database
{
public:
    Database()
    {
        std::string tableQuery = "CREATE TABLE IF NOT EXISTS " + tableName + "("
                                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "NAME TEXT NOT NULL, "
                                 "DATE DATE NOT NULL, "
                                 "VALUE REAL NOT NULL);";

        char* errMsg;
        int exit = sqlite3_open(databaseFileName.c_str(), &db);
        exit = sqlite3_exec(db, tableQuery.c_str(), NULL, 0, &errMsg);

        if(exit != SQLITE_OK)
        {
            std::cerr << "Error: Could not open database and create table\n";
            sqlite3_free(errMsg);
        }
        else
        {
            isTableGood = true;
        }
        sqlite3_close(db);
    }

    bool insert(std::string values)
    {
        std::string insertQuery = "INSERT INTO " + tableName + " VALUES(" + values + ")";

        char* errMsg;
        int exit = sqlite3_open(databaseFileName.c_str(), &db);
        exit = sqlite3_exec(db, insertQuery.c_str(), NULL, 0, &errMsg); 
        if(exit != SQLITE_OK)
        {
            std::cerr << "Error on insert: " << insertQuery << "\n" << sqlite3_errmsg(db) << "\n";
            sqlite3_free(errMsg);
        }

        sqlite3_close(db);
        return exit == SQLITE_OK;
    }
    
    void printWhole()
    {
        std::string query = "SELECT * FROM " + tableName;

        int exit = sqlite3_open(databaseFileName.c_str(), &db);
        const auto callback = []([[maybe_unused]] void* data, int argc, char** argv, char** azColName){ 
            for(int i = 0; i < argc; i++)
                std::printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "-");
            return 0;
        };

        if(exit)
            std::cout << "ERROR on opening";

        exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);

        sqlite3_close(db);
    }

    bool isTableAvaiable()
    {
        return isTableGood;
    }

    ~Database()
    {
    }
private:
    sqlite3* db;
    bool isTableGood = false;
    std::string tableName = "EXPENSES";
    std::string databaseFileName = "data.db";
};

TEST(DatabaseShould, CreateItself)
{
    Database db;
    EXPECT_TRUE(db.isTableAvaiable());
}

TEST(DatabaseShould, InsertData)
{
    Database db;
    EXPECT_TRUE(db.insert("NULL, 'Nazwa', '2002-03-16', 900.9"));

    db.printWhole();
}

}  // namesapce tracker::ut
