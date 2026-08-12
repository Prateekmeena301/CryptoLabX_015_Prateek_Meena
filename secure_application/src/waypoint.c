#include <stdio.h>
#include <stdlib.h>
#include "waypoint.h"

void upload_waypoints()
{
    int number_of_waypoints;

    printf("\n========== WAYPOINT UPLOAD ==========\n");

    printf("Enter number of waypoints: ");
    scanf("%d", &number_of_waypoints);

    if (number_of_waypoints <= 0)
    {
        printf("Invalid number of waypoints.\n");
        return;
    }

    FILE *file = fopen("../outputs/waypoints.txt", "w");

    if (file == NULL)
    {
        printf("Error opening waypoint file.\n");
        return;
    }

    for (int i = 0; i < number_of_waypoints; i++)
    {
        double latitude;
        double longitude;

        printf("\nWaypoint %d\n", i + 1);

        printf("Latitude: ");
        scanf("%lf", &latitude);

        printf("Longitude: ");
        scanf("%lf", &longitude);

        fprintf(file, "Waypoint %d: Latitude=%lf Longitude=%lf\n",
                i + 1, latitude, longitude);
    }

    fclose(file);

    printf("\nWaypoints uploaded successfully.\n");
}
