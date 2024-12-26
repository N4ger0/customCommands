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
#include "../target/Target.h"

class Parsing {
    std::vector<Command *> commandsToParse;
    Target targets;

public:
    Parsing(const Target &targets);

    void addCommand(Command *command);

    Command *findCommand(const std::string &name) const;

    void parseInput(int argc, char *argv[]) const;

    void executeAll() const;

    std::vector<std::string> allDescriptions() const;

    bool checkMissingMandatory() const ;

    ~Parsing();
};


#endif //PARSING_H
