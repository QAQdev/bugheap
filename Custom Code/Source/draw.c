#include "univLib.h" 
#include "userIntr.h" 
#include "collide.h" 
#include "draw.h" 
#include "rule.h" 
#include "archive.h" 
#include "view.h" 
#include "cover.h" 
 
extern const char* SnooCOLOR[8]; 
 
extern bool isGameOver; 
extern bool snookerBreakOff; 
 
extern bool ifRodMove; 
extern bool ifBillKnock; 
extern bool ifPlcmMove; 
 
/*For POOL*/ 
extern bool isStart; 
extern bool ifChangeTurn; 
extern bool funcOnce; 
//Called in GameMode::SIDEPOC 
extern bool ifLagForBreak; 
extern bool ifDrawMark1; 
extern bool ifDrawMark2; 
extern bool ifSideKnock; 
extern bool ifBackCushionKnock; 
extern bool ifServe; 
extern bool ifChooseIfServe; 
extern bool ifPlayer1; 
extern bool ifDrawWin; 
extern int minID; 
extern int upToChoose; 
/*For Snooker*/ 
extern int snookerCurType; 
extern bool ifFirstPot; 
extern bool ifFirstCollide; 
 
extern struct billiard *plcm; 
 
extern bool enableExtension; 
extern bool enableMusic; 
extern bool selectQuit; 
extern bool showRule; 
extern bool showIllst1; 
extern bool showIllst2; 
extern bool ifinitCover; 
extern bool ifinitOption; 
extern bool ifshowHelp; 
extern bool chooseMode; 
extern bool ifeditName;
extern bool ifShowAbout;
 
void nextTimeInit(struct billiard* head) { 
    struct billiard* p0 = head, * p1; 
    struct billiard* op; 
    int Repeat = REPEAT; 
    int soundType; 
 
    while (Repeat-- > 0) { 
        for (p0 = head; p0 != NULL; p0 = p0->next) { 
            if (!p0->ifInPoc && !p0->ifDectet && (p0->vx != 0 || p0->vy != 0)) { 
                p1 = findNextCol(head, p0); 
                while (p1 != NULL && p1->col_t <= p0->rem_t && p0->rem_t > 0) { 
 
                    if (GameMode == 2 && ifFirstCollide) snookerProcess(p0, p1, player1, player2); 
                    calBilCollison(p0, p1); 
                    for (op = head; op != NULL; op = op->next) { 
                        if (op->rem_t - p1->col_t > 0) op->rem_t -= p1->col_t; 
                        else op->ifDectet = TRUE; 
                    } 
                    p1 = findNextCol(head, p0); 
 
                    srand((unsigned)time(NULL)); 
                    soundType = rand() % 2; 
                    if (soundType == 0) mciSendString(TEXT("play ..\\Music\\Bimpacting0.wav"), NULL, 0, NULL); 
                    else mciSendString(TEXT("play ..\\Music\\Bimpacting1.wav"), NULL, 0, NULL); 
                } 
            } 
 
            if (!p0->ifInPoc && ifInPocket(myTable, p0)) { 
 
                switch (GameMode) { 
                case 0: 
                    POOLProcess(p0, player1, player2); 
                    break; 
                case 1: 
                    SIDEPOCProcess(p0, player1, player2); 
                    break; 
                case 2: 
                    snookerProcess(p0, NULL, player1, player2); 
                    break; 
                } 
                mciSendString(TEXT("play ..\\Music\\FallInHole.wav"), NULL, 0, NULL); 
            } 
 
            while (!p0->ifInPoc && ifCollideTable(p0) == TRUE && p0->rem_t > 0) { 
                calTableCollison(p0); 
                mciSendString(TEXT("play ..\\Music\\HitBar.wav"), NULL, 0, NULL); 
                if (p0->rem_t - p0->col_t > 0) p0->rem_t -= p0->col_t; 
                else p0->ifDectet = TRUE; 
            } 
        } 
 
        if (p0 != NULL && p0->rem_t <= 0) { 
            p0->ifDectet = TRUE; 
        } 
    } 
 
 
    for (p0 = head; p0 != NULL; p0 = p0->next) { 
        if (!p0->ifInPoc && !p0->ifDectet) calNextData(p0, p0->rem_t); 
        p0->rem_t = DT; 
        p0->ifDectet = FALSE; 
    } 
 
} 
 
 
void screenRefresh(struct billiard* head) { 
    DisplayClear(); 
 
    if (ifinitCover) { 
        initCover(); 
        drawButton(); 
    } 
 
    if (!ifinitCover && ifinitOption) { 
        initOption(); 
        drawButton(); 
    } 
 
    if (!ifinitCover && !ifinitOption && ifshowHelp) { 
        displayIntro(); 
        drawButton(); 
    } 
 
    if (!ifinitCover && !ifinitOption && !ifshowHelp) { 
 
        drawBackground(); 
        drawTable();     
        drawPlayer(); 
        drawWoodenCase(); 
        drawMenu(); 
        drawBilliards(head); 
 
        if (ifeditName) { 
            editName(); 
            drawButton(); 
        } 
 
        if (snookerBreakOff) { 
            breakOff(); 
            drawButton(); 
        } 
 
        if (selectQuit) { 
            archiveOK(); 
            drawButton(); 
        } 
 
        if (showRule == TRUE) { 
            displayRule(); 
            drawButton(); 
        } 
 
        if (showIllst1 == TRUE) { 
            displayIllst1(); 
            drawButton(); 
        } 
 
        if (showIllst2 == TRUE) { 
            displayIllst2(); 
            drawButton(); 
        } 
 
        if (ifShowAbout == TRUE) {
            displayAbout();
            drawButton();
        }

        displayPoints(player1, 0.4, 11.3); 
        displayPoints(player2, 24.8, 3); 
 
 
        switch (GameMode) { 
        case 0: 
            if (ifAllStop() && ifChangeTurn == 1 && funcOnce == 1) { 
                changeTurn(); 
                funcOnce = 0; 
            } 
            if (ifAllStop() && isGameOver) { 
                gameOver(player1, player2); 
                drawButton(); 
            } 
            break; 
        case 1: 
            if (ifAllStop() && ifChangeTurn == 1 && funcOnce == 1) { 
                changeTurn(); 
                funcOnce = 0; 
            } 
            if (ifAllStop() && isGameOver) { 
                gameOver(player1, player2); 
                drawButton(); 
            } 
            break; 
        case 2: 
            if (ifAllStop() && funcOnce == 1) { 
                changeTurn(); 
                ifFirstCollide = TRUE; 
                ifFirstPot = TRUE; 
                if (snookerCurType == RED) snookerCurType = COLORS; 
                else snookerCurType = RED; 
                funcOnce = 0; 
            } 
            if (ifAllStop() && isGameOver) { 
                gameOver(player1, player2); 
            } 
            SetPenColor("Brown"); 
            SetPointSize(15); 
            if (snookerCurType == RED) { 
                drawBox(10, 13.9, TextStringWidth("Colors"), 0.8, 1, "Red", 'C', "Golden"); 
            } 
            else { 
                drawBox(10, 13.9, TextStringWidth("Colors"), 0.8, 1, "Colors", 'C', "Golden"); 
            } 
            break; 
        } 
        if (ifRodMove) { 
            drawRod(bil_list->x, bil_list->y); 
        } 
    } 

}

