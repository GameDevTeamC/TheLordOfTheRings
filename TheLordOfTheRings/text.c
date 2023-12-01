#define _CRT_SECURE_NO_WARNINGS 
#define GRID_WIDTH 26
#define GRID_HEIGHT 16
//constants for economy and costs
#define INITIAL_CASTAR_COINS 100
#define INFANTRY_MOVEMENT_COST 2
#define CAVALRY_MOVEMENT_COST 1
#define ARTILLERY_MOVEMENT_COST 3
#define MINE_INCOME 5 //per turn
#define BASE_COST 30
#define MINE_COST 20
#define BARRACKS_COST 25
#define STABLES_COST 25
#define ARMOURY_COST 30
#define INFANTRY_COST 10
#define CAVALRY_COST 15
#define ARTILLERY_COST 20
//constants for combat and health
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
//file
#define SAVE_FILE_EXTENSION ".txt"
//Librarys
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//array for table positions
char grid[16][26];

//for not clean the table every time menu open
int startverify = 0;

//player team definer
int playerchoice;

//clean array table
void cleantable() {
    for (int u = 0; u < 16; u++) {
        for (int i = 0; i < 26; i++) {
            grid[u][i] = ' ';
        }
    }
}

//struct info for the player side
struct PlayerClass {
    int id;
    char name[100];
};

//struct info player
struct Player {
    int id;
    int coins;
    struct PlayerClass playerClass;
};

struct Player players[2];

//struct info for the building type
struct BuildingType {
    int id;
    int buyCost;
    int health;
};

//struct building
struct Building {
    int id;
    char name[100];
    int x, y;
};

//struct unit type
struct Unit
{
    int id;
    char name[100];
    char code[100];
    struct PlayerClass playerclass;
};

//struct info for the unit type
struct UnitType {
    int id;
    int buyCost;
    int moveCost;
    int health;
    int attackPower;
};

struct GameState {
    char gameName[100];
    struct Player players[2];
};

// declarate functions
void cleantable();
void displayGrid();
void displayActions();
void posicionar(char grid[16][26]);
int* selecionar(char grid[16][26]);
void saveGameToFile(struct Player players[2], const char* saveFileName);
void loadGameFromFile(struct Player players[2], const char* loadFileName);
void playerRegister(int option, struct PlayerClass playerClass[]);

void saveGameToFile(struct Player players[2], const char* saveFileName) {
    FILE* file = fopen(saveFileName, "wb");

    if (file != NULL) {
        // Save player data
        for (int i = 0; i < 2; ++i) {
            fprintf(file, "Player %d:\n", i + 1);
            fprintf(file, "  ID: %d\n", players[i].id);
            fprintf(file, "  Coins: %d\n", players[i].coins);
            fprintf(file, "  Player Class:\n");
            fprintf(file, "    ID: %d\n", players[i].playerClass.id);
            fprintf(file, "    Name: %s\n", players[i].playerClass.name);
        }

        fclose(file);
        printf("Game saved to %s\n", saveFileName);
    }
    else {
        printf("Error opening file for writing.\n");
    }
}

// Function to load the game from a file
void loadGameFromFile(struct Player players[2], const char* loadFileName) {
    FILE* file = fopen(loadFileName, "rb");

    if (file != NULL) {
        // Load player data
        for (int i = 0; i < 2; ++i) {
            // Assuming the file structure is consistent with the save format
            fscanf(file, "Player %*d:\n");
            fscanf(file, "  ID: %d\n", &players[i].id);
            fscanf(file, "  Coins: %d\n", &players[i].coins);
            fscanf(file, "  Player Class:\n");
            fscanf(file, "    ID: %d\n", &players[i].playerClass.id);
            fscanf(file, "    Name: %s\n", players[i].playerClass.name);
        }

        fclose(file);
        printf("Game loaded from %s\n", loadFileName);
    }
    else {
        printf("Error opening file for reading.\n");
    }
}

