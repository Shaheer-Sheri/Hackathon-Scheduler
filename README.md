# Hackathon-Scheduler
Hackathon Scheduler – A C++ application that manages and simulates cybersecurity hackathons. Built using arrays, pointers, and structures with Windows Forms for a user-friendly interface. The system supports team registration, match scheduling, round simulation, and automatic winner calculation. Developed as a semester project for CS-213 (DSA)

# Hackathon Scheduler (C++ DSA Semester Project)

## Overview
Hackathon Scheduler is a C++ application developed using core data structures and Windows Forms. It allows users to manage a cybersecurity-themed hackathon by registering teams, scheduling matches, simulating rounds, and identifying winners. Built as part of the Data Structures and Algorithms course (CS-213), this project applies practical concepts like arrays, pointers, structures, and queues.

## Features
- Add and manage teams
- Schedule and simulate rounds
- Automatically determine match outcomes and the final winner
- Responsive UI with background simulation using `BackgroundWorker`
- Easy navigation through all hackathon stages

## Program Flow
1. **Startup**: Main interface (`MyForm`) launches with hackathon info and "Start" button
2. **Add Teams**: User inputs teams in the `AddTeams` form
3. **Manage Rounds**: Navigate to `ManageRounds` form for scheduling and simulation
4. **Simulation**: Matches simulate in the background for a responsive experience
5. **Completion**: Final winner displayed at the end

## Major Components
- `MyForm`: Main welcome screen
- `AddTeams`: Interface for team registration
- `ManageRounds`: Schedule and simulate matches
- `Scheduler`: Logic for match generation and results tracking
- `TeamQueue`: Custom queue for managing team progression

## Data Structures Used
- **Arrays**: To store teams, members, match data
- **Pointers**: For managing linked match lists and dynamic data
- **Structures**:
  - `Team`: Stores team info and members
  - `Match`: Represents a single match with participants and results
  - `MatchList`: Linked list of matches per round
- **Custom Queue** (`TeamQueue`): For handling team order during scheduling

## Technologies
- C++
- Windows Forms
- Object-Oriented Programming
- Core Data Structures (arrays, pointers, structs)

## Future Improvements
- Real-time scoring system
- Export match results to a file
- Support for online team registration

---

**Note**: This project was developed as a semester assignment for the CS-213 course (Data Structures and Algorithms).

