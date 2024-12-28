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

class Command {
protected:
    std::string c_name;
    std::vector<std::string> c_aliases;
    size_t c_nbOfArguments;
    std::string c_description;
    bool c_isMandatory;
    bool c_activateImmediately;

public:
    Command(const std::string &name, const std::vector<std::string> &aliases, size_t nbOfArguments,
            const std::string &description, bool isMandatory, bool activateImmediately);

    virtual ~Command() = default;

    virtual void setArguments(const std::vector<std::string> &args) = 0;

    virtual void execute() = 0;

    const std::string &name() const;

    const std::string &description() const;

    const std::vector<std::string> &aliases() const;

    bool isMandatoryCommand() const;

    bool executesNow() const;

    std::size_t nbArguments() const;
};

class CommandWithArgs : public Command {
public :
    std::vector<std::string> args;
    void setArguments(const std::vector<std::string> &args) override;
};


class HelpCommand : public Command {
    const Parsing &parser;

public:
    HelpCommand(const Parsing &parser);

    void setArguments(const std::vector<std::string> &args) override;

    void execute() override;
};

#endif //COMMAND_H
