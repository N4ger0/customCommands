//
// Created on 29/11/2024.
// CAILLE / HARDY
// PAUL / OREGAN
// M1 - CL
//

#ifndef PARSING_H
#define PARSING_H
#include <vector>

#include "../commands/Command.h"
#include "../target/Targets.h"

/**
 * @class Parsing
 * @brief Class responsible for parsing command-line input, managing commands, and handling targets.
 *
 * This class represents a command-line parser that supports adding commands,
 * parsing input arguments, and managing execution flow. It also validates mandatory
 * commands and organizes the parsed targets.
 *
 * @authors
 * - Paul Caillé
 * - Oregan Hardy
 * @version 1.0.0
 */
class Parsing {
    /**
     * @brief Reference to the Targets object that stores parsed target data.
     */
    Targets &p_targets;

    /**
     * @brief Vector containing all commands added to the parser.
     */
    std::vector<Command *> p_commandsToParse;

    /**
     * @brief Name of the executable (parsed from input).
     */
    mutable std::string p_exename;

    /**
     * @brief Finds a command by its name or alias.
     *
     * This method searches for a command in the parser by comparing its name or aliases.
     *
     * @param name The name or alias of the command to find.
     * @return A pointer to the matching Command, or nullptr if not found.
     */
    Command *findCommand(const std::string &name) const;

    /**
     * @brief Executes all commands that are not set to execute immediately.
     *
     * This method processes deferred commands after parsing is completed.
     */
    void executeAll() const;

    /**
     * @brief Checks for missing mandatory commands in the input.
     *
     * Iterates through the commands to ensure that all mandatory commands are present in the input.
     *
     * @param inputParts Vector of input arguments converted to std::string.
     * @return `true` if a mandatory command is missing, `false` otherwise.
     */
    bool checkMissingMandatory(const std::vector<std::string> &inputParts) const;

public:

    /**
     * @brief Constructs a Parsing object.
     *
     * @param targets A reference to a Targets object where parsed targets will be stored.
     */
    explicit Parsing(Targets &targets);

    /**
     * @brief Adds a command to the parser.
     *
     * @param command A pointer to the Command to add. Must not be nullptr.
     */
    void addCommand(Command *command);

    /**
     * @brief Parses input arguments and processes commands and targets.
     *
     * This is the main method for parsing command-line input. It organizes commands,
     * validates arguments, and stores targets as needed.
     *
     * @param argc The argument count (from the command line).
     * @param argv The argument vector (from the command line).
     * @throw std::runtime_error if parsing errors occur (e.g., unrecognized commands, missing arguments).
     */
    void parseInput(int argc, const char *argv[]) const;

    /**
     * @brief Retrieves descriptions of all commands added to the parser.
     *
     * Generates a vector of command descriptions, including aliases and their purpose.
     *
     * @return A vector of strings, each containing a command description.
     */
    std::vector<std::string> allCommandDescriptions() const;

    /**
     * @brief Generates the usage string for the parser.
     *
     * This string details the expected input format, including commands, arguments, and targets.
     *
     * @return A string representing the usage format of the program.
     */
    std::string generateUsage() const;

    /**
     * @brief Checks if a specific command exists in the parser.
     *
     * @param name The name or alias of the command to check.
     * @return `true` if the command exists, `false` otherwise.
     */
    bool hasCommand(const std::string &name) const;

    /**
     * @brief Retrieves the name of the executable.
     *
     * This is typically the first element in the argument vector.
     *
     * @return A string containing the executable's name.
     */
    std::string executableName() const;

    /**
     * @brief Retrieves the Targets object storing parsed targets.
     *
     * @return A constant reference to the Targets object.
     */
    const Targets &targets() const;

    /**
     * @brief Destructor for Parsing.
     *
     * Frees the memory allocated for the commands stored in the parser.
     */
    ~Parsing();
};

#endif //PARSING_H
