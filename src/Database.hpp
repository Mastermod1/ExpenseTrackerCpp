#pragma once

#include <DataTypes/ContainerWrapper.hpp>
#include <DataTypes/Row.hpp>
#include <string>

namespace tracker::database {
class Database {
   public:
    virtual bool insert(const std::string& values) = 0;
    virtual datatypes::ContainerWrapper<datatypes::Row>* select() { return nullptr; };
    virtual void printWhole() = 0;
};
}  // namespace tracker::database
