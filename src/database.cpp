#include "database.hpp"

#include <iostream>
#include <fstream>

namespace db
{
Database::Database(IDatabaseSourcePtr dbSource)
    : databaseSource(dbSource) {}

void Database::insert(std::string data)
{
    databaseSource->write(data);
}

std::string Database::get()
{
    return databaseSource->read();
}
}  // namespace db
