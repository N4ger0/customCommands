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

std::string Command::description() const {
    std::string fullDescription;
    for (size_t i = 0; i < c_aliases.size(); ++i) {
        fullDescription += c_aliases[i];
        if (i != c_aliases.size() - 1) {
            fullDescription += ", ";
        }
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

HelpCommand::HelpCommand(const Parsing &parser) : Command("help", {"--help", "-h"},
                                                          0, "Display this \033[4mhelp\033[0m message", false, true), parser(parser) {
}

void HelpCommand::execute() {
    std::string usage;
    usage += "Usage : " + parser.exename + " ";
    for (const auto &command: parser.p_commandsToParse) {
        usage += "[";
        for (size_t i = 0; i < command->aliases().size(); ++i) {
            usage += command->aliases()[i];
            if (i != c_aliases.size() - 1) {
                usage += "|";
            }
        }
        if(command->nbArguments() != 0) {
            for(int i = 0; i < command->nbArguments(); ++i) {
                usage += " argument_" + std::to_string(i+1) ;
            }
        }
        usage += "] ";
    }
    usage += "Targets*" ;

    std::cout << usage << std::endl;
    std::cout << "Options :" <<std::endl;

    const auto descriptions = parser.allDescriptions();
    for (const auto &description: descriptions) {
        std::cout <<  "\t" + description << "\n";
    }
}

void HelpCommand::setArguments(const std::vector<std::string> &args) {
    if (!args.empty()) {
        throw std::runtime_error("Help command does not take arguments.");
    }
}
