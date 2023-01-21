#include "../include/brain.hpp"

Brain::Brain(size_t _vectors) {
    steps = 0;
    directions = std::vector<Vec2>(_vectors);

    std::random_device device;
    std::mt19937 engine{device()};
    std::uniform_real_distribution<float> dist{0, 2 * PI};
    std::generate(
        std::begin(directions), std::end(directions), [&dist, &engine]() -> Vec2 {
            return {cosf(dist(engine)), sinf(dist(engine))};
        });
}

Vec2 Brain::getNextInstruction() {
    if (steps >= directions.size()) {
        return directions.back();
    }

    return directions[steps++];
}

size_t Brain::getStepCount() {
    return steps;
}

void Brain::reset() {
    steps = 0;
}

void Brain::mutate(double chance) {
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_real_distribution<double> mutationRoll{0.00, 1.00},
        directionRoll{0, 2 * PI};

    for (auto &dir : directions) {
        if (mutationRoll(engine) > chance) {
            continue;
        }

        dir = directionRoll(engine);
    }
}
