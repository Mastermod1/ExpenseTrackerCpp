#include <sqlite3.h>
#include <DataTypes/Row.hpp>
#include <Database.hpp>
#include <string>
#include <iostream>

namespace tracker::database
{
class SqlDatabase : public Database
{
public:
    SqlDatabase()
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

    bool insert(const std::string& values)
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

    bool insert(const datatypes::Row& row)
    {
        return insert("NULL, '" + row.name + "', '" + row.date + "', " + std::to_string(row.cash));
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

    template <typename Data>
    datatypes::ContainerWrapper<Data>* select()
    {
        std::string query = "SELECT * FROM " + tableName;
        
        datatypes::ContainerWrapper<Data>* localDb = new datatypes::ContainerWrapper<Data>(); 

        int exit = sqlite3_open(databaseFileName.c_str(), &db);
        const auto callback = []([[maybe_unused]]void* data, [[maybe_unused]]int argc, char** argv, [[maybe_unused]]char** azColName){ 
            datatypes::ContainerWrapper<Data>* localDb = (datatypes::ContainerWrapper<Data>*)data;
            localDb->rows.push_back({argv[1], argv[2], std::stof(argv[3])});
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

    ~SqlDatabase()
    {
    }
private:
    sqlite3* db;
    bool isTableGood = false;
    std::string tableName = "EXPENSES";
    std::string databaseFileName = "data.db";
};
}  // namespace tracker::database
