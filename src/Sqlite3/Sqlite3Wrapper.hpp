#pragma once

#include <sqlite3.h>

namespace tracker::database::sqlite3_wrapper
{
class Sqlite3Wrapper
{
   public:
    operator sqlite3*() { return impl; }

    operator sqlite3**() { return &impl; }

   private:
    sqlite3* impl;
};
}  // namespace tracker::database::sqlite3_wrapper
