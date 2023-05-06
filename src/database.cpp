#include "database.hpp"

namespace db
{
Database::Database(IDatabaseSourcePtr dbSource)
    : databaseSource(dbSource) {}

void Database::insert(std::string data)
{
    databaseSource->write(data);
}

std::string Database::get(int lineNumber)
{
    return databaseSource->read(lineNumber);
}
}  // namespace db
