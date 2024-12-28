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

/**
 * Class representing the command parser
 * @authors Paul Caillé, Oregan Hardy
 * @version 1.0.0
 */
class Parsing {
    /**
     * Targets object that were parsed
     */
    Targets &p_targets;

    /**
     * Return the command with the name in param, use hasCommand to ensure the command exist before
     * @param name the command to find
     * @return Command
     */
    Command *findCommand(const std::string &name) const;

    /**
     * Execute all commands in p_commandsToParse
     * @deprecated
     */
    void executeAll() const;

    /**
     * Check if a mandatory argument is missing
     * @param inputParts the argv array casted into std::string
     * @return boolean, true if a mandatory argument is missing
     */
    bool checkMissingMandatory(const std::vector<std::string> &inputParts) const;

public:
    /**
     * Vector of all commands added to the parser
     */
    std::vector<Command *> p_commandsToParse;

    /**
     * Name of the executable
     */
    mutable std::string exename ;

    /**
     * Constructor for a parser
     * @param targets
     */
    explicit Parsing(Targets &targets);

    /**
     * Add a command to the parser
     * @param command
     */
    void addCommand(Command *command);

    /**
     * Main method to parse command
     * @param argc
     * @param argv
     */
    void parseInput(int argc, const char *argv[]) const;

    /**
     * Return the description of all the commands added to the parser
     * @return std::vector<std::string>
     */
    std::vector<std::string> allDescriptions() const;

    /**
     * Check if the given command name is present in p_commandToParse
     * @param name
     * @return boolean, if the command exist in the parser
     */
    bool hasCommand(const std::string &name) const;

    /**
     * Getter for p_targets
     * @return Target
     */
    const Targets &targets() const;

    /**
     * Destructor for Parsing
     */
    ~Parsing();
};


#endif //PARSING_H
