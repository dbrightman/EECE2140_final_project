#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <vector>

// This class handles path planning for an elevator.
// It keeps the scheduling logic separate from the elevator data itself.
class Scheduler {
private:
    // This stores which algorithm the user chose.
    std::string algorithmType;

public:
    // Constructor:
    // Saves the starting algorithm name so the scheduler knows what to use.
    Scheduler(const std::string& algorithm = "FCFS");

    // setAlgorithm:
    // Changes the saved algorithm when the user picks a different one.
    void setAlgorithm(const std::string& algorithm);

    // getAlgorithm:
    // Returns the current algorithm name for printing and checking.
    std::string getAlgorithm() const;

    // computeFCFS:
    // Returns floors in the same order they were originally requested.
    std::vector<int> computeFCFS(const std::vector<int>& requestQueue, int currentFloor) const;

    // computeSSTF:
    // Builds a path by repeatedly choosing the closest next floor.
    std::vector<int> computeSSTF(const std::vector<int>& requestQueue, int currentFloor) const;

    // computeSCAN:
    // Builds a path by moving one direction first and then reversing.
    std::vector<int> computeSCAN(const std::vector<int>& requestQueue, int currentFloor, const std::string& direction) const;

    // getOptimalPath:
    // Calls the correct function based on the saved algorithm choice.
    std::vector<int> getOptimalPath(const std::vector<int>& requestQueue,int currentFloor, const std::string& direction) const;
};

#endif
