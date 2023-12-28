#define _CRT_SECURE_NO_WARNINGS
#define GRID_WIDTH 26
#define GRID_HEIGHT 16
// constants for economy and costs
#define INITIAL_CASTAR_COINS 100
#define INFANTRY_MOVEMENT_COST 2
#define CAVALRY_MOVEMENT_COST 1
#define ARTILLERY_MOVEMENT_COST 3
#define MINE_INCOME 5 // per turn
#define BASE_COST 30
#define MINE_COST 20
#define BARRACKS_COST 25
#define STABLES_COST 25
#define ARMOURY_COST 30
#define INFANTRY_COST 10
#define CAVALRY_COST 15
#define ARTILLERY_COST 20
// constants for combat and health
#define INFANTRY_ATTACK_POWER 5
#define CAVALRY_ATTACK_POWER 7
#define ARTILLERY_ATTACK_POWER 10
#define BASE_HEALTH 100
#define MINE_HEALTH 50
#define BARRACKS_HEALTH 70
#define STABLES_HEALTH 70
#define ARMOURY_HEALTH 70
#define INFANTRY_HEALTH 30
#define CAVALRY_HEALTH 40
#define ARTILLERY_HEALTH 20
// file
#define SAVE_FILE_EXTENSION ".txt"
// Librarys
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

// array for table positions
char grid[16][26];

// for not clean the table every time menu open
int startverify = 0;

// player team definer
int playerchoice;

// struct info for the player side
struct PlayerClass
{
    int id;
    char name[100];
};

struct PlayerClass playerClass[2] = {
    {1, "Gondor"},
    {2, "Mordor"}};

// struct info for the building type
struct BuildingType
{
    int id;
    int buyCost;
    int health;
};

struct BuildingType buildingType[5] = {
    //  id , cost , health
    {1, BASE_COST, BASE_HEALTH},         // base
    {2, MINE_COST, MINE_HEALTH},         // mine
    {3, BARRACKS_COST, BARRACKS_HEALTH}, // barracks
    {4, STABLES_COST, STABLES_HEALTH},   // stable
    {5, ARMOURY_COST, ARMOURY_HEALTH},   // armoury
};

// struct building
struct Building
{
    int id;
    char name[20];
    char code[4];
    struct PlayerClass *playerclass;
    struct BuildingType *buildingType;
    int x, y;
};

struct Building building[10] = {
    {1, "Bases", "GGGG", &playerClass[0], &buildingType[0]},
    {2, "Mines", "SS", &playerClass[0], &buildingType[1]},
    {3, "Barracks", "RR", &playerClass[0], &buildingType[2]},
    {4, "Stables", "LL", &playerClass[0], &buildingType[3]},
    {5, "Armoury", "GF", &playerClass[0], &buildingType[4]},
    {1, "Bases", "MMMM", &playerClass[1], &buildingType[0]},
    {2, "Mines", "EE", &playerClass[1], &buildingType[1]},
    {3, "Barracks", "II", &playerClass[1], &buildingType[2]},
    {4, "Stables", "MK", &playerClass[1], &buildingType[3]},
    {5, "Armoury", "DF", &playerClass[1], &buildingType[4]}};

// struct info for the unit type
struct UnitType
{
    int id;
    int buyCost;
    int moveCost;
    int health;
    int attackPower;
};

struct UnitType unitType[3] = {
    {1, INFANTRY_COST, INFANTRY_MOVEMENT_COST, INFANTRY_HEALTH, INFANTRY_ATTACK_POWER},    // infantary
    {2, CAVALRY_COST, CAVALRY_MOVEMENT_COST, CAVALRY_HEALTH, CAVALRY_ATTACK_POWER},        // cavalary
    {3, ARTILLERY_COST, ARTILLERY_MOVEMENT_COST, ARTILLERY_HEALTH, ARTILLERY_ATTACK_POWER} // artilary
};

// struct unit type
struct Unit
{
    int id;
    char name[100];
    char code[100];
    struct PlayerClass *playerclass;
    struct UnitType *unitType;
    int x, y;
};

