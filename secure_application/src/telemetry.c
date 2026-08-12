#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "telemetry.h"

void display_telemetry()
{
    printf("\n========== DRONE TELEMETRY ==========\n");

    srand(time(NULL));

    int battery = 50 + rand() % 51;
    int altitude = 20 + rand() % 81;
    int speed = 10 + rand() % 31;

    printf("Battery Level : %d%%\n", battery);
    printf("Altitude      : %d meters\n", altitude);
    printf("Speed         : %d km/h\n", speed);
    printf("GPS Status    : Connected\n");
    printf("Drone Status  : Operational\n");
}
