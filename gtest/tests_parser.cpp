#include "gtest/gtest.h"
#include "../target/Targets.h"
#include "../parsing/Parsing.h"
#include "test_commands/test_commands.h"

TEST(TestCommand, TestDebutTraitement) {
    Targets targets(true, "Je suis une target");

    auto *parser = new Parsing(targets);
    parser->addCommand(new FinishedCommand());
    parser->addCommand(new MandatoryCommand());
    parser->addCommand(new ParamCommand());

    const char *arguments[] = {"program_name", "-h", "-m"};
    int argCount = 3;

    testing::internal::CaptureStdout();
    parser->parseInput(argCount, arguments);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output,
              "Available commands :\n- help : Display this help message\n- finished : Display finished message at the end of the execution\n- mandatory : Mandatory command\n- param : display the given parameter\n");

    delete parser;
}

TEST(TestCommand, TestInexistant) {
    Targets target(true, "");

    auto *parser = new Parsing(target);
    parser->addCommand(new FinishedCommand());
    parser->addCommand(new MandatoryCommand());
    parser->addCommand(new ParamCommand());

    const char *arguments[] = {"program_name", "-o", "-m"};
    int argCount = 3;

    ASSERT_THROW(parser->parseInput(argCount, arguments), std::runtime_error);

    delete parser;
}

TEST(TestCommand, TestFinTraitement) {
    Targets target(true, "");

    auto *parser = new Parsing(target);
    parser->addCommand(new FinishedCommand());
    parser->addCommand(new MandatoryCommand());
    parser->addCommand(new ParamCommand());

    const char *arguments[] = {"program_name", "-f", "-m"};
    int argCount = 3;

    testing::internal::CaptureStdout();
    parser->parseInput(argCount, arguments);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Finished !");

    delete parser;
}

TEST(TestCommand, TestMandatory) {
    Targets target(true, "");

    auto *parser = new Parsing(target);
    parser->addCommand(new FinishedCommand());
    parser->addCommand(new MandatoryCommand());
    parser->addCommand(new ParamCommand());

    const char *arguments[] = {"program_name", "-h"};
    int argCount = 2;

    ASSERT_THROW(parser->parseInput(argCount, arguments), std::runtime_error);

    delete parser;
}

TEST(TestCommand, TestParam) {
    Targets target(true, "");

    auto *parser = new Parsing(target);
    parser->addCommand(new FinishedCommand());
    parser->addCommand(new MandatoryCommand());
    parser->addCommand(new ParamCommand());

    const char *arguments[] = {"program_name", "-p", "testParam", "-m"};
    int argCount = 4;

    testing::internal::CaptureStdout();
    parser->parseInput(argCount, arguments);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Param : testParam\n");

    delete parser;
}

TEST(TestCommand, TestPreservation) {
    Targets target(true, "");

    auto *parser = new Parsing(target);
    parser->addCommand(new FinishedCommand());
    parser->addCommand(new MandatoryCommand());
    parser->addCommand(new ParamCommand());

    const char *arguments[] = {"program_name", "-f", "-h", "-m"};
    int argCount = 4;

    testing::internal::CaptureStdout();
    parser->parseInput(argCount, arguments);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output,
              "Available commands :\n- help : Display this help message\n- finished : Display finished message at the end of the execution\n- mandatory : Mandatory command\n- param : display the given parameter\nFinished !");

    delete parser;
}

TEST(TestCommand, TestTargetMisplaced) {
    Targets target(false, "des trucs textes");

    auto *parser = new Parsing(target);
    parser->addCommand(new FinishedCommand());
    parser->addCommand(new MandatoryCommand());
    parser->addCommand(new ParamCommand());

    const char *arguments[] = {"program_name", "-p", "testParam", "testParam2", "-m", "target"};
    int argCount = 6;

    ASSERT_THROW(parser->parseInput(argCount, arguments), std::runtime_error);

    delete parser;
}
