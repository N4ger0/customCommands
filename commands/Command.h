//
// Created on 29/11/2024.
// CAILLE
// PAUL
// M1 - CL
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>


class Parsing;

/**
 * Class representing a Command of the parser
 * @authors Paul Caillé, Oregan Hardy
 * @version 1.0.0
 */
class Command {
protected:
    /**
     * Name of the command
     */
    std::string c_name;
    /**
     * Vector of the aliases for the command, must start with "-" or "--" for long name
     */
    std::vector<std::string> c_aliases;
    /**
     * Number of argument the command takes
     */
    size_t c_nbOfArguments;
    /**
     * Description of the command displayed by help
     */
    std::string c_description;
    /**
     * Boolean if the command is mandatory or not
     */
    bool c_isMandatory;
    /**
     * If the command can be executed immediately after being parsed
     * Command using Targets object must be at false
     */
    bool c_activateImmediately;

public:
    /**
     * Constructor of a Command
     * @param name name of the Command
     * @param aliases vector of string contained in c_aliases
     * @param nbOfArguments number of argument taken by the Command
     * @param description description of the class, displayed by help
     * @param isMandatory if the command is mandatory
     * @param activateImmediately if the command can be executed directly when parsed
     */
    Command(const std::string &name, const std::vector<std::string> &aliases, size_t nbOfArguments,
            const std::string &description, bool isMandatory, bool activateImmediately);

    /**
     * Destructor of a Command, used by the desctructor of Parsing
     */
    virtual ~Command() = default;

    /**
     * Set arguments parsed by Parser in the Command
     * @param args
     */
    virtual void setArguments(const std::vector<std::string> &args) = 0;

    /**
     * Method launched by Parser, main execution of the command
     */
    virtual void execute() = 0;

    /**
     * Getter for c_name
     * @return std::string
     */
    const std::string &name() const;

    /**
     * Getter for c_destruction
     * @return std::string
     */
    std::string description() const;

    /**
     * Getter for c_aliases
     * @return std::vector<std::string>
     */
    const std::vector<std::string> &aliases() const;

    /**
     * Getter for c_isMandatory
     * @return bool
     */
    bool isMandatoryCommand() const;

    /**
     * Getter for c_activateImmediately
     * @return bool
     */
    bool executesNow() const;

    /**
     * Getter for c_nbOfArguments
     * @return std::size_t
     */
    std::size_t nbArguments() const;
};

/**
 * Class representing Help Command
 * @authors Paul Caillé, Oregan Hardy
 * @version 1.0.0
 */
class HelpCommand final : public Command {
 /**
  * Instance of Parser
  */
 const Parsing &parser;

public:
 /**
  * Constructor for HelpCommand
  * @param parser
  */
 explicit HelpCommand(const Parsing &parser);

 /**
  * Implementation of setArguments method
  * @throws std::runtime_error if the vector is not empty
  * @param args std::vector<std::string>>
  */
 void setArguments(const std::vector<std::string> &args) override;

 /**
  * Display the help message of the commands inside of Parser
  */
 void execute() override;
};

#endif //COMMAND_H
