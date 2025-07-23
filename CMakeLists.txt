cmake_minimum_required(VERSION 3.31)
project(budget_manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-stdlib=libc++)
    link_libraries(-lc++ -lc++abi)
endif()

add_executable(budget_manager main.cpp parser.cpp budget_manager.cpp)
