#include "Building.h"
#include "Scheduler.h"
#include "Simulation.h"

#include <iostream>
#include <string>
#include <vector>

// printPath helper:
// Prints the floors in one line with arrows so the path is easy to read.
void printPath(const std::vector<int>& path) {
    // This handles the case where the path vector has no floors in it.
    if (path.empty()) {
        std::cout << "empty";
        return;
    }

    // This loop prints each floor and adds arrows between them.
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i != path.size() - 1) {
            std::cout << " -> ";
        }
    }
}

// main:
// Controls the full program by collecting input, building paths, and running the simulation.
int main() {
    int totalFloors;
    int numberOfElevators;
    int numberOfRequests;
    std::string algorithmChoice;

    // ----- Section 1: Get building information -----
    // This section asks the user how big the building is and how many elevators it has.
    std::cout << "Enter total number of floors: ";
    std::cin >> totalFloors;

    std::cout << "Enter number of elevators: ";
    std::cin >> numberOfElevators;

    // ----- Section 2: Validate the first inputs -----
    // This section stops the program early if the basic building setup is invalid.
    if (totalFloors < 1 || numberOfElevators < 1) {
        std::cout << "Error: floors and elevators must both be at least 1.\n";
        return 1;
    }

    // ----- Section 3: Create the building object -----
    // This section makes the main Building object that will store all elevators.
    Building building(totalFloors);

    // ----- Section 4: Add elevators to the building -----
    // This section asks for each starting floor and creates the elevator objects one by one.
    for (int i = 1; i <= numberOfElevators; i++) {
        int startFloor;
        std::cout << "Enter starting floor for Elevator " << i << ": ";
        std::cin >> startFloor;

        // This check keeps every elevator start floor inside the building range.
        if (startFloor < 1 || startFloor > totalFloors) {
            std::cout << "Invalid start floor. Setting Elevator " << i << " to floor 1.\n";
            startFloor = 1;
        }

        building.addElevator(startFloor);
    }

    // ----- Section 5: Collect floor requests -----
    // This section asks for all requested floors and sends each request into the building system.
    std::cout << "Enter number of floor requests: ";
    std::cin >> numberOfRequests;

    for (int i = 1; i <= numberOfRequests; i++) {
        int requestedFloor;
        std::cout << "Enter requested floor " << i << ": ";
        std::cin >> requestedFloor;
        building.requestFloor(requestedFloor);
    }

    // ----- Section 6: Show elevator status before scheduling -----
    // This section prints each elevator's current floor, direction, and saved queue.
    building.displayAllStatus();

    // ----- Section 7: Choose the scheduling algorithm -----
    // This section lets the user choose FCFS, SSTF, or SCAN for path calculation.
    std::cout << "\nChoose scheduling algorithm (FCFS, SSTF, or SCAN): ";
    std::cin >> algorithmChoice;

    // This creates the two helper objects used for path planning and movement.
    Scheduler scheduler(algorithmChoice);
    Simulation simulation;

    // ----- Section 8: Process each elevator -----
    // This section gets each elevator's queue, calculates its path, and simulates the movement.
    for (int elevatorID = 1; elevatorID <= numberOfElevators; elevatorID++) {
        Elevator* elevator = building.getElevatorByID(elevatorID);

        // This skips the loop safely if the elevator pointer was not found.
        if (elevator == nullptr) {
            continue;
        }

        // This copies the queue so the scheduler can build an ordered path from it.
        std::vector<int> queue = elevator->getQueue();

        std::cout << "\n========================================\n";
        std::cout << "Processing Elevator " << elevator->getElevatorID() << std::endl;
        std::cout << "Original queue: ";
        printPath(queue);
        std::cout << std::endl;

        // This chooses a direction for SCAN, and idle elevators begin by going up.
        std::string direction = elevator->getDirection();
        if (direction == "idle") {
            direction = "up";
        }

        // This asks the scheduler to build the best visit order using the chosen algorithm.
        std::vector<int> path = scheduler.getOptimalPath(
            queue,
            elevator->getCurrentFloor(),
            direction
        );

        // This prints the finished path so the user can see the order before movement starts.
        std::cout << "Calculated path using " << scheduler.getAlgorithm() << ": ";
        printPath(path);
        std::cout << std::endl;

        // This runs the floor-by-floor movement and then clears finished requests.
        simulation.run(*elevator, path);
        elevator->clearRequests();
    }

    // ----- Section 9: Print final results -----
    // This section shows the saved movement log and the elevators' final ending positions.
    simulation.printLog();
    building.displayAllStatus();

    return 0;
}
