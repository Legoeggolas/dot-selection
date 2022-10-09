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

    /*
    #ifdef CON
        CPRINT("Generated Brain with directions:\n");
        for (auto const &ele : directions) {
            CPRINT(ele.GetX() << ", " << ele.GetY() << "\n");
        }
    #endif
    */
}

Vec2 Brain::getNextInstruction() {
    if (steps >= directions.size()) {
        return *directions.end();
    }

    return directions[steps++];
}

size_t Brain::getStepCount() {
    return steps;
}
