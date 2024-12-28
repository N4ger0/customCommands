#ifndef TARGETS_H
#define TARGETS_H

#include <string>
#include <vector>

class Targets {
    std::string t_description;
    std::vector<std::string> t_targs;
    bool t_canBeEmpty;

public:
    using const_iterator = std::vector<std::string>::const_iterator;

    Targets(bool canBeEmpty, const std::string &description);

    bool canBeEmpty() const;

    const std::vector<std::string> &targets() const;

    void addTarget(const std::string &targ);

    bool empty() const;

    const_iterator begin() const;

    const_iterator end() const;

    friend std::ostream &operator<<(std::ostream &os, const Targets &targets);
};

#endif // TARGETS_H
