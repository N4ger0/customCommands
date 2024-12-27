//
// Created on 29/11/2024.
// CAILLE
// PAUL
// M1 - CL
//

#ifndef PARSING_H
#define PARSING_H
#include <vector>

#include "../commands/Command.h"
#include "../target/Targets.h"

class Parsing {
    std::vector<Command *> commandsToParse;
    Targets& targets;

public:
    Parsing(Targets& targets);

    void addCommand(Command *command);

    Command *findCommand(const std::string &name) const;

    void parseInput(int argc, const char *argv[]) const;

    void executeAll() const;

    std::vector<std::string> allDescriptions() const;

    bool checkMissingMandatory(std::vector<std::string> inputParts) const ;

    ~Parsing();
};


#endif //PARSING_H
