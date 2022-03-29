#include "univLib.h" 
#include "collide.h" 
#include "rule.h" 
#include "userIntr.h" 
 
/* isStart --- whether it's at the beginning of the game 
 */ 
bool isStart = TRUE; 
bool isGameOver = FALSE; 
bool ifChangeTurn; 
 
int offset1 = 1; 
int offset2 = 1; 
 
struct billiard *plcm = NULL; 
 
extern bool ifPlcmMove; 
extern bool ifRodMove; 
extern bool ifBillKnock; 
 
extern bool funcOnce; 
 
extern const char* SnooCOLOR[8]; 
 
/*For All*/ 
void putAside(struct billiard* p) { 
    int k; 
    p->vx = 0; 
    p->vy = 0; 
 
    switch (GameMode) { 
    case 0: 
        switch (checkColor(p)) { 
        case PURE: 
            if (player1->type == PURE) { 
                p->x = 0.8; 
                p->y = 3.3 + 0.8 * (offset1 - 1); 
                offset1++; 
            } 
            else { 
                p->x = 25.2; 
                p->y = 11.3 - 0.8 * (offset2 - 1); 
                offset2++; 
            } 
            break; 
        case MIXED: 
            if (player1->type == MIXED) { 
                p->x = 0.8; 
                p->y = 3.3 + 0.8 * (offset1 - 1); 
                offset1++; 
            } 
            else { 
                p->x = 25.2; 
                p->y = 11.3 - 0.8 * (offset2 - 1); 
                offset2++; 
            } 
            break; 
        } 
        break; 
    case 1: 
        p->x = 2.4 + (p->id - 1) * 0.8; 
        p->y = 14.3; 
        break; 
    case 2: 
        if (p->color == "Red") { 
            p->x = 7.2; 
            p->y = 14.3; 
        } 
        else { 
            for (k = 1; k <= 6; k++) { 
                if (p->color == SnooCOLOR[k]) break; 
            } 
            p->x = 2.4 + (k - 1) * 0.8; 
            p->y = 14.3; 
        } 
        break; 
    } 
     
} 
 
 
void changeTurn() { 
    if (player1->myTurn == TRUE) player1->myTurn = FALSE; 
    else player1->myTurn = TRUE; 
 
    if (player2->myTurn == TRUE) player2->myTurn = FALSE; 
    else player2->myTurn = TRUE; 
} 
 
 
void gameOver(struct player* player1, struct player* player2) { 
    char* text = (char*)malloc(10 * sizeof(char)); 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    double fH = GetFontHeight(); 
    double pointsize = GetPointSize(); 
 
    SetPenColor("Wood"); 
    SetPointSize(30); 
    drawBox(w / 2 - cX / 4, h / 2 - cY / 4, 0.5 * cX, 0.5 * cY, 1, "Score Board", 'C', "White"); 
    SetPenColor("Golden"); 
    SetPenSize(2); 
    drawRectangle(w / 2 - cX / 4, h / 2 - cY / 4, 0.5 * cX, 0.5 * cY, 0); 
 
    SetPointSize(20); 
    SetPenColor("White"); 
    MovePen(w / 2 - 3, h / 2); 
    DrawTextString(player1->name); 
    MovePen(w / 2 - 3, h / 2 - fH);
    if(gameMode != 1){
        sprintf(text, "%d", player1->points); 
        DrawTextString(text);
    } 
    MovePen(w / 2 - 3, h / 2 - 2 * fH); 
    if (player1->victory) DrawTextString("Victory!"); 
 
    MovePen(w / 2 + 3, h / 2); 
    DrawTextString(player2->name); 
    MovePen(w / 2 + 3, h / 2 - fH);
    if(gameMode != 1){
        sprintf(text, "%d", player2->points); 
        DrawTextString(text); 
    }
    MovePen(w / 2 + 3, h / 2 - 2 * fH); 
    if (player2->victory) DrawTextString("Victory!"); 
 
    SetPointSize(pointsize); 
} 
 
 
void initMotherBil() { 
    bil_list->vx = 0; 
    bil_list->vy = 0; 
    bil_list->x = 0.8; 
    bil_list->y = 14.3; 
 
    ifPlcmMove = 0; 
    plcm = bil_list; 
    ifRodMove = 0; 
    ifBillKnock = 0; 
} 
 
 
void randomInit(double  coord[][2], int n) { 
    double** b; 
    int i, j; 
    double t; 
 
    b = (double*)malloc(sizeof(double) * n); 
    for (i = 0; i < n; i++) { 
        b[i] = (double*)malloc(sizeof(double) * 2); 
    } 
 
    srand(time(NULL) + GetTickCount()); 
 
    for (i = 0; i < n; i++) 
        b[i][0] = rand(); 
    for (i = 0; i < n - 1; i++) 
        for (j = i + 1; j < n; j++) { 
            if (b[i][0] < b[j][0]) { 
                t = b[i][0]; 
                b[i][0] = b[j][0]; 
                b[j][0] = t; 
 
                t = coord[i][0]; 
                coord[i][0] = coord[j][0]; 
                coord[j][0] = t; 
 
                t = coord[i][1]; 
                coord[i][1] = coord[j][1]; 
                coord[j][1] = t; 
            } 
        } 
} 
 
 
void arbitraryPlacement(struct billiard* p) { 
    plcm = p; 
    ifPlcmMove = FALSE; 
} 
 
