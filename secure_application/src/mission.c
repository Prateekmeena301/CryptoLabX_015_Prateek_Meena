#include <stdio.h>
#include <unistd.h>
#include "mission.h"

void execute_mission()
{
    printf("\n========== MISSION EXECUTION ==========\n");

    printf("Checking mission data...\n");
    sleep(1);

    printf("Starting drone mission...\n");
    sleep(1);

    printf("Drone taking off...\n");
    sleep(1);

    printf("Drone following uploaded waypoints...\n");
    sleep(1);

    printf("Mission in progress...\n");
    sleep(1);

    printf("Drone returning to base...\n");
    sleep(1);

    printf("Drone landed successfully.\n");
    printf("Mission completed.\n");
}
