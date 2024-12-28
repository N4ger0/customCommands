#ifndef TARGETS_H
#define TARGETS_H

#include <string>
#include <vector>

/**
 * Class representing the targets of the program, such as files
 * @authors Paul Caillé, Oregan Hardy
 * @version 1.0.0
 */
class Targets {
    /**
     * Small description for the targets
     */
    std::string t_description;
    /**
     * Vector containing the targets
     */
    std::vector<std::string> t_targs;
    /**
     * Boolean indicating if the targets is empty
     */
    bool t_canBeEmpty;

public:
    using const_iterator = std::vector<std::string>::const_iterator;

    /**
     * Constructor for Targets
     * @param canBeEmpty
     * @param description 
     */
    Targets(bool canBeEmpty, const std::string &description);

    /**
     * Getter for t_canBeEmpty
     * @return boolean
     */
    bool canBeEmpty() const;

    /**
     * Getter for t_targs
     * @return std::vector<std::string>
     */
    const std::vector<std::string> &targets() const;

    /**
     * Add a target to the targets vector
     * @param targ the target to add
     */
    void addTarget(const std::string &targ);

    /**
     * Indicate if the list is empty
     * @return boolean
     */
    bool empty() const;

    const_iterator begin() const;

    const_iterator end() const;

    friend std::ostream &operator<<(std::ostream &os, const Targets &targets);
};

#endif // TARGETS_H
