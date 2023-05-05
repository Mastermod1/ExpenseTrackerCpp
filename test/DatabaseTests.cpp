#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <unistd.h>

#include "IDatabaseSource.hpp"
#include "database.hpp"

using namespace ::testing;

namespace db::ut
{

class DatabaseSourceMock : public db::IDatabaseSource
{
public:
    MOCK_METHOD(void, write, (std::string), (override));
    MOCK_METHOD(std::string, read, (), (override));
};

class DatabaseShould : public ::testing::Test
{
public:
    DatabaseShould() : sut(dbSource) {}

    std::shared_ptr<DatabaseSourceMock> dbSource = std::make_shared<DatabaseSourceMock>();
    db::Database sut;
};


TEST_F(DatabaseShould, ReadFromDatabase)
{   
    const std::string sampleDbReturn = "ROW";

    EXPECT_CALL(*dbSource, read()).WillOnce(Return(sampleDbReturn));
    EXPECT_EQ(sut.get(), sampleDbReturn);
}

TEST_F(DatabaseShould, WriteToDatabase)
{
    const std::string sampleDbInsert = "DATA";

    EXPECT_CALL(*dbSource, write(sampleDbInsert)).Times(1);
    sut.insert(sampleDbInsert);
}
}  // namespace db::ut
