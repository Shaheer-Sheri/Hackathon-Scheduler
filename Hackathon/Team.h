#pragma once

struct Team {
    char teamName[50];
    char members[4][50];
    int memberCount;
    int rank;

    Team();
    void addMember(const char* memberName);
};