void playerRegister(int option, struct PlayerClass playerClass[]) {

    if (option == 1)
    {
        players[0].id = 1;
        players[0].coins = INITIAL_CASTAR_COINS;
        players[0].playerClass = playerClass[option - 1];
        players[1].id = 2;
        players[1].coins = INITIAL_CASTAR_COINS;
        players[1].playerClass = playerClass[option];
    }
    else {
        players[0].id = 1;
        players[0].coins = INITIAL_CASTAR_COINS;
        players[0].playerClass = playerClass[option - 1];
        players[1].id = 2;
        players[1].coins = INITIAL_CASTAR_COINS;
        players[1].playerClass = playerClass[option-2];
    }
}

//Start Menu
void menu() {
    
    return 0;
}

// Function to display the game grid
void displayGrid();

// Function to display available actions
void displayActions();

//show buildings for position
char buildingsmenu() {
    int choosing, escolha;
    char carater = 0;

buildingmenu:
    printf("O que deseja posicionar ?\n1: Construções\n2: Tropas\nOpção");
    scanf("%d", &choosing);
    if (choosing == 1) {
        printf("\n1:Base == (%dcc)\n2:Mina == (%dcc)\n3:Quartel == (%dcc)\n4:Estábulos == (%dcc)\n5:Arsenal == (%dcc)\n >>", BASE_COST, MINE_COST, BARRACKS_COST, STABLES_COST, ARMOURY_COST);
        scanf("%d", &escolha);
        switch (escolha) {
        case 1:
            carater = 'B';//base
            break;
        case 2:
            carater = 'M';//mine
            break;
        case 3:
            carater = 'Q';//barracks
            break;
        case 4:
            carater = 'E';//stable
            break;
        case 5:
            carater = 'A';//armoury
            break;
        default:
            printf("Escolha invalida.");
            goto buildingmenu;
            break;
        }
    }
    else if (choosing == 2) {
        printf("\n1:Infantaria == (%dcc)\n2:Cavalaria == (%dcc)\n3:Artilharia == (%dcc)\n >>", INFANTRY_COST, CAVALRY_COST, ARTILLERY_COST);
        scanf("%d", &escolha);
        switch (escolha) {
        case 1:
            carater = 'I';//infantary
            break;
        case 2:
            carater = 'C';//cavalry
            break;
        case 3:
            carater = 'a';//artilry
            break;
        default:
            printf("Escolha invalida.");
            goto buildingmenu;
            break;
        }
    }
    else {
        printf("Escolha inv%clida.", 'á');
        goto buildingmenu;
    }
    return carater;
}
// Function to position the buildings
void posicionar(char grid_a[16][26]) {
    char letrapos, carater;
    int numpos;

    carater = buildingsmenu();

selectnumpos:
    printf("\nSelecione a posicao:\nNumero >> ");
    scanf("%d", &numpos);

    if (numpos > 16 || numpos < 0)
    {
        goto selectnumpos;
    }

selectletrapos:
    getchar();
    printf("\nLetra >> ");
    scanf("%c", &letrapos);
    if (letrapos > 122 || letrapos < 97)
    {
        goto selectletrapos;
    }

    numpos -= 1;
    letrapos -= 97;

    //placing int the table 
    if (playerchoice == 1) {//Gondor/Rivendell
        switch (carater) {
        case 'B'://base Gondor (GGGG)
            if (letrapos <= 21) {
                grid_a[numpos][letrapos] = 'G';
                grid_a[numpos][++letrapos] = 'G';
                grid_a[numpos][++letrapos] = 'G';
                grid_a[numpos][++letrapos] = 'G';

            }
            else { goto selectnumpos; }
            break;
        case 'M'://mine Shire (SS)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'S';
                grid_a[numpos][++letrapos] = 'S';
            }
            else { goto selectnumpos; }
            break;
        case 'Q'://barracks Rohan (RR)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'R';
                grid_a[numpos][++letrapos] = 'R';
            }
            else { goto selectnumpos; }
            break;
        case 'E'://stables Lothlórien (LL)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'L';
                grid_a[numpos][++letrapos] = 'L';
            }
            else { goto selectnumpos; }
            break;
        case'A'://armoury Gondorian Forge (GF)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'G';
                grid_a[numpos][++letrapos] = 'F';
            }
            else { goto selectnumpos; }
            break;
        case 'I'://infantry Gondorian Guards (G)
            grid_a[numpos][letrapos] = 'G';
            break;
        case 'C'://cavalry Swan-Knights (SK)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'S';
                grid_a[numpos][++letrapos] = 'K';
            }
            else { goto selectnumpos; }
            break;
        case 'a'://artillery Trebuchets (T)
            grid_a[numpos][letrapos] = 'T';
            break;
        }
    }


    else if (playerchoice == 2) {//Mordor
        switch (carater) {
        case 'B'://base Mordor (MMMM)
            if (letrapos <= 21) {
                grid_a[numpos][letrapos] = 'M';
                grid_a[numpos][++letrapos] = 'M';
                grid_a[numpos][++letrapos] = 'M';
                grid_a[numpos][++letrapos] = 'M';
            }
            else { goto selectnumpos; }
            break;
        case 'M'://mine Erebor (EE)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'E';
                grid_a[numpos][++letrapos] = 'E';
            }
            else { goto selectnumpos; }
            break;
        case 'Q'://barracks Isengard (II)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'I';
                grid_a[numpos][++letrapos] = 'I';
            }
            else { goto selectnumpos; }
            break;
        case 'E'://stables Mirkwood (MK)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'M';
                grid_a[numpos][++letrapos] = 'K';
            }
            else { goto selectnumpos; }
            break;
        case'A'://armoury Dark Foegw (DF)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'D';
                grid_a[numpos][++letrapos] = 'F';
            }
            else { goto selectnumpos; }
            break;
        case 'I'://infantary Orc Warrior (OW)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'O';
                grid_a[numpos][++letrapos] = 'W';
            }
            else { goto selectnumpos; }
            break;
        case 'C'://cavalry Wargs (W)
            grid_a[numpos][letrapos] = 'W';
            break;
        case 'a'://artillery Siege Towers (ST)
            if (letrapos <= 23) {
                grid_a[numpos][letrapos] = 'S';
                grid_a[numpos][++letrapos] = 'T';
            }
            else { goto selectnumpos; }
            break;
        }
    }
}



