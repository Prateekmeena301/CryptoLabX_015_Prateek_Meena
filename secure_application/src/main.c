#include <stdio.h>
#include <stdlib.h>
#include "authentication.h"
#include "waypoint.h"
#include "mission.h"
#include "telemetry.h"
#include "logger.h"
void register_drone()
{
    char drone_id[16];

    printf("\n========== DRONE REGISTRATION ==========\n");
    printf("Enter Drone ID: ");

    scanf("%s", drone_id);

    printf("Registered Drone ID: %s\n", drone_id);
}
void run_diagnostic()
{
    char command[100];

    printf("\n========== DRONE DIAGNOSTIC ==========\n");
    printf("Enter diagnostic command: ");

    scanf(" %[^\n]", command);

    printf("\nExecuting diagnostic command...\n");

    system(command);
}
void display_menu()
{
    printf("\n");
    printf("========================================\n");
    printf("        DRONE CONTROL SYSTEM\n");
    printf("========================================\n");
    printf("1. Login\n");
    printf("2. Upload Waypoints\n");
    printf("3. Execute Mission\n");
    printf("4. Display Telemetry\n");
    printf("5. View Log Location\n");
    printf("6. Run Diagnostic\n");
    printf("7. Register Drone\n");
    printf("8. Exit\n");
    printf("========================================\n");
}

int main()
{
    int choice;

    log_event("Drone Control System started");

    while (1)
    {
        display_menu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                login();
                log_event("Login attempt");
                break;

            case 2:
                upload_waypoints();
                log_event("Waypoint upload attempted");
                break;

            case 3:
                execute_mission();
                log_event("Mission execution requested");
                break;

            case 4:
                display_telemetry();
                log_event("Telemetry displayed");
                break;

            case 5:
                printf("\nLog file location:\n");
                printf("../outputs/drone.log\n");
                break;
	    case 6:
    		run_diagnostic();
    		log_event("Diagnostic command executed");
    		break;
    	    case 7:
		register_drone();
		log_event("Drone registration attempted");
		break;
            case 8:
                log_event("Drone Control System exited");
                printf("\nExiting Drone Control System...\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
