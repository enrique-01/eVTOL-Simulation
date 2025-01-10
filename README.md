# eVTOL-Simulation

Classes
---------
Vehicle Class
Charger Class
Simulation Class

Vehicle Class represent eVTOL w/ vehicle specs, info to track, etc
Charger Class represents the 3 chargers being used. Can work with a queue of vehicles, assign to chargers if empty, and simulate charging per timestep
Simulation Class represents the simulation logic for the 20 vehicles being initalized, 3 chargers being initialized, then simulating a timestep in which the vehicles can be charging/flying

Currently Working:
- Average time per flight
- Average distance traveled per flight
- Average time charging per charge session
- Total number of faults
- Total number of passenger miles


ToDo
- Unit Tests
- What to do during fault? Currently doing nothing assume this is just something we track. Would need to be discussion about what a fault even is
    what action do we want to take, is it recoverable, different severity levels, etc..
    -Do nothing for now
- Maybe improve the fault calulations
    -lot of small numbers due to probablity/timestep. suspect theres some precision being lost also due to rounding, etc. Maybe we dont care?
- Compiler flags/warnings
    -unused variables/functions
