#include <stdio.h>
#include <string.h>
#include "authentication.h"

static int authenticated = 0;

int login()
{
    char username[50];
    char password[50];

    printf("\n========== DRONE LOGIN ==========\n");

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "drone123") == 0)
    {
        authenticated = 1;
        printf("\nLogin successful!\n");
        return 1;
    }

    printf("\nInvalid username or password.\n");
    return 0;
}

int is_authenticated()
{
    return authenticated;
}
