project(ExpenseTracker)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wunused -std=c++1z -l sqlite3)

include_directories(src)

add_subdirectory(src)
add_subdirectory(lib/googletest)
add_subdirectory(test)

# CMake configuration: https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html
