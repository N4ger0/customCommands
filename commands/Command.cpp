//
// Created on 29/11/2024.
// CAILLE
// PAUL
// M1 - CL
//

#include "Command.h"
#include "../parsing/Parsing.h"

#include <iostream>

Command::Command(const std::string &name, const std::vector<std::string> &aliases, const size_t nbOfArguments,
                 const std::string &description, const bool isMandatory, const bool activateImmediately) : c_name(name),
    c_aliases(aliases), c_nbOfArguments(nbOfArguments)
    , c_description(description), c_isMandatory(isMandatory), c_activateImmediately(activateImmediately) {
}


const std::string &Command::name() const {
    return c_name;
}

const std::string &Command::description() const {
    return c_description;
}

const std::vector<std::string> &Command::aliases() const {
    return c_aliases;
}

bool Command::isMandatoryCommand() const {
    return c_isMandatory;
}

bool Command::executesNow() const {
    return c_activateImmediately;
}

std::size_t Command::nbArguments() const {
    return c_nbOfArguments;
}

HelpCommand::HelpCommand(const Parsing &parser) : Command("help", {"-h", "--help"},
                                                          0, "Display this help message", false, true), parser(parser) {
}

void HelpCommand::execute() {
    std::cout << "Available commands :\n";
    const auto descriptions = parser.allDescriptions();
    for (const auto &description: descriptions) {
        std::cout << description << "\n";
    }
}

void HelpCommand::setArguments(const std::vector<std::string> &args) {
    if (!args.empty()) {
        throw std::runtime_error("Help command does not take arguments.");
    }
}

FinishedCommand::FinishedCommand() : Command("finished", {"-f", "--finished"},
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

MandatoryCommand::MandatoryCommand() : Command("mandatory", {"-m", "--mandatory"},
                                                          0, "Mandatory command", true, true) {
}

void MandatoryCommand::execute() {
}

void MandatoryCommand::setArguments(const std::vector<std::string> &args) {
    if (!args.empty()) {
        throw std::runtime_error("Help command does not take arguments.");
    }
}

ParamCommand::ParamCommand() : Command("param", {"-p", "--param"}, 1, "display the given parameter", false, true
    ){}

void ParamCommand::setArguments(const std::vector<std::string> &args) {
    this->param = args.at(0);
}

void ParamCommand::execute() {
    std::cout << "Param : " << this->param << "\n";
}