/*For POOL*/ 
int checkColor(struct billiard* p) { 
    int type; 
 
    if (p->id == 0) type = motherBill; 
    if (p->id >= 1 && p->id <= 7) type = PURE; 
    if (p->id >= 9 && p->id <= 15) type = MIXED; 
    if (p->id == 8) type = BLACK; 
 
    return type; 
} 
 
 
struct player* checkTurn(struct player* P1, struct player* P2) { 
    if (P1->myTurn == TRUE) return P1; 
    else return P2; 
} 
 
 
void determineSuit(struct billiard* p) { 
 
    struct player* curr = checkTurn(player1, player2); 
    struct player* not; 
    if (curr == player1) not= player2; 
    else not= player1; 
 
    switch (checkColor(p)) { 
    case motherBill: 
        initMotherBil(); 
        arbitraryPlacement(p); 
        break; 
 
    case PURE: 
        curr->type = PURE; 
        not->type = MIXED; 
        isStart = FALSE; 
        break; 
 
    case MIXED: 
        curr->type = MIXED; 
        not->type = PURE; 
        isStart = FALSE; 
        break; 
 
    case BLACK: 
        p->x = cX / 3; 
        p->y = 12.5 - cY / 2 - 0.6; 
        p->pre_x = cX / 3; 
        p->pre_y = 12.5 - cY / 2 - 0.6;  
        p->vx = 0; 
        p->vy = 0; 
        p->pre_vx = 0; 
        p->pre_vy = 0; 
        break; 
    } 
} 
 
 
void calScore(struct billiard* p, struct player* P1, struct player* P2) { 
 
    struct player* player = checkTurn(P1, P2); 
    struct player* not; 
    if (player == player1) not= player2; 
    else not= player1; 
 
    switch (checkColor(p)) { 
    case motherBill: 
        player->points -= GRD; 
        arbitraryPlacement(p); 
        break; 
    case BLACK: 
        if (player->goal == 7) { 
            player->points += GRD; 
            player->victory = TRUE; 
            not->victory = FALSE; 
        } 
        else { 
            not->victory = TRUE; 
            player->victory = FALSE; 
        } 
        isGameOver = TRUE; 
 
        p->x = 5 * cX; 
        p->y = 5 * cY;    //put the black off-frame 
        break; 
    default: 
        if (player->type == checkColor(p)) { 
            player->goal++; 
            player->points += GRD; 
        } 
        else { 
            not->goal++; 
            not->points += GRD; 
        } 
        break; 
    } 
} 
 
 
void POOLProcess(struct billiard* p, struct player* P1, struct player* P2) { 
 
    if (isStart == TRUE) { 
        determineSuit(p, player1, player2); 
    } 
    else { 
        calScore(p, player1, player2); 
        if (checkColor(p) == checkTurn(player1, player2)->type) ifChangeTurn = 0; 
 
        if (p == bil_list) { 
            initMotherBil(); 
        } 
        else { 
            p->ifInPoc = TRUE; 
            putAside(p); 
        } 
    } 
} 
 
 
/*For SidePocket*/ 
bool ifLagForBreak = FALSE; 
bool ifDrawMark1 = FALSE; 
bool ifDrawMark2 = FALSE; 
extern string COLOR[16]; 
 
bool ifSideKnock; 
bool ifBackCushionKnock; 
bool ifServe; 
bool ifChooseIfServe; 
 
int minID; 
 
double serveLine[2][2]; 
double spotSLDYel[2]; 
double spotSTPYel[2]; 
double spots[7][2]; 
 
double markLag[2][2]; 
int upToChoose = 0; 
int firstKnock; 
bool ifDrawWin = FALSE; 
bool ifInPock; 
 
void checkMinID(void) { 
    for (struct billiard* p = bil_list->next; p != NULL; p = p->next) { 
        if (p->ifInPoc == FALSE) { 
            minID = p->id; 
            break; 
        } 
    } 
} 
 
