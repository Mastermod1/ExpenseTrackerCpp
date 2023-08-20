#pragma once

#include <string>

namespace tracker::view::state::types {
struct Field {
  std::string text = "......";
  bool isInsert = false;
};
}  // namespace tracker::view::state::types
