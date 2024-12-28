//
// Created on 27/12/2024.
// CAILLE
// PAUL
// M1 - CL
//

#include "test_commands.h"

#include <iostream>
#include "../../commands/Command.h"

FinishedCommand::FinishedCommand() : Command("finished", {"--finished","-f"},
                                             0, "Display finished message at the end of the execution", false, false) {
}

void FinishedCommand::execute() {
    std::cout << "Finished !";
}

void FinishedCommand::setArguments(const std::vector<std::string> &args) {
    if (!args.empty()) {
        throw std::runtime_error("Help command does not take arguments.");
    }
}

MandatoryCommand::MandatoryCommand() : Command("mandatory", {"--mandatory", "-m"},
                                               0, "Mandatory command", true, true) {
}

void MandatoryCommand::execute() {
}

void MandatoryCommand::setArguments(const std::vector<std::string> &args) {
    if (!args.empty()) {
        throw std::runtime_error("Help command does not take arguments.");
    }
}

ParamCommand::ParamCommand() : Command("param", {"--param", "-p"}, 1, "display the given parameter", false, true
) {
}

void ParamCommand::setArguments(const std::vector<std::string> &args) {
    this->param = args.at(0);
}

void ParamCommand::execute() {
    std::cout << "Param : " << this->param << "\n";
}