struct Unit unit[6] = {
    {1, "Infantry", "G", &playerClass[0], &unitType[0], 1, 1},
    {2, "Cavalry", "SK", &playerClass[0], &unitType[1], 1, 2},
    {3, "Artillery", "T", &playerClass[0], &unitType[2], 1, 3},
    {1, "Infantry", "OW", &playerClass[1], &unitType[0], 2, 1},
    {2, "Cavalry", "W", &playerClass[1], &unitType[1], 2, 2},
    {3, "Artillery", "ST", &playerClass[1], &unitType[2], 2, 3}};

// struct info player
struct Player
{
    int id;
    int coins;
    struct PlayerClass *playerClass;
    struct Unit *unit[100];
    struct Building *building[100];
};

struct Player players[2];

// ver
struct GameState
{
    char gameName[100];
    struct Player players[2];
};

// declarate functions
void cleantable();
int countBuildings();
int countUnits();
void displayGrid();
void displayActions();
void posicionar(char grid[16][26], int currentplayer, int playerclass);
int *selecionar(char grid[16][26]);
void moverPeca(char grid[GRID_HEIGHT][GRID_WIDTH], int currentPlayer, struct PlayerClass *playerClass);
bool isValidCoordinate(int row, char col);
int convertToGridIndex(char col);
int findUnitIndexByCode(const char *code, int playerClassId);
void saveGameToFile(struct Player players[2], const char *saveFileName);
void loadGameFromFile(struct Player players[2], const char *loadFileName);
void playerRegister(int option);

// clean array table
void cleantable()
{
    for (int u = 0; u < 16; u++)
    {
        for (int i = 0; i < 26; i++)
        {
            grid[u][i] = ' ';
        }
    }
}

void saveGameToFile(struct Player players[2], const char *saveFileName, int currentPlayer)
{
    FILE *file = fopen(saveFileName, "wb");

    int numUnits = 0, numBuildings = 0;

    // players[currentPlayer].building[numBuildings] = malloc(sizeof(struct Building*));

    if (file != NULL)
    {
        // Save player data
        for (int i = 0; i < 2; ++i)
        {
            numUnits = countUnits(i);
            numBuildings = countBuildings(i);

            if (i > 0)
                fprintf(file, "\n--------------- // -------------\n");

            fprintf(file, "Player %d:\n", i + 1);
            fprintf(file, "  ID: %d\n", players[i].id);
            fprintf(file, "  Coins: %d\n", players[i].coins);
            fprintf(file, "  Player Class:\n");
            fprintf(file, "    ID: %d\n", players[i].playerClass->id);
            fprintf(file, "    Name: %s\n", players[i].playerClass->name);

            if (numBuildings > 0)
            {
                fprintf(file, "  Player Buildings:\n");
                for (int j = 0; j < numBuildings; j++)
                {
                    fprintf(file, "    ID: %d\n", players[i].building[j]->id);
                    fprintf(file, "    X: %d\n", players[i].building[j]->x);
                    fprintf(file, "    Y: %d\n", players[i].building[j]->y);
                }
            }

            if (numUnits > 0)
            {
                fprintf(file, "  Player Units:\n");
                for (int j = 0; j < numUnits; j++)
                {
                    fprintf(file, "    ID: %d\n", players[i].unit[j]->id);
                    fprintf(file, "    X: %d\n", players[i].unit[j]->x);
                    fprintf(file, "    Y: %d\n", players[i].unit[j]->y);
                }
            }
        }

        fclose(file);
        printf("Game saved to %s\n", saveFileName);
    }
    else
    {
        printf("Error opening file for writing.\n");
    }
}

// Function to load the game from a file
void loadGameFromFile(struct Player players[2], const char *loadFileName)
{
    FILE *file = fopen(loadFileName, "rb");

    if (file != NULL)
    {
        // Load player data
        for (int i = 0; i < 2; ++i)
        {
            // Assuming the file structure is consistent with the save format
            fscanf(file, "Player %*d:\n");
            fscanf(file, "  ID: %d\n", &players[i].id);
            fscanf(file, "  Coins: %d\n", &players[i].coins);
            fscanf(file, "  Player Class:\n");
            fscanf(file, "    ID: %d\n", &players[i].playerClass->id);
            fscanf(file, "    Name: %s\n", players[i].playerClass->name);
        }

        fclose(file);
        printf("Game loaded from %s\n", loadFileName);
    }
    else
    {
        printf("Error opening file for reading.\n");
    }
}

