#include "../include/population.hpp"

Population::Population(size_t _pop_size, Goal _goal) : goal(_goal) {
    dots = std::vector<Dot>(_pop_size);
    pop_size = _pop_size;

#ifdef CN
    CPRINT("Generated population of size " << pop_size << "\n");
#endif
}

void Population::draw() {
    goal.draw();

    for (auto &dot : dots) {
        bool status = dot.isAlive();
        dot.draw();

        if (status == true && goal.posInGoal(dot.getPos())) {
            dot.kill();
        }

        pop_size -= (dot.isAlive() != status);
    }
}

bool Population::allDead() {
    return pop_size == 0;
}

raylib::Color const Goal::goal_color = GREEN;

Goal::Goal(Vec2 _centre, float _radius) : centre{_centre}, radius{_radius} {}

void Goal::draw() {
    centre.DrawCircle(radius, Goal::goal_color);
}

bool Goal::posInGoal(Vec2 pos) {
    if (pos.x > centre.x - radius && pos.x < centre.x + radius &&
        pos.y > centre.y - radius && pos.y < centre.y + radius) {
        return true;
    }

    return false;
}

Simulation::Simulation(size_t pop_size, Goal _goal) : max_pop_size{pop_size}, goal(_goal) {
    pop = new Population(pop_size, goal);
    epoch = 1;
#ifdef CN
    CPRINT("Created new Simulation\n");
#endif
}

Simulation::~Simulation() {
    free(pop);
#ifdef CN
    CPRINT("Simulation has ended\n");
#endif
}

void Simulation::simulateEpoch() {
#ifdef CN
    CPRINT("Started simulating epoch " << epoch << "\n");
#endif

    if (!pop->allDead()) {
        pop->draw();
        return;
    }

#ifdef CN
    CPRINT("Entire population has died\n");
#endif

#ifdef CN
    CPRINT("Finished simulating epoch\n");
#endif

    // do stuff

    nextEpoch();
}

void Simulation::nextEpoch() {
    auto new_population = new Population(max_pop_size, goal);
    delete pop;
    pop = new_population;

    ++epoch;

#ifdef CN
    CPRINT("Generated new epoch\n");
#endif
}
