//
// Created on 29/11/2024.
// CAILLE
// PAUL
// M1 - CL
//

#include <ostream>
#include "Targets.h"


Targets::Targets(bool canBeEmpty, const std::string &description)
    : t_description(description), t_canBeEmpty(canBeEmpty) {
}

bool Targets::canBeEmpty() const {
    return t_canBeEmpty;
}

const std::vector<std::string> &Targets::targets() const {
    return t_targs;
}

void Targets::addTarget(const std::string &targ) {
    t_targs.push_back(targ);
}

bool Targets::empty() const {
    return t_targs.empty();
}

Targets::const_iterator Targets::begin() const {
    return t_targs.begin();
}

Targets::const_iterator Targets::end() const {
    return t_targs.end();
}

std::ostream &operator<<(std::ostream &os, const Targets &targets) {
    os << "\nTargets: ";
    if (targets.t_targs.empty()) {
        os << "None";
    } else {
        for (const auto &target: targets.t_targs) {
            os << target << " ";
        }
    }
    os << "\nDescription: " << targets.t_description << "\n";
    os << "Can be empty: " << (targets.t_canBeEmpty ? "Yes" : "No") << "\n";
    return os;
}
