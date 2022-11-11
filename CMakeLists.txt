cmake_minimum_required(VERSION 3.22)
project(fgengine C)

set(CMAKE_C_STANDARD 23)

# LIBRARY

include_directories(${PROJECT_SOURCE_DIR}/Library/inc)

file(GLOB PROJECT_HEADER_FILES
        "${PROJECT_SOURCE_DIR}/library/inc/*/*.h"
        "${PROJECT_SOURCE_DIR}/library/inc/*.h"
)
file(GLOB PROJECT_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/library/src/*/*.mm"
        "${PROJECT_SOURCE_DIR}/library/src/*/*.m"
        "${PROJECT_SOURCE_DIR}/library/src/*/*.cpp"
        "${PROJECT_SOURCE_DIR}/library/src/*/*.c"
        "${PROJECT_SOURCE_DIR}/library/src/*.mm"
        "${PROJECT_SOURCE_DIR}/library/src/*.m"
        "${PROJECT_SOURCE_DIR}/library/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/library/src/*.c"
)
add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# TEST

enable_testing()
add_subdirectory(library/test)
