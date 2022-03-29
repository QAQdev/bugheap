//
//  userIntr.c
//
//  User Interface Funcs.
//  v0.3, 30 May 2021

#include "univLib.h"
#include "collide.h"
#include "userIntr.h"
#include "rule.h"
#include "draw.h"

extern bool enableExtension;
double mouseX, mouseY;
double tempV;			//	store the velocity of mother billiard to be koncked at.
int recuLimt;

//  Called in GameMode::SIDEPOC
extern bool ifSideKnock;
extern bool ifBackCushionKnock;
extern bool ifServe;
extern bool ifChooseIfServe;
extern bool ifPlayer1;
extern int minID;
extern bool ifInPock;

extern struct billiard* plcm;

void initFlags(void) {
	ifBillKnock = 0;
	ifChangeTurn = 1;
	funcOnce = 1;
}

void billKnock(void) {
	if (bil_list->x != mouseX || bil_list->y != mouseY) {
		double distance = sqrt((bil_list->y - mouseY) * (bil_list->y - mouseY) + (bil_list->x - mouseX) * (bil_list->x - mouseX));
		double theta = asin((mouseY - bil_list->y) / distance);
		if (mouseX < bil_list->x) {
			theta = PI - theta;
		}
		ifRodMove = 0;
		initFlags();
		bil_list->vx = -tempV * cos(theta);
		bil_list->vy = -tempV * sin(theta);
	}
	else {
		bil_list->vx = 0;
		bil_list->vy = 0;
		ifBillKnock = 0;
		ifRodMove = 0;
		initFlags();
	}
}

void drawRod(double cenX, double cenY) {
	double distance;
	double theta;

	SetPenSize(1);
	SetPenColor("Black");
	if (bil_list->x != mouseX || bil_list->y != mouseY) {
		distance = sqrt((bil_list->y - mouseY) * (bil_list->y - mouseY) + (bil_list->x - mouseX) * (bil_list->x - mouseX));
		theta = asin((mouseY - bil_list->y) / distance);
		if (mouseX < cenX) {
			theta = PI - theta;
		}
	}
	else {
		distance = 0;
		theta = 0;
	}
	if (distance >= 12 * R) {
		distance = 12 * R;
	}

	MovePen(cenX, cenY);
	double tOri[2];
	double fillCoor[6][2];

	movePenPolar(theta, distance-5.7);
	tOri[0] = GetCurrentX();
	tOri[1] = GetCurrentY();
	movePenPolar(theta + 0.007, 5.7);
	fillCoor[0][0] = GetCurrentX();
	fillCoor[0][1] = GetCurrentY();
	movePenPolar(theta + 0.007, 5);
	fillCoor[1][0] = GetCurrentX();
	fillCoor[1][1] = GetCurrentY();
	movePenPolar(theta + 0.007, 5);
	fillCoor[2][0] = GetCurrentX();
	fillCoor[2][1] = GetCurrentY();

	MovePen(tOri[0], tOri[1]);

	movePenPolar(theta - 0.007, 5.7);
	fillCoor[3][0] = GetCurrentX();
	fillCoor[3][1] = GetCurrentY();
	movePenPolar(theta - 0.007, 5);
	fillCoor[4][0] = GetCurrentX();
	fillCoor[4][1] = GetCurrentY();
	movePenPolar(theta - 0.007, 5);
	fillCoor[5][0] = GetCurrentX();
	fillCoor[5][1] = GetCurrentY();

	SetPenColor("Golden");
	StartFilledRegion(1);
	MovePen(fillCoor[0][0], fillCoor[0][1]);
	drawLineTo(fillCoor[1][0], fillCoor[1][1]);
	drawLineTo(fillCoor[4][0], fillCoor[4][1]);
	drawLineTo(fillCoor[3][0], fillCoor[3][1]);
	drawLineTo(fillCoor[0][0], fillCoor[0][1]);
	EndFilledRegion();
	
	SetPenColor("Dark Ochre");
	StartFilledRegion(1);
	MovePen(fillCoor[1][0], fillCoor[1][1]);
	drawLineTo(fillCoor[2][0], fillCoor[2][1]);
	drawLineTo(fillCoor[5][0], fillCoor[5][1]);
	drawLineTo(fillCoor[4][0], fillCoor[4][1]);
	drawLineTo(fillCoor[1][0], fillCoor[1][1]);
	EndFilledRegion();

	drawPolarLine(theta + PI / 36, R);
	drawPolarLine(theta - PI / 2, R * 0.520944);
	drawPolarLine(theta - PI / 36 + PI, R);
	drawPolarLine(theta + PI / 2, R * 0.347296);
	MovePen(cenX, cenY);
	drawPolarLine(theta, distance);

	hittingPosiPreview(bil_list->knPosHor, bil_list->knPosVer, theta);
	tempV = 0.015 * distance / 4 / R;
	recuLimt = 7;
	if (enableExtension) {
		pathPreview(bil_list->x, bil_list->y, bil_list->knPosHor, bil_list->knPosVer, -tempV * cos(theta), -tempV * sin(theta), theta, "White");
	}
}


