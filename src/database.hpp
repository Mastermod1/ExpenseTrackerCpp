#pragma once

#include <IDatabaseSource.hpp>

namespace db
{
class Database
{
public:
    Database(IDatabaseSourcePtr dbSource);

    void insert(std::string data);
    std::string get(int lineNumber);
private:
    IDatabaseSourcePtr databaseSource;
};
}  // namespace db
