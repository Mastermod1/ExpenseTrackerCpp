#pragma once

namespace tracker::helpers
{
class Size
{
   public:
    Size(int y, int x);

    int centeredXBy(const Size& s);

    int centeredYBy(const Size& s);

    int y = 0;
    int x = 0;
};
}  // namespace tracker::helpers
