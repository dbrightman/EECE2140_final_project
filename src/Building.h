#ifndef BUILDING_H
#define BUILDING_H

#include "Elevator.h"

#include <vector>

// This class represents the whole building.
// It owns all elevators and decides where new floor requests should go.
class Building {
private:
    // These variables store the building size and every elevator object.
    int totalFloors;
    std::vector<Elevator> elevators;

public:
    // Constructor:
    // Saves how many floors exist in the building.
    Building(int floors = 1);

    // addElevator:
    // Creates one new elevator and stores it in the building's list.
    void addElevator(int startFloor);

    // addRequestToElevator:
    // Sends a validated floor request directly to one chosen elevator.
    void addRequestToElevator(int elevatorID, int floorNumber);

    // assignBestElevator:
    // Finds the elevator whose current floor is closest to the request.
    int assignBestElevator(int requestedFloor) const;

    // requestFloor:
    // Handles a new building request by choosing the best elevator first.
    void requestFloor(int requestedFloor);

    // getElevatorByID:
    // Searches the vector and returns a pointer to the matching elevator.
    Elevator* getElevatorByID(int elevatorID);

    // getElevators:
    // Returns all elevators so their data can be viewed from outside the class.
    const std::vector<Elevator>& getElevators() const;

    // displayAllStatus:
    // Prints the status of every elevator one by one.
    void displayAllStatus() const;

    // getTotalFloors:
    // Returns the building's floor count for validation and display.
    int getTotalFloors() const;
};

#endif
