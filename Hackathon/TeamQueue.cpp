#include "TeamQueue.h"
#include <iostream>
using namespace std;

void TeamQueue::enqueue(Team newTeam)
{
    QueueNode* temp = new QueueNode();
    temp->team = newTeam;
    temp->next = nullptr;
    if (back == nullptr)
    {
        front = back = temp;
    }
    else
    {
        back->next = temp;
        back = temp;
    }
}

Team TeamQueue::dequeue()
{
    if (front == nullptr)
    {
        cout << "Queue is empty!" << endl;
        exit(1);
    }

    Team team = front->team;
    QueueNode* temp = front;
    front = front->next;
    if (front == nullptr)
    {
        back = nullptr;
    }
    delete temp;
    return team;
}

bool TeamQueue::isEmpty()
{
    return front == nullptr;
}