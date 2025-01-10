#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
    public:
        // Constructor
        Vehicle(std::string companyIdentifier, double cruiseSpeed, double batteryCapacity, double timeToCharge, 
                double energyUseAtCruise, int passengerCount, double probablyFaultPerHour, bool isFlying, 
                bool isCharging, bool isLanding, bool isFaulty);


        // Setters
        void setCompanyIdentifier(std::string companyIdentifier);
        void setCruiseSpeed(double cruiseSpeed);
        void setBatteryCapacity(double batteryCapacity);
        void setTimeToCharge(double timeToCharge);
        void setEnergyUseAtCruise(double energyUseAtCruise);
        void setPassengerCount(int passengerCount);
        void setProbablyFaultPerHour(double probablyFaultPerHour);

        void setTotalFlightTime(double totalFlightTime);
        void setTotalDistance(double totalDistance);
        void setTotalTimeCharging(double totalTimeCharging);
        void setNumChargingSessions(int numChargingSessions);
        void setNumFaults(int numFaults);
        void setFaultProbability(double faultProbability);
        void setCurrentBatteryLevel(double currentBatteryLevel);

        void incrementNumFaults();
        void incrementNumChargingSessions();
        void incrementTotalFlightTime(double timeStep);
        void incrementTotalDistance(double distance);
        void incrementTotalTimeCharging(double timeStep);

        void setIsFlying(bool isFlying);
        void setIsCharging(bool isCharging);
        void setIsLanding(bool isLanding);
        void setIsFaulty(bool isFaulty);

        // Getters
        std::string getCompanyIdentifier();
        double getCruiseSpeed();
        double getBatteryCapacity();
        double getTimeToCharge();
        double getEnergyUseAtCruise();
        int getPassengerCount();
        double getProbablyFaultPerHour();

        double getTotalFlightTime();
        double getTotalDistance();
        double getTotalTimeCharging();
        int getNumChargingSessions();
        int getNumFaults();
        double getFaultProbability();
        double getCurrentBatteryLevel();

        bool getIsFlying();
        bool getIsCharging();
        bool getIsLanding();
        bool getIsFaulty();

    private:
        // Base Vehicle Properties
        std::string companyIdentifier;
        double cruiseSpeed;         // mph
        double batteryCapacity;     // kWh
        double timeToCharge;        // hours
        double energyUseAtCruise;   // kWh/mile
        int passengerCount;
        double probablyFaultPerHour;

        // Extra Stats to Track
        double totalFlightTime;     // hours
        double totalDistance;       // miles
        double totalTimeCharging;   // hours
        int numChargingSessions;
        int numFaults;
        double faultProbability;
        double currentBatteryLevel; // kWh

        // Vehicle States
        bool isFlying;
        bool isCharging;
        bool isLanding;
        bool isFaulty; // ToDo: do nothing if faulty just keep track of count, implement logic at later time

};

#endif // VEHICLE_H
