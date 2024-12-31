cmake_minimum_required(VERSION 3.29.6)
project(customCommands)

set(CMAKE_CXX_STANDARD 17)

add_executable(customCommands main.cpp
        commands/Command.cpp
        commands/Command.h
        target/Targets.cpp
        target/Targets.h
        parsing/Parsing.cpp
        parsing/Parsing.h
)
