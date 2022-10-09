#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>

#include "dot.hpp"

class Goal {
   private:
    Vec2 centre;
    float const radius;

    static raylib::Color const goal_color;

   public:
    Goal(Vec2 _centre, float radius);
    void draw();
    bool posInGoal(Vec2 pos);
};

class Population {
   private:
    std::vector<Dot> dots;
    size_t pop_size;
    Goal goal;

   public:
    Population(size_t _pop_size, Goal _goal);

    void draw();
    bool allDead();
};

class Simulation {
   private:
    Population *pop;
    size_t epoch;
    size_t const max_pop_size;
    Goal const goal;

   public:
    Simulation(size_t pop_size, Goal _goal);
    ~Simulation();
    void simulateEpoch();
    void nextEpoch();
};

#endif
