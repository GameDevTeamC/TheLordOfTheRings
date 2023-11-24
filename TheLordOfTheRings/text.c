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

//clean array table
void cleantable() {
    for (int u = 0; u < 16;u++) {
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
    struct PlayerClass playerClass;

    int id;
    int coins;
};


//struct info for the building type
struct BuildingType {
    int id;
    int buyCost;
    int moveCost;
    int health;
};

//struct building
struct Builing {
    struct BuildingType buildingtype;

    int id;
    char name[100];
    int x, y;
};

//struct info for the unit type
struct UnitType {
    int id;
    int buyCost;
    int moveCost;
    int health;
    int attackPower;
};

//struct unit type
struct Unit
{
    struct UnitType unittype;

    int id;
    char name[100];
    int x, y;
};


// Structure unit
typedef struct {
    int x, y;
    int movementRange;
} Unit;

// Structure building
typedef struct {
    int x, y;
} Building;

//Start Menu
void menu() {
    //variables
    int choice;
    int playerchoice;

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

    printf("1. Come%car um Novo Jogo\n",128);
    printf("2. Carregar Jogo\n");
    printf("3. Defeni%c%ces\n",128,228);
    printf("4. Sair\n\n");
    printf("Introduza a sua escolha (1-4): ");
    scanf("%d", &choice);


    switch (choice)
    {
    case 1:
        system("cls");
        printf("\nCome%cando um novo Jogo ...\n",128);     
        Sleep(2000);
        printf("Escolha o seu lado:\n");
        printf("1. Gondor/Rivendell\n");
        printf("2. Mordor\n");
        printf("Introduza a sua Escolha (1-2): ");
        scanf("%d", &playerchoice);
        switch (playerchoice) {
        case 1:
            system("cls");
            printf("Voce escolheu Gondor/Rivendell. Vamos come%car o jogo!\n",128);
            Sleep(2000);
            break;
        case 2:
            system("cls");
            printf("Voce escolheu Mordor. Vamos come%car o jogo!\n",128);
            Sleep(2000);
            break;
        default:
            system("cls");
            printf("Escolha invalida, por favor selecione o seu lado.\n");
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
        printf("\nAcessando as defeni%c%ces ... \n", 'ç','õ');
        Sleep(2000);
        break;

    case 4:
        system("cls");
        printf("\nSaindo do Ring World. At%c %c proxima!\n",'é','à');
        //system.Exit();
        Sleep(2000);
        break;

    default:
        printf("\nEscolha inv%clida, por favor selecione um n�mero entre 1-4!\n",'á');
        Sleep(2000);
        goto Startmenu;
        break;
    }
    return 0;
}

// Function to display the game grid
void displayGrid(Unit* units, int numUnits, Building* buildings, int numBuildings);

// Function to display available actions
void displayActions();

//show buildings for position
char buildingsmenu() { 
    int choosing,escolha;
    char carater=0;

    buildingmenu:
    printf("O que deseja posicionar ?\n1: Constru%c%ces\n2: Tropas\nOp%c%co",'ç','õ','ç','ã');
    scanf("%d", &choosing);
    if (choosing == 1) {
        printf("\n1:Base == (%dcc)\n2:Mina == (%dcc)\n3:Quartel == (%dcc)\n4:Est%cbulos == (%dcc)\n5:Arsenal == (%dcc)\n >>", BASE_COST, MINE_COST, BARRACKS_COST, 181, STABLES_COST, ARMOURY_COST);
        scanf("%d", &escolha);
        switch (escolha) {
        case 1:
            carater = 'G';
            break;
        case 2:
            carater = 'M';
            break;
        case 3:
            carater = 'Q';
            break;
        case 4:
            carater = 'E';
            break;
        case 5:
            carater = 'A';
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
            carater = 'I';
            break;
        case 2:
            carater = 'C';
            break;
        case 3:
            carater = 'a';
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
    //falta parte para posicionar na tabela
    grid_a[numpos][letrapos] = carater;
}



//function to select a unit from the grid
void selecionar()
{
    char grid[16][26];
    int x;
    char y;

    getchar();
    printf("Selecione a posi%c%co da unidade (linha e coluna): ",'ç','ã');
    scanf("%d %c", &x, &y);

    //checks if the selected position is within the grid bounds
    if (x >= 1 && x <= GRID_HEIGHT && y >= 1 && y <= GRID_WIDTH)
    {
        //checks if there is a unit at the selected position
        if (grid[x - 1][y - 1] != ' ') {
            return 1;//valid selection
        }
        else
        {
            printf("N%co h%c nenhuma unidade nessa posicao. Escolha novamente!\n",'ã','á');
        }
    }
    else
    {
        printf("Posi%c%co inv%clida. Escolha novamente!\n",'ç','ã','á');
    }
    return 0;//invalid selection
}

//function to display the unit actions after being select
void displayUnitActions() {

    printf("\nAcoes disponiveis para a unidade:\n");
    printf("1. Mover\n");
    printf("2. Atacar\n");
    printf("3. Voltar\n");
}

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
        printf("Op%c%co:",'ç','ã');
        scanf("%d", &choice);

       

        switch (choice) {
        case 1:
            system("cls");
            displayGrid(units, 2, buildings, 2);
            posicionar(grid);
            break;
        case 2:

            selecionar();
            system("cls");
            displayGrid(units, 2, buildings, 2);
            displayUnitActions();
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
            printf("Op��o Inv�lida. Escolher outra vez.\n");
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
            /* for (int k = 0; k < numUnits; k++) {
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
            }*/

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
    printf("3. Mover Unidade\n");
    printf("4. Atacar\n");
    printf("5. Encerrar Turno\n");
}




