#include "Vehicle.h"

// Constructor
Vehicle::Vehicle(std::string companyIdentifier, double cruiseSpeed, double batteryCapacity, double timeToCharge, 
                 double energyUseAtCruise, int passengerCount, double probablyFaultPerHour, bool isFlying, 
                 bool isCharging, bool isLanding, bool isFaulty)
    : companyIdentifier(companyIdentifier), cruiseSpeed(cruiseSpeed), batteryCapacity(batteryCapacity),
      timeToCharge(timeToCharge), energyUseAtCruise(energyUseAtCruise), passengerCount(passengerCount),
      probablyFaultPerHour(probablyFaultPerHour), totalFlightTime(0), totalDistance(0), totalTimeCharging(0),
      numChargingSessions(0), numFaults(0), faultProbability(0), currentBatteryLevel(batteryCapacity), 
      isFlying(isFlying), isCharging(isCharging), isLanding(isLanding), isFaulty(isFaulty) {}

// Setters
void Vehicle::setCompanyIdentifier(std::string companyIdentifier) {
    this->companyIdentifier = companyIdentifier;
}

void Vehicle::setCruiseSpeed(double cruiseSpeed) {
    this->cruiseSpeed = cruiseSpeed;
}

void Vehicle::setBatteryCapacity(double batteryCapacity) {
    this->batteryCapacity = batteryCapacity;
}

void Vehicle::setTimeToCharge(double timeToCharge) {
    this->timeToCharge = timeToCharge;
}

void Vehicle::setEnergyUseAtCruise(double energyUseAtCruise) {
    this->energyUseAtCruise = energyUseAtCruise;
}

void Vehicle::setPassengerCount(int passengerCount) {
    this->passengerCount = passengerCount;
}

void Vehicle::setProbablyFaultPerHour(double probablyFaultPerHour) {
    this->probablyFaultPerHour = probablyFaultPerHour;
}

void Vehicle::setTotalFlightTime(double totalFlightTime) {
    this->totalFlightTime = totalFlightTime;
}

void Vehicle::setTotalDistance(double totalDistance) {
    this->totalDistance = totalDistance;
}

void Vehicle::setTotalTimeCharging(double totalTimeCharging) {
    this->totalTimeCharging = totalTimeCharging;
}

void Vehicle::setNumChargingSessions(int numChargingSessions) {
    this->numChargingSessions = numChargingSessions;
}

void Vehicle::setNumFaults(int numFaults) {
    this->numFaults = numFaults;
}

void Vehicle::setFaultProbability(double faultProbability) {
    this->faultProbability = faultProbability;
}

void Vehicle::setCurrentBatteryLevel(double currentBatteryLevel) {
    this->currentBatteryLevel = currentBatteryLevel;
}

void Vehicle::incrementNumFaults() {
    numFaults++;
}

void Vehicle::incrementNumChargingSessions() {
    numChargingSessions++;
}

void Vehicle::incrementTotalFlightTime(double timeStep) {
    totalFlightTime += timeStep;
}

void Vehicle::incrementTotalDistance(double distance) {
    totalDistance += distance;
}

void Vehicle::incrementTotalTimeCharging(double timeStep) {
    totalTimeCharging += timeStep;
}

void Vehicle::setIsFlying(bool isFlying) {
    this->isFlying = isFlying;
}

void Vehicle::setIsCharging(bool isCharging) {
    this->isCharging = isCharging;
}

void Vehicle::setIsLanding(bool isLanding) {
    this->isLanding = isLanding;
}

void Vehicle::setIsFaulty(bool isFaulty) {
    this->isFaulty = isFaulty;
}

// Getters
std::string Vehicle::getCompanyIdentifier() {
    return companyIdentifier;
}

double Vehicle::getCruiseSpeed() {
    return cruiseSpeed;
}

double Vehicle::getBatteryCapacity() {
    return batteryCapacity;
}

double Vehicle::getTimeToCharge() {
    return timeToCharge;
}

double Vehicle::getEnergyUseAtCruise() {
    return energyUseAtCruise;
}

int Vehicle::getPassengerCount() {
    return passengerCount;
}

double Vehicle::getProbablyFaultPerHour() {
    return probablyFaultPerHour;
}

double Vehicle::getTotalFlightTime() {
    return totalFlightTime;
}

double Vehicle::getTotalDistance() {
    return totalDistance;
}

double Vehicle::getTotalTimeCharging() {
    return totalTimeCharging;
}

int Vehicle::getNumChargingSessions() {
    return numChargingSessions;
}

int Vehicle::getNumFaults() {
    return numFaults;
}

double Vehicle::getFaultProbability() {
    return faultProbability;
}

double Vehicle::getCurrentBatteryLevel() {
    return currentBatteryLevel;
}

bool Vehicle::getIsFlying() {
    return isFlying;
}

bool Vehicle::getIsCharging() {
    return isCharging;
}

bool Vehicle::getIsLanding() {
    return isLanding;
}

bool Vehicle::getIsFaulty() {
    return isFaulty;
}