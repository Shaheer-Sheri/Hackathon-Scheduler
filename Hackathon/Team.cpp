#include "Team.h"
#include <iostream>
#include <cstring>

// Constructor
Team::Team() {
    teamName[0] = '\0';
    memberCount = 0;
    rank = 0;

    for (int i = 0; i < 4; ++i) {
        members[i][0] = '\0';
    }
}

// Add a member to the team
void Team::addMember(const char* memberName) {
    if (memberCount < 4) {
        // Copy the member name to the members array, ensuring it does not exceed the buffer size
        strncpy(members[memberCount], memberName, sizeof(members[memberCount]) - 1);
        // Ensure the string is null-terminated
        members[memberCount][sizeof(members[memberCount]) - 1] = '\0';
        // Increment the member count
        memberCount++;
    }
    else {
        // Print an error message if the team is full
        std::cerr << "Team is full. Cannot add more members.\n";
    }
}

