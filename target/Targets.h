#ifndef TARGET_H
#define TARGET_H
#include <string>
#include <vector>
#include <iterator>

class Targets {
    std::string t_description;
    public:
    std::vector<std::string> t_targs;
    bool t_canBeEmpty;

public:
    Targets(const bool canBeEmpty, const std::string& description)
        : t_description(description), t_canBeEmpty(canBeEmpty) {}

    bool canBeEmpty() const {
        return t_canBeEmpty;
    }

    const std::vector<std::string>& targets() const {
        return t_targs;
    }

    void addTarget(const std::string& targ) {
        t_targs.push_back(targ);
    }

    bool empty() const {
        return t_targs.empty();
    }
};

#endif // TARGET_H