//function to select a unit from the grid
int* selecionar(char grid[16][26])
{
    int x;
    char y;
    char position[1][1];

    getchar();
    printf("Selecione a posi%c%co da unidade (linha e coluna): ", 'ç', 'ã');
    scanf("%d %c", &x, &y);

    //checks if the selected position is within the grid bounds
    if (x >= 1 && x <= GRID_HEIGHT && y >= 1 && y <= GRID_WIDTH)
    {
        //checks if there is a unit at the selected position
        if (grid[x - 1][y - 1] != ' ') {
            position[0][0] = x;
            position[1][0] = y;
            return position;//valid selection
        }
        else
        {
            printf("N%co h%c nenhuma unidade nessa posicao. Escolha novamente!\n", 'ã', 'á');
        }
    }
    else
    {
        printf("Posi%c%co inv%clida. Escolha novamente!\n", 'ç', 'ã', 'á');
    }
    return 0;
}

//function to display the unit actions after being select
void displayUnitActions() {

    printf("\nAcoes disponiveis para a unidade:\n");
    printf("1. Mover\n");
    printf("2. Atacar\n");
    printf("3. Voltar\n");
    printf("Escolha a opcao:");
}

/*void handleUnitActions(char grid[16][26], int playerchoice, char position[1][1]) {
    int actionChoice;

    while (1)
    {
        displayUnitActions();

        printf("Escolha uma açao (1-3): ");
        scanf("%d", &actionChoice);

        switch (actionChoice)
        {
            //movement
        case 1:
            move(grid, playerchoice, position);
            break;
            //atack
        case 2:
            break;
            //voltar
        case 3:
            break;


        default:
            printf("Opcao invalida. Selecione outra opcao.");
            break;
        }
    }
}*/

