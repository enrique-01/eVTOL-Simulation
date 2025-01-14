# eVTOL-Simulation

Results
- Single run results can be found in results.txt

Classes
---------
Vehicle Class
Charger Class
Simulation Class

Vehicle Class - eVTOL w/ vehicle specs, info to track, etc
Charger Class - the 3 chargers being used. Can work with a queue of vehicles, assign to chargers if empty, and simulate charging per timestep
Simulation Class - the simulation logic for the 20 vehicles being initalized, 3 chargers being initialized, then simulating a timestep in which the vehicles can be charging/flying

Currently Working:
- All Requirements

-------------------------------------------------------------------------------------------------------------

To Build
- make clean
- make (to build simulator)
- make run_tests (to build tests)
- ./build/bin/simulator (to run simulator)
- ./build/bin/test_simulator (to run tests)

Tests done via gtest

sudo apt-get install g++
sudo apt-get install make
sudo apt-get install libgtest-dev

Pretty much need standard libs: libstdc++, libm, libgcc &
Google Test - libgtest-dev

(Removed .gitignore of build folder to keep leftover build artifacts)

-------------------------------------------------------------------------------------------------------------

ToDo
- Unit Tests - Add more coverage
- Fault - currently we only keep track of the faults we don't do anything if one were to occur.
        - discussion on behavior of faults. What are faults, severity levels, what action do we need to take, etc.
- Maybe improve the fault calulations
        -lot of small numbers due to probablity/timestep. suspect theres some precision being lost also due to rounding, etc.
- Static Analysis (Probably not)
        - Clang?
- State Machine - if we wanted to add behavior for faults and more advanced simulation (ie not instant cruise speed, etc). 
- Base Class w/ Virtual declaration - could leverage polymorphism to have different vehicle with different behaviors, but similar base functionalities. Could also add extra methods/etc specfic to that vehicle.
        - seems a bit overkill for this given the vehicles share the exact same behaviors and stats
- Logger - add better logger than just cout to follow execution path better and create logs for errors. 