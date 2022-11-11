cmake_minimum_required(VERSION 3.22)
project(test_utf C)

set(CMAKE_C_STANDARD 17)

add_executable(${PROJECT_NAME} test.c)
target_link_libraries(${PROJECT_NAME} fgengine)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
