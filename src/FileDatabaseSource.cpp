#include "FileDatabaseSource.hpp"

#include <fstream>
#include <iostream>
#include <string>

namespace db::filedb
{
FileDatabaseSource::FileDatabaseSource()
{
    std::fstream file;
    file.open("database.txt", std::fstream::out);
    file.close();
}

std::string FileDatabaseSource::read(int lineNumber)
{
    std::fstream file;
    file.open("database.txt", std::fstream::in);
    if (!file.eof())
    {
	lastLine++;
    }
    if (lineNumber > lastLine)
    {
	return "";
    }
    std::string line;
    for(int i = 0; i <= lineNumber; i++)
	std::getline(file, line);
    file.close();
    return line; 
}

void FileDatabaseSource::write(std::string data)
{
    std::fstream file;
    file.open("database.txt", std::fstream::out | std::fstream::app);
    if (file.is_open())
    {
	file << data << "\n";
    }
    file.close();
}

}  // namespace db::filedb
