#pragma once

//
//  userIntr.h
//
//  User Interface Funcs.
//  v0.3, 30 May 2021

//	Inner Boundaries of the Table
#define	leftX		0
#define	rightX		cX
#define	bottomY		0
#define	upperY		cY


//	Struct Abbr.
/*
#define CP struct collPair
*/  //  [Preserved] Not yet in process.

//	Universal Flags
int gameMode;	//	
bool ifBillKnock;	//	Set FALSE on initialization or as one billiard being knocked, 
					//	    and is set TRUE when all bill. stops.
bool ifRodMove;		//	Set TRUE on clicking at the rod, and turn FALSE ones BUTTON_UP.

bool ifPlcmMove;	//	Set FALSE by default, and is TRUE when func arbitraryPlacement() is executed.

extern bool ifChangeTurn;

bool funcOnce;

bool ifOffFrame(struct billiard* cur);

//	Callback Funcs
void mouseEvent(int x, int y, int button, int event);
void keyboardEvent(int key, int event);
void CharEventProcess(char ch);


//	Billard Knocking Funcs
void billKnock(void);
void drawRod(double cenX, double cenY);
void pathPreview(double curX, double curY, int kn_hor, int kn_ver, double vx, double vy, double theta, string color);
void hittingPosiPreview(int nk_hor, int nk_ver, double theta);
bool ifHitValid(int h);
bool ifOnBillClick(int billNumber, int x, int y);
double calcInvsOrin(double x, double y);

//	If Any Billiard Be in Motion
bool ifAllStop(void);
void initFlags(void);

//	Drawing tools in polar coordinate
void drawExclamation(void);
void drawPolarLine(double theta, double distance);
void movePenPolar(double theta, double distance);
void movepenDelta(double dx, double dy);
void drawLineTo(double x, double y);
void drawCross(double size);

bool checkDistAll(double x, double y);
/*
//	Cell Separation
double cellWidth, cellHeight;
struct collPair{
	bool ifCal;
	bool ifCollide;
};
*/  //  [Preserved] Not yet in process.

