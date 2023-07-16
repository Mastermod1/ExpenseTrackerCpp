#pragma once

#include <string>

namespace tracker::view::state::types
{
struct Field
{
    std::string text = "......";
    bool isInsert = false;
    int row = 0;
    int col = 0;
};
}
