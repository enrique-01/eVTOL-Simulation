#include "Charger.h"

// Constructor
Charger::Charger() : isAvailable(true), remainingChargeTime(0), vehicle(nullptr) {}

// Assign vehicle to charger
void Charger::assignVehicle(std::shared_ptr<Vehicle> vehicle) {
    //std::cout << "Assigning vehicle to charger" << std::endl;
    if (isAvailable && vehicle) {
        this->vehicle = vehicle;  // Store the assigned vehicle
        isAvailable = false;
        // Calculate the remaining charge time based on the vehicle's battery status
        remainingChargeTime = (vehicle->getBatteryCapacity() - vehicle->getCurrentBatteryLevel()) / vehicle->getTimeToCharge();
    } else if (!isAvailable) {
        //std::cout << "Charger is not available, cannot assign vehicle" << std::endl;
    } else {
        //std::cout << "Invalid vehicle, cannot assign" << std::endl;
    }
}

// Charge vehicle for the given time step
void Charger::ChargeVehicleFor(double timeStep) {
    if (vehicle) {  // Ensure the vehicle pointer is valid
        //std::cout << "Charging vehicle for " << timeStep << " hours" << std::endl;

        if (!isAvailable) {
            // Calculate the charging rate per hour (how much battery is charged per hour)
            double chargeRate = vehicle->getTimeToCharge();  // Time to charge fully (in hours)
            double maxChargePerHour = vehicle->getBatteryCapacity() / chargeRate;  // Amount of battery charged per hour

            // Calculate the maximum charge possible during this time step
            double maxCharge = timeStep * maxChargePerHour;

            // Calculate how much charge is needed to reach full capacity
            double chargeNeeded = vehicle->getBatteryCapacity() - vehicle->getCurrentBatteryLevel();

            // Determine the actual charge amount
            double chargeAmount = std::min(maxCharge, chargeNeeded);

            // Get the current battery level before charging
            double oldBatteryLevel = vehicle->getCurrentBatteryLevel();

            // Update the vehicle's battery level
            double newBatteryLevel = oldBatteryLevel + chargeAmount;
            vehicle->setCurrentBatteryLevel(newBatteryLevel);

            // Deduct the time used for charging
            remainingChargeTime -= timeStep;

            // Track charging statistics
            vehicle->incrementTotalTimeCharging(timeStep); // Only count the actual charging time

            /*
            // Increment num charging sessions only if the battery level goes from 0 to 100
            if (oldBatteryLevel == 0 && newBatteryLevel == vehicle->getBatteryCapacity()) {
                vehicle->incrementNumChargingSessions();
            }
            */

            // If the vehicle is fully charged or time is exhausted, release the vehicle
            if (newBatteryLevel >= vehicle->getBatteryCapacity() || remainingChargeTime <= 0) {
                vehicle->incrementNumChargingSessions();  // Increment the number of charging sessions
                //std::cout << "Total number of charging sessions: " << vehicle->getNumChargingSessions() << std::endl;
                isAvailable = true;  // Mark the charger as available
                remainingChargeTime = 0;  // Reset remaining charge time
                vehicle = nullptr;  // Reset the assigned vehicle
            }

        }
    } else {
        //std::cout << "No vehicle assigned to charger!" << std::endl;
    }
}



// Get the currently assigned vehicle
std::shared_ptr<Vehicle> Charger::getAssignedVehicle() const {
    return vehicle;  // Return the currently assigned vehicle
}

// Release the currently assigned vehicle and make the charger available
void Charger::releaseVehicle() {
    if (vehicle) {
        //std::cout << "Releasing vehicle from charger" << std::endl;
        vehicle = nullptr;  // Reset the vehicle pointer
        isAvailable = true;  // Mark the charger as available
        remainingChargeTime = 0;  // Reset remaining charge time
    }
}

void Charger::setIsAvailable(bool isAvailable) {
    this->isAvailable = isAvailable;
}

bool Charger::getIsAvailable() {
    return isAvailable;
}