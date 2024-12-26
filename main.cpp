#include <iostream>

#include "parsing/Parsing.h"
#include "commands/Command.h"

int main(int argc, char *argv[]) {
    Target target;

    const auto *parser = new Parsing(target);

    parser->parseInput(argc, argv);

    delete parser;
}
