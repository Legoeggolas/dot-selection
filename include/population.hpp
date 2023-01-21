#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <algorithm>
#include <numeric>
#include <vector>

#include "dot.hpp"

/**
 * @brief Represents a goal area for the Dots to arrive in.
 * This is the expected correct final position.
 *
 */
class Goal {
   private:
    float const radius;  // the radius of the goal area

    static raylib::Color const goal_color;  // the color of the goal

   public:
    Vec2 centre;  // the centre of the goal area

    /**
     * @brief Construct a new Goal object
     *
     * @param _centre The centre of the goal area.
     * @param radius The radius of the goal area.
     */
    Goal(Vec2 _centre, float radius);

    /**
     * @brief Draw the object to the window.
     *
     */
    void draw();

    /**
     * @brief Checks whether a given position lies on the goal area or not.
     *
     * @param pos The position to check.
     * @return true if lies on the goal area.
     * @return false if lies outside the goal area.
     */
    bool posInGoal(Vec2 pos);
};

/**
 * @brief A container class that stores a population.
 *
 */
class Population {
   private:
    Goal goal;  // the goal area for the current population

   public:
    std::vector<Dot> dots;  // the Dots representing this population
    size_t pop_size;        // the size of the population

    /**
     * @brief Construct a new Population object
     *
     * @param _pop_size The size of the Dot population.
     * @param _goal The goal area to use.
     */
    Population(size_t _pop_size, Goal _goal);

    /**
     * @brief Draw each Dot in the population on the window.
     *
     */
    void draw();

    /**
     * @brief Checks if all the Dots have died or not.
     *
     * @return true if all the dots are dead.
     * @return false if there are still some dots alive.
     */
    bool allDead();
};

/**
 * @brief The main class that represents a single simulation.
 *
 */
class Simulation {
   private:
    //? Should be on the stack
    Population *pop;            // stores a population
    size_t const max_pop_size;  // the maximum allowed population size
    Goal const goal;            // the goal area

   public:
    size_t epoch;  // what epoch is currently running

    /**
     * @brief Construct a new Simulation object
     *
     * @param pop_size The population size to start with.
     * @param _goal The goal area.
     */
    Simulation(size_t pop_size, Goal _goal);

    /**
     * @brief Destroy the Simulation object
     *
     */
    ~Simulation();

    /**
     * @brief Simulates the current epoch on the window.
     *
     */
    void simulateEpoch();

    /**
     * @brief Advances the simulation to the next epoch.
     *
     */
    void nextEpoch();
};

#endif
