#include "../include/population.hpp"
#include "../include/raylib/raylib-cpp.hpp"

#ifndef CN
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
    int const screenWidth = 1920;
    int const screenHeight = 1080;

    raylib::Window window(screenWidth, screenHeight, "nanomachines son");

    SetTargetFPS(60);

#ifdef CN
    CPRINT("Window created\n");
#endif

    Simulation sim(1000, {{0.9 * screenWidth, 0.9 * screenHeight}, 15});
    while (!window.ShouldClose()) {
        BeginDrawing();
        window.ClearBackground(WHITE);

        sim.simulateEpoch();
        EndDrawing();
    }

    return 0;
}
