#include <iostream>
#include "src/Simulation.h"

int main() {
    // 20 cars, 3 chargers, 3.0 hours
    // Time step is int he simulation constructor change it there
    Simulation simulation(20, 3, 3.0);
    simulation.run();

    return 0;
}