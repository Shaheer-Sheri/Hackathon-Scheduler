#include "Match.h"
#include <iostream>
#include <cstring>

MatchList::MatchList() : head(nullptr) {}

MatchList::~MatchList() {
    while (head) {
        Match* temp = head;
        head = head->next;
        delete temp;
    }
}

void MatchList::addMatch(const Match& newMatch) {
	Match* temp = new Match(); // Create a new match
	*temp = newMatch; // Copy the new match data
	temp->next = head; // Set the next pointer to the current head
	head = temp; // Set the new match as the head
}

