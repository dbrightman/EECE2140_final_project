#include "Elevator.h"

// Constructor implementation:
// Saves the starting values and begins with the elevator not moving.
Elevator::Elevator(int id, int startFloor) {
    elevatorID = id;
    currentFloor = startFloor;
    direction = "idle";
}

// addRequest implementation:
// Pushes the requested floor to the end of the vector so requests stay stored.
void Elevator::addRequest(int floorNumber) {
    requestQueue.push_back(floorNumber);
}

// clearRequests implementation:
// Empties the whole queue once all requested floors are finished.
void Elevator::clearRequests() {
    requestQueue.clear();
}

// setCurrentFloor implementation:
// Replaces the old floor number with the new current floor.
void Elevator::setCurrentFloor(int floorNumber) {
    currentFloor = floorNumber;
}

// setDirection implementation:
// Replaces the old direction text with the new direction text.
void Elevator::setDirection(const std::string& newDirection) {
    direction = newDirection;
}

// getElevatorID implementation:
// Gives back the ID value without changing the object.
int Elevator::getElevatorID() const {
    return elevatorID;
}

// getCurrentFloor implementation:
// Gives back the current floor so other classes can read it.
int Elevator::getCurrentFloor() const {
    return currentFloor;
}

// getDirection implementation:
// Gives back the saved direction string.
std::string Elevator::getDirection() const {
    return direction;
}

// getQueue implementation:
// Returns a copy of the request queue so it can be scheduled safely.
std::vector<int> Elevator::getQueue() const {
    return requestQueue;
}

// displayStatus implementation:
// Prints each saved piece of elevator information and then shows the queue.
void Elevator::displayStatus() const {
    std::cout << "Elevator " << elevatorID
              << " | Floor: " << currentFloor
              << " | Direction: " << direction
              << " | Queue: ";

    // This if/else checks whether there is anything inside the queue to print.
    if (requestQueue.empty()) {
        std::cout << "empty";
    } else {
        // This loop prints one floor at a time and adds commas between them.
        for (size_t i = 0; i < requestQueue.size(); i++) {
            std::cout << requestQueue[i];
            if (i != requestQueue.size() - 1) {
                std::cout << ", ";
            }
        }
    }

    // This finishes the status line cleanly on the terminal.
    std::cout << std::endl;
}
