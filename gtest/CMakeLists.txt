# 'Google_test' is the subproject name
project(gtest)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run test1.cpp
)
add_library(parsing ../parsing/Parsing.cpp)
add_library(commands ../commands/Command.cpp)
add_library(target ../target/Target.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main parsing commands target)

