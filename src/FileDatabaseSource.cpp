#include "FileDatabaseSource.hpp"

#include <fstream>
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
    if (lineNumber > lineCount)
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
	lineCount++;
    }
    file.close();
}

unsigned FileDatabaseSource::getLineCount()
{
    return lineCount;
}
}  // namespace db::filedb
