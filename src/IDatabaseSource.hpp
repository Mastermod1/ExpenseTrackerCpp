#pragma once

#include <memory>
#include <string>

namespace db
{
class IDatabaseSource
{
public:
    virtual std::string read() = 0;
    virtual void write(std::string) = 0;

    virtual ~IDatabaseSource() = default;
};

using IDatabaseSourcePtr = std::shared_ptr<IDatabaseSource>;
}
