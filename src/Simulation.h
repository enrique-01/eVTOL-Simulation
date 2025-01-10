#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "Charger.h"
#include <memory>
#include <vector>
#include <queue>
#include <ctime>
#include <iostream>
#include <unordered_map>

class Simulation {
    public:
        // Constructor
        Simulation(int totalVehicles, int totalChargers, double simulationTime);

        void run();

    private:
        // Methods
        void initVehicles();
        void initChargers();
        void simulateTimeStep(double timeStep);
        void printCompanyStats();
        void vehicleFlight(std::shared_ptr<Vehicle> vehicle, double timeStep);

        // Variables
        double simulationTime;
        double timeStep;
        double currentTime;
        int numVehicles;

        // Vehicle and Charger Containers
        std::vector<std::shared_ptr<Vehicle>> vehicles;
        std::vector<std::shared_ptr<Charger>> chargers;
        std::queue<std::shared_ptr<Vehicle>> chargerQueue;
        
};

#endif // SIMULATION_H