void chooseIfServe(int choose) { 
    ifChooseIfServe = TRUE; 
    upToChoose = choose; 
} 
 
void initSidePoc(void) { 
    //    calculate basic constants with dependancies upon other varibles. 
    serveLine[0][0] = myTable->corner[0][0] + (myTable->corner[2][0] - myTable->corner[0][0]) / 4; 
    serveLine[0][1] = myTable->corner[0][1]; 
    serveLine[1][0] = myTable->corner[0][0] + (myTable->corner[2][0] - myTable->corner[0][0]) / 4; 
    serveLine[1][1] = myTable->corner[2][1]; 
    spotSLDYel[0] = myTable->corner[0][0] + (myTable->corner[2][0] - myTable->corner[0][0]) * 3 / 4; 
    spotSLDYel[1] = (myTable->corner[0][1] + myTable->corner[2][1]) / 2; 
    spotSTPYel[0] = myTable->corner[0][0] + (myTable->corner[2][0] - myTable->corner[0][0]) * 3 / 4 + 3.5 * R; 
    spotSTPYel[1] = (myTable->corner[0][1] + myTable->corner[2][1]) / 2; 
 
    //    Second Row: 
 
    spots[0][0] = spotSLDYel[0] + 1.75 * R; 
    spots[0][1] = spotSLDYel[1] - 1.01 * R; 
 
    spots[1][0] = spotSLDYel[0] + 1.75 * R; 
    spots[1][1] = spotSLDYel[1] + 1.01 * R; 
 
    //    Third Row: 
    spots[2][0] = spotSLDYel[0] + 3.5 * R; 
    spots[2][1] = spotSLDYel[1] - 2.02 * R; 
 
    spots[3][0] = spotSLDYel[0] + 3.5 * R; 
    spots[3][1] = spotSLDYel[1] + 2.02 * R; 
 
    //    Fourth Row: 
    spots[4][0] = spotSLDYel[0] + 5.25 * R; 
    spots[4][1] = spotSLDYel[1] - 1.01 * R; 
 
    spots[5][0] = spotSLDYel[0] + 5.25 * R; 
    spots[5][1] = spotSLDYel[1] + 1.01 * R; 
 
    //    Fifth Row: 
    spots[6][0] = spotSLDYel[0] + 7 * R; 
    spots[6][1] = spotSLDYel[1]; 
 
    bil_list = initBilSidePoc(); 
    bil_list->next = NULL; 
 
    chooseIfServe(1); 
 
    //lagForBreak(); 
} 
 
 
void lagForBreak(void) { 
 
    ifLagForBreak = TRUE; 
 
    bil_list = (struct billiard*)malloc(sizeof(struct billiard)); 
    bil_list->next = NULL; 
    bil_list->id = 0; 
    bil_list->color = "White"; 
    bil_list->ifInPoc = FALSE; 
 
    double distance[2]; 
    upToChoose = 0; 
 
    for (int i = 1; i <= 2; i++) { 
        //    Init layout for break lag; 
 
        bil_list->x = serveLine[0][0]; 
        bil_list->y = (serveLine[0][1] + serveLine[1][1]) / 2; 
 
        if (!ifBillKnock && ifAllStop()) { 
            if (!ifOffFrame(bil_list)) { 
                distance[i - 1] = myTable->corner[2][0] - bil_list->x; 
                markLag[i - 1][0] = bil_list->x; 
                markLag[i - 1][1] = bil_list->y; 
                if (i == 1) { 
                    ifDrawMark1 = TRUE; 
                } 
                else if (i == 2) { 
                    ifDrawMark2 = TRUE; 
                } 
            } 
            else { 
                upToChoose = i = 1 ? 2 : 1; 
                break; 
            } 
        } 
    } 
 
    if (upToChoose == 0) { 
        if (distance[0] < distance[1]) { 
            upToChoose == 1; 
        } 
        else { 
            upToChoose == 2; 
        } 
    } 
    chooseIfServe(upToChoose); 
 
 
    ifDrawMark1 = FALSE; 
    ifDrawMark2 = FALSE; 
    ifLagForBreak = FALSE; 
    upToChoose = 0; 
} 
 
 
void serveSidePoc(void) { 
    bil_list = initBilSidePoc(); 
    initCueSidePoc(); 
    initMotherBil(); 
    ifServe = 1; 
} 
 
void initCueSidePoc() { 
    ifPlcmMove = FALSE; 
    plcm = bil_list; 
} 
 
