#include <univLib.h>
#include <init.h>

const char* COLOR[16] = { "White",
"Yellow","Blue","Red","Violet","Orange","Black Green","Dark Ochre",
"Black",
"Yellow","Blue","Red","Violet","Orange","Black Green","Dark Ochre" };

const char* SnooCOLOR[8] = { "White","Yellow" , "Black Green" , "Brown" ,"Blue" ,"Violet" ,"Black" ,"Red" };


void initPlayers() {

    player1 = (struct player*)malloc(sizeof(struct player));
    player1->myTurn = TRUE;
    player1->goal = 0;
    player1->points = 0;
    player1->victory = FALSE;
    strcpy(player1->name, "P1");

    player2 = (struct player*)malloc(sizeof(struct player));
    player2->myTurn = FALSE;
    player2->goal = 0;
    player2->points = 0;
    player2->victory = FALSE;
    strcpy(player2->name, "P2");

}

void initTable() {
    myTable = (struct table*)malloc(sizeof(struct table));

    //  define a table pockets, from left-bottom, counterclockwise.

    myTable->pocketPos[0][0] = 2.2;
    myTable->pocketPos[0][1] = 1.1;

    myTable->pocketPos[1][0] = 2.2;
    myTable->pocketPos[1][1] = 12.7;

    myTable->pocketPos[2][0] = 13;
    myTable->pocketPos[2][1] = 12.7;

    myTable->pocketPos[3][0] = 23.8;
    myTable->pocketPos[3][1] = 12.7;

    myTable->pocketPos[4][0] = 23.8;
    myTable->pocketPos[4][1] = 1.1;

    myTable->pocketPos[5][0] = 13;
    myTable->pocketPos[5][1] = 1.05;

    //  define a table by its four corners, from left-bottom, counterclockwise.

    myTable->corner[0][0] = 2.4;
    myTable->corner[0][1] = 1.3;

    myTable->corner[1][0] = 23.6;
    myTable->corner[1][1] = 1.3;

    myTable->corner[2][0] = 23.6;
    myTable->corner[2][1] = 12.5;

    myTable->corner[3][0] = 2.4;
    myTable->corner[3][1] = 12.5;
}

struct billiard* initBilliards() {
    struct billiard* head = NULL, * tail = NULL, * p;
    int m = 0, j = 0, k = 0, t = 0;
    double coor[15][2];

    for (int i = 0; i < 15; i++) {
        if (i >= 0 && i <= 4) {
            coor[i][0] = myTable->corner[2][0] * 4 / 5;
            coor[i][1] = 12.5 - cY / 2 - 0.6 + 4 * R - m * 2 * 1.04 * R;
            m++;
        }
        else if (i >= 5 && i <= 8) {
            coor[i][0] = myTable->corner[2][0] * 4 / 5 - 1.8 * R;
            coor[i][1] = 12.5 - cY / 2 - 0.6 + 3 * R - j * 2 * 1.04 * R;
            j++;
        }
        else if (i >= 9 && i <= 11) {
            coor[i][0] = myTable->corner[2][0] * 4 / 5 - 3.6 * R;
            coor[i][1] = 12.5 - cY / 2 - 0.6 + 2 * R - k * 2 * 1.04 * R;
            k++;
        }
        else if (i >= 12 && i <= 13) {
            coor[i][0] = myTable->corner[2][0] * 4 / 5 - 5.4 * R;
            coor[i][1] = 12.5 - cY / 2 - 0.6 + R - t * 2 * 1.04 * R;
            t++;
        }
        else {
            coor[i][0] = myTable->corner[2][0] * 4 / 5 - 7.2 * R;
            coor[i][1] = 12.5 - cY / 2 - 0.6;
        }
    }

    randomInit(coor, 15);

    switch (GameMode) {
    case 0:
        for (int i = 0; i < 16; i++) {
            p = (struct billiard*)malloc(sizeof(struct billiard));
            p->vx = 0;
            p->vy = 0;
            p->id = i;
            p->color = COLOR[i];
            p->ifInPoc = FALSE;
            p->ifDectet = FALSE;
            if (p->id >= 1) {
                p->x = coor[i - 1][0];
                p->y = coor[i - 1][1];
            }

            if (head == NULL) head = p;
            else tail->next = p;
            tail = p;
            p->next = NULL;

        }
        break;
    case 1:

        break;
    case 2:
        for (int i = 0; i < 22; i++) {
            p = (struct billiard*)malloc(sizeof(struct billiard));
            p->vx = 0;
            p->vy = 0;
            p->id = i;
            if (i == 0) {
                p->color = "White";
                p->x = cX * 2 / 5 - 2 * R;
                p->y = 12.5 - cY / 2 - 0.6 - cY / 12 - 0.25;
            }
            else if (i == 1) {
                p->color = "Yellow";
                p->x = cX * 2 / 5;
                p->y = 12.5 - cY / 2 - 0.6 - cY / 6 - 0.5;
            }
            else if (i == 2) {
                p->color = "Black Green";
                p->x = cX * 2 / 5;
                p->y = 12.5 - cY / 2 - 0.6 + cY / 6 + 0.5;
            }
            else if (i == 3) {
                p->color = "Brown";
                p->x = cX * 2 / 5;
                p->y = 12.5 - cY / 2 - 0.6;
            }
            else if (i == 4) {
                p->color = "Blue";
                p->x = cX / 2 + 3;
                p->y = 12.5 - cY / 2 - 0.6;
            }
            else if (i == 5) {
                p->color = "Violet";
                p->x = myTable->corner[2][0] * 4 / 5 - 7.2 * R - 4 * R;
                p->y = 12.5 - cY / 2 - 0.6;
            }
            else if (i == 6) {
                p->color = "Black";
                p->x = myTable->corner[2][0] * 4 / 5 + 4 * R;
                p->y = 12.5 - cY / 2 - 0.6;
            }
            else {
                p->color = "Red";
                p->x = coor[i - 7][0];
                p->y = coor[i - 7][1];
            }
            p->ifInPoc = FALSE;


            if (head == NULL) head = p;
            else tail->next = p;
            tail = p;
            p->next = NULL;
        }
        break;
    }

    return head;
}