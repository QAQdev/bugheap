#pragma once

bool ifCalCut(struct billiard* p);

bool ifCutLinear(struct billiard* p, double line[2][2]);

bool ifInBetween(double border1, double border2, double target);

//void calDiagCol(struct billiard* p, int type);

//int ifCollideCorner(struct billiard* p);

bool restrictInside(struct billiard* p);


/*Find the minest positive root for quadratic equation*/
double findMinPosiRoot(double A, double B, double C);


/*Judge whether the billiard p0 would
* collide with billiard p1 */
bool ifBilCollide(struct billiard* p0, struct billiard* p1);


/*Find the nearest billiard which 
* may collide with billiard p 
* during current time interval*/
struct billiard* findNextCol(struct billiard* colhead, struct billiard* p);


/*Judge whether the billiard would
* slide into the pocket*/
bool ifInPocket(struct table* table, struct billiard* p);


/*Calculate vecolity of
* two billiards after they
* collide with each other*/
void calBilCollison(struct billiard* p0, struct billiard* p1);


/*Judge whether the billiard would 
* collide with the table during 
* current time interval*/
bool ifCollideTable(struct billiard* p);


/*Calculate vecolity of 
* one billiard after it 
* collides with the table*/
void calTableCollison(struct billiard* p);


/*Calculate all the parameters of 
* one billiard at the start of next 
* time interval*/
void calNextData(struct billiard* p, double time);


int avgRound(int rnd1, int rnd2);

