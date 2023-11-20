#define _CRT_SECURE_NO_WARNINGS 
#define GRID_WIDTH 21
#define GRID_HEIGHT 16
#define INITIAL_CASTAR_COINS 100
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

// Structure unit
typedef struct {
    int x, y;
    int movementRange;
} Unit;

// Structure building
typedef struct {
    int x, y;
} Building;


void menu() {
    //variables
    int choice;
  
    //start menu
    Startmenu:
    printf("Welcome to the Ring World!\n\n");

    printf("1. Start New Game\n");
    printf("2. Load Game\n");
    printf("3. Settings\n");
    printf("4. Exit\n\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

   
    switch(choice)
    {
       case 1:
          system("cls");
          printf("\nStarting a new game...\n");
          getchar();
          break;

       case 2:
          system("cls");
          printf("\nLoading game...\n");
          getchar();
          break;

       case 3:
          system("cls");
          printf("\nEntering settings...\n");
          getchar();
          break;

       case 4:
          system("cls");
          printf("\nExiting the Ring World. See you soon..!\n");
          getchar();
          break;

      default:
          printf("\nInvalid choice, please select a number between 1-4.\n");
          getchar(); 
          goto Startmenu;
          break;
    }
    printf("end");
    return 0;
}

// Function to display the game grid
void displayGrid(Unit* units, int numUnits, Building* buildings, int numBuildings);

// Function to display available actions
void displayActions();

int main() {
    menu();

    int currentPlayer = 1;
    int castarCoins[2] = { INITIAL_CASTAR_COINS, INITIAL_CASTAR_COINS };
    Unit units[2];
    Building buildings[2];

    // Game loop
    while (1) {
        system("cls");
        displayGrid(units, 2, buildings, 2);
        printf("Vez do jogador %d\n", currentPlayer);
        printf("Castar Coins: %d\n", castarCoins[currentPlayer - 1]);

        displayActions();

        int choice;
        printf("Opção: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // Place building
            break;
        case 2:
            // Select unit
            break;
        case 3:
            // Move unit
            break;
        case 4:
            // Attack
            break;
        case 5:
            // End turn
            // Switch players
            currentPlayer = (currentPlayer % 2) + 1;
            break;
        default:
            printf("Opção Inválida. Escolher outra vez.\n");
        }
    }

    return 0;
}

void displayGrid(Unit* units, int numUnits, Building* buildings, int numBuildings) {
    // Print letters
    printf("   ");
    for (int i = 0; i < GRID_WIDTH; i++) {
        printf(" %c", 'A' + i);
    }
    printf("\n");

    // Print top border
    printf("   ");
    printf("%c%c%c", 218, 196, 194);
    for (int i = 0; i < (GRID_WIDTH / 2) * 2 - 1; i++) {
        printf("%c%c", 196, 194);
    }
    printf("%c%c", 196, 191);
    printf("\n");

    // Print grid
    for (int i = 0; i < GRID_HEIGHT; i++) {
        // Prin left border and numbers
        printf("%2d %c", i + 1, 179);

        for (int j = 0; j < GRID_WIDTH; j++) {
            // Check if a unit or building in this position
            int unitOrBuilding = 0;
            for (int k = 0; k < numUnits; k++) {
                if (units[k].x == j && units[k].y == i) {
                    printf("U");
                    unitOrBuilding = 1;
                    break;
                }
            }
            if (!unitOrBuilding) {
                for (int k = 0; k < numBuildings; k++) {
                    if (buildings[k].x == j && buildings[k].y == i) {
                        printf("B");
                        unitOrBuilding = 1;
                        break;
                    }
                }
            }

            // If no unit or building print empty cell
            if (!unitOrBuilding) {
                printf("E");
            }

            // Print vertical bordar
            if (j < GRID_WIDTH - 1) {
                printf("%c", 179);
            }
        }

        // Print right border
        printf("%c\n", 179, i + 1);

        // Print horizontal border
        if (i < GRID_HEIGHT - 1) {
            printf("   ");
            printf("%c%c%c", 195, 196, 197);
            for (int j = 0; j < (GRID_WIDTH / 2) * 2 - 1; j++) {
                printf("%c%c", 196, 197);
            }
            printf("%c%c", 196, 180);

            printf("\n");
        }
    }
    // Print bottom border
    printf("   ");
    printf("%c%c%c", 192, 196, 193);
    for (int i = 0; i < (GRID_WIDTH / 2) * 2 - 1; i++) {
        printf("%c%c", 196, 193);
    }
    printf("%c%c", 196, 217);
    printf("\n");
}


void displayActions() {
    // Display available actions for the player
    printf("1. Place Building\n");
    printf("2. Select Unit\n");
    printf("3. Move Unit\n");
    printf("4. Attack\n");
    printf("5. End Turn\n");
}






