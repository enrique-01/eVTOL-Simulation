#include "Simulation.h"

// Constructor
// Constructor implementation
Simulation::Simulation(int totalVehicles, int totalChargers, double simulationTime)
    : simulationTime(simulationTime), timeStep(0.01), currentTime(0.0), numVehicles(totalVehicles) {

    // Initialize vehicles and chargers
    initVehicles();
    initChargers();
}

// Run the simulation
void Simulation::run() {

    // Simulation loop
    while (currentTime < simulationTime) {
        simulateTimeStep(timeStep);
        currentTime += timeStep;
    }

    // Print company stats
    printCompanyStats();
}

// Initialize vehicles
void Simulation::initVehicles() {

    struct VehicleSpecs {
        std::string name;
        double cruiseSpeed;
        double batteryCapacity;
        double timeToCharge;
        double energyUseAtCruise;
        int passengerCount;
        double faultProbability;
    };

    // Vehicle specs for different companies
    // Pretty much just used as a lookup table
    const std::vector<VehicleSpecs> vehicleSpecs = {
        {"Alpha Company", 120, 320, 0.6, 1.6, 4, 0.25},
        {"Bravo Company", 100, 100, 0.2, 1.5, 5, 0.10},
        {"Charlie Company", 160, 220, 0.8, 2.2, 3, 0.05},
        {"Delta Company", 90, 120, 0.62, 0.8, 2, 0.22},
        {"Echo Company", 30, 150, 0.3, 5.8, 2, 0.61},
    };

    std::srand(std::time(nullptr)); // Seed for random number generation

    for (int i = 0; i < 20; ++i) {
        // Randomly select a company for each vehicle
        int companyIndex = std::rand() % vehicleSpecs.size();
        const VehicleSpecs& specs = vehicleSpecs[companyIndex];

        // Create a new vehicle with the selected specs
        std::shared_ptr<Vehicle> vehicle = std::make_shared<Vehicle>(
            specs.name, specs.cruiseSpeed, specs.batteryCapacity, specs.timeToCharge,
            specs.energyUseAtCruise, specs.passengerCount, specs.faultProbability,
            false, false, false, false
        );

        // Add the vehicle to the list
        vehicles.push_back(vehicle);
    }

}

// Initialize chargers
void Simulation::initChargers() {
    for (int i = 0; i < 3; ++i) {
        chargers.push_back(std::make_shared<Charger>());
    }
}

// Helper function to check if a vehicle is in the queue
bool isVehicleInQueue(const std::shared_ptr<Vehicle>& vehicle, const std::queue<std::shared_ptr<Vehicle>>& queue) {
    std::queue<std::shared_ptr<Vehicle>> tempQueue = queue; // Create a temporary copy of the queue
    while (!tempQueue.empty()) {
        if (tempQueue.front() == vehicle) {
            return true;
        }
        tempQueue.pop();
    }
    return false;
}

// Simulate time step
void Simulation::simulateTimeStep(double timeStep) {
    // Process the charging queue
    for (std::shared_ptr<Charger> charger : chargers) {
        if (charger->getIsAvailable() && !chargerQueue.empty()) {
            // Assign the first vehicle in the queue to the charger
            std::shared_ptr<Vehicle> vehicleToCharge = chargerQueue.front();
            chargerQueue.pop(); // Remove from the front of the queue
            charger->assignVehicle(vehicleToCharge);
        }
    }

    // Charge vehicles assigned to chargers
    for (std::shared_ptr<Charger> charger : chargers) {
        if (!charger->getIsAvailable()) {
            std::shared_ptr<Vehicle> assignedVehicle = charger->getAssignedVehicle();

            // Charge the vehicle fully from 0 to 100%
            if (assignedVehicle->getCurrentBatteryLevel() < assignedVehicle->getBatteryCapacity()) {
                charger->ChargeVehicleFor(timeStep);
            }

            // If the vehicle is fully charged, release it
            if (assignedVehicle->getCurrentBatteryLevel() >= assignedVehicle->getBatteryCapacity()) {
                charger->releaseVehicle();
            }
        }
    }

    // Process each vehicle for flying and queuing
    for (std::shared_ptr<Vehicle> vehicle : vehicles) {
        // If the vehicle's battery is full and it's not flying or charging, start flying
        if (!vehicle->getIsFlying() && vehicle->getCurrentBatteryLevel() == vehicle->getBatteryCapacity() && !vehicle->getIsCharging()) {
            vehicle->setIsFlying(true);
        }

        // If the vehicle is flying, simulate its flight
        if (vehicle->getIsFlying()) {
            vehicleFlight(vehicle, timeStep);

            // If the vehicle's battery is depleted, stop flying and enqueue it for charging
            if (vehicle->getCurrentBatteryLevel() <= 0) {
                vehicle->setIsFlying(false);
                if (!isVehicleInQueue(vehicle, chargerQueue)) {
                    chargerQueue.push(vehicle);
                }
            }
        }

        // If the vehicle is queued for charging, ensure it's properly managed
        if (!vehicle->getIsFlying() && vehicle->getCurrentBatteryLevel() < vehicle->getBatteryCapacity() && !vehicle->getIsCharging()) {
            // Vehicle is ready to charge but not assigned; ensure it's in the queue
            if (!isVehicleInQueue(vehicle, chargerQueue)) {
                chargerQueue.push(vehicle);
            }
        }
    }
}

