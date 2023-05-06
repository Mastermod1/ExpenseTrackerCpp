#pragma once

#include <fstream>
#include "IDatabaseSource.hpp"

namespace db::filedb
{
class FileDatabaseSource : public IDatabaseSource
{
public:
    FileDatabaseSource();

    std::string read(int lineNumber) override;
    void write(std::string data) override;
private:
    unsigned lastLine = 0;
};

}  // namespace db::filedb
