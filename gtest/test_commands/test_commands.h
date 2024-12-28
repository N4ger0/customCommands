//
// Created on 27/12/2024.
// CAILLE
// PAUL
// M1 - CL
//

#ifndef TEST_COMMANDS_H
#define TEST_COMMANDS_H
#include <vector>
#include "../../commands/Command.h"

class FinishedCommand : public Command {
public:
    FinishedCommand();

    void setArguments(const std::vector<std::string> &args) override;

    void execute() override;
};

class MandatoryCommand : public Command {
public:
    MandatoryCommand();

    void setArguments(const std::vector<std::string> &args) override;

    void execute() override;
};

class ParamCommand : public Command {
    std::string param;

public:
    ParamCommand();

    void setArguments(const std::vector<std::string> &args) override;

    void execute() override;
};


#endif //TEST_COMMANDS_H
