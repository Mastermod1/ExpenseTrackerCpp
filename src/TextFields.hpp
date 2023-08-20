#include <string>
#include <vector>

namespace tracker::text_fields {
struct Menu {
  const std::string title;
  const std::vector<std::string> fields;
  const int size = fields.size();
};

inline static Menu MAIN_MENU{"MENU", {"INSERT DATA", "SHOW DATABASE", "EXIT"}};
inline static Menu INSERT_MENU{"INSERT DATA",
                               {"DATE", "DESC", "VALUE", "APPLY", "BACK"}};
inline static Menu DISPLAY_MENU{"DISPLAY DATABASE", {"BACK"}};
}  // namespace tracker::text_fields
