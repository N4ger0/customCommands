#include <iostream>

#include "parsing/Parsing.h"
#include "commands/Command.h"

int main(int argc, char *argv[]) {

    const auto *parser = new Parsing();

    parser->parseInput(argc, argv);

    delete parser;
}
