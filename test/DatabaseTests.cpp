#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "IDatabaseSource.hpp"
#include "database.hpp"

using namespace ::testing;

namespace db::ut
{

class DatabaseSourceMock : public db::IDatabaseSource
{
public:
    MOCK_METHOD(void, write, (std::string), (override));
    MOCK_METHOD(std::string, read, (int), (override));
};

class DatabaseShould : public Test
{
public:
    DatabaseShould() : sut(dbSource) {}

    std::shared_ptr<DatabaseSourceMock> dbSource = std::make_shared<DatabaseSourceMock>();
    db::Database sut;
};


TEST_F(DatabaseShould, ReadFromDatabase)
{   
    const std::string sampleDbReturn = "ROW";

    EXPECT_CALL(*dbSource, read(_)).WillOnce(Return(sampleDbReturn));
    EXPECT_EQ(sut.get(0), sampleDbReturn);
}

TEST_F(DatabaseShould, WriteToDatabase)
{
    const std::string sampleDbInsert = "DATA";

    EXPECT_CALL(*dbSource, write(sampleDbInsert)).Times(1);
    sut.insert(sampleDbInsert);
}
}  // namespace db::ut
