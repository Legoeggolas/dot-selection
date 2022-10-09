#include <iostream>

#ifndef CON
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
    std::cout << "Hello, world!\n";

    return 0;
}
