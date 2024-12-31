cmake_minimum_required(VERSION 3.29.6)
project(customCommands)

set(CMAKE_CXX_STANDARD 17)

add_library(customCommands STATIC
        commands/Command.cpp
        target/Targets.cpp
        parsing/Parsing.cpp
)
