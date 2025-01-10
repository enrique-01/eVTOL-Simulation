#ifndef CHARGER_H
#define CHARGER_H

#include "Vehicle.h"
#include <memory>
#include <queue>
#include <iostream>

class Charger {
public:
    Charger();  // Constructor
    void assignVehicle(std::shared_ptr<Vehicle> vehicle);
    void ChargeVehicleFor(double timeStep);

    // New methods
    std::shared_ptr<Vehicle> getAssignedVehicle() const;  // Get the assigned vehicle
    void releaseVehicle();  // Release the assigned vehicle and make the charger available

    // Getters
    bool getIsAvailable();

    // Setters
    void setIsAvailable(bool isAvailable);

private:
    bool isAvailable;
    double remainingChargeTime;
    std::shared_ptr<Vehicle> vehicle;  // Pointer to the assigned vehicle
};


#endif // CHARGER_H
