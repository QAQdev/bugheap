#pragma once

/*Draw centered filled circle*/
void drawCenteredCircle(double x, double y, double r);
void drawCenteredDisc(double x, double y, double r);
void drawCenteredDiscDashed(double x, double y, double r);	//	filled by the density of 0.5

/*Draw entrance*/
void initCover();

void drawOneko();

void initOption();

void displayIntro();

/*Game Process*/
void displayPoints(struct player* player, double x, double y);

/*A case used to place cue ball*/
void drawWoodenCase();

void drawBackground();

void drawTable();

void noHistoryFile();

/*All buttons*/
void drawButton();

/*All menulist*/
void drawMenu();
void highlightPlayer(int player);
void displayRule();

/*Illustrations about pathpreview and side*/
void displayIllst1();
void displayIllst2();

/*Archived files successful*/
void archiveOK();

/*draw a solid ball*/
void drawBillSLD(struct billiard* op);

/*draw a stripe ball*/
void drawBillSTP(struct billiard* op);

void drawBilliards(struct billiard* head);

void printFreeHand(FILE* p, double x, double y, double w, double h, int size);