// HARDY
// Oregan

#include "gtest/gtest.h"
#include "../target/Target.h"
#include "../parsing/Parsing.h"

TEST(TestCommand, TestHelp) {
    testing::internal::CaptureStdout() ;

    Target target;

    const auto *parser = new Parsing(target);

    char *arguments[] = {"program_name", "-h"};
    int argCount = 2;

    parser->parseInput(argCount, arguments);

    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Available commands :\n- help : Display this help message\n");

    delete parser;
}

TEST(TestCommand, TestInexistant) {
    Target target;

    const auto *parser = new Parsing(target);

    char *arguments[] = {"program_name", "-o"};
    int argCount = 2;
    try {
        parser->parseInput(argCount, arguments);
    } catch (const std::exception &e) {
        ASSERT_THROW("Command not recognized: -o",std::runtime_error);
    }

    delete parser;
}
