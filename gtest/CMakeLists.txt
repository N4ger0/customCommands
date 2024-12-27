# 'Google_test' is the subproject name
project(gtest)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run tests_parser.cpp
)
add_library(parsing ../parsing/Parsing.cpp)
add_library(commands ../commands/Command.cpp
        test_commands/test_commands.cpp
        test_commands/test_commands.h)
add_library(target ../target/Targets.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main parsing commands target)

