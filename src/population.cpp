#include "../include/population.hpp"

Population::Population(size_t _pop_size, Goal _goal) : goal(_goal) {
    Vec2 startPos{(float)GetScreenWidth() / 10, (float)GetScreenHeight() / 10};

    dots = std::vector<Dot>(_pop_size);
    for (auto &dot : dots) {
        dot.reset(startPos);
    }
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

        if (status == false || goal.posInGoal(dot.getPos()) == true) {
            dot.kill();
            dot.fitness(goal.centre);
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

    nextEpoch();
}

void Simulation::nextEpoch() {
    // Selection Function: Truncation
    // since the task is pretty simple and in one variable
    // there is no real need for genetic diversity

    long double maxFitness = 0, minFitness = 10000, avgFitness = 0;
    for (auto const &dot : pop->dots) {
        maxFitness = std::max(dot.calculatedFitness, maxFitness);
        minFitness = std::min(dot.calculatedFitness, minFitness);
        avgFitness += dot.calculatedFitness / pop->dots.size();
    }

    std::sort(std::begin(pop->dots), std::end(pop->dots), [](Dot a, Dot b) {
        return a.calculatedFitness > b.calculatedFitness;
    });

#ifdef CN
    CPRINT("Max: " << maxFitness << "\tFound: " << pop->dots.front().calculatedFitness);
    CPRINT("\nMin: " << minFitness << "\tFound: " << pop->dots.back().calculatedFitness << "\n");
    CPRINT("Average: " << avgFitness << "\n");
#endif

    // elitism to preserve the top dots
    size_t popOffset = pop->dots.size() * 0.4;
    size_t remainder = pop->dots.size() - popOffset;
    pop->dots.erase(pop->dots.begin() + popOffset, pop->dots.end());

    long double cumulativeFitness = 0;
    for (auto const &dot : pop->dots) {
        cumulativeFitness += dot.calculatedFitness;
    }

    for (size_t i = 0; i < popOffset && remainder > 0; i++) {
        size_t portion = remainder * (pop->dots[i].calculatedFitness / cumulativeFitness);
        remainder -= portion;

        for (size_t j = 0; j < portion; j++) {
            pop->dots.push_back(pop->dots[i]);
        }
    }

    for (; remainder > 0; remainder--) {
        pop->dots.push_back(pop->dots[0]);
    }

    Vec2 startPos{(float)GetScreenWidth() / 10, (float)GetScreenHeight() / 10};
    for (size_t i = 0; i < pop->dots.size(); i++) {
        pop->dots[i].reset(startPos);

        if (i >= popOffset) {
            pop->dots[i].mutate();
        }
    }

    pop->pop_size = pop->dots.size();

    ++epoch;

#ifdef CN
    CPRINT("Generated new epoch\n");
    CPRINT("Pop size is: " << pop->pop_size << "\n");
#endif
}
