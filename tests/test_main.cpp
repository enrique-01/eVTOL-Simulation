#include <gtest/gtest.h>

#include "../src/Simulation.h"
#include "../src/Vehicle.h"
#include "../src/Charger.h"

// Verify vehicle and charger intialization
TEST(SimulationTest, InitializationTest) {
    Simulation simulation(20, 3, 3);
    std::cout << "Test for vehicle and charger initialization..." << std::endl;

    EXPECT_GE(simulation.getNumVehicles(), 20);
    EXPECT_GE(simulation.getNumChargers(), 3);
}

TEST(SimulationTest, RunSimulationTest) {
    Simulation simulation(20, 3, 3);
    simulation.run();
    std::cout << "Test for simulation run..." << std::endl;

    for (const auto& vehicle : simulation.getVehicles()) {
        EXPECT_GE(vehicle->getCurrentBatteryLevel(), 0); 
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ToDo add more test coverages