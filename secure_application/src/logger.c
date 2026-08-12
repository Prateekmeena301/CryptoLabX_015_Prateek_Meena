#include <stdio.h>
#include <time.h>
#include "logger.h"

void log_event(const char *event)
{
    FILE *file = fopen("../outputs/drone.log", "a");

    if (file == NULL)
    {
        printf("Unable to open log file.\n");
        return;
    }

    time_t current_time = time(NULL);

    fprintf(file, "%s - %s", ctime(&current_time), event);

    fclose(file);
}
