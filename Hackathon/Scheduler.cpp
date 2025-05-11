#include "Scheduler.h"
#include "TeamQueue.h" // Include TeamQueue
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <chrono>

// Constants
const int MAX_TEAMS = 16;
const int MAX_MEMBERS = 4;
const int MEMBER_NAME_SIZE = 50;

// Constructor
Scheduler::Scheduler() : teamCount(0) {
    for (int i = 0; i < 4; i++) {
        matchList[i] = MatchList(); // Initialize each MatchList
    }
}

void Scheduler::loadTeamsFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file!\n";
        return;
    }

    while (teamCount < MAX_TEAMS) {
        Team newTeam = {};
        file >> newTeam.rank;
        if (file.fail()) break;
        file.ignore();
        file.getline(newTeam.teamName, sizeof(newTeam.teamName));

        newTeam.memberCount = 0;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (file.peek() == '\n' || file.eof()) break;
            char member[MEMBER_NAME_SIZE];
            file.getline(member, sizeof(member));
            if (strlen(member) > 0) {
                strncpy_s(newTeam.members[newTeam.memberCount], sizeof(newTeam.members[newTeam.memberCount]), member, _TRUNCATE);
                newTeam.memberCount++;
            }
        }
        teams[teamCount++] = newTeam;
        std::cout << "Loaded team: " << newTeam.teamName << ", Rank: " << newTeam.rank << std::endl;
    }

    file.close();
    sortTeamsByRank();
}

// Sort teams by rank
void Scheduler::sortTeamsByRank() {
    for (int i = 0; i < teamCount - 1; i++) {
        for (int j = 0; j < teamCount - i - 1; j++) {
            if (teams[j].rank > teams[j + 1].rank) {
                Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
    std::cout << "Teams sorted by rank." << std::endl;
}

void Scheduler::scheduleFirstRound() {
    time_t now = time(0); // Get the current time
    tm ltm; // Local time
    localtime_s(&ltm, &now); // Convert the current time to the local time
    char date[20];
    sprintf_s(date, sizeof(date), "%04d-%02d-%02d", 1900 + ltm.tm_year, 1 + ltm.tm_mon, ltm.tm_mday); // Format the date

    // Shuffle the first 8 teams and the last 8 teams separately
    shuffleTeams(teams, 8);
    shuffleTeams(teams + 8, 8);

    for (int i = 0; i < 8; i++) {
        Match newMatch; // Create a new match
        strcpy_s(newMatch.team1, sizeof(newMatch.team1), teams[i].teamName); // Copy the team name to the match
        strcpy_s(newMatch.team2, sizeof(newMatch.team2), teams[i + 8].teamName); // Copy the team name to the match
        strcpy_s(newMatch.date, sizeof(newMatch.date), date); // Copy the date to the match
        strcpy_s(newMatch.time, sizeof(newMatch.time), "10:00 AM"); // Copy the time to the match
        newMatch.completed = false; // Set the match as incomplete
        strcpy_s(newMatch.winner, sizeof(newMatch.winner), "N/A"); // Set the winner as N/A

        matchList[0].addMatch(newMatch); // Add the match to the first round
    }
}

// Shuffle teams
void Scheduler::shuffleTeams(Team teams[], int size) {
    for (int i = 0; i < size; i++) {
        int randomIndex = rand() % size;
        Team temp = teams[i];
        teams[i] = teams[randomIndex];
        teams[randomIndex] = temp;
    }
    std::cout << "Teams shuffled." << std::endl;
}

int Scheduler::getCurrentRound() {
    for (int i = 0; i < 4; i++) {
        // If the current round has no matches or is incomplete, return its index
        if (!matchList[i].head || !matchList[i].head->completed) {
            return i;
        }
    }
    return 4; // Tournament is complete
}

void Scheduler::scheduleNextRound(int currentRound) {
    if (currentRound <= 0 || currentRound >= 4) {
        throw std::runtime_error("Invalid round index. It must be between 1 and 3.");
    }

    if (!matchList[currentRound - 1].head) {
        throw std::runtime_error("Cannot schedule the next round. No matches found in the previous round.");
    }

    Match* prevRound = matchList[currentRound - 1].head;
    TeamQueue winnersQueue;

    // For each match in the previous round
    while (prevRound != nullptr) {
        Team winner;
        if (strcmp(prevRound->winner, prevRound->team1) == 0) { // If team1 is the winner
            strcpy(winner.teamName, prevRound->team1);
        }
        else { // If team2 is the winner
            strcpy(winner.teamName, prevRound->team2);
        }
        winnersQueue.enqueue(winner);
        prevRound = prevRound->next;
    }

    // While there are winners in the queue
    while (!winnersQueue.isEmpty()) {
        Team team1 = winnersQueue.dequeue(); // Dequeue the first winner
        if (winnersQueue.isEmpty()) break;

        Team team2 = winnersQueue.dequeue(); // Dequeue the second winner
        Match newMatch;
        strcpy(newMatch.team1, team1.teamName);
        strcpy(newMatch.team2, team2.teamName);
        strcpy(newMatch.date, "2024-12-31");
        strcpy(newMatch.time, "10:00 AM");
        newMatch.completed = false;
        strcpy(newMatch.winner, "N/A");

        matchList[currentRound].addMatch(newMatch); // Adding the match to the current round match list
    }
}

void Scheduler::reset() {
    // Reset the team count
    teamCount = 0;

    // Clear the match lists
    for (int i = 0; i < 4; ++i) {
        Match* current = matchList[i].head;
        while (current != nullptr) {
            Match* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        matchList[i].head = nullptr;
    }
}

const char* Scheduler::getWinnerTeam() {
    if (getCurrentRound() < 4) {
        throw std::runtime_error("The tournament is not yet complete.");
    }

    Match* finalMatch = matchList[3].head;
    while (finalMatch != nullptr) {
        if (finalMatch->completed) {
            return finalMatch->winner;
        }
        finalMatch = finalMatch->next;
    }

    throw std::runtime_error("No winner found.");
}
