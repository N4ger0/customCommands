#include <iostream>

#include "parsing/Parsing.h"
#include "commands/Command.h"

int main(const int argc, const char *argv[]) {

    Targets targets(true, "test");

    const Parsing parser(targets);

    try {
        parser.parseInput(argc, argv);
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << parser.targets() << std::endl;

}
