#ifndef DOT_HPP
#define DOT_HPP

#include "brain.hpp"
#include "raylib/raylib-cpp.hpp"

#ifdef CN
#include "macros.hpp"
#endif

using Vec2 = raylib::Vector2;

/**
 * @brief Defines a Dot, used to represent the pathfinders
 *
 */
class Dot {
   private:
    Vec2 pos;    // the current position of the Dot
    Vec2 vel;    // the current velocity of the Dot
    Vec2 accel;  // the current acceleration of the dot

    Brain brain;            // stores the instructions used for movement
    double mutationChance;  // the chance for an instruction to mutate

    bool alive;  // represents whether the Dot has ended movement or not

    // defaults
    static Vec2 const default_pos;
    static raylib::Color const default_color;
    static float const default_radius;
    static size_t const default_brain_size;
    static double const default_mutation_chance;
    static float const vel_lim;

   public:
    long double calculatedFitness;  // the fitness of the Dot after the epoch ends

    /**
     * @brief Construct a new Dot object
     *
     */
    Dot();

    /**
     * @brief Construct a new Dot object
     *
     * @param _pos The starting position of the Dot.
     * @param brainSize The number of directional inputs stored by the brain.
     */
    Dot(Vec2 _pos, size_t brainSize);

    /**
     * @brief Construct a new Dot object
     *
     * @param _pos The starting position of the Dot.
     * @param brainSize The number of directional inputs stored by the brain.
     * @param chance The chance to mutate a direction.
     */
    Dot(Vec2 _pos, size_t brainSize, double chance);

    /*Methods*/
    /**
     * @brief Get the current position of the Dot.
     *
     * @return Vec2 The position
     */
    Vec2 getPos() const;

    /**
     * @brief Draws the Dot in the window.
     *
     */
    void draw();

    /**
     * @brief Updates the kinematic attributes of the Dot.
     *  Exits early if the dot is dead.
     */
    void update();

    /**
     * @brief Returns whether the Dot is still functional or not.
     *
     * @return true The Dot has not hit the boundaries or the goal post.
     * @return false The Dot has hit a boundary or the goal post.
     */
    bool isAlive() const;

    /**
     * @brief Kills the dot. Sets the alive boolean to false.
     *
     */
    void kill();

    /**
     * @brief Signals the brain to mutate its directional vectors.
     *
     */
    void mutate();

    /**
     * @brief Resets the Dot to its original state. The default position property is used.
     *
     */
    void reset();

    /**
     * @brief Resets the Dot to its original state, but the position is specified.
     *
     * @param _pos The new starting position of the reset Dot.
     */
    void reset(Vec2 _pos);

    /**
     * @brief Calculates and stores the fitness in the member calculatedFitness.
     *
     * @param ref The centre of the goal post.
     */
    void fitness(Vec2 const& ref);
};

#endif
