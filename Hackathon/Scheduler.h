#pragma once
#include "Team.h"
#include "Match.h"
#include "TeamQueue.h"

class Scheduler {
public:
    Team teams[16]; // 16 teams
    int teamCount; // number of teams
    MatchList matchList[4]; // 4 rounds

    Scheduler();
    void loadTeamsFromFile(const char* filename);  //load teams from file
    void sortTeamsByRank(); //sort teams by rank
    void scheduleFirstRound(); //schedule first round
    void shuffleTeams(Team teams[], int size); //shuffle teams
    void scheduleNextRound(int currentRound); //schedule next round
    int getCurrentRound(); //get current round
    void reset(); //reset the scheduler
    const char* getWinnerTeam(); //get winner team
};
