#include "../include/dot.hpp"

Vec2 const Dot::default_pos{25, 25};
raylib::Color const Dot::default_color = BLACK;
float const Dot::default_radius = 3;
size_t const Dot::default_brain_size = 1000;
double const Dot::default_mutation_chance = 0.25;
float const Dot::vel_lim = 10;

Dot::Dot() : Dot(default_pos, default_brain_size) {
}

Dot::Dot(Vec2 _pos, size_t brainSize) : Dot(_pos, brainSize, default_mutation_chance) {
}

Dot::Dot(Vec2 _pos, size_t brainSize, double chance) : brain{Brain(brainSize)}, mutationChance{chance} {
    reset(_pos);
}

Vec2 Dot::getPos() const {
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

bool Dot::isAlive() const {
    return alive;
}

void Dot::kill() {
    alive = false;
}

void Dot::fitness(Vec2 const &ref) {
    long double xdist = ref.x - pos.x;
    long double ydist = ref.y - pos.y;
    long double dist_sq = (xdist * xdist) + (ydist * ydist);

    long double score = 1000000 / (1 + sqrt(dist_sq));

    calculatedFitness = score;
}

/**
 * @brief Mutates the brain of a dot with a given mutation chance for each step
 *
 */
void Dot::mutate() {
    brain.mutate(mutationChance);
}

void Dot::reset() {
    reset(default_pos);
}

void Dot::reset(Vec2 _pos) {
    pos = _pos;
    vel = {0, 0};
    accel = {0, 0};
    alive = true;
    calculatedFitness = 0;
    brain.reset();
}
