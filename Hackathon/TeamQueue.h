#ifndef TEAMQUEUE_H
#define TEAMQUEUE_H

#include "Team.h"

// Queue for managing teams progressing through rounds
struct QueueNode
{
    Team team;
    QueueNode* next; // Pointer to the next node in the queue
};

class TeamQueue
{
public:
    QueueNode* front;
    QueueNode* back;

    TeamQueue() : front(nullptr), back(nullptr) {}
    void enqueue(Team newTeam);
    Team dequeue();
    bool isEmpty();
};

#endif
