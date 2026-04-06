#ifndef SIMULATION_H
#define SIMULATION_H

#include "Elevator.h"

#include <string>
#include <vector>

// This class runs the movement part of the program.
// It moves elevators floor by floor and saves a text log of each step.
class Simulation {
private:
    // These variables store the total step count and all printed events.
    int stepCount;
    std::vector<std::string> log;

public:
    // Constructor:
    // Starts the simulation with zero steps and an empty log.
    Simulation();

    // run:
    // Moves one elevator through one finished path and records each move.
    void run(Elevator& elevator, const std::vector<int>& path);

    // printLog:
    // Prints every saved event line after the simulation ends.
    void printLog() const;

    // reset:
    // Clears the saved log and puts the simulation back at zero steps.
    void reset();
};

#endif
