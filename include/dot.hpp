#ifndef DOT_HPP
#define DOT_HPP

#include "brain.hpp"
#include "raylib/raylib-cpp.hpp"

#ifdef CN
#include "macros.hpp"
#endif

using Vec2 = raylib::Vector2;

class Dot {
   private:
    Vec2 pos;
    Vec2 vel;
    Vec2 accel;

    Brain brain;

    bool alive;

    static raylib::Color const default_color;
    static float const default_radius;
    static size_t const default_brain_size;
    static float const vel_lim;

   public:
    Dot();
    Dot(Vec2 _pos);

    Vec2 getPos();

    void draw();
    void update();
    bool isAlive();
    void kill();
};

#endif