void playerRegister(int option)
{

    if (option == 1)
    {
        players[0].id = 1;
        players[0].coins = INITIAL_CASTAR_COINS;
        players[0].playerClass = &playerClass[option - 1];
        players[1].id = 2;
        players[1].coins = INITIAL_CASTAR_COINS;
        players[1].playerClass = &playerClass[option];
    }
    else
    {
        players[0].id = 1;
        players[0].coins = INITIAL_CASTAR_COINS;
        players[0].playerClass = &playerClass[option - 1];
        players[1].id = 2;
        players[1].coins = INITIAL_CASTAR_COINS;
        players[1].playerClass = &playerClass[option - 2];
    }
}

// Function to display the game grid
void displayGrid();

// Function to display available actions
void displayActions();

// chose between unit or building
int actionOption()
{
    int option;

    printf("O que deseja posicionar ?\n1: Constru%c%ces\n2: Tropas\n >> ", 135, 228);
    scanf("%d", &option);

    return option;
}

// show buildings for position
char buildingsmenu()
{
    int option;

    do
    {

        system("cls");
        displayGrid();
        printf("\n1:Base == (%dcc)\n2:Mina == (%dcc)\n3:Quartel == (%dcc)\n4:Est%cbulos == (%dcc)\n5:Arsenal == (%dcc)\n >> ", BASE_COST, MINE_COST, BARRACKS_COST, 160, STABLES_COST, ARMOURY_COST);
        scanf("%d", &option);

    } while (option > 5 || option < 1);

    return option;
}

int countBuildings(int currentPlayer)
{
    int count = 0;

    for (int i = 0; i < 100; i++)
    {
        if (players[currentPlayer].building[i] != NULL)
        {
            count++;
        }
    }

    return count;
}

int unitMenu()
{
    int option;

    do
    {

        system("cls");
        displayGrid();
        printf("\n1:Infantaria == (%dcc)\n2:Cavalaria == (%dcc)\n3:Artilharia == (%dcc)\n >>", INFANTRY_COST, CAVALRY_COST, ARTILLERY_COST);
        scanf("%d", &option);

    } while (option > 3 || option < 1);

    return option;
}

int countUnits(int currentPlayer)
{
    int count = 0;

    for (int i = 0; i < 100; i++)
    {
        if (players[currentPlayer].unit[i] != NULL)
        {
            count++;
        }
    }

    return count;
}