void displayAbout(void) {
    double wid = 4, hei = 6;
    double wwidth = GetWindowWidth();
    double wheight = GetWindowHeight();
    int pointsize = GetPointSize();
    string tColor = GetPenColor();
    SetPenColor("Wood");
    drawRectangle(wwidth / 2 - wid / 2, wheight / 2 - hei / 2, wid, hei, 1);
    SetPenColor("Golden");
    SetPenSize(2);
    SetPointSize(25);
    drawRectangle(wwidth / 2 - wid / 2, wheight / 2 - hei / 2, wid, hei, 0);
    MovePen(wwidth / 2 - TextStringWidth("About")/2, wheight / 2 + 0.4 * hei);
    DrawTextString("About");
    SetPenColor("White");
    FILE* fp1 = fopen("..\\About\\czl.txt", "r");
    printFreeHand(fp1, wwidth / 2 - 0.4 * wid, wheight / 2 + 0.25, 0.8 * wid, wid * 2.4 / 4, 2);
    FILE* fp2 = fopen("..\\About\\hyx.txt", "r");
    printFreeHand(fp2, wwidth / 2 - 0.38 * wid, wheight / 2 - hei / 8 + 0.35, 0.8 * wid, wid * 1.6 / 4, 2);
    FILE* fp3 = fopen("..\\About\\fyy.txt", "r");
    printFreeHand(fp3, wwidth / 2 - 0.4 * wid, wheight / 2 - hei / 3 + 0.45, 0.82 * wid, wid * 1.6 / 4, 2);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    SetPointSize(15);
    MovePen(wwidth / 2 - TextStringWidth("Version 2.1") / 2, wheight / 2 - 0.4 * hei);
    SetPenColor("Golden");
    DrawTextString("Version 2.1");
    SetPenColor("White");
    MovePen(wwidth / 2 - TextStringWidth("22 June 2021") / 2, wheight / 2 - 0.45 * hei);
    DrawTextString("22 June 2021");
    SetPointSize(pointsize);
    SetPenColor(tColor);
}