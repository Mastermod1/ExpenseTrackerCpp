#include <Helpers/Size.hpp>

namespace tracker::helpers
{
Size::Size(int y, int x) : y{y}, x{x} {}

int Size::centeredXBy(const Size& s) { return (x - s.x) / 2; }

int Size::centeredYBy(const Size& s) { return (y - s.y) / 2; }
}  // namespace tracker::helpers
