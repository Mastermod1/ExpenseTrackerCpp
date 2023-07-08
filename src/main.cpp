#include "DataTypes/Row.hpp"
#include "SqlDatabase.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <thread>
#include <iomanip>
#include <chrono>

#if __linux__
    #define CLEAR "clear"
#else
    #define CLEAR "cls"
#endif

using namespace std::chrono_literals;

void clearConsole()
{
    std::system(CLEAR);
}

std::string fieldNameParser(const char* fieldNames, const int ith)
{
    std::string result = "";
    int occurences = -1;
    for(int i = 0; fieldNames[i] != '\0'; i++)
    {
	if(fieldNames[i] == ';')
	{
	    occurences++;
	    if(ith == occurences)
		return result;
	    result = "";
	}
	else
	{
	    result += fieldNames[i];
	}
    }
    return result;
}

bool menu(tracker::database::Database& db)
{
    std::cout << "----MENU----\n"; 
    std::cout << "  1. Add expense\n";
    std::cout << "  2. Show raport\n";
    std::cout << "  3. Exit\n";
    
    int option = 0;
    std::cin >> option;

    if (option != 1 and option != 2)
    {
	return false;
    }

    if (option == 1)
    {
	// for(int i = 0; i < 101; i++)
	// {
	//     std::cout << "|" << std::left << std::setw(100) << std::string(i, '-') << "|" << i << "%" << std::flush;
	//     std::cout << std::string(100 + 6, '\b');
	//     std::this_thread::sleep_for(500ms);
	// }
	std::vector<std::string> params;
	std::string xd = "XD";
	for(int i = 0; i < 3; i++)
	{
	    std::string str;
	    printf("Please insert %s:\n", fieldNameParser(tracker::datatypes::Row::fieldNames, i).c_str());
	    std::cin >> str;
	    params.push_back(str);
	}
	db.insert("NULL, '" + params[0] + "', '" + params[1] + "', " + params[2]);
    }

    if (option == 2)
    {
	db.printWhole();
	std::this_thread::sleep_for(9500ms);
    }

    return true;
}

int main()
{
    tracker::database::SqlDatabase db;
    clearConsole();
    while(menu(db))
    {
	clearConsole();
    }
}
