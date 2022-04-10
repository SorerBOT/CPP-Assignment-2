cmake_minimum_required(VERSION 3.21)
project(Assignment2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment2 main.cpp Account.cpp Account.h Bank.cpp Bank.h Person.cpp Person.h Transaction.cpp Transaction.h)
