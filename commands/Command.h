//
// Created on 29/11/2024.
// CAILLE / HARDY
// PAUL / OREGAN
// M1 - CL
//

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Parsing;

/**
 * @class Command
 * @brief Represents a command in the parser framework.
 *
 * This abstract class serves as a base for creating commands that can be
 * parsed, validated, and executed by the parser. Each command can have
 * aliases, a description, arguments, and specific execution behavior.
 *
 * @authors
 * - Paul Caillé
 * - Oregan Hardy
 * @version 1.0.0
 */
class Command {
protected:
    /**
     * @brief The primary name of the command.
     */
    std::string c_name;

    /**
     * @brief A list of aliases for the command.
     *
     * Aliases must begin with "-" for short names;
     */
    std::vector<std::string> c_aliases;

    /**
     * @brief The number of arguments the command expects.
     */
    size_t c_nbOfArguments;

    /**
     * @brief A short description of the command, displayed in the help menu.
     */
    std::string c_description;

    /**
     * @brief Indicates if the command is mandatory.
     */
    bool c_isMandatory;

    /**
     * @brief Determines if the command can be executed immediately after being parsed.
     *
     */
    bool c_activateImmediately;

public:
    /**
     * @brief Constructs a new Command object.
     *
     * @param name The primary name of the command.
     * @param aliases A vector of aliases for the command.
     * @param nbOfArguments The number of arguments required by the command.
     * @param description A description of the command's functionality.
     * @param isMandatory Whether the command is mandatory.
     * @param activateImmediately Whether the command can execute directly upon parsing.
     */
    Command(const std::string &name, const std::vector<std::string> &aliases, size_t nbOfArguments,
            const std::string &description, bool isMandatory, bool activateImmediately);

    /**
     * @brief Virtual destructor for Command.
     *
     * The `Parsing` class deletes commands when it is destroyed.
     */
    virtual ~Command() = default;

    /**
     * @brief Sets the arguments parsed by the parser.
     *
     * @param args A vector of arguments to set.
     */
    virtual void setArguments(const std::vector<std::string> &args) = 0;

    /**
     * @brief Executes the command's main logic.
     *
     * This is invoked by the parser after validation.
     */
    virtual void execute() = 0;

    /**
     * @brief Retrieves the name of the command.
     *
     * @return The name of the command as a string.
     */
    const std::string &name() const;

    /**
     * @brief Retrieves a formatted description of the command.
     *
     * Combines the name, aliases, and description into a single string.
     *
     * @return A string containing the command description.
     */
    std::string description() const;

    /**
     * @brief Retrieves the aliases of the command.
     *
     * @return A constant reference to the vector of aliases.
     */
    const std::vector<std::string> &aliases() const;

    /**
     * @brief Checks if the command is mandatory.
     *
     * @return `true` if the command is mandatory, `false` otherwise.
     */
    bool isMandatoryCommand() const;

    /**
     * @brief Checks if the command is set to execute immediately after parsing.
     *
     * @return `true` if the command executes immediately, `false` otherwise.
     */
    bool executesNow() const;

    /**
     * @brief Retrieves the number of arguments required by the command.
     *
     * @return The number of arguments as a `size_t`.
     */
    std::size_t nbArguments() const;
};

/**
 * @class HelpCommand
 * @brief A concrete implementation of the `Command` class for displaying help information.
 *
 * The `HelpCommand` displays usage instructions and a list of available commands
 * within the parser.
 *
 * @authors
 * - Paul Caillé
 * - Oregan Hardy
 * @version 1.0.0
 */
class HelpCommand final : public Command {
    /**
     * @brief A reference to the parser instance, used to access command data.
     */
    const Parsing &parser;

public:
    /**
     * @brief Constructs a `HelpCommand` object.
     *
     * @param parser A reference to the parser containing the commands.
     */
    explicit HelpCommand(const Parsing &parser);

    /**
     * @brief Sets arguments for the command.
     *
     * Overrides the base class method. Throws an exception if arguments are provided,
     * as the `HelpCommand` does not accept any arguments.
     *
     * @param args A vector of arguments.
     * @throws std::runtime_error If the vector of arguments is not empty.
     */
    void setArguments(const std::vector<std::string> &args) override;

    /**
     * @brief Executes the `HelpCommand`.
     *
     * Displays the help message with usage and descriptions of all commands in the parser.
     */
    void execute() override;
};

#endif // COMMAND_H
