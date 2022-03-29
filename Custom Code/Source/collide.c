#include "univLib.h"
#include "collide.h"
#include "userIntr.h"

///* ppocTL  ---  two points: top left (x, y) 
// * ppocTR  ---  two points: top right (x, y)
// * ppocTML ---  top midlle left (x, y) & top middle (x, y)
// * ppocTMR ---  top middle (x, y) & top midlle right (x,y)
// * ppocBL  ---  two points: bottom left (x, y)
// * ppocBR  ---  two points: bottom right (x, y)
// * ppocBML ---  bottom middle left (x, y) & bottom middle (x, y)
// * ppocBMR ---  bottom middle (x, y) & bottom middle right (x, y)
// */
//const double ppocTL[2][2] = { 2.4, 11.9, 3, 12.5 };
//const double ppocTR[2][2] = { 23, 12.5, 23.6, 11.9 };
//const double ppocTML[2][2] = { 12.2, 12.5, 13, 12.28 };
//const double ppocTMR[2][2] = { 13, 12.28, 13.8, 12.5 };
//
//const double ppocBL[2][2] = { 2.4, 1.9, 3, 1.3 };
//const double ppocBR[2][2] = { 23, 1.3, 23.6, 1.9 };
//const double ppocBML[2][2] = { 12.2, 1.3, 13, 1.5 };
//const double ppocBMR[2][2] = { 13, 1.5, 13.84, 1.3 };
//
///* lines formed by the points mentioned above
// * y = kx+b
// * the first element is k, the second is b
// */
//const double TL[2] = { 1,9.5 };
//const double BL[2] = { -1,4.3 };
//const double BR[2] = { 1,-21.7 };
//const double TR[2] = { -1,35.5 };

/*  [Precise]  detection of potting billliards.
 *        Denote "poc" "pocket". Consisting the x, y coordinates
 *        of both ends of the reference segment.
 *
 * topbarL  --  top-left bar, any billiard would collide with the boundary as long as whose path cut through.
 * topbarR  --  top-left bar
 * botbarL  --  bottom-left bar
 * botbarR  --  bottom-right bar
 * leftbar  --  left bar
 * rightbar  --  right abr
 */

const double topbarL[2][2] = { 2.89, 12.22, 12.31, 12.22 };
const double topbarR[2][2] = { 13.69, 12.22, 23.11, 13.22 };
const double botbarL[2][2] = { 2.89, 1.57, 12.31, 1.57 };
const double botbarR[2][2] = { 13.69, 1.57, 23.11, 1.57 };
const double leftbar[2][2] = { 2.67, 1.79, 2.67, 12.01 };
const double rightbar[2][2] = { 23.32, 1.79, 23.32, 12.01 };

/*  [Precise]  detection of potting billliards.
 *        Denote "poc" "pocket". Consisting the x, y coordinates
 *        of both ends of the reference segment.
 *
 * pocTL  ---  top-left pocket.
 * pocTR  ---  top-left pocket.
 * pocTML ---  top-midlle pocket, left reference segment.
 * pocTMM ---  top-midlle pocket, middle reference segment.
 * pocTMR ---  top-midlle pocket, right reference segment.
 * pocBL  ---  bottom-left pocket.
 * pocBR  ---  bottom-right pocket.
 * pocBML ---  bottom-midlle pocket, left reference segment.
 * pocBMM ---  bottom-midlle pocket, middle reference segment.
 * pocBMR ---  bottom-midlle pocket, right reference segment.
 */

const double pocTL[2][2] = { 2.38, 12.31, 2.59, 12.52 };
const double pocTR[2][2] = { 23.41, 12.52, 23.62, 12.31 };
const double pocTML[2][2] = { 23.58, 24.92, 23.77, 25.05 };
const double pocTMM[2][2] = { 23.77, 25.05, 24.23, 25.05 };
const double pocTMR[2][2] = { 24.23, 25.05, 24.43, 24.92 };


const double pocBL[2][2] = { 2.38, 1.49, 2.59,1.28 };
const double pocBR[2][2] = { 23.41, 1.28, 23.62, 1.49 };
const double pocBML[2][2] = { 23.58, 14.27, 23.79, 14.12 };
const double pocBMM[2][2] = { 23.79, 14.12, 24.21, 14.12 };
const double pocBMR[2][2] = { 24.21, 14.12, 24.42, 14.27 };


