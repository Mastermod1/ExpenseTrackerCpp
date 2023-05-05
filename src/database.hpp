#pragma once

#include <fstream>
#include <memory>
#include <IDatabaseSource.hpp>

namespace db
{
class Database
{
public:
    Database(IDatabaseSourcePtr dbSource);

    void insert(std::string data);
    std::string get();
private:
    IDatabaseSourcePtr databaseSource;
};
}  // namespace db
