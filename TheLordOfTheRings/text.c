#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;

    printf("Welcome to the Ring World!\n\n");

    printf("1. Start New Game\n");
    printf("2. Load Game\n");
    printf("3. Settings\n");
    printf("4. Exit\n\n");

    do {

        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Starting a new game...\n");
        }
        else if(choice == 2)
        {
            printf("Loading game...\n");
        }
        else if(choice == 3)
        {
            printf("Entering settings...\n");
        }
        else if(choice == 4)
        {
            printf("Exiting the Ring World. See you soon..!\n");
        }
        else
        {
            printf("Invalid choice, please select a number between 1-4.\n");
        }

    } while (choice != 4);

    return 0;
}