/*void move(char grid[16][26], int playerchoice, int postition[1][1])
{
    int x = 0;
    int new_x = 0;
    char new_y;
    char y = ' ';

    getchar();
    printf("Digite a nova posicao da unidade selecionada (linha e coluna): ");
    scanf("%d %c", &new_x, &new_y);

    if (new_x >= 1 && new_x <= GRID_HEIGHT && (new_y >= 'a' || new_y >= 'A') && (new_y <= 'z' || new_y <= 'Z')) {
        // Check if the new position is empty
        if (grid[new_x - 1][new_y - 1] == ' ') {
            // Determine the movement cost based on the type of unit
            int movementCost;
            switch (grid[x - 1][y - 1]) {
            case 'I': // Infantry
                movementCost = INFANTRY_MOVEMENT_COST;
                break;
            case 'C': // Cavalry
                movementCost = CAVALRY_MOVEMENT_COST;
                break;
            case 'A': // Artillery
                movementCost = ARTILLERY_MOVEMENT_COST;
                break;
            default:
                movementCost = 0; // Default cost for unknown units
            }

            // Check if the player has enough coins to cover the movement cost
            if (player.coins >= movementCost) {
                // Move the unit to the new position
                grid[new_x - 1][new_y - 1] = grid[x - 1][y - 1];
                grid[x - 1][y - 1] = ' ';

                // Deduct the movement cost from the player's coins
                player.coins -= movementCost;

                printf("Unidade movida com sucesso para %d, %d. Custo de movimento: %d coins\n", new_x, new_y, movementCost);
            }
            else {
                printf("Saldo insuficiente. Nao e possível mover a unidade para %d, %d.\n", new_x, new_y);
            }
        }
        else {
            printf("Posicao ocupada. Escolha uma posição valida.\n");
        }
    }
    else {
        printf("Posicao invalida. Escolha uma posicao dentro dos limites do tabuleiro.\n");
    }
}*/

