//
// Created on 29/11/2024.
// CAILLE / HARDY
// PAUL / OREGAN
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

std::string Command::description() const {
    std::string fullDescription;
    fullDescription += c_name;
    for (const auto &c_aliase: c_aliases) {
        fullDescription += ", ";
        fullDescription += c_aliase;
    }
    fullDescription += " : " + c_description;
    return fullDescription;
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

HelpCommand::HelpCommand(const Parsing &parser) : Command("--help", {"-h"},
                                                          0, "Display this \033[4mhelp\033[0m message", false, true),
                                                  parser(parser) {
}

void HelpCommand::execute() {
    std::cout << parser.generateUsage() << std::endl;
    std::cout << "Options:\n";

    const auto descriptions = parser.allCommandDescriptions();
    for (const auto &description: descriptions) {
        std::cout << "\t" << description << "\n";
    }
}

void HelpCommand::setArguments(const std::vector<std::string> &args) {
    if (!args.empty()) {
        throw std::runtime_error("Help command does not take arguments.");
    }
}