/*  [Gross]    detection of potting billliards.
 *        poc for pocket, p for prime.
 *
 * ppocTL  ---  two points: top left (x, y)
 * ppocTR  ---  two points: top right (x, y)
 * ppocTML ---  top midlle left (x, y) & top middle (x, y)
 * ppocTMR ---  top middle (x, y) & top middle right (x,y)
 * ppocBL  ---  two points: bottom left (x, y)
 * ppocBR  ---  two points: bottom right (x, y)
 * ppocBML ---  bottom middle left (x, y) & bottom middle (x, y)
 * ppocBMR ---  bottom middle (x, y) & bottom middle right (x, y)
 */
const double ppocTL[2][2] = { 2.4, 11.9, 3, 12.5 };
const double ppocTR[2][2] = { 23, 12.5, 23.6, 11.9 };
const double ppocTML[2][2] = { 12.2, 12.5, 13, 12.28 };
const double ppocTMR[2][2] = { 13, 12.28, 13.8, 12.5 };

const double ppocBL[2][2] = { 2.4, 1.9, 3, 1.3 };
const double ppocBR[2][2] = { 23, 1.3, 23.6, 1.9 };
const double ppocBML[2][2] = { 12.2, 1.3, 13, 1.5 };
const double ppocBMR[2][2] = { 13, 1.5, 13.84, 1.3 };




/* lines formed by the points mentioned above
 * y = kx+b
 * the first element is k, the second is b
 */

const double TM[2] = { 13,13.5 };
const double BM[2] = { 13,0 };
const double TL[2] = { 1,9.5 };
const double BL[2] = { -1,4.3 };
const double BR[2] = { 1,-21.7 };
const double TR[2] = { -1,35.5 };

const double BML[2] = { 0.25,-1.75 };
const double BMR[2] = { -0.24,4.6 };
const double TML[2] = { -0.28,15.86 };
const double TMR[2] = { 0.28,8.71 };

const double corTL1[2][2] = { 2.38, 12.31, 2.67, 12.01 };
const double corTL2[2][2] = { 2.59, 12.52, 2.89, 12.22 };
const double corTR1[2][2] = { 23.11, 12.22, 23.41, 12.52 };
const double corTR2[2][2] = { 23.32, 12.01, 23.62, 12.31 };

const double corBL1[2][2] = { 2.38, 1.49, 2.67, 1.79 };
const double corBL2[2][2] = { 2.59, 1.28, 2.89, 1.57 };
const double corBR1[2][2] = { 23.11, 1.57, 23.41, 1.28 };
const double corBR2[2][2] = { 23.32, 1.79, 23.62, 1.49 };


bool restrictInside(struct billiard* p) {
	if (p->x <= 2.2 || p->x >= 23.8) return FALSE;
	else if (p->y >= 12.7 || p->y <= 1.05) return FALSE;
	else return TRUE;
}


double findMinPosiRoot(double A, double B, double C) {
	double s1, s2;
	double delta = B * B - 4 * A * C;
	if (delta < 0) return -1;
	else {
		s1 = (sqrt(delta) - B) / (2 * A);
		s2 = (-sqrt(delta) - B) / (2 * A);
		if (s1 < 0 && s2 < 0) return -1;
		else if (s1 >= 0 && s2 < 0) return s1;
		else if (s1 < 0 && s2 >= 0) return s2;
		else {
			s1 = (s1 > s2) ? s2 : s1;
			return s1;
		}
	}
}


bool ifBilCollide(struct billiard* p0, struct billiard* p1) {
	double test[3];
	test[0] = (p0->vx - p1->vx) * (p0->vx - p1->vx) + (p0->vy - p1->vy) * (p0->vy - p1->vy);
	test[1] = 2 * ((p0->x - p1->x) * (p0->vx - p1->vx) + (p0->y - p1->y) * (p0->vy - p1->vy));
	test[2] = (p0->x - p1->x) * (p0->x - p1->x) + (p0->y - p1->y) * (p0->y - p1->y) - 4 * R * R;

	double delta = test[1] * test[1] - 4 * test[0] * test[2];

	if (test[0] > 0 && test[1] < 0 && test[2] >= 0 && delta > 0) {
		p0->col_t = findMinPosiRoot(test[0], test[1], test[2]);
		p1->col_t = findMinPosiRoot(test[0], test[1], test[2]);

		if (p1->col_t >= 0 && p1->col_t <= DT) return TRUE;
		else return FALSE;
	}
	else return FALSE;
}


struct billiard* findNextCol(struct billiard* head, struct billiard* p) {
	struct billiard* op, * op2;
	struct billiard* colhead = NULL, * q, * coltail = NULL, * nextcol = colhead;
	int min_id, min_col_t;

