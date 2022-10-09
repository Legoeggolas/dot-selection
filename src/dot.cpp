#include "../include/dot.hpp"

raylib::Color const Dot::default_color = BLACK;
float const Dot::default_radius = 3;
size_t const Dot::default_brain_size = 1000;
float const Dot::vel_lim = 10;

Dot::Dot() : brain{Brain(default_brain_size)} {
    pos = {(float)GetScreenWidth() / 10, (float)GetScreenHeight() / 10};
    vel = {0, 0};
    accel = {0, 0};
    alive = true;
}

Dot::Dot(Vec2 _pos) : brain{Brain(default_brain_size)} {
    Dot();
    pos = _pos;
}

Vec2 Dot::getPos() {
    return pos;
}

void Dot::draw() {
    pos.DrawCircle(default_radius, default_color);
    if (!alive) {
        return;
    }
    update();
}

void Dot::update() {
    if (pos.x < 0 || pos.x > GetScreenWidth() || pos.y < 0 || pos.y > GetScreenHeight()) {
        alive = false;
        return;
    }

    pos = pos.Add(vel);
    vel = vel.Add(accel);
    if (abs(vel.x) > vel_lim) {
        vel.x = vel_lim * (vel.x / abs(vel.x));
    }
    if (abs(vel.y) > vel_lim) {
        vel.y = vel_lim * (vel.y / abs(vel.y));
    }

    accel = brain.getNextInstruction();
}

bool Dot::isAlive() {
    return alive;
}

void Dot::kill() {
    alive = false;
}