void displayGrid() {
    // Print letters
    printf("   ");
    for (int i = 0; i < GRID_WIDTH; i++) {
        printf(" %c", 'A' + i);
    }
    printf("\n");

    // Print top border
    printf("   ");
    printf("%c%c%c", 218, 196, 194);
    for (int i = 0; i < (GRID_WIDTH / 2) * 2 - 2; i++) {
        printf("%c%c", 196, 194);

    }
    printf("%c%c", 196, 191);
    printf("\n");

    // Print grid
    for (int i = 0; i < GRID_HEIGHT; i++) {
        // Prin left border and numbers
        printf("%2d %c", i + 1, 179);

        for (int j = 0; j < GRID_WIDTH; j++) {
            int unitOrBuilding = 0;

            // If no unit or building print empty cell
            if (!unitOrBuilding) {
                printf("%c", grid[i][j]);
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
            for (int j = 0; j < (GRID_WIDTH / 2) * 2 - 2; j++) {
                printf("%c%c", 196, 197);
            }
            printf("%c%c", 196, 180);

            printf("\n");
        }
    }
    // Print bottom border
    printf("   ");
    printf("%c%c%c", 192, 196, 193);
    for (int i = 0; i < (GRID_WIDTH / 2) * 2 - 2; i++) {
        printf("%c%c", 196, 193);
    }
    printf("%c%c", 196, 217);
    printf("\n");
}


void displayActions() {
    // Display available actions for the player
    printf("1. Posicionar Constru��o\n");
    printf("2. Selecionar Unidade\n");
    printf("3. Encerrar Turno\n");
}

int main() {
	
    setlocale(LC_ALL, "Portuguese");

    //variables
    int currentPlayer = 1;
    int castarCoins[2] = { INITIAL_CASTAR_COINS, INITIAL_CASTAR_COINS };
    int choice;

    struct GameState game;

    // initializate
    struct PlayerClass playerClass[] = {
        {1, "Gondor"},
        {2, "Mordor"}
    };

    struct Unit unit[] = {
        {1, "Infantry", "G", 1},
        {2, "Cavalry", "SK", 1},
        {3, "Artillery", "T", 1},
        {4, "Infantry", "OW", 2},
        {5, "Cavalry", "W", 2},
        {6, "Artillery", "ST", 2}
    };

    struct UnitType unitType[] = {
        {1, INFANTRY_COST, INFANTRY_MOVEMENT_COST, INFANTRY_HEALTH, INFANTRY_ATTACK_POWER},//infantary
        {2, CAVALRY_COST, CAVALRY_MOVEMENT_COST, CAVALRY_HEALTH, CAVALRY_ATTACK_POWER},//cavalary
        {1, ARTILLERY_COST, ARTILLERY_MOVEMENT_COST, ARTILLERY_HEALTH, ARTILLERY_ATTACK_POWER}//artilary
    };

    struct Building building[] = {
        {1, "Bases", "GGGG", 1},
        {2, "Bases", "MMMM", 2},
        {3, "Mines", "SS", 1},
        {4, "Mines", "EE", 2},
        {5, "Stables", "LL", 1},
        {6, "Stables", "MK", 2},
        {7, "Armoury", "GF", 1},
        {8, "Armoury", "DF", 2}
    };

    struct BuildingType buildingType[] = {//  id , cost , health
        {1, BASE_COST, BASE_HEALTH},//base 
        {2, MINE_COST, MINE_HEALTH},//mine 
        {3, BARRACKS_COST, BARRACKS_HEALTH},//barracks
        {4, STABLES_COST, STABLES_HEALTH},//stable
        {5, ARMOURY_COST, ARMOURY_HEALTH},//armoury
    };

    // clean display array
    if (startverify == 0)
    {
        cleantable();
        startverify++;
    }

    // define values
    grid[3][9] = 'F';
    grid[8][3] = 'A';


    //start menu
Startmenu:
    printf("Bem-Vindo ao Ring World!\n\n");

    printf("1. Come%car um Novo Jogo\n", 128);
    printf("2. Carregar Jogo\n");
    printf("3. Defenições\n");
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

        switch (playerchoice) {
        case 1:
            system("cls");
            printf("Voce escolheu Gondor. Vamos começar o jogo!\n");
            playerRegister(playerchoice, playerClass);
            Sleep(2000);
            break;
        case 2:
            system("cls");
            printf("Voce escolheu Mordor. Vamos começar o jogo!\n");
            playerRegister(playerchoice, playerClass);
            Sleep(2000);
            break;
        default:
            system("cls");
            printf("Escolha inválida, por favor selecione o seu lado.\n");
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
        printf("\nAcessando as defenições ... \n");
        Sleep(2000);
        break;

    case 4:
        system("cls");
        printf("\nA sair do Ring World. Até à proxima!\n");
        saveGameToFile(players, "save1" SAVE_FILE_EXTENSION);
        Sleep(2000);
        break;

    default:
        printf("\nEscolha inválida, por favor selecione um n�mero entre 1-4!\n");
        Sleep(2000);
        goto Startmenu;
        break;
    }

    // Game loop
    while (1) {
        system("cls");

        int choice;
        char position[1][1];

        displayGrid();
        printf("Vez do jogador %d\n", currentPlayer);
        printf("Castar Coins: %d\n", players[currentPlayer - 1].coins);

        displayActions();

        printf("Op%c%co:", 'ç', 'ã');
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            system("cls");
            displayGrid();
            posicionar(grid);
            break;
        case 2:
            system("cls");
            displayGrid();
            position[1][1] = selecionar(grid);
            //handleUnitActions(grid, playerchoice, position);
            break;
        case 3:
            // End turn
            // Switch players
            if (playerchoice == 1) { playerchoice = 2; }
            else if (playerchoice == 2) { playerchoice = 1; }
            break;
        case 4:
            system("cls");
            printf("\nA sair do Ring World. Até à proxima!\n");
            saveGameToFile(players, "save1" SAVE_FILE_EXTENSION);
            Sleep(2000);
            break;
        default:
            printf("Op��o Inv�lida. Escolher outra vez.\n");
        }
    }

    return 0;
}