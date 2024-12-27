#include <iostream>

#include "parsing/Parsing.h"
#include "commands/Command.h"
#include "gtest/test_commands/test_commands.h"

int main(const int argc, const char *argv[]) {

    Targets targets(true, "test");

    auto *parser = new Parsing(targets);

    try {
        parser->parseInput(argc, argv);
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }


    delete parser;
}
