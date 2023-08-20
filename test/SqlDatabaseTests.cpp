#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <SqlDatabase.hpp>

using tracker::database::SqlDatabase;
using namespace ::testing;

namespace tracker::ut {
class SqlDatabaseShould : public Test {
 public:
  ~SqlDatabaseShould() { std::system("rm data.db"); }
};

TEST_F(SqlDatabaseShould, CreateItself) {
  SqlDatabase db;
  EXPECT_TRUE(db.isTableAvaiable());
}

TEST_F(SqlDatabaseShould, InsertData) {
  SqlDatabase db;
  EXPECT_TRUE(db.insert("NULL, 'Nazwa', '2002-03-16', 900.9"));
}

TEST_F(SqlDatabaseShould, Return0RowCountIfNoRowsInDB) {
  SqlDatabase db;

  const auto count = db.countSelectedRows();
  ASSERT_EQ(count, 0);
}

TEST_F(SqlDatabaseShould, ReturnRowCountWithSelectedRows) {
  SqlDatabase db;
  int insertCount = 7;
  for (int i = 0; i < insertCount; i++)
    db.insert("NULL, 'Nazwa', '2002-03-16', 21.37");

  const auto count = db.countSelectedRows();
  ASSERT_EQ(count, insertCount);
}

TEST_F(SqlDatabaseShould, ReturnEmptyLocalDatabase) {
  SqlDatabase db;

  const auto localDb = db.select();
  ASSERT_TRUE(localDb->isEmpty());
  delete localDb;
}

TEST_F(SqlDatabaseShould, ReturnLocalDatabaseWithSelectedRow) {
  SqlDatabase db;
  db.insert("NULL, 'Nazwa', '2002-03-16', 21.37");

  const auto localDb = db.select();
  const auto result = localDb->getRows();

  ASSERT_EQ(result[0].name, "Nazwa");
  ASSERT_EQ(result[0].date, "2002-03-16");
  ASSERT_FLOAT_EQ(result[0].cash, 21.37);
  delete localDb;
}

TEST_F(SqlDatabaseShould, ReturnLocalDatabaseWithSelectedMultipleRows) {
  SqlDatabase db;
  db.insert("NULL, 'Nazwa1', '2002-03-16', 21.37");
  db.insert("NULL, 'Nazwa2', '2002-03-16', 20.37");
  db.insert("NULL, 'Nazwa3', '2002-03-16', 19.37");

  const auto localDb = db.select();

  ASSERT_THAT(
      localDb->getRows(),
      UnorderedElementsAre(datatypes::Row{"Nazwa1", "2002-03-16", 21.37},
                           datatypes::Row{"Nazwa2", "2002-03-16", 20.37},
                           datatypes::Row{"Nazwa3", "2002-03-16", 19.37}));
  delete localDb;
}

TEST_F(SqlDatabaseShould, InsertRowWithRowObject) {
  SqlDatabase db;
  std::vector<datatypes::Row> rows{{"N1", "2000-01-01", 4.99},
                                   {"N2", "2000-01-01", 5.99}};
  for (const auto& row : rows) db.insert(row);

  const auto localDb = db.select();

  ASSERT_THAT(localDb->getRows(), UnorderedElementsAre(rows[0], rows[1]));
  delete localDb;
}
}  // namespace tracker::ut