struct billiard* initBilSidePoc() { 
    struct billiard* head = NULL, * tail = NULL, * p; 
    int m = 0, j = 0, k = 0, t = 0; 
    p = (struct billiard*)malloc(sizeof(struct billiard)); 
    bil_list = p; 
 
    randomInit(spots, 7); 
    int posiRemain = 0; 
 
    for (int i = 0; i <= 9; i++) { 
 
 
        p->vx = 0; 
        p->vy = 0; 
 
        p->id = i; 
        p->color = COLOR[i]; 
 
        p->ifInPoc = FALSE; 
 
        if (head == NULL) head = p; 
        else tail->next = p; 
        tail = p; 
        p->next = NULL; 
 
 
        switch (i) { 
        case 0: 
            break; 
        case 1: 
            p->x = spotSLDYel[0]; 
            p->y = spotSLDYel[1]; 
            break; 
        case 9: 
            p->x = spotSTPYel[0]; 
            p->y = spotSTPYel[1]; 
            break; 
        default: 
            p->x = spots[posiRemain][0]; 
            p->y = spots[posiRemain][1]; 
 
            posiRemain++; 
            break; 
        } 
 
        if (i != 9) { 
            p->next = (struct billiard*)malloc(sizeof(struct billiard)); 
            p = p->next; 
        } 
        else { 
            p->next = NULL; 
        } 
    } 
 
    return head; 
} 
 
 
void freeBall(void) { 
    initMotherBil(); 
} 
 
void freeBallValid(void) { 
    if (bil_list->x >= serveLine[0][0]) { 
        return FALSE; 
    } 
} 
 
 
void notChangeTurn(void) { 
    if (player1->myTurn == TRUE) { 
        player2->myTurn = FALSE; 
    } 
    else if (player2->myTurn == TRUE) { 
        player1->myTurn = FALSE; 
    } 
} 
 
void sidePocWin(void) { 
    isGameOver = TRUE; 
    if (player1->myTurn == TRUE) { 
        player1->victory = TRUE; 
    } 
    else if (player2->myTurn == TRUE) { 
        player2->victory = TRUE; 
    } 
} 
 
void SIDEPOCProcess(struct billiard* p0, struct player* player1, struct player* player2) { 
 
    if (p0->id == 0) { 
        changeTurn(); 
        initMotherBil(); 
    } 
    else { 
        p0->ifInPoc = TRUE; 
        if (p0->id == minID) { 
            if (minID == 9) { 
                isGameOver = TRUE; 
                if (player1->myTurn == TRUE) { 
                    player1->victory = TRUE; 
                } 
                else if (player2->myTurn == TRUE) { 
                    player2->victory = TRUE; 
                } 
                gameOver(player1, player2); 
                putAside(p0); 
            } 
            else { 
                checkMinID(); 
                putAside(p0); 
                changeTurn(); 
            } 
        } 
        else { 
            if (p0->id == 9) { 
                isGameOver = TRUE; 
                if (player1->myTurn == TRUE) { 
                    player1->victory = TRUE; 
                } 
                else if (player2->myTurn == TRUE) { 
                    player2->victory = TRUE; 
                } 
                gameOver(player1, player2); 
                putAside(p0); 
            } 
            else { 
                changeTurn(); 
                putAside(p0); 
                initMotherBil(); 
            } 
        } 
    } 
} 
 
void drawChoiceBreakOff(void) { 
    char* tipText = "Wanna break off?"; 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    double tw = GetWindowWidth() / 5; 
    double th = GetWindowHeight() / 5; 
    int pensize = GetPointSize(); 
 
    SetPenColor("Wood"); 
    SetPointSize(20); 
    drawBox(w / 2 - tw / 2, h / 2 - th / 2, tw, th, 1, tipText, 'C', "White"); 
    SetPenColor("Golden"); 
    drawRectangle(w / 2 - tw / 2, h / 2 - th / 2, tw, th, 0); 
    SetPointSize(pensize); 
} 
 
 
void drawEndSidePoc(void) { 
    char* tipText = "Congrats! One more round?"; 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    double tw = GetWindowWidth() / 5; 
    double th = GetWindowHeight() / 5; 
    int pensize = GetPointSize(); 
 
    SetPenColor("Wood"); 
    SetPointSize(20); 
    drawBox(w / 2 - tw / 2, h / 2 - th / 2, tw, th, 1, tipText, 'C', "White"); 
    SetPenColor("Golden"); 
    drawRectangle(w / 2 - tw / 2, h / 2 - th / 2, tw, th, 0); 
    SetPointSize(pensize); 
} 
 
 
 
 
/*For Snooker*/ 
bool snookerBreakOff = FALSE; 
int snookerCurType = COLORS; 
bool ifFirstPot = TRUE; 
bool ifFirstCollide = TRUE; 
bool ifTargetPot = TRUE; 
 
