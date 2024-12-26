//
// Created on 29/11/2024.
// CAILLE
// PAUL
// M1 - CL
//

#include "Parsing.h"

#include <iostream>
#include <ostream>

Parsing::Parsing(const Target &targets) : commandsToParse(), targets(targets) {
    commandsToParse.push_back(new HelpCommand(*this));
    commandsToParse.push_back(new FinishedCommand());
}

std::vector<std::string> Parsing::allDescriptions() const {
    std::vector<std::string> descriptions;
    descriptions.reserve(commandsToParse.size());
    for (const Command *command: commandsToParse) {
        std::string description = "- " + command->name() + " : " + command->description();
        descriptions.push_back(description);
    }
    return descriptions;
}

void Parsing::parseInput(int argc, char *argv[]) const {
    std::vector<std::string> inputParts;
    for (int i = 1; i < argc; ++i) {
        inputParts.emplace_back(argv[i]);
    }

    if (inputParts.empty()) {
        std::cout << "No command provided. Use 'help' for a list of commands." << std::endl;
    }

    const std::string &commandName = inputParts[0];
    Command *command = findCommand(commandName);

    if (!command) {
        throw std::runtime_error("Command not recognized: " + commandName);
    }

    const std::vector<std::string> args(inputParts.begin() + 1, inputParts.end());

    if (args.size() != command->isMandatoryCommand() && args.size() != command->isMandatoryCommand() + command->
        aliases().size()) {
        throw std::runtime_error("Incorrect number of arguments for command: " + commandName);
    }

    command->setArguments(args);

    if (command->executesNow()) {
        command->execute();
    }
}

void Parsing::executeAll() const {
    for (auto *command: commandsToParse) {
        if (!command->executesNow()) {
            command->execute();
        }
    }
}

Command *Parsing::findCommand(const std::string &name) const {
    for (auto *command: commandsToParse) {
        if (command->name() == name) {
            return command;
        }
        for (const auto &alias: command->aliases()) {
            if (alias == name) {
                return command;
            }
        }
    }

    return nullptr;
}

void Parsing::addCommand(Command *command) {
    if (command == nullptr) {
        throw std::invalid_argument("Commande invalide");
    }
    commandsToParse.push_back(command);
}

Parsing::~Parsing() {
    for (const auto *command: commandsToParse) {
        delete command;
    }
}
