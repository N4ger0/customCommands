//
// Created on 29/11/2024.
// CAILLE / HARDY
// PAUL / OREGAN
// M1 - CL
//

#include "Parsing.h"

#include <iostream>
#include <ostream>

Parsing::Parsing(Targets &targets) : p_targets(targets), p_commandsToParse() {
    p_commandsToParse.push_back(new HelpCommand(*this));
}

std::vector<std::string> Parsing::allCommandDescriptions() const {
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

    // on stocke le nom de l'exécutable (argv[0]) pour utilisation
    p_exename = argv[0];

    // remplit le vecteur inputParts avec les arguments passés en ligne de commande (argv)
    // on ignore le premier élément qui est le nom de l'exécutable (deja traité)
    for (int i = 1; i < argc; ++i) {
        inputParts.emplace_back(argv[i]);
    }

    // si aucun argument n'est fourni, affiche un message et exécute la commande help
    if (inputParts.empty()) {
        std::cout << "No command provided\n" << std::endl;
        Command *command = p_commandsToParse.front(); // Récupère la commande help de la liste.
        command->execute(); // exécute cette commande.
        return;
    }

    // Vérifie si des commandes obligatoires manquent dans les arguments.
    // Si c'est le cas, lève une exception.
    if (checkMissingMandatory(inputParts)) {
        throw std::runtime_error("Mandatory command not found.");
    }

    // vecteur pour stocker les commandes différées (qui seront exécutées a la fin)
    std::vector<std::pair<Command *, std::vector<std::string> > > deferredCommands;

    // boucle sur chaque élément de inputParts pour analyser les commandes et les cibles
    for (size_t i = 0; i < inputParts.size(); ++i) {
        const std::string &commandName = inputParts[i];

        // Vérifie si l'élément actuel est une commande (commence par un '-').
        if (commandName.empty() || commandName[0] == '-') {
            // trouve la commande correspondante
            Command *command = findCommand(commandName);

            // si la commande n'existe pas, lève une exception.
            if (!command) {
                throw std::runtime_error("Command not recognized: " + commandName);
            }

            // prépare un vecteur pour stocker les arguments associés à cette commande.
            std::vector<std::string> args;

            // si la commande attend des arguments, les collecte.
            if (command->nbArguments() > 0) {
                size_t numArgsCollected = 0;

                // collecte les arguments jusqu'à atteindre le nombre requis ou rencontrer une autre commande.
                while (i + 1 < inputParts.size() && inputParts[i + 1][0] != '-') {
                    args.push_back(inputParts[++i]); // Ajoute l'argument suivant.
                    numArgsCollected++;
                    if (numArgsCollected == command->nbArguments()) {
                        break; // Arrête une fois que le nombre requis est atteint.
                    }
                }

                // si le nombre d'arguments est incorrect, lève une exception.
                if (numArgsCollected != command->nbArguments()) {
                    throw std::runtime_error("Incorrect number of arguments for command: " + commandName);
                }
            }

            // associe les arguments collectés à la commande
            command->setArguments(args);

            // si la commande peut être exécutée immédiatement, elle est exécutée
            // sinon, elle est ajoutée à la liste des commandes dites "différées"
            if (command->executesNow()) {
                command->execute();
            } else {
                deferredCommands.emplace_back(command, args);
            }
        } else {
            // si l'élément n'est pas une commande (ne commence pas par un '-'), il est traité comme une cible.

            // Ajoute la cible actuelle à la liste des cibles.
            p_targets.addTarget(commandName);

            // continuer à collecter les cibles suivantes tant qu'aucune commande n'est rencontrée
            while (i + 1 < inputParts.size()) {
                if (inputParts[i + 1][0] == '-') {
                    // si une commande est rencontrée à la place lève une exception pour une cible mal placée.
                    throw std::runtime_error("Misplaced target : " + inputParts[i]);
                }
                p_targets.addTarget(inputParts[++i]); // Ajoute la cible suivante.
            }
        }
    }

    // exécute toutes les commandes différées une fois que l'analyse est finie
    for (const auto &[command, args] : deferredCommands) {
        command->setArguments(args); // Associe les arguments avant exécution.
        command->execute();
    }

    // si aucune cible n'a été fournie alors qu'elles sont obligatoires alors lève une exception
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

std::string Parsing::generateUsage() const {
    std::string usage = "Usage : " + executableName() + " ";
    for (const auto &command: p_commandsToParse) {
        usage += "[";
        for (size_t i = 0; i < command->aliases().size(); ++i) {
            usage += command->aliases()[i];
            if (i != command->aliases().size() - 1) {
                usage += "|";
            }
        }
        for (int i = 0; i < command->nbArguments(); ++i) {
            usage += " argument_" + std::to_string(i + 1);
        }
        usage += "] ";
    }
    usage += "Targets*";
    return usage;
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

std::string Parsing::executableName() const {
    return p_exename;
}

Parsing::~Parsing() {
    for (const auto *command: p_commandsToParse) {
        delete command;
    }
}