void pathPreview(double curX, double curY, int kn_hor, int kn_ver, double vx, double vy, double theta, string color) {
	recuLimt--;
	SetPenSize(1);
	SetPenColor(color);
	if (recuLimt >= 0) {

		struct billiard* pMth, mth, * pCol, col, * pTemp, temp;
		pMth = &mth;
		col.color = "White";
		double thetaAft, distance;
		int deltaCount = 0;
		pMth->next = NULL;
		pMth->x = curX;
		pMth->y = curY;
		pMth->knPosHor = kn_hor;
		pMth->knPosVer = kn_ver;
		pMth->vx = vx;
		pMth->vy = vy;

		temp = *pMth;
		pTemp = &temp;
		pCol = findNextCol(bil_list->next, pMth);

		while (pCol == NULL || pCol == bil_list) {
			deltaCount++;
			MovePen(pTemp->x, pTemp->y);
			drawLineTo(pMth->x, pMth->y);
			temp = *pMth;
			pTemp = &temp;
			calNextData(pMth, DT);
			if (ifInPocket(myTable, pMth)) {
				//drawLineTo(pMth->x, pMth->y);
				MovePen(pMth->x + R, pMth->y);
				if (color == "White") {
					drawLineTo(pMth->x, pMth->y);
					drawExclamation();
					break;
				}
				SetPenColor(color);
				StartFilledRegion(1);
				DrawArc(R, 0, 360);
				EndFilledRegion();
				break;
			}
			if (ifOffFrame(pMth)) {      //  calculate collision with table once visual path be off of the frame.
				if (ifCollideTable)
					calTableCollison(pTemp);
				drawLineTo(pTemp->x, pTemp->y);
				MovePen(pTemp->x + R, pTemp->y);
				SetPenColor(color);
				StartFilledRegion(0.3);
				DrawArc(R, 0, 360);
				EndFilledRegion();
				DrawArc(R, 0, 360);
				distance = sqrt((pTemp->vx) * (pTemp->vx) + (pTemp->vy) * (pTemp->vy));
				thetaAft = asin(-pTemp->vy / distance);
				if (pTemp->vx > 0) {
					thetaAft = PI - thetaAft;
				}
				pathPreview(pTemp->x, pTemp->y, pTemp->knPosHor, pTemp->knPosVer, pTemp->vx, pTemp->vy, thetaAft, color);
				break;
			}
			else {
				if (pMth->vx == 0 && pMth->vy == 0) {    //  dying down without collision.
					MovePen(pTemp->x, pTemp->y);
					drawLineTo(pMth->x, pMth->y);
					MovePen(pMth->x + R, pMth->y);
					SetPenColor(color);
					StartFilledRegion(0.3);
					DrawArc(R, 0, 360);
					EndFilledRegion();
					DrawArc(R, 0, 360);
					break;
				}
			}
			pCol = findNextCol(bil_list, pTemp);
		}
		//  Calculate collision with other billiards.
		if (pCol != NULL && pCol != bil_list) {
			col = *pCol;
			pCol = &col;
			MovePen(pTemp->x, pTemp->y);
			calBilCollison(pTemp, pCol);
			drawLineTo(pTemp->x, pTemp->y);
			MovePen(pTemp->x + R, pTemp->y);
			SetPenColor(color);
			StartFilledRegion(0.3);
			DrawArc(R, 0, 360);
			EndFilledRegion();
			DrawArc(R, 0, 360);
			distance = sqrt((pTemp->vx) * (pTemp->vx) + (pTemp->vy) * (pTemp->vy));
			thetaAft = asin(-pTemp->vy / distance);
			if (pTemp->vx > 0) {
				thetaAft = PI - thetaAft;
			}
			pathPreview(pTemp->x, pTemp->y, pTemp->knPosHor, pTemp->knPosVer, pTemp->vx, pTemp->vy, thetaAft, color);
			distance = sqrt((pCol->vx) * (pCol->vx) + (pCol->vy) * (pCol->vy));
			thetaAft = asin(-pCol->vy / distance);
			if (pCol->vx > 0) {
				thetaAft = PI - thetaAft;
			}
			pathPreview(pCol->x, pCol->y, pCol->knPosHor, pCol->knPosVer, pCol->vx, pCol->vy, thetaAft, pCol->color);
		}
	}
}


