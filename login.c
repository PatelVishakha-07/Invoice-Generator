#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"

int login() {
    clearScreen();

    char username[20], password[20], ch;
    char correctUser[] = "admin", correctPass[] = "1234";
    int i;

    while (1) {
        system("cls");
        printf("\n");
        printf(" \t\t\t\t    =====================================================================================\n");
        printf(" \t\t\t\t   ||                                                                                    ||\n");
        printf(" \t\t\t\t   ||                WELCOME TO GENERAL STORE INVOICE GENERATOR SYSTEM                   ||\n");
        printf(" \t\t\t\t   ||                                                                                    ||\n");
        printf(" \t\t\t\t    =====================================================================================\n\n");

        printf("\t\t\t\t\t    -------------------------------------------------------------------------\n");
        printf("\t\t\t\t\t   |                                                                         |\n");
        printf("\t\t\t\t\t   |   Username : ");
        scanf("%19s", username);
        printf("\t\t\t\t\t   |                                                                         |\n");

        printf("\t\t\t\t\t   |   Password : ");

        // Password with masking
        i = 0;
        while (1) {
            ch = getch();

            if (ch == 13) {
                password[i] = '\0';
                break;
            }
            if (ch == 8 && i > 0) {
                i--;
                printf("\b \b");
                continue;
            }
            if (ch != 8) {
                password[i] = ch;
                i++;
                printf("*");
            }
        }

        printf("\n\t\t\t\t\t   |                                                                         |\n");
        printf("\t\t\t\t\t    -------------------------------------------------------------------------\n");

        if (strcmp(username, correctUser) == 0 && strcmp(password, correctPass) == 0) {
            printf("\n\n");
            printf("  \t\t\t\t    --------------------------------------------------------------------------------------\n");
            printf("  \t\t\t\t\t\t      Login Successful! Access Granted...\n");
            printf("  \t\t\t\t    --------------------------------------------------------------------------------------\n");

            printf("  \n\n\t\t\t\t\t\t      Please Press Any Key To Continue...\n");
            getch();
            system("cls");
            return 1;
        }
        else {
            printf("\n\n\n  \t\t\t\t    --------------------------------------------------------------------------------------\n");
            printf("  \t\t\t\t\t        Incorrect Username or Password! Please Press Any Key To Try Again.\n");
            printf("  \t\t\t\t    --------------------------------------------------------------------------------------\n");
            getch();
        }
    }
}
