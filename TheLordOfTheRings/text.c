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

int main() {
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
