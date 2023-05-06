#pragma once

#include <memory>
#include <string>

namespace db
{
class IDatabaseSource
{
public:
    virtual std::string read(int lineNumber) = 0;
    virtual void write(std::string data) = 0;

    virtual ~IDatabaseSource() = default;
};

using IDatabaseSourcePtr = std::shared_ptr<IDatabaseSource>;
}
