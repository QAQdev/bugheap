#pragma once

void putAside(struct billiard* p);

/*For All*/
void changeTurn();


void gameOver(struct player* player1, struct player* player2);


void initMotherBil();


void randomInit(double  coord[][2], int n);


void arbitraryPlacement(struct billiard* p);


int checkColor(struct billiard* p);


struct player* checkTurn(struct player* P1, struct player* P2);


/*For POOL*/
int checkColor(struct billiard* p);


struct player* checkTurn(struct player* P1, struct player* P2);


void determineSuit(struct billiard* p);


void calScore(struct billiard* p, struct player* P1, struct player* P2);


void POOLProcess(struct billiard* p, struct player* P1, struct player* P2);


/*For Side Pocket*/
void lagForBreak(void);

void initSidePoc(void);

void checkMinID(void);

void chooseIfServe(int choose);

void serveSidePoc(void);

void initCueSidePoc(void);

struct billiard* initBilSidePoc(void);

void notChangeTurn(void);

void sidePocWin(void);

void SIDEPOCProcess(struct billiard* p0, struct player* player1, struct player* player2);

void drawChoiceBreakOff(void);

void drawEndSidePoc(void);

void checkMinID(void);

/*For Snooker*/
void breakOff();


int checkPoints(struct billiard* p);


bool ifInOrder(struct billiard* head, struct billiard* p);


void calSnookerScore(struct billiard* p, struct billiard* p1, struct player* P1, struct player* P2);


void snookerProcess(struct billiard* p, struct billiard* p1, struct player* P1, struct player* P2);