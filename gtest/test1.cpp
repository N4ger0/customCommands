// HARDY
// Oregan

#include "gtest/gtest.h"
#include "../target/Target.h"
#include "../parsing/Parsing.h"

TEST(TestCommand, TestDebutTraitement) {
    testing::internal::CaptureStdout() ;

    Target target;

    const auto *parser = new Parsing(target);

    char *arguments[] = {"program_name", "-h"};
    int argCount = 2;

    parser->parseInput(argCount, arguments);

    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Available commands :\n- help : Display this help message\n- finished : Display finished message at the end of the execution\n");

    delete parser;
}

TEST(TestCommand, TestInexistant) {
    Target target;

    const auto *parser = new Parsing(target);

    char *arguments[] = {"program_name", "-o"};
    int argCount = 2;

    ASSERT_THROW(parser->parseInput(argCount, arguments),std::runtime_error);

    delete parser;
}

TEST(TestCommand, TestFinTraitement) {
    testing::internal::CaptureStdout() ;

    Target target;

    const auto *parser = new Parsing(target);

    char *arguments[] = {"program_name", "-f"};
    int argCount = 2;

    parser->parseInput(argCount, arguments);

    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Finished");

    delete parser;
}
