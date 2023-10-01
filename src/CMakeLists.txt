set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_libraries(${BINARY}_run sqlite3)
target_link_libraries(${BINARY}_run menu)
target_link_libraries(${BINARY}_run form)
target_link_libraries(${BINARY}_run ncurses)