	for (op = head; op != NULL; op = op->next) {

		if (ifBilCollide(p, op) == TRUE) {
			q = (struct billiard*)malloc(sizeof(struct billiard));
			*q = *op;
			q->next = NULL;
			if (colhead == NULL) colhead = q;
			else coltail->next = q;
			coltail = q;
		}
	}

	if (colhead == NULL) return NULL;
	else {
		min_id = colhead->id;
		min_col_t = DT;
		for (op = colhead; op != NULL; op = op->next) {
			if (op->col_t < min_col_t) {
				min_col_t = op->col_t;
				min_id = op->id;
			}
		}
		
		for (op = colhead, op2 = colhead; op != NULL && op2 != NULL; op2 = op) {
			op = op2->next;
			free(op2);
		}

		if (min_id == 0) return head;
		else {
			op = head;
			while (op->next != NULL && min_id != op->next->id) op = op->next;
			return op->next;
		}
	}
}


void calBilCollison(struct billiard* p0, struct billiard* p1) {

	double delta_vx, delta_vy;

	double dist = (p0->x - p1->x) * (p0->x - p1->x) + (p0->y - p1->y) * (p0->y - p1->y) - 2 * R;

	if (dist > LIM_DIST) {
		calNextData(p0, p1->col_t);
		calNextData(p1, p1->col_t);
	}

	delta_vx = ((p0->vx - p1->vx) * (p0->x - p1->x) * (p0->x - p1->x) 
		+ (p0->vy - p1->vy) * (p0->x - p1->x) * (p0->y - p1->y)) 
		/ ((p0->x - p1->x) * (p0->x - p1->x) + (p0->y - p1->y) * (p0->y - p1->y));

	delta_vy = ((p0->vy - p1->vy) * (p0->y - p1->y) * (p0->y - p1->y) 
		+ (p0->vx - p1->vx) * (p0->x - p1->x) * (p0->y - p1->y)) 
		/ ((p0->x - p1->x) * (p0->x - p1->x) + (p0->y - p1->y) * (p0->y - p1->y));

	p0->vx -= delta_vx;
	p0->vy -= delta_vy;

	p1->vx += delta_vx;
	p1->vy += delta_vy;

	// Update attributive motion infomation.

	int newKH = avgRound(p0->knPosHor, p1->knPosHor);
	int newKV = avgRound(p0->knPosVer, p1->knPosVer);

	p0->knPosHor = newKH;
	p0->knPosVer = newKV;
	
	p1->knPosHor = newKH;
	p1->knPosVer = newKV;
}


bool ifInPocket(struct table* table, struct billiard* p) {
	double dist[6];
	double Ldist[4];

	if (p->id == 0 && ifPlcmMove == TRUE) {
		return FALSE;
	}

	Ldist[0] = BL[0] * p->x + BL[1] - p->y;
	Ldist[1] = BR[0] * p->x + BR[1] - p->y;
	Ldist[2] = TR[0] * p->x + TR[1] - p->y;
	Ldist[3] = TL[0] * p->x + TL[1] - p->y;

	for (int i = 0; i < 6; i++) {
		dist[i] = sqrt((p->x - table->pocketPos[i][0]) * (p->x - table->pocketPos[i][0])
			+ (p->y - table->pocketPos[i][1]) * (p->y - table->pocketPos[i][1]));
		if (restrictInside(p) && (dist[i] <= POC_R ||
			Ldist[0] > 0 || Ldist[1] > 0 || Ldist[2] < 0 || Ldist[3] < 0)) {
			return TRUE;
		}
	}
	return FALSE;
}


//  decide if the two segments determined by two pairs of given points cut with each other.
bool ifCutLinear(struct billiard* p, double line[2][2]) {
	if (ifPlcmMove == 1) {
		return FALSE;
	}
	double slope1, slope2;
	double interX, interY;
	//  considering vertical movement;
	if (p->pre_x == p->x) {
		if (p->pre_y == p->y) {
			return FALSE;
		}
		else if (line[0][0] == line[1][0]) {
			return FALSE;
		}
		if (line[0][1] == line[1][1]) {
			interY = line[0][1];
		}
		else {
			slope2 = (line[1][1] - line[0][1]) / (line[1][0] - line[0][0]);
			interY = slope2 * p->x - slope2 * line[0][0] + line[0][1];
		}
	}
	else if (line[0][0] == line[1][0]) {
		slope1 = (p->y - p->pre_y) / (p->x - p->pre_x);
		interY = slope1 * line[0][0] - slope1 * p->x + p->y;
	}
	//  when both slopes are finite and real.
	else {
		slope1 = (p->y - p->pre_y) / (p->x - p->pre_x);
		slope2 = (line[1][1] - line[0][1]) / (line[1][0] - line[0][0]);
		if (slope1 == slope2) {
			return FALSE;
		}  //  parallel, no intersection.
		interX = (slope1 * p->x - slope2 * line[0][0] - p->y + line[0][1]) / (slope1 - slope2);
		//  horizontal coordinate of the intersection.
		return(ifInBetween(line[0][0], line[1][0], interX) && ifInBetween(p->pre_x, p->x, interX) ? TRUE : FALSE);
	}
	return(ifInBetween(line[0][1], line[1][1], interY) ? TRUE : FALSE);
}


