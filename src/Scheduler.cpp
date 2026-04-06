#include "Scheduler.h"

#include <algorithm>
#include <cmath>
#include <iostream>

// Constructor implementation:
// Stores the algorithm name that will be used later for path calculation.
Scheduler::Scheduler(const std::string& algorithm) {
    algorithmType = algorithm;
}

// setAlgorithm implementation:
// Overwrites the old algorithm name with a new one.
void Scheduler::setAlgorithm(const std::string& algorithm) {
    algorithmType = algorithm;
}

// getAlgorithm implementation:
// Returns the current algorithm choice without changing it.
std::string Scheduler::getAlgorithm() const {
    return algorithmType;
}

// computeFCFS implementation:
// Simply returns the queue as-is because FCFS uses arrival order.
std::vector<int> Scheduler::computeFCFS(const std::vector<int>& requestQueue, int currentFloor) const {
    (void)currentFloor; // This tells the compiler currentFloor is unused on purpose.

    // This handles the simple case where there is nothing to schedule.
    if (requestQueue.empty()) {
        std::cout << "No pending requests.\n";
        return {};
    }

    // Returning the queue directly works because FCFS does not reorder anything.
    return requestQueue;
}

// computeSSTF implementation:
// Repeatedly chooses the floor with the smallest distance from the current position.
std::vector<int> Scheduler::computeSSTF(const std::vector<int>& requestQueue, int currentFloor) const {
    // This handles the empty input case before any loop starts.
    if (requestQueue.empty()) {
        std::cout << "No pending requests.\n";
        return {};
    }

    // remaining stores floors we have not used yet, and path stores the answer.
    std::vector<int> remaining = requestQueue;
    std::vector<int> path;
    int position = currentFloor;

    // This loop keeps running until every requested floor has been added to the path.
    while (!remaining.empty()) {
        int bestIndex = 0;
        int bestDistance = std::abs(remaining[0] - position);

        // This loop checks every remaining floor to find the closest one.
        for (size_t i = 1; i < remaining.size(); i++) {
            int currentDistance = std::abs(remaining[i] - position);
            if (currentDistance < bestDistance) {
                bestDistance = currentDistance;
                bestIndex = static_cast<int>(i);
            }
        }

        // This adds the closest floor to the path and moves the position there.
        path.push_back(remaining[bestIndex]);
        position = remaining[bestIndex];

        // This removes the used floor so it is not chosen again later.
        remaining.erase(remaining.begin() + bestIndex);
    }

    // The finished path is returned once every request has been ordered.
    return path;
}

// computeSCAN implementation:
// Splits floors into above and below groups, then visits them based on direction.
std::vector<int> Scheduler::computeSCAN(const std::vector<int>& requestQueue, int currentFloor, const std::string& direction) const {
    // This stops early if there is nothing to sort or visit.
    if (requestQueue.empty()) {
        std::cout << "No pending requests.\n";
        return {};
    }

    // above stores requests at or above the elevator, and below stores lower requests.
    std::vector<int> above;
    std::vector<int> below;
    std::vector<int> path;

    // This loop separates requests into two groups around the current floor.
    for (size_t i = 0; i < requestQueue.size(); i++) {
        if (requestQueue[i] >= currentFloor) {
            above.push_back(requestQueue[i]);
        } else {
            below.push_back(requestQueue[i]);
        }
    }

    // These sorts arrange the groups in the order SCAN needs to visit them.
    std::sort(above.begin(), above.end());
    std::sort(below.begin(), below.end(), std::greater<int>());

    // This chooses which group gets visited first based on the current direction.
    if (direction == "up") {
        // When moving up, the elevator visits higher floors first, then comes back down.
        for (size_t i = 0; i < above.size(); i++) {
            path.push_back(above[i]);
        }
        for (size_t i = 0; i < below.size(); i++) {
            path.push_back(below[i]);
        }
    }
    else {
        // When moving down, the elevator visits lower floors first, then goes back up.
        for (size_t i = 0; i < below.size(); i++) {
            path.push_back(below[i]);
        }
        for (size_t i = 0; i < above.size(); i++) {
            path.push_back(above[i]);
        }
    }

    // The combined visit order is returned as the final SCAN path.
    return path;
}

// getOptimalPath implementation:
// Checks the saved algorithm text and calls the matching scheduling function.
std::vector<int> Scheduler::getOptimalPath(const std::vector<int>& requestQueue, int currentFloor, const std::string& direction) const {
    // This branch runs FCFS if that is the chosen algorithm.
    if (algorithmType == "FCFS") {
        return computeFCFS(requestQueue, currentFloor);
    }

    // This branch runs SSTF if that is the chosen algorithm.
    if (algorithmType == "SSTF") {
        return computeSSTF(requestQueue, currentFloor);
    }

    // This branch runs SCAN if that is the chosen algorithm.
    if (algorithmType == "SCAN") {
        return computeSCAN(requestQueue, currentFloor, direction);
    }

    // If the input is invalid, the program falls back to FCFS so it still works.
    std::cout << "Invalid algorithm choice. Defaulting to FCFS.\n";
    return computeFCFS(requestQueue, currentFloor);
}
