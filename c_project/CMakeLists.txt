cmake_minimum_required(VERSION 3.10)

project(c_project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

add_executable(app
    src/main.c
    src/logger.c
    src/utils.c
    src/sort.c
)

target_compile_options(app PRIVATE -Wall -Wextra)

add_executable(test_utils
    tests/test_utils.c
    src/utils.c
)

target_compile_options(test_utils PRIVATE -Wall -Wextra)
target_include_directories(test_utils PRIVATE include)