bool ifInBetween(double border1, double border2, double target) {
	if (border1 > border2) {
		return ((target <= border1) && (target >= border2) ? TRUE : FALSE);
	}
	else if (border1 < border2) {
		return ((target >= border1) && (target <= border2) ? TRUE : FALSE);
	}
	else {
		return (target == border1 ? TRUE : FALSE);
	}
}


bool ifCalCut(struct billiard* p) {
	//  Gross Rect., reducing calculation complexity.
	if (p->x >= corTL2[1][0] &&
		p->y <= corTL2[1][1] &&
		p->x <= corBR1[0][0] &&
		p->y >= corBL1[0][1])
	{
		return FALSE;
	}
	else if (p->x > corTL1[1][0] &&
		p->y < corTL2[1][0]) {
		if (p->y < corTL2[1][1] - corTL2[1][0] + p->x &&
			p->y > corBL2[1][1] + corBL2[1][0] - p->x)
		{
			return FALSE;
		}
	}
	return TRUE;
}


//bool ifInPocket(struct table* table, struct billiard* p) {
//	if (ifCalCut(p)) {
//		if (ifCutLinear(p, pocTL) ||
//			ifCutLinear(p, pocTR) ||
//			ifCutLinear(p, pocBL) ||
//			ifCutLinear(p, pocBR) ||
//			ifCutLinear(p, pocTMM) ||
//			ifCutLinear(p, pocBMM))
//		{
//			return TRUE;
//		}
//	}
//	return FALSE;
//}


bool ifCollideTable(struct billiard* p) {

	double Ldist[4];
	double delta_x = 0, delta_y = 0;

	if (p->vx == 0 && p->vy == 0) return FALSE;

	double ax, ay;
	double rotAcc = 0.2 * a * p->knPosHor;
	double magnVelo = sqrt(p->vx * p->vx + p->vy * p->vy);
	if (p->vx != 0 || p->vy != 0) {
		ax = -a * (1 - 0.2 * (p->knPosVer)) * p->vx / magnVelo + rotAcc * p->vy / magnVelo * fabs(p->vx) / 0.01;
		ay = -a * (1 - 0.2 * (p->knPosVer)) * p->vy / magnVelo - rotAcc * p->vx / magnVelo * fabs(p->vy) / 0.01;
	}

	if (p->vx != 0) delta_x = p->vx * DT + 0.5 * ax * DT * DT;
	if (p->vy != 0) delta_y = p->vy * DT + 0.5 * ay * DT * DT;

	Ldist[0] = BL[0] * (p->x + delta_x) + BL[1] - (p->y + delta_y);
	Ldist[1] = BR[0] * (p->x + delta_x) + BR[1] - (p->y + delta_y);
	Ldist[2] = TR[0] * (p->x + delta_x) + TR[1] - (p->y + delta_y);
	Ldist[3] = TL[0] * (p->x + delta_x) + TL[1] - (p->y + delta_y);

	if (p->x + delta_x <= 12.658 || p->x + delta_x >= 13.342) {
		if (Ldist[0] < 0 && Ldist[1] < 0 && Ldist[2]>0 && Ldist[3]>0 &&
			p->x + delta_x < myTable->corner[2][0] - R &&
			p->x + delta_x > myTable->corner[0][0] + R &&
			p->y + delta_y < myTable->corner[2][1] - R &&
			p->y + delta_y > myTable->corner[0][1] + R) return FALSE;
		if (Ldist[0] < 0 && Ldist[1] < 0 && Ldist[2]>0 && Ldist[3]>0 &&
			(p->x + delta_x >= myTable->corner[2][0] - R ||
			 p->x + delta_x <= myTable->corner[0][0] + R ||
			 p->y + delta_y >= myTable->corner[2][1] - R ||
			 p->y + delta_y <= myTable->corner[0][1] + R)) return TRUE;
	}
	else return FALSE;
}


