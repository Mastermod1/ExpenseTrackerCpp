#pragma once

#include <string>
#include <ostream>
#include <vector>

namespace tracker::datatypes
{
struct Row
{
    std::string name = "-";
    std::string date = "1900-01-01";
    float cash = 0;

    bool operator == (const Row& rhs) const
    {
        return name == rhs.name && date == rhs.date && cash == rhs.cash;
    }

    static constexpr const char* fieldNames = "Name;Date;Cash";
};

inline std::ostream& operator << (std::ostream& os, const Row& row)
{
    return os << "Name: " << row.name << ", Date: " << row.date << ", Value: " << row.cash;
}
}  // namespace tracker::datatypes