void breakOff() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    int pensize = GetPenSize(); 
    char* font = GetFont(); 
    char line[15] = "Who First?"; 
    double tw = TextStringWidth(line); 
 
    SetPenColor("Wood"); 
    drawRectangle(w / 2 - 2, h / 2 - 2, 4, 4, 1); 
    SetPenColor("Golden"); 
    drawRectangle(w / 2 - 2, h / 2 - 2, 4, 4, 0); 
 
    MovePen(w / 2 - tw / 2, h / 2 + 1); 
    DrawTextString(line); 
 
    MovePen(w / 2 - 1, h / 2); 
    DrawTextString(player1->name); 
 
    MovePen(w / 2 + 1, h / 2); 
    DrawTextString(player2->name); 
} 
 
 
int checkPoints(struct billiard* p) { 
    if (p->color == "Red") return RedP; 
    else if (p->color == "Yellow") return YellowP; 
    else if (p->color == "Black Green") return GreenP; 
    else if (p->color == "Brown") return BrownP; 
    else if (p->color == "Blue") return BlueP; 
    else if (p->color == "Violet") return PinkP; 
    else return BlackP; 
} 
 
 
bool ifInOrder(struct billiard* head, struct billiard* p) { 
    struct billiard* op = head->next; 
    int i = 1; 
 
    for (i = 1; i <= 6; i++) { 
        if (!op->ifInPoc && op != p && op->id < p->id) break; 
        op - op->next; 
    } 
    if (i == 6) return TRUE; 
    else return FALSE; 
} 
 
 
void calSnookerScore(struct billiard* p, struct billiard* p1, struct player* P1, struct player* P2) { 
    struct player* curr = checkTurn(player1, player2); 
    struct player* not; 
    if (curr == player1) not= player2; 
    else not= player1; 
 
    int type; 
    if (p->color == "Red") type = RED; 
    else if (p->color == "White") type = motherBill; 
    else type = COLORS; 
 
    if (ifInPocket(myTable, p)) { 
        if (type == snookerCurType) { 
            if (type == RED) { 
                curr->points++; 
                curr->goal++; 
            } 
            else { 
                if (ifFirstPot) { 
                    if (ifInOrder(bil_list, p)) { 
                        curr->points += checkPoints(p); 
                        curr->goal++; 
                    } 
                    else { 
                        not->points += checkPoints(p); 
                        not->goal++; 
                    } 
                } 
                else { 
                    not->points += checkPoints(p); 
                    not->goal++; 
                } 
            } 
        } 
        else { 
            if (type == motherBill) { 
                not->points += 4; 
                arbitraryPlacement(p); 
            } 
            else { 
                not->points += checkPoints(p); 
                not->goal++; 
            } 
        } 
    } 
 
    if (type == motherBill && !p->ifInPoc && p1 != NULL) { 
        if (snookerCurType == RED) { 
            if (ifFirstCollide && p1->color != "Red") { 
                if (checkPoints(p1) <= 4) { 
                    not->points += 4; 
                } 
                else { 
                    not->points += checkPoints(p1); 
                } 
            } 
        } 
        else { 
            if (ifFirstCollide && (p1->color == "Red" || !ifInOrder(bil_list, p1))) { 
                if (checkPoints(p1) <= 4) { 
                    not->points += 4; 
                } 
                else { 
                    not->points += checkPoints(p1); 
                } 
            } 
        } 
    } 
 
    struct billiard* op = bil_list; 
    int num = 0; 
    for (op = bil_list; op != NULL; op = op->next) { 
        if (!op->ifInPoc) num++; 
    } 
    if (num == 1) { 
        if (player1->points > player2->points) player1->victory = TRUE; 
        else if (player1->points < player2->points) player2->points = TRUE; 
        else {} 
        isGameOver = TRUE; 
    } 
    else isGameOver = FALSE; 
} 
 
void snookerProcess(struct billiard* p, struct billiard* p1, struct player* P1, struct player* P2) { 
 
    if (ifInPocket(myTable, p) && !p->ifInPoc) { 
        calSnookerScore(p, NULL, P1, P2); 
        ifFirstPot = FALSE; 
 
        if (p != bil_list) { 
            p->ifInPoc = TRUE; 
            putAside(p); 
        } 
        else { 
            initMotherBil(); 
        } 
    } 
 
    else { 
        if (p1 != NULL) { 
            calSnookerScore(p, p1, P1, P2); 
            ifFirstCollide = FALSE; 
        } 
    } 
}