void calTableCollison(struct billiard* p) {
	double dist[4];

	dist[0] = p->y - myTable->corner[0][1];
	dist[1] = myTable->corner[2][0] - p->x;
	dist[2] = myTable->corner[2][1] - p->y;
	dist[3] = p->x - myTable->corner[0][0];

	double deltaTime[4], delta_t;
	
	double ax = 0, ay = 0;
	double rotAcc = 0.2 * a * p->knPosHor;
	double magnVelo = sqrt(p->vx * p->vx + p->vy * p->vy);
	if (p->vx != 0 || p->vy != 0) {
		ax = -a * (1 - 0.2 * (p->knPosVer)) * p->vx / magnVelo + rotAcc * p->vy / magnVelo * fabs(p->vx) / 0.01;
		ay = -a * (1 - 0.2 * (p->knPosVer)) * p->vy / magnVelo - rotAcc * p->vx / magnVelo * fabs(p->vy) / 0.01;
	}

	int index = -1;

	deltaTime[0] = findMinPosiRoot(ay, 2 * p->vy, 2 * (dist[0] - R));
	deltaTime[1] = findMinPosiRoot(ax, 2 * p->vx, -2 * (dist[1] - R));
	deltaTime[2] = findMinPosiRoot(ay, 2 * p->vy, -2 * (dist[2] - R));
	deltaTime[3] = findMinPosiRoot(ax, 2 * p->vx, 2 * (dist[3] - R));
	//	calculate theoretical col times for further comparison.

	double minTime = -1;

	for (int i = 0; i < 4; i++) {
		if (deltaTime[i] >= 0) {
			if (minTime < 0) {
				minTime = deltaTime[i];
				index = i;
			}
			else if (deltaTime[i] < minTime){
				minTime = deltaTime[i];
				index = i;
			}
		}
	}

	delta_t = deltaTime[index];

	switch (index) {
	case 0:
		p->col_t = delta_t;
		calNextData(p, delta_t);
		p->vy = -LOSS_RATE * p->vy;
		break;
	case 1:
		p->col_t = delta_t;
		calNextData(p, delta_t);
		p->vx = -LOSS_RATE * p->vx;
		break;
	case 2:
		p->col_t = delta_t;
		calNextData(p, delta_t);
		p->vy = -LOSS_RATE * p->vy;
		break;
	case 3:
		p->col_t = delta_t;
		calNextData(p, delta_t);
		p->vx = -LOSS_RATE * p->vx;
		break;
	}
	
}


void calNextData(struct billiard* p, double time) {

	double ax, ay;
	double rotAcc = 0.2 * a * p->knPosHor;
	double magnVelo = sqrt(p->vx * p->vx + p->vy * p->vy);
	if (p->vx != 0 || p->vy != 0) {
		ax = -a * (1 - 0.2 * (p->knPosVer)) * p->vx / magnVelo + rotAcc * p->vy / magnVelo * fabs(p->vx) / 0.01;
		ay = -a * (1 - 0.2 * (p->knPosVer)) * p->vy / magnVelo - rotAcc * p->vx / magnVelo * fabs(p->vy) / 0.01;
	}


	double modiTime;

	p->pre_vx = p->vx;
	p->pre_vy = p->vy;
	p->pre_x = p->x;
	p->pre_y = p->y;

	if (p->vx != 0 && p->vx * (p->vx + ax * time) < 0) {
		p->vx = 0;
		modiTime = p->pre_vx / ax;
		p->x += p->pre_vx / 2 * modiTime;
	}
	else if (p->vx != 0 && p->vx * (p->vx + ax * time) >= 0) {
		p->vx += ax * time;
		p->x += (p->pre_vx + p->vx) / 2 * time;
	}
	else {}

	if (p->vy != 0 && p->vy * (p->vy + ay * time) < 0) {
		p->vy = 0;
		modiTime = p->pre_vy / ay;
		p->y += p->pre_vy / 2 * modiTime;
	}
	else if (p->vy != 0 && p->vy * (p->vy + ay * time) >= 0) {
		p->vy += ay * time;
		p->y += (p->pre_vy + p->vy) / 2 * time;
	}
	else {}

}


int avgRound(int rnd1, int rnd2) {
	
	double temp;
	temp = (rnd1 + rnd2) / 2;
	
	if (temp >= 0){
		int round = 1;
		while (temp >= round) {
			round += 1;
		}
		return(round-1);
	}
	else {
		int round = -1;
		while (temp <= round) {
			round -= 1;
		}
		return(round + 1);
	}
}