//
// Created on 29/11/2024.
// CAILLE
// PAUL
// M1 - CL
//

#include "Parsing.h"

#include <iostream>
#include <ostream>

Parsing::Parsing(Targets &targets) : p_commandsToParse(), p_targets(targets) {
    p_commandsToParse.push_back(new HelpCommand(*this));
}

std::vector<std::string> Parsing::allDescriptions() const {
    std::vector<std::string> descriptions;
    descriptions.reserve(p_commandsToParse.size());
    for (const Command *command: p_commandsToParse) {
        std::string description = command->description();
        descriptions.push_back(description);
    }
    return descriptions;
}

void Parsing::parseInput(const int argc, const char *argv[]) const {
    std::vector<std::string> inputParts;

    exename = argv[0] ;

    for (int i = 1; i < argc; ++i) {
        inputParts.emplace_back(argv[i]);
    }

    if (inputParts.empty()) {
        std::cout << "No command provided\n" << std::endl;
        Command* command = p_commandsToParse.back();
        command->execute();
        return;
    }

    if (checkMissingMandatory(inputParts)) {
        throw std::runtime_error("Mandatory command not found.");
    }

    std::vector<std::pair<Command *, std::vector<std::string> > > deferredCommands;

    for (size_t i = 0; i < inputParts.size(); ++i) {
        const std::string &commandName = inputParts[i];

        if (commandName.empty() || commandName[0] == '-') {
            Command *command = findCommand(commandName);

            if (!command) {
                throw std::runtime_error("Command not recognized: " + commandName);
            }

            std::vector<std::string> args;

            if (command->nbArguments() > 0) {
                size_t numArgsCollected = 0;

                while (i + 1 < inputParts.size() && inputParts[i + 1][0] != '-') {
                    args.push_back(inputParts[++i]);
                    numArgsCollected++;
                    if (numArgsCollected == command->nbArguments()) {
                        break;
                    }
                }

                if (numArgsCollected != command->nbArguments()) {
                    throw std::runtime_error("Incorrect number of arguments for command: " + commandName);
                }
            }

            command->setArguments(args);

            if (command->executesNow()) {
                command->execute();
            } else {
                deferredCommands.emplace_back(command, args);
            }
        } else {
            p_targets.addTarget(commandName);
            while (i + 1 < inputParts.size()) {
                if (inputParts[i + 1][0] == '-') {
                    throw std::runtime_error("Misplaced target : " + inputParts[i]);
                }
                p_targets.addTarget(inputParts[++i]);
            }
        }
    }

    for (const auto &[command, args]: deferredCommands) {
        command->setArguments(args);
        command->execute();
    }

    if (p_targets.empty() && !p_targets.canBeEmpty()) {
        throw std::runtime_error("Targets cannot be empty.");
    }
}

bool Parsing::hasCommand(const std::string &name) const {
    for (const auto *command: p_commandsToParse) {
        if (command->name() == name) {
            return true;
        }
        for (const auto &alias: command->aliases()) {
            if (alias == name) {
                return true;
            }
        }
    }
    return false;
}

const Targets &Parsing::targets() const {
    return p_targets;
}


void Parsing::executeAll() const {
    for (auto *command: p_commandsToParse) {
        if (!command->executesNow()) {
            command->execute();
        }
    }
}

Command *Parsing::findCommand(const std::string &name) const {
    for (auto *command: p_commandsToParse) {
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
    p_commandsToParse.push_back(command);
}

bool Parsing::checkMissingMandatory(const std::vector<std::string> &inputParts) const {
    for (auto *command: p_commandsToParse) {
        if (command->isMandatoryCommand()) {
            for (const auto &myarg: inputParts) {
                if (command->name() == myarg) {
                    return false;
                }
                for (const auto &alias: command->aliases()) {
                    if (alias == myarg) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    return false;
}


Parsing::~Parsing() {
    for (const auto *command: p_commandsToParse) {
        delete command;
    }
}