void hittingPosiPreview(int nk_hor, int nk_ver, double theta) {
	double cellX = 0.8 * R, cellY = 0.8 * R;
	double centerX = GetCurrentX() + R * cos(theta) - 4 * R * sin(theta);
	double centerY = GetCurrentY() + R * sin(theta) + 4 * R * cos(theta);
	int tPensize = GetPenSize();
	string tPencolor = GetPenColor();

	SetPenSize(2);
	SetPenColor("Gray");

	StartFilledRegion(1);
	MovePen(centerX, centerY);
	movepenDelta(3 * R, 0);
	DrawArc(3 * R, 0, 360);
	EndFilledRegion();

	MovePen(centerX, centerY);
	if (nk_hor < 0) {
		nk_hor = -nk_hor;
		cellX = -cellX;
	}
	if (nk_ver < 0) {
		nk_ver = -nk_ver;
		cellY = -cellY;
	}
	for (int i = nk_hor; i > 0; i--) {
		movepenDelta(cellX, 0);
	}
	for (int i = nk_ver; i > 0; i--) {
		movepenDelta(0, cellY);
	}

	SetPenSize(3);
	
	if (nk_hor == 0 && nk_ver == 0) {
		SetPenColor("Black");
	}
	else {
		SetPenColor("White");
	}

	drawCross(cellX);
	SetPenSize(tPensize);
	SetPenColor(tPencolor);
}


bool ifAllStop(void) {
	if (ifBillKnock) {
		return 1;
	}
	bool allStopTemp = 1;
	struct billiard* cursor = bil_list;
	for (cursor; cursor != NULL; cursor = cursor->next) {
		if (cursor->vx == 0 && cursor->vy == 0) {
			cursor->knPosHor = 0;
			cursor->knPosVer = 0;
		}
		else {
			allStopTemp = 0;
		}
	}
	if (allStopTemp) {
		return 1;
	}
	else {
		return 0;
	}
}


void mouseEvent(int x, int y, int button, int event) {

	uiGetMouse(x, y, button, event);

	if (ifBillKnock) {
		switch (event) {
		case BUTTON_DOWN:
			if (button == LEFT_BUTTON) {
				if (ifOnBillClick(motherBill, x, y)) {
					ifRodMove = 1;
					mouseX = bil_list->x;
					mouseY = bil_list->y;
				}
			}
			break;
		case MOUSEMOVE:
			if (ifRodMove) {
				mouseX = ScaleXInches(x);
				mouseY = ScaleYInches(y);
			}
			break;
		case BUTTON_UP:
			if (ifRodMove) {
				checkMinID();
				billKnock();
				if (GameMode == 1) {
					if (ifInPocket) {
						changeTurn();
					}
					ifInPock = 0;
				}
			}
			break;
		}
	}

	if (plcm != NULL) {
		switch (event) {
		case BUTTON_DOWN:
			if (button == LEFT_BUTTON) {
				if (!ifPlcmMove && ifOnBillClick(plcm->id, x, y)) {
					ifPlcmMove = 1;
				}
			}
			break;
		case MOUSEMOVE:
			if (ifPlcmMove) {
				mouseX = ScaleXInches(x);
				mouseY = ScaleYInches(y);
				if (!checkDistAll(mouseX, mouseY)) {
					plcm->x = mouseX;
					plcm->y = mouseY;
				}
				else {
					SetPenColor("Red");
					drawCenteredDiscDashed(mouseX, mouseY, R);
				}
			}
			break;
		case BUTTON_UP:
			if (ifOffFrame(bil_list)) {
				initMotherBil();
				break;
			}
			ifServe = FALSE;
			ifPlcmMove = 0;
			plcm = NULL;
			ifRodMove = 0;
			ifBillKnock = 1;
			checkMinID();
			break;
		}
	}
}


void keyboardEvent(int key, int event) {
	
	uiGetKeyboard(key, event);


	if (ifBillKnock) {
		if (event == KEY_DOWN) {
			switch (key) {
				//	VK_W is unexpectedly unavaliable in this IDE, thus referring these directly by virtual code.
			case 87:	//	VK_W
				if (!ifHitValid(1)) {
					break;
				}
				bil_list->knPosVer += 1;
				break;
			case 83:	//	VK_S
				if (!ifHitValid(2)) {
					break;
				}
				bil_list->knPosVer -= 1;
				break;
			case 68:	//	VK_D
				if (!ifHitValid(3)) {
					break;
				}
				bil_list->knPosHor += 1;
				break;
			case 65:	//	VK_A
				if (!ifHitValid(4)) {
					break;
				}
				bil_list->knPosHor -= 1;
				break;
				//		Press ESC to abandon current knocking.
			case 27:	//	VK_ESC
				ifRodMove = FALSE;
				break;
			}
		}
	}
}


