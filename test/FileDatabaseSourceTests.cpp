#include "FileDatabaseSource.hpp"

#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace ::testing;

namespace db::filedb::ut
{
class FileDatabaseSourceShould : public Test
{
    void TearDown() override
    {
        std::system("rm database.txt");
    }
};

TEST_F(FileDatabaseSourceShould, CreateFile)
{
    FileDatabaseSource dbSource;
    std::fstream checkedFile;
    checkedFile.open("database.txt", std::fstream::out); 
    EXPECT_TRUE(checkedFile.good());
    checkedFile.close();
}

TEST_F(FileDatabaseSourceShould, WriteToFile)
{
    FileDatabaseSource dbSource;
    dbSource.write("100;200;100");
    
    std::fstream checkedFile;
    checkedFile.open("database.txt", std::fstream::in); 
    std::string line;
    std::getline(checkedFile, line);

    EXPECT_EQ(line, "100;200;100");
}

TEST_F(FileDatabaseSourceShould, WriteTwoLinesToFile)
{
    FileDatabaseSource dbSource;
    dbSource.write("100;200;100");
    dbSource.write("100;300;100");
    
    std::fstream checkedFile;
    checkedFile.open("database.txt", std::fstream::in); 
    std::string line;

    std::getline(checkedFile, line);
    EXPECT_EQ(line, "100;200;100");
    std::getline(checkedFile, line);
    EXPECT_EQ(line, "100;300;100");
}

TEST_F(FileDatabaseSourceShould, ReadLineFromEmptyFile)
{
    FileDatabaseSource dbSource;
    
    EXPECT_EQ(dbSource.read(0), "");
}

TEST_F(FileDatabaseSourceShould, ReadLineFromOneLineFile)
{
    FileDatabaseSource dbSource;
    dbSource.write("100;200;100");
    
    EXPECT_EQ(dbSource.read(0), "100;200;100");
}

TEST_F(FileDatabaseSourceShould, ReadLineFromManyLineFile)
{
    FileDatabaseSource dbSource;
    dbSource.write("100;200;100");
    dbSource.write("100;300;100");
    dbSource.write("100;400;100");
    
    EXPECT_EQ(dbSource.read(0), "100;200;100");
    EXPECT_EQ(dbSource.read(1), "100;300;100");
    EXPECT_EQ(dbSource.read(2), "100;400;100");
}

TEST_F(FileDatabaseSourceShould, ReturnNothingWhenEofIsReached)
{
    FileDatabaseSource dbSource;
    dbSource.write("100;200;100");
    
    EXPECT_EQ(dbSource.read(0), "100;200;100");
    EXPECT_EQ(dbSource.read(1), "");
    EXPECT_EQ(dbSource.read(2), "");
}

TEST_F(FileDatabaseSourceShould, ReturnNothingWhenNegativeLineNumberIsGiven)
{
    FileDatabaseSource dbSource;
    dbSource.write("100;200;100");
    
    EXPECT_EQ(dbSource.read(-1), "");
}

TEST_F(FileDatabaseSourceShould, Return0ForEmptyFile)
{
    FileDatabaseSource dbSource;

    EXPECT_EQ(dbSource.getLineCount(), 0);
}


TEST_F(FileDatabaseSourceShould, ReturnRaiseLineCountOnWrite)
{
    FileDatabaseSource dbSource;
    dbSource.write("100;200;100");
    dbSource.write("100;200;100");

    EXPECT_EQ(dbSource.getLineCount(), 2);
}

TEST_F(FileDatabaseSourceShould, EnableIteratingOverWholeFile)
{
    FileDatabaseSource dbSource;
    std::vector<std::string> lines{"100;200;100", "100;300;100", "100;400;100"};
    dbSource.write(lines[0]);
    dbSource.write(lines[1]);
    dbSource.write(lines[2]);

    for(int i = 0; i < dbSource.getLineCount(); i++)
    {
        EXPECT_EQ(dbSource.read(i), lines[i]);
    }
}
}  // namespace db::filedb::ut

