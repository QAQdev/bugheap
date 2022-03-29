#pragma once

 /*  univLib.h
  *
  *  Universal library, including standard headers, win32 libiaries, "graphics.h",
  *  "imgui.h" and other preset dependancies given in the demo project.
  *  v0.1, 24 May 2021
  */

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include <time.h>
#include <windows.h>
#include <olectl.h>

#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include <direct.h>

#include "imgui.h"

/* Game Mode*/
#define POOL 0
#define SidePocket 1
#define Snooker 2
int GameMode;

  /* DT --- calculate per 15 milliseconds
   * RF --- refresh screen per 15 millseconds
   */
#define DT 15
#define RF 15
#define LIM_DIST 0.0007
#define REPEAT 3

#define PI 3.1415926

   /*
	* TIMER_CAL --- ID of timer which invokes calculate function
	* TIMER_REF --- ID of timer which invokes screenrefresh function
	*/

#define TIMER_CAL 1
#define TIMER_REF 2

	/*  R    --- radius of billiard
     * POC_R --- radious of pocket
     */
#define R 0.26
#define POC_R 0.424



   /* cX --- canvas width
	* cY --- canvas height
	*/
#define cX 20.0
#define cY 10.0

	/*    a      --- acceleration of sliding friction
	 *    e      --- coefficient of restitution
	 * LOSS_RATE --- energy loss rate
	 */
#define a 0.00002
#define e 0.92000
#define LOSS_RATE 0.99


#define SHADOW_FACTOR 1.015

/* Parameters
 * id             ---   number of billiard
 * color          ---   color of billiard
 * (x, y)         ---   current coordinates of billiard
 * (pre_x, pre_y) ---   previous coordinates of billiard
 * vx,vy          ---   partial velocity in X direction and Y direction
 * pre_vx,pre_vy  ---   previous partial velocity in X direction and Y direction
 * col_t          ---   exact time interval of two billiards' collison during current time interval
 * rem_t          ---   remaining time in current time interval
 * shadow[2]      ---   coordinates of simulated shadows
 * ifInPOc        ---   in pocket or not
 * knPosVer       ---
 * knPosHor       --- 
 */
struct billiard {
	int id;
	string color;
	double x, y;
	double pre_x, pre_y;
	double vx, vy;
	double pre_vx, pre_vy;
	double col_t;
	double rem_t;
	double shadow[2];
	bool ifInPoc;
	bool ifDectet;

	int knPosVer;
	int knPosHor;

	struct strike* pattern;
	struct skRec* ptRec;

	struct billiard* next;
};
struct billiard* bil_list;

struct copy {
	int id;
	double x, y;
	double pre_x, pre_y;
	double vx, vy;
	double pre_vx, pre_vy;
	double col_t;
	double rem_t;
	double shadow[2];
	bool ifInPoc;

	int knPosVer;
	int knPosHor;

};

struct table {
	double pocketPos[6][2];
	double corner[4][2];
};
struct table* myTable;


/* motherBill --- white
 * MIXED      --- mixed colored billiards
 * PURE       --- pure colored billiards
 * BLACK      --- number 8
 */
#define motherBill 0
#define PURE 1
#define MIXED 2
#define BLACK 3


/* RED     ---   red ball
 * COLORS  ---   colored ball
 * RedP    ---   1 point
 * YellowP ---   2 points
 * GreenP  ---   3 points
 * BrownP  ---   4 points
 * BlueP   ---   5 points
 * PinkP   ---   6 points
 * BlackP  ---   7 points
 */
#define RED 1
#define COLORS 2

#define RedP 1
#define YellowP 2
#define GreenP 3
#define BrownP 4
#define BlueP 5
#define PinkP 6
#define BlackP 7

 /*GRD --- get GRD points per potting*/
#define GRD 10

/* name[8] --- player's name
 * goal    --- number of potting
 * points  --- player's grade
 * type    --- which type(MIXED or PURE)
 * myTurn  --- whether it's my turn
 * victory --- victory or defeat
 */

struct player {
	char name[20];
	int goal;
	int points;
	int type;
	bool myTurn;
	bool victory;
};
struct player* player1, * player2;


/*
 *	ifDraw	---	whether draw ref point
 *	theta	---	angle with respect to z-axle
 *	phi		---	angle with respect to x-axle
 *	projX	---	x of projection in xoy plain
 *	projY	---	x of projection in xoy plain
 *	pre		---	previous node address
 *	next	---	next node address
 */

struct refPoint {
	bool ifDraw;
	double theta;
	double phi;
	double projX;
	double projY;
	struct refPoint* pre;
	struct refPoint* next;
};

/*
 *	ifDraw	---	whether draw ref point
 *	x		---	
 *	y		---	
 *	z		---	
 *	vec		---	4-dim vector
 *	pre		---	previous node address
 *	next	---	next node address
 */
struct rpRec {
	bool ifDraw;
	double x;
	double y;
	double z;
	double vec[4];
	struct rpRec* pre;
	struct rpRec* next;
};

/*
 *	ifClose	---	whether strike close
 *	fill	---	density of area filling
 *	colour	---	pen colour
 *	weight	---	strike weight
 *	refList	---	head address of refPoint list
 *	next	---	next node address
 */
struct strike {
	bool ifClose;
	double fill;
	string colour;
	int weight;
	struct refPoint* refList;
	struct strike* next;
};

/*
 *	ifClose	---	whether strike close
 *	fill	---	density of area filling
 *	colour	---	pen colour
 *	weight	---	strike weight
 *	refList	---	head address of refPoint list
 *	next	---	next node address
 */
struct skRec {
	bool ifClose;
	double fill;
	string colour;
	int weight;
	struct rpRec* refList;
	struct skRec* next;
};