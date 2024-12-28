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
    std::vector<Command *> p_commandsToParse;
    Targets &p_targets;

    Command *findCommand(const std::string &name) const;

    void executeAll() const;

    bool checkMissingMandatory(const std::vector<std::string> &inputParts) const;

public:
    explicit Parsing(Targets &targets);

    void addCommand(Command *command);

    void parseInput(int argc, const char *argv[]) const;

    std::vector<std::string> allDescriptions() const;

    bool hasCommand(const std::string &name) const;

    const Targets &targets() const;

    ~Parsing();
};


#endif //PARSING_H
