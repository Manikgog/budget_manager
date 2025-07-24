cmake_minimum_required(VERSION 3.31)
project(budget_manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(budget_manager main.cpp parser.cpp budget_manager.cpp)
