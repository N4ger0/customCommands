//
// Created on 29/11/2024.
// CAILLE / HARDY
// PAUL / OREGAN
// M1 - CL
//

#ifndef TARGETS_H
#define TARGETS_H

#include <string>
#include <vector>
#include <ostream>

/**
 * @class Targets
 * @brief Represents the collection of targets for the program, such as file paths.
 *
 * This class manages a list of targets and provides functionality to add, iterate,
 * and check properties of the targets. It also includes metadata such as a description
 * and whether the list can be empty.
 *
 * @authors
 * - Paul Caillé
 * - Oregan Hardy
 * @version 1.0.0
 */
class Targets {
    /**
     * @brief A small description providing context about the targets.
     */
    std::string t_description;

    /**
     * @brief A vector containing the list of targets.
     */
    std::vector<std::string> t_targs;

    /**
     * @brief A flag indicating if the targets list is allowed to be empty.
     */
    bool t_canBeEmpty;

public:
    /**
     * @brief Type alias for a constant iterator over the targets vector.
     */
    using const_iterator = std::vector<std::string>::const_iterator;

    /**
     * @brief Constructs a Targets object.
     *
     * @param canBeEmpty Specifies if the targets list can be empty.
     * @param description A description of the targets.
     */
    Targets(bool canBeEmpty, const std::string &description);

    /**
     * @brief Checks if the targets list can be empty.
     *
     * @return `true` if the targets list can be empty, `false` otherwise.
     */
    bool canBeEmpty() const;

    /**
     * @brief Retrieves the list of targets.
     *
     * @return A constant reference to the vector of targets.
     */
    const std::vector<std::string> &targets() const;

    /**
     * @brief Adds a new target to the list of targets.
     *
     * @param targ The target to add.
     */
    void addTarget(const std::string &targ);

    /**
     * @brief Checks if the targets list is empty.
     *
     * @return `true` if the list is empty, `false` otherwise.
     */
    bool empty() const;

    /**
     * @brief Returns an iterator pointing to the beginning of the targets list.
     *
     * @return A constant iterator to the start of the vector.
     */
    const_iterator begin() const;

    /**
     * @brief Returns an iterator pointing to the end of the targets list.
     *
     * @return A constant iterator to the end of the vector.
     */
    const_iterator end() const;

    /**
     * @brief Overloads the `<<` operator to print the targets.
     *
     * Outputs the description and the list of targets to the given output stream.
     *
     * @param os The output stream.
     * @param targets The Targets object to print.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Targets &targets);
};

#endif // TARGETS_H
