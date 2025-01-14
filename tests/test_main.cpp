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

// Checking that vehicles have a valid battery level
TEST(SimulationTest, RunSimulationTest) {
    Simulation simulation(20, 3, 3);
    simulation.run();
    std::cout << "Test for simulation run..." << std::endl;

    for (const auto& vehicle : simulation.getVehicles()) {
        EXPECT_GE(vehicle->getCurrentBatteryLevel(), 0); 
    }
}

// Verify that vehicle battery levels are updated correctly
TEST(SimulationTest, BatteryLevelTest) {
    Simulation simulation(20, 3, 3);
    simulation.run();
    std::cout << "Test for battery levels..." << std::endl;

    for (const auto& vehicle : simulation.getVehicles()) {
        EXPECT_GE(vehicle->getCurrentBatteryLevel(), 0);
        EXPECT_LE(vehicle->getCurrentBatteryLevel(), vehicle->getBatteryCapacity());
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ToDo add more test coverages
// Add more thourough charger assignment test?
// Battery drain test
// Edge case for 0 cars / 0 chargers? <- should never happen regardless