// Função para posicionar as construções e unidades
void posicionar(char grid_a[16][26], int currentPlayer)
{
    char letrapos;
    int numpos, option, buildingId, unitId, numUnits = 0, numBuildings = 0;

    numUnits = countUnits(currentPlayer);
    numBuildings = countBuildings(currentPlayer);
    option = actionOption();

    if (option == 1)
        buildingId = buildingsmenu();
    else
        unitId = unitMenu();

    do
    {
        printf("\nSelecione a posi%c%co\nN%cmero: ", 135, 198, 163);
        scanf("%d", &numpos);
    } while (numpos > 16 || numpos < 0);

    do
    {
        getchar();
        printf("\nLetra: ");
        scanf("%c", &letrapos);

    } while (letrapos > 122 || letrapos < 97);

    numpos -= 1;
    letrapos -= 97;

    if (option == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (players[currentPlayer].playerClass->id == building[i].playerclass->id && building[i].id == buildingId)
            {
                int size = strlen(building[i].code);
                int verify = (letrapos + size);
                int aux = verify - 26;

                // Aloca memória para a construção no jogador
                players[currentPlayer].building[numBuildings] = malloc(sizeof(struct Building *));

                players[currentPlayer].coins -= building[i].buildingType->buyCost;

                if (verify > 26)
                {
                    letrapos -= aux;

                    players[currentPlayer].building[numBuildings]->id = building[i].id;
                    players[currentPlayer].building[numBuildings]->x = letrapos;
                    players[currentPlayer].building[numBuildings]->y = numpos;
                    // strcpy(players[currentPlayer].building[numUnits]->code, building[i].code);

                    for (int h = 0; h < size; h++)
                    {
                        grid_a[numpos][letrapos++] = building[i].code[h];
                    }
                }
                else
                {

                    players[currentPlayer].building[numBuildings]->id = building[i].id;
                    players[currentPlayer].building[numBuildings]->x = letrapos;
                    players[currentPlayer].building[numBuildings]->y = numpos;

                    for (int h = 0; h < size; h++)
                    {
                        grid_a[numpos][letrapos++] = building[i].code[h];
                    }
                }
                numBuildings++;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            if (unit[i].playerclass->id == players[currentPlayer].playerClass->id && unit[i].id == unitId)
            {
                int size = strlen(unit[i].code);
                int verify = (letrapos + size);
                int aux = verify - 26;

                // Aloca memória para a unidade no jogador
                players[currentPlayer].unit[numUnits] = malloc(sizeof(struct Unit *));

                players[currentPlayer].coins -= unit[i].unitType->buyCost;

                if (verify > 26)
                {
                    letrapos -= aux;

                    players[currentPlayer].unit[numUnits]->id = unit[i].id;
                    players[currentPlayer].unit[numUnits]->x = letrapos;
                    players[currentPlayer].unit[numUnits]->y = numpos;

                    for (int h = 0; h < size; h++)
                    {
                        grid_a[numpos][letrapos++] = unit[i].code[h];
                    }
                }
                else
                {

                    players[currentPlayer].unit[numUnits]->id = unit[i].id;
                    players[currentPlayer].unit[numUnits]->x = letrapos;
                    players[currentPlayer].unit[numUnits]->y = numpos;

                    for (int h = 0; h < size; h++)
                    {
                        grid_a[numpos][letrapos++] = unit[i].code[h];
                    }
                }
                numUnits++;
                break;
            }
        }
    }
}

// function to display the unit actions after being select
void displayUnitActions()
{

    printf("\nA%c%ces disponiveis para a unidade:\n", 135, 198);
    printf("1. Mover\n");
    printf("2. Atacar\n");
    printf("3. Voltar\n");
    printf("Escolha a opcao:");
}

// Função para mover uma peça
void moverPeca(char grid[16][26], int currentPlayer)
{
    char fromC, toC;
    int fromL, toL;

    // as coordenadas da peça a ser movida
    printf("Digite as coordenadas da pe%ca a ser movida (linha/coluna): ", 135);
    scanf("%d %c", &fromL, &fromC);

    // as coordenadas para onde a peça será movida
    printf("Digite as coordenadas para onde a pe%ca ser%c movida (linha/coluna): ", 135, 160);
    scanf("%d %c", &toL, &toC);

    // Validate coordinates
    if (!isValidCoordinate(fromL, fromC) || !isValidCoordinate(toL, toC))
    {
        printf("Invalid coordinates. Please try again.\n");
        return;
    }

    // Convert coordinates to grid indices
    fromC = convertToGridIndex(fromC);
    toC = convertToGridIndex(toC);
    fromL--;
    toL--;

    // Copy the piece code until an empty field is found
    char code[5];
    int i, j;
    for (i = fromC, j = 0; i < GRID_WIDTH && grid[fromL][i] != ' '; i++, j++)
    {
        code[j] = grid[fromL][i];
    }
    code[j] = '\0';

    // Move the piece to the new position
    int size = strlen(code);
    for (int h = 0; h < size; h++)
    {
        grid[toL][toC + h] = code[h];
    }

    // Clear the source position
    for (int h = fromC; h < GRID_WIDTH && grid[fromL][h] != ' '; h++)
    {
        grid[fromL][h] = ' ';
    }

    int unitIndex = findUnitIndexByCode(code, players[currentPlayer].playerClass->id);

    if (unitIndex != -1)
    {
        // Update the x and y coordinates of the moved unit
        players[currentPlayer].unit[unitIndex] = malloc(sizeof(struct Unit *));
        players[currentPlayer].unit[unitIndex]->x = toC;
        players[currentPlayer].unit[unitIndex]->y = toL;

        // Display success message
        printf("Unit moved successfully!\n");
    }
    else
    {
        printf("Invalid piece. Please select a valid piece.\n");
    }
}

