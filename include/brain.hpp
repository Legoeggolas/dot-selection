#ifndef BRAIN_H
#define BRAIN_H

#include <cmath>
#include <random>
#include <vector>

#include "raylib/raylib-cpp.hpp"

#ifdef CON
#include "macros.hpp"
#endif

using Vec2 = raylib::Vector2;

class Brain {
   private:
    std::vector<Vec2> directions;
    size_t steps;

   public:
    Brain(size_t _vectors);

    Vec2 getNextInstruction();
    size_t getStepCount();
};

#endif
