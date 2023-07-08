#pragma once

#include <vector>

namespace tracker::datatypes
{
template<typename Data>
class ContainerWrapper 
{
public:
    std::vector<Data> getRows()
    {
        return rows;
    }

    bool isEmpty()
    {
        return rows.empty();
    }

    std::vector<Data> rows;
};
}  // namesapce tracker::datatypes