// Helper function to check if coordinates are valid
bool isValidCoordinate(int row, char col)
{
    return (col >= 'a' && col <= 'z' || col >= 'A' && col <= 'Z') && row >= 1 && row <= GRID_HEIGHT;
}

// Helper function to convert column character to grid index
int convertToGridIndex(char col)
{
    return (col >= 'a' && col <= 'z') ? (col - 'a') : (col - 'A');
}

int findUnitIndexByCode(const char *code, int playerClassId)
{
    for (int i = 0; i < 6; i++)
    {
        if (unit[i].playerclass->id == playerClassId && strcmp(unit[i].code, code) == 0)
        {
            return i;
        }
    }
    return -1; // Unit not found
}

// function to atack unit, or at least it's supposed to be
void atack()
{
    char fromC, atkC;
    int fromL, atkL;

    // display grid
    system("cls");
    displayGrid();

    // selecionar as coordenadas da peça
    printf("Digite as coordenadas da pe%ca que deseja utilizar (linha/coluna): ", 135);
    scanf("%d %c", &fromL, &fromC);

    // selecionar as coordenadas da peça a ser atacada
    printf("Digite as coordenadas da pe%ca que deseja atacar (linha/coluna): ", 135);
    scanf("%d %c", &atkL, &atkC);

    // Validate coordinates
    if (!isValidCoordinate(fromL, fromC) || !isValidCoordinate(atkL, atkC))
    {
        printf("Invalid coordinates. Please try again.\n");
        return;
    }

    // Convert coordinates to grid indices
    fromC = convertToGridIndex(fromC);
    atkC = convertToGridIndex(atkC);
    fromL--;
    atkL--;

    //verifica se tem uma peça para atacar
    if (grid[atkL][atkC]==' ')
    {
      printf("N%co existe uma pe%ca no local selecionado.",198,135);
      Sleep(1000);
      return 0;
    }
    

}

void displayGrid()
{
    // Print letters
    printf("   ");
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        printf(" %c", 'A' + i);
    }
    printf("\n");

    // Print top border
    printf("   ");
    printf("%c%c%c", 218, 196, 194);
    for (int i = 0; i < (GRID_WIDTH / 2) * 2 - 2; i++)
    {
        printf("%c%c", 196, 194);
    }
    printf("%c%c", 196, 191);
    printf("\n");

    // Print grid
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        // Prin left border and numbers
        printf("%2d %c", i + 1, 179);

        for (int j = 0; j < GRID_WIDTH; j++)
        {
            int unitOrBuilding = 0;

            // If no unit or building print empty cell
            if (!unitOrBuilding)
            {
                printf("%c", grid[i][j]);
            }

            // Print vertical bordar
            if (j < GRID_WIDTH - 1)
            {
                printf("%c", 179);
            }
        }

        // Print right border
        printf("%c\n", 179, i + 1);

        // Print horizontal border
        if (i < GRID_HEIGHT - 1)
        {
            printf("   ");
            printf("%c%c%c", 195, 196, 197);
            for (int j = 0; j < (GRID_WIDTH / 2) * 2 - 2; j++)
            {
                printf("%c%c", 196, 197);
            }
            printf("%c%c", 196, 180);

            printf("\n");
        }
    }
    // Print bottom border
    printf("   ");
    printf("%c%c%c", 192, 196, 193);
    for (int i = 0; i < (GRID_WIDTH / 2) * 2 - 2; i++)
    {
        printf("%c%c", 196, 193);
    }
    printf("%c%c", 196, 217);
    printf("\n");
}

void displayActions()
{
    // Display available actions for the player
    printf("1. Posicionar Constru%c%co\n", 135, 198);
    printf("2. Selecionar Unidade\n");
    printf("3. Encerrar Turno\n");
}

