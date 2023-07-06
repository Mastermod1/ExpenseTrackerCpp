#include <string>
#include <DataTypes/ContainerWrapper.hpp>

namespace tracker::database
{
class Database
{
public:
    virtual bool insert(const std::string& values) = 0;
    // Remove dynamic polymorphism by using impl database
    // template<typename Data>
    // virtual datatypes::ContainerWrapper<Data>* select() { return nullptr; };
};
}  // namespace tracker::database
