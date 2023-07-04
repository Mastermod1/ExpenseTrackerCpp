#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <sqlite3.h>

namespace tracker::ut
{
struct Row
{
    float cash = 0;
};

struct LocalDataBase
{
    LocalDataBase(int rowCount) : size(rowCount)
    {
        rows = new Row[size];
    }

    ~LocalDataBase()
    {
        delete [] rows;
    }

    int getLastId()
    {
        return lastItemId;
    }

    void incrementLastId()
    {
        lastItemId++;
    }

    Row* getRows()
    {
        return rows;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int size = 0;
    int lastItemId = 0;
    Row* rows;
};

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

    LocalDataBase* select()
    {
        std::string query = "SELECT * FROM " + tableName;
        
        LocalDataBase* localDb = new LocalDataBase(countSelectedRows()); 

        int exit = sqlite3_open(databaseFileName.c_str(), &db);
        const auto callback = []([[maybe_unused]]void* data, int argc, char** argv, [[maybe_unused]]char** azColName){ 
            LocalDataBase* localDb = (LocalDataBase*)data;
            for(int i = 0; i < argc; i++)
            {
                if(i == 3)
                    (localDb->getRows())[localDb->getLastId()].cash = std::stof(argv[i]);
            }
            localDb->incrementLastId();
            return 0;
        };

        if(exit)
            std::cout << "ERROR on opening";

        exit = sqlite3_exec(db, query.c_str(), callback, (void*)localDb, NULL);

        sqlite3_close(db);

        return localDb;
    }

    int countSelectedRows()
    {
        std::string countQuery = "SELECT COUNT(*) FROM " + tableName;
        
        int* count = new int(0);
        int exit = sqlite3_open(databaseFileName.c_str(), &db);
        const auto callback = [](void* data, int argc, char** argv, [[maybe_unused]]char** azColName){ 
            if(argc != 0)
                *((int*)data) = std::stoi(argv[0]);
            return 0;
        };

        if(exit)
            std::cout << "ERROR on opening";

        exit = sqlite3_exec(db, countQuery.c_str(), callback, (void*)count, NULL);

        sqlite3_close(db);
        
        int tmp = *count;
        delete count;

        return tmp;
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

class DatabaseWrapperShould : public ::testing::Test
{
public:
    ~DatabaseWrapperShould()
    {
        std::system("rm data.db");
    }
};

TEST_F(DatabaseWrapperShould, CreateItself)
{
    Database db;
    EXPECT_TRUE(db.isTableAvaiable());
}

TEST_F(DatabaseWrapperShould, InsertData)
{
    Database db;
    EXPECT_TRUE(db.insert("NULL, 'Nazwa', '2002-03-16', 900.9"));
}

TEST_F(DatabaseWrapperShould, Return0RowCountIfNoRowsInDB)
{
    Database db;

    const auto count = db.countSelectedRows();
    ASSERT_EQ(count, 0);
}

TEST_F(DatabaseWrapperShould, ReturnRowCountWithSelectedRows)
{
    Database db;
    db.insert("NULL, 'Nazwa', '2002-03-16', 21.37");
    db.insert("NULL, 'Nazwa', '2002-03-16', 1.0");
    db.insert("NULL, 'Nazwa', '2002-03-16', 1.0");
    db.insert("NULL, 'Nazwa', '2002-03-16', 1.0");
    db.insert("NULL, 'Nazwa', '2002-03-16', 1.0");
    db.insert("NULL, 'Nazwa', '2002-03-16', 1.0");
    db.insert("NULL, 'Nazwa', '2002-03-16', 1.0");

    const auto count = db.countSelectedRows();
    ASSERT_EQ(count, 7);
}

TEST_F(DatabaseWrapperShould, ReturnEmptyLocalDatabase)
{
    Database db;

    const auto localDb = db.select();
    ASSERT_TRUE(localDb->isEmpty());
    delete localDb;
}

TEST_F(DatabaseWrapperShould, ReturnLocalDatabaseWithSelectedRow)
{
    Database db;
    db.insert("NULL, 'Nazwa', '2002-03-16', 21.37");

    const auto localDb = db.select();
    ASSERT_FLOAT_EQ(localDb->getRows()[0].cash, 21.37);
    delete localDb;
}
}  // namesapce tracker::ut