int settingsmenu()
{
    int choice;
    do
    {
        getchar();
        // display settings menu
        system("cls");
        printf("Defeni%c%ces:\n", 135, 228);
        printf("1. Alguma coisa\n");
        printf("2. Outra coisa\n");
        printf("3. Sei la\n");
        printf("4. Voltar ao menu\n");
        printf(" >> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            return 0;
            break;
        }
    } while (choice < 1 || choice > 4);
}
int main()
{

    // variables
    int currentPlayer = 0;
    int castarCoins[2] = {INITIAL_CASTAR_COINS, INITIAL_CASTAR_COINS};
    int choice;

    // clean display array
    if (startverify == 0)
    {
        cleantable();
        startverify++;
    }

// start menu
Startmenu:
    system("cls");
    printf("Bem-Vindo ao Ring World!\n\n");
    printf("1. Come%car um Novo Jogo\n", 135);
    printf("2. Carregar Jogo\n");
    printf("3. Defeni%c%ces\n", 135, 228);
    printf("4. Sair\n\n");
    printf("Introduza a sua escolha (1-4): ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls");
        printf("Escolha o seu lado:\n");
        printf("1. Gondor\n");
        printf("2. Mordor\n");
        printf("Introduza a sua Escolha (1-2): ");
        scanf("%d", &playerchoice);

        switch (playerchoice)
        {
        case 1:
            system("cls");
            printf("Voce escolheu Gondor. Vamos come%car o jogo!\n", 135);
            playerRegister(playerchoice, playerClass);
            Sleep(2000);
            break;
        case 2:
            system("cls");
            printf("Voce escolheu Mordor. Vamos come%car o jogo!\n", 135);
            playerRegister(playerchoice, playerClass);
            Sleep(2000);
            break;
        default:
            system("cls");
            printf("Escolha inv%clida, por favor selecione o seu lado.\n", 160);
            Sleep(2000);
            goto Startmenu;
        }
        break;

    case 2:
        system("cls");
        printf("\nCarregando o jogo ... ");
        Sleep(2000);
        break;

    case 3:
        system("cls");
        printf("\nAcessando as defeni%c%ces ... \n", 135, 228);
        Sleep(2000);
        settingsmenu();
        goto Startmenu;
        break;

    case 4:
        system("cls");
        printf("\nA sair do Ring World. At%c %c pr%cxima!\n", 130, 133, 162);
        saveGameToFile(players, "save1" SAVE_FILE_EXTENSION, currentPlayer);
        Sleep(2000);
        break;

    default:
        printf("\nEscolha inv%clida, por favor selecione um n%cmero entre 1-4!\n", 160, 163);
        Sleep(2000);
        goto Startmenu;
        break;
    }

    // Game loop
    while (1)
    {
        system("cls");

        int choice;
        char position[1][1];

        displayGrid();
        printf("Vez do jogador %d (%s)\n", players[currentPlayer].id, players[currentPlayer].playerClass->name);
        printf("Castar Coins: %d\n", players[currentPlayer].coins);

        displayActions();

        printf("Op%c%co:", 135, 198);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            displayGrid();
            posicionar(grid, currentPlayer, playerClass);
            break;
        case 2:
            system("cls");
            displayGrid();
            displayUnitActions();
            scanf("%d", &choice);
            if (choice == 1)
            {
                switch (choice)
                {
                case 1:
                    moverPeca(grid, currentPlayer, playerClass);
                    system("cls");
                    displayGrid();
                    break;
                case 2:
                    atack();
                    break;
                default:
                    break;
                }
            }
            else
            {
            }
            break;
        case 3:
            if (currentPlayer == 0)
            {
                currentPlayer = 1;
            }
            else if (currentPlayer == 1)
            {
                currentPlayer = 0;
            }
            break;
        case 4:
            system("cls");
            printf("\nA sair do Ring World. At%c %c pr%cxima!\n", 130, 133, 162);
            saveGameToFile(players, "save1" SAVE_FILE_EXTENSION, currentPlayer);
            Sleep(2000);
            break;
        default:
            printf("Op%c%co Inv%clida. Escolher outra vez.\n", 135, 198, 160);
        }
    }

    return 0;
}