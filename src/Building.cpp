#include "Building.h"

#include <cmath>
#include <iostream>
#include <limits>

// Constructor implementation:
// Saves the total number of floors so the building knows its valid range.
Building::Building(int floors) {
    totalFloors = floors;
}

// addElevator implementation:
// Creates a new elevator ID automatically and adds the elevator to the vector.
void Building::addElevator(int startFloor) {
    int newID = static_cast<int>(elevators.size()) + 1;
    elevators.push_back(Elevator(newID, startFloor));
}

// addRequestToElevator implementation:
// First checks for bad input, then adds the request to the chosen elevator's queue.
void Building::addRequestToElevator(int elevatorID, int floorNumber) {
    // This makes sure the requested floor exists in the building.
    if (floorNumber < 1 || floorNumber > totalFloors) {
        std::cout << "Error: floor " << floorNumber << " is out of range.\n";
        return;
    }

    // This looks up the elevator pointer so we can edit the correct object.
    Elevator* elevator = getElevatorByID(elevatorID);
    if (elevator == nullptr) {
        std::cout << "Error: elevator " << elevatorID << " does not exist.\n";
        return;
    }

    // This adds the request after both checks have passed.
    elevator->addRequest(floorNumber);
    std::cout << "Floor " << floorNumber
              << " added to Elevator " << elevatorID << " queue.\n";
}

// assignBestElevator implementation:
// Loops through every elevator and keeps the one with the smallest distance.
int Building::assignBestElevator(int requestedFloor) const {
    // This handles the case where the building does not have any elevators yet.
    if (elevators.empty()) {
        std::cout << "Error: no elevators available.\n";
        return -1;
    }

    // bestID stores the answer, and minDistance starts very large for comparison.
    int bestID = -1;
    int minDistance = std::numeric_limits<int>::max();

    // This loop compares each elevator's current floor to the requested floor.
    for (size_t i = 0; i < elevators.size(); i++) {
        int distance = std::abs(elevators[i].getCurrentFloor() - requestedFloor);
        if (distance < minDistance) {
            minDistance = distance;
            bestID = elevators[i].getElevatorID();
        }
    }

    // This prints and returns the closest elevator that was found.
    std::cout << "Elevator " << bestID << " assigned to floor " << requestedFloor << ".\n";
    return bestID;
}

// requestFloor implementation:
// Validates the floor, finds the best elevator, and sends the request to it.
void Building::requestFloor(int requestedFloor) {
    // This rejects floors below 1 or above the building's top floor.
    if (requestedFloor < 1 || requestedFloor > totalFloors) {
        std::cout << "Error: floor " << requestedFloor << " is out of range.\n";
        return;
    }

    // This asks the building which elevator should handle the request.
    int bestID = assignBestElevator(requestedFloor);
    if (bestID != -1) {
        addRequestToElevator(bestID, requestedFloor);
    }
}

// getElevatorByID implementation:
// Searches through the elevator vector until the matching ID is found.
Elevator* Building::getElevatorByID(int elevatorID) {
    // This loop checks each elevator one at a time.
    for (size_t i = 0; i < elevators.size(); i++) {
        if (elevators[i].getElevatorID() == elevatorID) {
            return &elevators[i];
        }
    }

    // Returning nullptr tells the caller that no elevator matched the ID.
    return nullptr;
}

// getElevators implementation:
// Returns the whole elevator list so other code can read it safely.
const std::vector<Elevator>& Building::getElevators() const {
    return elevators;
}

// displayAllStatus implementation:
// Prints a heading and then asks each elevator to print its own status.
void Building::displayAllStatus() const {
    std::cout << "\n--- Elevator Status ---\n";
    for (size_t i = 0; i < elevators.size(); i++) {
        elevators[i].displayStatus();
    }
}

// getTotalFloors implementation:
// Returns the number of floors stored in the building object.
int Building::getTotalFloors() const {
    return totalFloors;
}
