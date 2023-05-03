#include <gtest/gtest.h>

#include "database.hpp"

TEST(DatabaseShould, Work)
{
    Database db;
    db.print();
    ASSERT_TRUE(true);
}
