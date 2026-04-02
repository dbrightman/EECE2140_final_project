# Elevator Path Tracking System

## Team Members
- Daniel Brightman
- Joel Kamhazi

## Project Overview
A C++ terminal program that simulates multiple elevators in a building. The user submits floor requests, and the system assigns each request to the nearest elevator and processes it using a chosen scheduling algorithm. All output is printed to the terminal.

## Main Functionalities
- Add a floor request to an elevator's queue
- Track each elevator's current floor and direction
- Calculate travel paths using FCFS, SSTF, or SCAN algorithms
- Assign incoming requests to the closest available elevator
- Run a step-by-step simulation and log every movement

## OOP Design Summary
- **Elevator** - stores floor, direction, and request queue; handles movement
- **Scheduler** - computes FCFS, SSTF, and SCAN paths
- **Building** - holds all elevators, dispatches requests to the best one
- **Simulation** - runs the movement loop and records the event log

## Tools and Technologies
- C++
- Arduino (serial display demo)
- Git / GitHub

## Folder Structure
```
ElevatorPathTracker/
├── README.md
├── docs/
│   └── System_Design_Overview.pdf
├── pseudocode/
│   └── pseudocode.tex
├── src/
│   ├── main.cpp
│   ├── Elevator.h
│   ├── Elevator.cpp
│   ├── Scheduler.h
│   ├── Scheduler.cpp
│   ├── Building.h
│   ├── Building.cpp
│   ├── Simulation.h
│   └── Simulation.cpp
└── images/
    └── system_diagram.png
```

## Project Goals
- Simulate elevator movement for any building configuration
- Implement and compare three scheduling strategies (FCFS, SSTF, SCAN)
- Measure efficiency: wait time, travel time, stops, and total floors traveled
- Build an Arduino demo that shows current floor and direction in real time

## GitHub Repository Purpose
This repository stores all source code, pseudocode, documentation, and project assets for the Elevator Path Tracking System. It tracks team contributions and progress across all iterations of the project.