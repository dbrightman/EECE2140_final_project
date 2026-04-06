#include "Simulation.h"

#include <iostream>

// Constructor implementation:
// Begins the simulation with stepCount set to zero.
Simulation::Simulation() {
    stepCount = 0;
}

// run implementation:
// Walks through the path target by target and moves one floor at a time.
void Simulation::run(Elevator& elevator, const std::vector<int>& path) {
    // This stops immediately when there is no path to follow.
    if (path.empty()) {
        std::cout << "No path to simulate.\n";
        return;
    }

    // position stores a temporary floor value while the elevator is moving.
    int position = elevator.getCurrentFloor();

    // This loop goes through each requested target floor in the planned path.
    for (size_t i = 0; i < path.size(); i++) {
        int target = path[i];

        // This loop moves one floor at a time until the elevator reaches the target.
        while (position != target) {
            std::string direction;

            // This if/else changes the floor by 1 and records the movement direction.
            if (target > position) {
                position++;
                direction = "up";
            } else {
                position--;
                direction = "down";
            }

            // This counts the move, updates the elevator, and builds a log message.
            stepCount++;
            elevator.setDirection(direction);

            std::string event = "Step " + std::to_string(stepCount) +
                                ": Elevator " + std::to_string(elevator.getElevatorID()) +
                                " at floor " + std::to_string(position) +
                                " moving " + direction;

            // This prints the step immediately and also saves it for later.
            std::cout << event << std::endl;
            log.push_back(event);
        }

        // This prints a message each time one requested floor is reached.
        std::cout << ">>> Arrived at requested floor: " << target << std::endl;
    }

    // This saves the final floor back into the elevator and marks it idle.
    elevator.setCurrentFloor(position);
    elevator.setDirection("idle");

    // This prints the total number of floor-by-floor moves made.
    std::cout << "Simulation complete. Total steps: " << stepCount << "\n";
}

// printLog implementation:
// Prints a heading and then outputs every saved event string.
void Simulation::printLog() const {
    std::cout << "\n--- Simulation Log ---\n";

    // This handles the case where no events were stored.
    if (log.empty()) {
        std::cout << "Log is empty.\n";
        return;
    }

    // This loop prints each saved line in the order it happened.
    for (size_t i = 0; i < log.size(); i++) {
        std::cout << log[i] << std::endl;
    }
}

// reset implementation:
// Clears old simulation data so the object can be reused cleanly.
void Simulation::reset() {
    stepCount = 0;
    log.clear();
}
