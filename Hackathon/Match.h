#pragma once

struct Match {
    char team1[50];
    char team2[50];
    char date[20];
    char time[10];
    bool completed;
    char winner[50];
    Match* next;
};

class MatchList {
public:
	Match* head; // Pointer to the first match in the list

    MatchList();
    ~MatchList();
	void addMatch(const Match& newMatch); // Add a new match to the list
};
