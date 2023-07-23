set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gmock)
target_link_libraries(${BINARY} PRIVATE sqlite3)
target_link_libraries(${BINARY} PRIVATE menu)
target_link_libraries(${BINARY} PRIVATE form)
target_link_libraries(${BINARY} PRIVATE ncurses)
