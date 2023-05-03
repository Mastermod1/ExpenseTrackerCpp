#include <iostream>
#include <stdlib.h>
#include <fstream>

#if __linux__
    #define CLEAR "clear"
#else
    #define CLEAR "cls"
#endif

void clearConsole()
{
    std::system(CLEAR);
}

bool menu()
{
    std::cout << "----MENU----\n"; 
    std::cout << "  1. Add expense\n";
    std::cout << "  2. Show raport\n";
    std::cout << "  3. Exit\n";
    
    int option = 0;
    std::cin >> option;

    if (option == 3)
    {
	return false;
    }
    return true;
}

int main()
{
    clearConsole();
    while(menu())
    {
	clearConsole();
    }
}