void Simulation::vehicleFlight(std::shared_ptr<Vehicle> vehicle, double timeStep) {
    std::cout << "Vehicle is flying" << std::endl;
    double energyUsed = vehicle->getEnergyUseAtCruise() * vehicle->getCruiseSpeed() * timeStep;
    vehicle->incrementTotalFlightTime(timeStep);
    vehicle->incrementTotalDistance(vehicle->getCruiseSpeed() * timeStep);

    // Drain the battery
    std::cout << "Battery Level before draining: " << vehicle->getCurrentBatteryLevel() << std::endl;
    double newBatteryLevel = vehicle->getCurrentBatteryLevel() - energyUsed;

    // Ensure battery doesn't go below 0
    if (newBatteryLevel < 0) {
        newBatteryLevel = 0;
    }

    vehicle->setCurrentBatteryLevel(newBatteryLevel);
    std::cout << "Battery Level after draining: " << vehicle->getCurrentBatteryLevel() << std::endl;

    // Check if battery is empty and transition to charging
    if (vehicle->getCurrentBatteryLevel() == 0) {
        std::cout << "Vehicle battery drained. Transitioning to charging." << std::endl;
        vehicle->setIsFlying(false);
        vehicle->setIsCharging(true);
    }
}

void Simulation::printCompanyStats() {
    std::unordered_map<std::string, std::vector<std::shared_ptr<Vehicle>>> companyVehicles;

    // Group vehicles by company
    for (std::shared_ptr<Vehicle> vehicle : vehicles) {
        companyVehicles[vehicle->getCompanyIdentifier()].push_back(vehicle);
    }

    // Print stats for each company
    for (const auto& [company, vehicles] : companyVehicles) {
        double totalFlightTime = 0.0;
        double totalDistance = 0.0;
        double totalChargingTime = 0.0;
        int numChargingSessions = 0;
        int numFlights = 0;
        double totalPassengerMiles = 0.0;
        double totalFaults = 0.0; // Use floating point for faults

        for (std::shared_ptr<Vehicle> vehicle : vehicles) {
            totalFlightTime += vehicle->getTotalFlightTime();
            totalDistance += vehicle->getTotalDistance();
            totalChargingTime += vehicle->getTotalTimeCharging();
            numChargingSessions += vehicle->getNumChargingSessions();
            numFlights++;
            totalPassengerMiles += vehicle->getTotalDistance() * vehicle->getPassengerCount();

            // Get the fault probability per hour for the vehicle
            //std::cout << "Fault Probability: " << vehicle->getFaultProbability() << std::endl;
            double faultProbabilityPerHour = vehicle->getFaultProbability(); // Fault probability per hour

            // Calculate the total number of faults for the vehicle (floating point)
            double vehicleFaults = vehicle->getTotalFlightTime() * faultProbabilityPerHour;

            // Accumulate the faults to the company total (floating-point)
            totalFaults += vehicleFaults;
        }

        // Handle division by zero
        if (numFlights == 0) {
            std::cout << "Error no flights." << std::endl;
            continue;
        }


        std::cout << "Company: " << company << std::endl;
        std::cout << "Average Flight Time: per Flight " << totalFlightTime / numFlights << " hours" << std::endl;
        std::cout << "Average Distance Traveled per Flight: " << totalDistance / numFlights << " miles" << std::endl;

        // ToDo need to change logic for this?
        if (numChargingSessions == 0) {
            std::cout << "Average Time per Charging Session: " << "No charging sessions." << std::endl;
            continue;
        }
        else {
            std::cout << "Average Time per Charging Session: " << totalChargingTime / numChargingSessions << " hours" << std::endl;
        }
        
        std::cout << "Number of Faults: " << std::round(totalFaults) << std::endl; // Round the faults to whole numbers
        std::cout << "Total Passenger Miles: " << totalPassengerMiles << std::endl;
        std::cout << std::endl;
    }
}