#ifndef BRAIN_H
#define BRAIN_H

#include <cmath>
#include <random>
#include <vector>

#include "raylib/raylib-cpp.hpp"

#ifdef CN
#include "macros.hpp"
#endif

using Vec2 = raylib::Vector2;

/**
 * @brief Defines a container class for a vector containing consecutive kinematic accelerations
 * that are imposed upon a Dot to simulate ordered movement.
 *
 */
class Brain {
   private:
    std::vector<Vec2> directions;  // the directional components of the acceleration
    size_t steps;                  // the current component in use

   public:
    /**
     * @brief Construct a new Brain object
     *
     * @param _vectors The raw vectors representing the direction set.
     */
    Brain(size_t _vectors);

    /**
     * @brief Get the next directional component to accelerate the Dot.
     *
     * @return Vec2 The directional component.
     */
    Vec2 getNextInstruction();

    /**
     * @brief Get the number of steps that have been taken till now.
     *
     * @return size_t
     */
    size_t getStepCount();

    /**
     * @brief Reset the step count to the start of the sequence.
     *
     */
    void reset();

    /**
     * @brief Mutate some parts of the sequence to different directional components.
     *
     * @param chance
     */
    void mutate(double chance = 0.01);

    /**
     * @brief Construct a new Brain object
     *
     * @param other Object to construct a copy of.
     */
    Brain(const Brain &other) {
        directions = other.directions;
    }

    /**
     * @brief Overloaded assignment operator.
     *
     * @param other The rvalue
     * @return Brain& The lvalue
     */
    Brain &operator=(const Brain &other) {
        directions = other.directions;

        return *this;
    }
};

#endif