void CharEventProcess(char ch) {
	uiGetChar(ch);
}


bool ifHitValid(int h) {
	int kHor = bil_list->knPosHor;
	int kVer = bil_list->knPosVer;
	switch (h) {
	case 1:
		kVer += 1;
		break;
	case 2:
		kVer -= 1;
		break;
	case 3:
		kHor += 1;
		break;
	case 4:
		kHor -= 1;
		break;
	}
	if (kHor * kHor + kVer * kVer <= 9) {
		return 1;
	}
	else {
		return 0;
	}
}

bool ifOnBillClick(int billNumber, int x, int y) {
	struct billiard* cursor = bil_list;
	double inchX, inchY, distanceSquare;
	inchX = ScaleXInches(x);
	inchY = ScaleYInches(y);
	for (int i = 0; i < billNumber; i++) {
		cursor = cursor->next;
	}
	distanceSquare = (inchX - cursor->x) * (inchX - cursor->x) + (inchY - cursor->y) * (inchY - cursor->y);
	if (distanceSquare <= R * R) {
		return 1;

	}
	else {
		return 0;
	}
}	//	judging whether the mouse click is on the certain given billiard.


bool ifOffFrame(struct billiard* cur) {
	if (cur->x >= myTable->corner[2][0] - R || cur->x <= myTable->corner[0][0] + R) {
		return 1;
	}
	else if (cur->y >= myTable->corner[2][1] - R || cur->y <= myTable->corner[0][1] + R) {
		return 1;
	}
	else return 0;
}

//	drawing tools in Polar Coordinate

void drawPolarLine(double theta, double distance) {
	double dx, dy;
	dx = distance * cos(theta);
	dy = distance * sin(theta);
	DrawLine(dx, dy);
}
void movePenPolar(double theta, double distance) {
	double dx, dy;
	dx = distance * cos(theta);
	dy = distance * sin(theta);
	movepenDelta(dx, dy);
}
void movepenDelta(double dx, double dy) {
	MovePen(GetCurrentX() + dx, GetCurrentY() + dy);
}
void drawLineTo(double x, double y) {
	DrawLine(x - GetCurrentX(), y - GetCurrentY());
}
void drawCross(double size) {
	movepenDelta(-size / 2, -size / 2);
	DrawLine(size, size);
	movepenDelta(0, -size);
	DrawLine(-size, size);
	movepenDelta(size / 2, -size / 2);
}

double calcInvsOrin(double x, double y) {
	double distance;
	double theta;
	if (x != 0 || y != 0) {
		distance = sqrt(x * x + y * y);
		theta = acos(x / distance);
		if (y < 0) {
			theta = -theta;
		}
	}
	else {
		distance = 0;
		theta = 0;
	}
	return theta + PI;
}

void drawExclamation(void) {
	double oriX = GetCurrentX();
	double oriY = GetCurrentY();
	
	SetPenColor("Red");
	StartFilledRegion(1);
	MovePen(oriX + R, oriY);
	DrawArc(R, 0, 360);
	EndFilledRegion();
	
	MovePen(oriX + 0.25 * R, oriY - 0.7 * R);
	SetPenColor("Yellow");
	
	StartFilledRegion(1);
	MovePen(oriX + 0.25 * R, oriY - 0.7 * R);
	DrawArc(0.25 * R, 0, 360);
	EndFilledRegion();

	MovePen(oriX - 0.25 * R, oriY + 0.7 * R);
	StartFilledRegion(1);
	drawLineTo(oriX, oriY - 0.5 * R);
	drawLineTo(oriX + 0.25 * R, oriY + 0.7 * R);
	DrawArc(0.25 * R, 0, 180);
	EndFilledRegion();

}

bool checkDistAll(double x, double y) {
	struct billiard* cursor;
	double aim = 4 * R * R;
	for (cursor = bil_list->next; cursor != NULL; cursor = cursor->next) {
		double dist = (cursor->x - x) * (cursor->x - x);
		dist += (cursor->y - y) * (cursor->y - y);
		if (aim > dist) {
			return TRUE;
			break;
		}
	}
	return FALSE;
}