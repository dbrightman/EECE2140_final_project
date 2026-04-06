#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <string>
#include <vector>

// This class represents one elevator in the building.
// It groups all elevator data together so the rest of the program
// can work with one object instead of many separate variables.
class Elevator {
private:
    // These variables store the elevator's identity and current state.
    int elevatorID;
    int currentFloor;
    std::string direction;
    std::vector<int> requestQueue;

public:
    // Constructor:
    // Creates an elevator object and gives it a starting ID and floor.
    Elevator(int id = 0, int startFloor = 1);

    // addRequest:
    // Adds one new requested floor to the back of the queue.
    void addRequest(int floorNumber);

    // clearRequests:
    // Removes all saved requests after they have been completed.
    void clearRequests();

    // setCurrentFloor:
    // Updates the elevator's location after moving.
    void setCurrentFloor(int floorNumber);

    // setDirection:
    // Updates whether the elevator is moving up, down, or idle.
    void setDirection(const std::string& newDirection);

    // getElevatorID:
    // Returns the elevator's ID so other classes can identify it.
    int getElevatorID() const;

    // getCurrentFloor:
    // Returns the elevator's current position in the building.
    int getCurrentFloor() const;

    // getDirection:
    // Returns the direction string stored in the object.
    std::string getDirection() const;

    // getQueue:
    // Returns a copy of the floor request list for scheduling.
    std::vector<int> getQueue() const;

    // displayStatus:
    // Prints the elevator's current data in a readable terminal format.
    void displayStatus() const;
};

#endif
