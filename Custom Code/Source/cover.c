#include "univLib.h" 
#include "userIntr.h" 
#include "collide.h" 
#include "draw.h" 
#include "rule.h" 
#include "archive.h" 
#include "view.h" 
#include "cover.h" 
#include "init.h" 
 
extern const char* COLOR[16]; 
extern const char* SnooCOLOR[8]; 
 
extern bool isGameOver; 
extern bool snookerBreakOff; 
 
/*For POOL*/ 
extern int offset1; 
extern int offset2; 
 
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
 
extern struct billiard* plcm; 

bool enableExtension = TRUE; 
bool enableMusic = TRUE; 
bool selectQuit = FALSE; 
bool showRule = FALSE; 
bool showIllst1 = FALSE; 
bool showIllst2 = FALSE; 
bool ifinitCover = TRUE; 
bool ifinitOption = TRUE; 
bool ifshowHelp = FALSE; 
int helpChoice = 0; 
bool chooseMode = FALSE; 
bool ifeditName = TRUE; 
bool showUs = FALSE;
bool ifShowAbout = FALSE;

char* intro[20]; 
int lines; 
 
 
void drawCenteredCircle(double x, double y, double r) { 
    MovePen(x + r, y); 
    SetPenSize(2); 
    DrawArc(r, 0, 360); 
} 
 
 
void drawCenteredDiscDashed(double x, double y, double r) { 
    StartFilledRegion(0.5); 
    MovePen(x + r, y); 
    SetPenSize(2); 
    DrawArc(r, 0, 360); 
    EndFilledRegion(); 
} 
 
 
void drawCenteredDisc(double x, double y, double r) { 
    StartFilledRegion(1); 
    MovePen(x + r, y); 
    SetPenSize(2); 
    DrawArc(r, 0, 360); 
    EndFilledRegion(); 
} 
 
 
void initCover() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    int pensize = GetPenSize(); 
 
    SetPenColor("Ivory Black"); 
    drawRectangle(0, 0, w, h, 1); 
 
    SetPenColor("Gray"); 
    MovePen(0, 0); 
    StartFilledRegion(1); 
    DrawLine(w / 5, 0); 
    DrawLine(-w / 5, h / 5); 
    DrawLine(0, -h / 5); 
    EndFilledRegion(); 
 
    StartFilledRegion(1); 
    MovePen(2 * w / 5, 0); 
    DrawLine(w / 5, 0); 
    DrawLine(-3 * w / 5, 3 * h / 5); 
    DrawLine(0, -h / 5); 
    DrawLine(2 * w / 5, -2 * h / 5); 
    EndFilledRegion(); 
 
    StartFilledRegion(1); 
    MovePen(0, 4 * h / 5); 
    DrawLine(4 * w / 5, -4 * h / 5); 
    DrawLine(w / 5, 0); 
    DrawLine(0, h / 5); 
    DrawLine(-4 * w / 5, 4 * h / 5); 
    DrawLine(-w / 5, 0); 
    DrawLine(0, -h / 5); 
    EndFilledRegion(); 
 
    StartFilledRegion(1); 
    MovePen(2 * w / 5, h); 
    DrawLine(3 * w / 5, -3 * h / 5); 
    DrawLine(0, h / 5); 
    DrawLine(-2 * w / 5, 2 * h / 5); 
    DrawLine(-w / 5, 0); 
    EndFilledRegion(); 
 
    StartFilledRegion(1); 
    MovePen(4 * w / 5, h); 
    DrawLine(w / 5, -h / 5); 
    DrawLine(0, h / 5); 
    DrawLine(-w / 5, 0); 
    EndFilledRegion(); 
 
    SetPenSize(25); 
    SetPenColor("Dodger Blue"); 
    MovePen(w / 6, h / 2); 
    DrawLine(0, 2.5); 
    DrawArc(1.25, 270, 180); 
    DrawLine(0, -5); 
    SetPenSize(25); 
    DrawArc(1.45, 240, 240); 
 
    SetPenSize(18); 
    SetPenColor("Indian Red"); 
    MovePen(w / 6 + 3, h / 2 + 2.5); 
    DrawLine(0, -1.5); 
    DrawArc(1, 180, 180); 
    DrawLine(0, 1.5); 
    DrawLine(0, -1.5); 
    DrawEllipticalArc(0.5, 1, 180, 90); 
    SetPenSize(10); 
    MovePen(w / 6 + 3 + 0.67, h / 2 + 2); 
    DrawLine(0, 0.5); 
    MovePen(w / 6 + 3 + 0.67 * 2, h / 2 + 2); 
    DrawLine(0, 0.5); 
    MovePen(w / 6 + 3.5, h / 2 + 1); 
    DrawArc(0.5, 180, 180); 
 
    SetPenSize(20); 
    SetPenColor("Yellow"); 
    MovePen(w / 6 + 6.5 + 0.8, h / 2 + 1); 
    DrawEllipticalArc(0.8, 1, 0, 360); 
    DrawLine(0, 1); 
    DrawLine(0, -3.2); 
    DrawEllipticalArc(0.8, 1, 0, -150); 
 
    SetPenColor("Dodger Blue"); 
    MovePen(w / 6 + 6.5 + 1.7, h / 2); 
    DrawLine(0, 4); 
    DrawArc(0.5, 0, 60); 
    MovePen(w / 6 + 6.5 + 1.7, h / 2 + 2.5); 
    DrawLine(2.3, 0.2); 
    DrawLine(0, 2); 
    DrawLine(0, -4); 
    DrawArc(0.5, 180, 60); 
 
    SetPenSize(15); 
    SetPenColor("Cobalt Green"); 
    MovePen(w / 6 + 6.5 + 1.7 + 4.3, h / 2 + 2); 
    DrawEllipticalArc(0.6, 0.6, 0, 180); 
    DrawEllipticalArc(0.8, 1, 170, 140); 
    MovePen(w / 6 + 6.5 + 1.7 + 4.3, h / 2 + 2); 
    DrawLine(-1, -0.2); 
    MovePen(w / 6 + 6.5 + 1.7 + 3.1, h / 2); 
    DrawLine(1.5, 0); 
 
    movepenDelta(0.2, 0); 
    SetPenColor("Indian Red"); 
    DrawLine(1.5, 0); 
    MovePen(w / 6 + 6.5 + 1.7 + 4.3 + 2, h / 2 + 1.6); 
    DrawEllipticalArc(0.7, 0.9, 0, 360); 
    DrawLine(0, 0.9); 
    DrawLine(0, -1.7); 
    DrawArc(0.4, 180, 60); 
 
    SetPenSize(20); 
    SetPenColor("Yellow"); 
    MovePen(w / 6 + 6.5 + 1.7 + 4.3 + 3, h / 2 + 2.7); 
    DrawLine(0, -4); 
    DrawLine(0, 2); 
    DrawArc(1, 240, 240); 
 
    //    draw authors. 
 
    SetPenColor("White"); 
    FILE* fp1 = fopen("..\\About\\czl.txt", "r"); 
    printFreeHand(fp1, 0.3 * cX, 0.02 * cY, cY / 8 * 4, cY / 8 * 3, 2); 
    FILE* fp2 = fopen("..\\About\\hyx.txt", "r"); 
    printFreeHand(fp2, 0.55 * cX, 0.11 * cY, cY / 8 * 3.5, cY / 8 * 1.9, 2); 
    FILE* fp3 = fopen("..\\About\\fyy.txt", "r"); 
    printFreeHand(fp3, 0.75 * cX, 0.11 * cY, cY / 8 * 3.8, cY / 8 * 2, 2); 
    fclose(fp1); 
    fclose(fp2); 
    fclose(fp3); 
    int tempSize = GetPointSize(); 
    SetPointSize(25); 
    MovePen(GetWindowWidth() / 2 - TextStringWidth("(c) 2021 All Rights Reserved.") / 2, GetWindowHeight() / 15); 
    DrawTextString("(c) 2021 All Rights Reserved."); 
    SetPointSize(tempSize); 
    SetPenSize(pensize); 
} 
 
 
void drawOneko() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
 
    MovePen(12.92, 11.87); 
    DrawLine(0, 12.01 - 11.87); 
    DrawLine(12.86 - 12.92, 0); 
    DrawLine(0, 12.13 - 12.01); 
    DrawLine(12.7 - 12.86, 12.25 - 12.13); 
    DrawLine(12.47 - 12.7, 11.87 - 12.25); 
    drawLineTo(12.47, 11.41); 
    drawLineTo(12.7, 11.2); 
    drawLineTo(12.85, 11.2); 
    drawLineTo(12.85, 11.14); 
    drawLineTo(12.64, 10.92); 
    drawLineTo(12.64, 10.74); 
    drawLineTo(12.44, 10.83); 
    drawLineTo(12.25, 10.7); 
    drawLineTo(12.25, 10.54); 
    drawLineTo(12.25, 10.46); 
    drawLineTo(12.2, 10.43); 
    drawLineTo(12.2, 10.38); 
    drawLineTo(12.7, 10.38); 
    drawLineTo(12.92, 10.38); 
    drawLineTo(13, 10.47); 
    drawLineTo(13.08, 10.38); 
    drawLineTo(13.3, 10.38); 
    drawLineTo(13.8, 10.38); 
    drawLineTo(13.8, 10.43); 
    drawLineTo(13.75, 10.46); 
    drawLineTo(13.75, 10.54); 
    drawLineTo(13.75, 10.7); 
    drawLineTo(13.56, 10.83); 
    drawLineTo(13.74, 11.02); 
    drawLineTo(13.74, 11.14); 
    drawLineTo(13.68, 11.2); 
    drawLineTo(13.36, 10.92); 
    drawLineTo(13.15, 11.14); 
    DrawLine(0, 0.06); 
    drawLineTo(13.3, 11.2); 
    drawLineTo(13.53, 11.41); 
    drawLineTo(13.53, 11.87); 
    drawLineTo(13.3, 12.25); 
    drawLineTo(13.14, 12.13); 
    drawLineTo(13.14, 12.01); 
    drawLineTo(13.08, 12.01); 
    drawLineTo(13.08, 11.87); 
    drawLineTo(12.92, 11.87); 
} 
 
 
void initOption() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    int pensize = GetPenSize(); 
 
    SetPenColor("Wood"); 
    drawRectangle(0, 0, w, h, 1); 
 
    SetPenColor("Golden"); 
    SetPenSize(3); 
    drawRectangle(w / 6, h / 6, 2 * w / 3, 2 * h / 3, 0); 
 
    SetPenColor("White"); 
    StartFilledRegion(1); 
    drawOneko(); 
    EndFilledRegion(); 
 
    SetPenColor("Ivory Black"); 
    SetPenSize(2); 
    drawOneko(); 
 
    SetPenColor("Golden"); 
    MovePen(12.45, 12.05); 
    drawLineTo(12.2, 12.3); 
    MovePen(12.25, 11.85); 
    drawLineTo(11.85, 12.05); 
    MovePen(12.05, 11.65); 
    drawLineTo(11.8, 11.65); 
    MovePen(13.6, 12.15); 
    drawLineTo(13.75, 12.35); 
    MovePen(13.65, 11.85); 
    drawLineTo(14.05, 12.05); 
    MovePen(13.8, 11.65); 
    drawLineTo(14.05, 11.65); 
 
    SetPenColor("Ivory Black"); 
    SetPenSize(3); 
    MovePen(12.78, 11.75); 
    drawLineTo(12.78, 11.58); 
    MovePen(13.22, 11.75); 
    drawLineTo(13.22, 11.58); 
    MovePen(12.62, 11.42); 
    drawLineTo(12.8, 11.42); 
    MovePen(12.97, 11.42); 
    drawLineTo(13.03, 11.42); 
    MovePen(13.2, 11.42); 
    drawLineTo(13.38, 11.42); 
    SetPenSize(2); 
    MovePen(12.25, 10.54); 
    drawLineTo(12.43, 10.54); 
    MovePen(12.64, 10.74); 
    drawLineTo(12.7, 10.65); 
    drawLineTo(12.7, 10.38); 
    MovePen(13.3, 10.38); 
    drawLineTo(13.3, 10.65); 
    drawLineTo(13.36, 10.74); 
    drawLineTo(13.36, 10.92); 
    MovePen(13.36, 10.74); 
    drawLineTo(13.56, 10.83); 
    MovePen(13.75, 10.54); 
    drawLineTo(13.57, 10.54); 
    MovePen(13, 10.47); 
    drawLineTo(13, 10.76); 
 
     
 
 
} 
 
 
void displayIntro() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    double fH = GetFontHeight(); 
    int pensize = GetPenSize(); 
    int pointsize = GetPointSize(); 
    static int readOnce = 0; 
 
    SetPenColor("Wood"); 
    drawRectangle(0, 0, w, h, 1); 
 
    readIntro(); 
 
    SetPenColor("Golden"); 
    drawRectangle(w / 5, h / 5, w * 2 / 3, h * 3 / 5, 0); 
 
    SetPenColor("White"); 
    MovePen(w  / 5 + 0.5, 3 * h / 4 - fH); 
 
    SetPointSize(30); 
    switch (helpChoice) { 
    case 0: 
        DrawTextString("POOL"); 
        break; 
    case 1: 
        DrawTextString("Side Pocket"); 
        break; 
    case 2: 
        DrawTextString("Snooker"); 
        break; 
    } 
    SetPointSize(20); 
 
    for (int i = 0; i < lines; i++) { 
        MovePen(w / 5 + 0.5, 3 * h / 4 - 3 * fH - i * 1.6 * fH); 
        DrawTextString(intro[i]); 
    } 
     
    SetPointSize(pointsize); 
} 
 
 
void displayPoints(struct player* player, double x, double y) { 
    char* text; 
    char* display = "Black"; 
    int pensize = GetPointSize(); 
    SetPenSize(1); 
 
    text = (char*)malloc(15 * sizeof(char)); 
 
    if (player->myTurn == TRUE) {
        display = "Golden";
        if (player == player1) highlightPlayer(1);
        else highlightPlayer(2);
    }
    else display = "White"; 
    SetPenColor(display); 
    MovePen(x + 0.05, y); 
    DrawTextString(player->name); 
 
    if (player == player1) { 
        MovePen(x + 0.05, y - 2 * GetFontHeight()); 
        DrawTextString("Pot"); 
        MovePen(x + 0.05, y - 3 * GetFontHeight()); 
        sprintf(text, "%d", player->goal); 
        DrawTextString(text); 
 
        MovePen(x + 0.05, y - 5 * GetFontHeight()); 
        DrawTextString("PTS"); 
        MovePen(x + 0.05, y - 6 * GetFontHeight()); 
        sprintf(text, "%d", player->points); 
        DrawTextString(text); 
 
        MovePen(x + 0.05, y - 8 * GetFontHeight()); 
        if (isStart == TRUE) text = "N/A"; 
        else { 
            if (player->type == PURE) text = "SLD"; 
            else text = "STP"; 
        } 
        DrawTextString(text); 
    } 
    else { 
        MovePen(x + 0.05, y + 2 * GetFontHeight()); 
        DrawTextString("Pot"); 
        MovePen(x + 0.05, y + 3 * GetFontHeight()); 
        sprintf(text, "%d", player->goal); 
        DrawTextString(text); 
 
        MovePen(x + 0.05, y + 5 * GetFontHeight()); 
        DrawTextString("PTS"); 
        MovePen(x + 0.05, y + 6 * GetFontHeight()); 
        sprintf(text, "%d", player->points); 
        DrawTextString(text); 
 
        MovePen(x + 0.05, y + 8 * GetFontHeight()); 
        if (isStart == TRUE) text = "N/A"; 
        else { 
            if (player->type == PURE) text = "SLD"; 
            else text = "STP"; 
        } 
        DrawTextString(text); 
    } 
 
    SetPointSize(pensize); 
} 
 
 
void drawWoodenCase() { 
 
    SetPenColor("Brown"); 
    drawRectangle(0.4, 13.9, 0.8, 0.8, 1); 
    SetPenColor("Golden"); 
    StartFilledRegion(0.5); 
    drawCenteredCircle(0.8, 14.3, 1.05 * R); 
    EndFilledRegion(); 
 
    if (GameMode == 1) { 
        SetPenColor("Brown"); 
        drawRectangle(2, 13.9, 7.2, 0.8, 1); 
 
        for (int i = 1; i <= 9; i++) { 
            SetPenColor(COLOR[i]); 
            StartFilledRegion(0.3); 
            drawCenteredCircle(2.4 + (i - 1) * 0.8, 14.3, 1.05 * R); 
            EndFilledRegion(); 
        } 
    } 
 
    else if (GameMode == 2) { 
        SetPenColor("Brown"); 
        drawRectangle(2, 13.9, 5.6, 0.8, 1); 
 
        for (int i = 1; i <= 7; i++) { 
            SetPenColor(SnooCOLOR[i]); 
            StartFilledRegion(0.3); 
            drawCenteredCircle(2.4 + (i - 1) * 0.8, 14.3, 1.05 * R); 
            EndFilledRegion(); 
        } 
    } 
} 
 
 
void drawBackground() { 
    SetPenColor("Floor"); 
    drawRectangle(0, 0, 1.3 * cX, 1.6 * cY - 1.5 * GetFontHeight(), 1); 
} 
 
 
void drawTable() { 
    double curx, cury; 
    SetPenSize(1); 
 
    /*Draw tablecloth*/ 
    SetPenColor("Green"); 
    StartFilledRegion(1); 
    MovePen(2.5, 0.8); 
    DrawLine(0.5, 0.5); 
    DrawLine(9.576, 0); 
    DrawLine(0.082, -0.5); 
    DrawLine(0.685, 0); 
    DrawLine(0.082, 0.5); 
    DrawLine(9.576, 0); 
    DrawLine(0.5, -0.5); 
 
    DrawLine(0.6, 0.6); 
 
    DrawLine(-0.5, 0.5); 
    DrawLine(0, 10); 
    DrawLine(0.5, 0.5); 
 
    DrawLine(-0.6, 0.6); 
 
    DrawLine(-0.5, -0.5); 
    DrawLine(-9.574, 0); 
    DrawLine(-0.126, 0.5); 
    DrawLine(-0.6, 0); 
    DrawLine(-0.124, -0.5); 
    DrawLine(-9.576, 0); 
    DrawLine(-0.5, 0.5); 
 
    DrawLine(-0.6, -0.6); 
 
    DrawLine(0.5, -0.5); 
    DrawLine(0, -10); 
    DrawLine(-0.5, -0.5); 
 
    DrawLine(0.6, -0.6); 
    EndFilledRegion(); 
 
    /*Draw wooden armrest*/ 
    SetPenColor("Wood"); 
    MovePen(2.5, 0.8); 
    drawRectangle(2.5, 0.3, 10.158, 0.5, 1); 
    drawRectangle(13.342, 0.3, 10.158, 0.5, 1); 
    drawRectangle(24.1, 1.4, 0.5, 11, 1); 
    drawRectangle(13.3, 13, 10.2, 0.5, 1); 
    drawRectangle(2.5, 13, 10.2, 0.5, 1); 
    drawRectangle(1.4, 1.4, 0.5, 11, 1); 
 
    /*Draw edge of the table*/ 
    SetPenColor("Cobalt Green"); 
    StartFilledRegion(1); 
    MovePen(2.5, 0.8); 
    DrawLine(0.5, 0.5); 
    DrawLine(9.576, 0); 
    DrawLine(0.082, -0.5); 
    DrawLine(-10.158, 0); 
    EndFilledRegion(); 
 
    DrawLine(10.158, 0); 
    DrawLine(0.685, 0); 
 
    StartFilledRegion(1); 
    DrawLine(0.082, 0.5); 
    DrawLine(9.576, 0); 
    DrawLine(0.5, -0.5); 
    DrawLine(-10.158, 0); 
    EndFilledRegion(); 
 
    DrawLine(10.158, 0); 
    DrawLine(0.6, 0.6); 
 
    StartFilledRegion(1); 
    DrawLine(-0.5, 0.5); 
    DrawLine(0, 10); 
    DrawLine(0.5, 0.5); 
    DrawLine(0, -11); 
    EndFilledRegion(); 
 
    DrawLine(0, 11); 
    DrawLine(-0.6, 0.6); 
 
    StartFilledRegion(1); 
    DrawLine(-0.5, -0.5); 
    DrawLine(-9.574, 0); 
    DrawLine(-0.126, 0.5); 
    DrawLine(10.2, 0); 
    EndFilledRegion(); 
 
    DrawLine(-10.2, 0); 
    DrawLine(-0.6, 0); 
 
    StartFilledRegion(1); 
    DrawLine(-0.126, -0.5); 
    DrawLine(-9.576, 0); 
    DrawLine(-0.5, 0.5); 
    DrawLine(10.2, 0); 
    EndFilledRegion(); 
 
    DrawLine(-10.2, 0); 
    DrawLine(-0.6, -0.6); 
 
    StartFilledRegion(1); 
    DrawLine(0.5, -0.5); 
    DrawLine(0, -10); 
    DrawLine(-0.5, -0.5); 
    DrawLine(0, 11); 
    EndFilledRegion(); 
 
    /*Draw leather corner*/ 
    SetPenColor("Leather"); 
    StartFilledRegion(1); 
    MovePen(2.5, 0.8); 
    DrawLine(-0.6, 0.6); 
    DrawLine(-0.5, 0); 
    DrawLine(0, -0.6); 
    DrawArc(0.5, 180, 90); 
    DrawLine(0.6, 0); 
    DrawLine(0, 0.5); 
    EndFilledRegion(); 
 
    DrawLine(10.158, 0); 
    DrawLine(0, -0.5); 
 
    curx = GetCurrentX(); 
    cury = GetCurrentY(); 
    drawRectangle(curx, cury, 0.685, 0.5, 1); 
 
    StartFilledRegion(1); 
    MovePen(23.5, 0.3); 
    DrawLine(0.6, 0); 
    DrawArc(0.5, 270, 90); 
    DrawLine(0, 0.6); 
    DrawLine(-0.5, 0); 
    DrawLine(-0.6, -0.6); 
    EndFilledRegion(); 
 
    StartFilledRegion(1); 
    MovePen(24.1, 12.4); 
    DrawLine(0.5, 0); 
    DrawLine(0, 0.6); 
    DrawArc(0.5, 0, 90); 
    DrawLine(-0.6, 0); 
    DrawLine(0, -0.5); 
    DrawLine(0.6, -0.6); 
    EndFilledRegion(); 
 
    MovePen(12.7, 13); 
    drawRectangle(12.7, 13, 0.6, 0.5, 1); 
 
    StartFilledRegion(1); 
    MovePen(2.5, 13); 
    DrawLine(0, 0.5); 
    DrawLine(-0.6, 0); 
    DrawArc(0.5, 90, 90); 
    DrawLine(0, -0.6); 
    DrawLine(0.5, 0); 
    EndFilledRegion(); 
 
    /*Draw pocket*/ 
    SetPenColor("Ivory Black"); 
    drawCenteredDisc(2.2, 1.1, POC_R); 
    drawCenteredDisc(2.2, 12.7, POC_R); 
    drawCenteredDisc(13, 12.7, POC_R); 
    drawCenteredDisc(23.8, 12.7, POC_R); 
    drawCenteredDisc(23.8, 1.1, POC_R); 
    drawCenteredDisc(13, 1.05, POC_R); 
 
    /*Draw D area*/ 
    if (GameMode == 2) { 
        SetPenColor("White"); 
        SetPenSize(2); 
        MovePen(2 * cX / 5, 12.5); 
        DrawLine(0, -cY - 1.2); 
        MovePen(2 * cX / 5, 12.5 - cY / 2 - 0.6); 
        DrawLine(-0.1, 0); 
        MovePen(2 * cX / 5, 12.5 - cY / 2 - 0.6 + cY / 6 + 0.5); 
        DrawArc(cY / 6 + 0.5, 90, 180); 
    } 
    else {  //Draw spot point 
        MovePen(cX / 3, 12.5 - cY / 2 - 0.6); 
        for (int i = 1; i <= 30; i++) { 
            if (i % 2 == 1) { 
                SetPenColor("White"); 
                DrawArc(R, 12 * (i - 1), 12); 
            } 
            else { 
                SetPenColor("Green"); 
                DrawArc(R, 12 * (i - 1), 12); 
            } 
        } 
    } 
} 
 
void highlightPlayer(int player) {
    int tSize = GetPenSize();
    string tColor = GetPenColor();

    SetPenSize(3);
    SetPenColor("Golden");

    switch (player) {
    case 1:
        MovePen(1.2, 13.6);
        DrawArc(0.9, 90, 90);
        DrawLine(0, -9.9);
        DrawLine(1, 0);
        DrawLine(0, 10.8);
        DrawLine(-0.1, 0);
        break;
    case 2:
        MovePen(24.8, 1);
        DrawArc(0.9, 270, 90);
        DrawLine(0, 9.9);
        DrawLine(-1, 0);
        DrawLine(0, -10.8);
        DrawLine(0.1, 0);
    }

    SetPenSize(tSize);
    SetPenColor(tColor);
}
 
void noHistoryFile() {
    double w = GetWindowWidth(), h = GetWindowHeight();
    double fH = GetFontHeight();
    char text[20] = { "No History File!" };
    double tw;
    int pointsize = GetPointSize();

    SetPenColor("Brown");
    drawRectangle(w / 2 - w / 8, h / 2 - h / 8, w / 4, h / 4, 1);
    SetPenColor("Golden");
    drawRectangle(w / 2 - w / 8, h / 2 - h / 8, w / 4, h / 4, 0);

    SetPenColor("White");
    SetPointSize(20);
    tw = TextStringWidth(text);
    MovePen(w / 2 - tw / 2, h / 2);
    DrawTextString(text);
    SetPointSize(pointsize);
    Pause(1);
}

void drawButton() { 
 
    double wwidth = GetWindowWidth(), wheight = GetWindowHeight(); 
    double fH = GetFontHeight(); 
    double h = 2 * fH; 
    int pointsize = GetPointSize(); 
 
    SetPointSize(30); 
    setButtonColors("Dodger Blue", "Dodger Blue", "Indian Red", "Indian Red", 0); 
    if (ifinitCover && button(GenUIID(0), wwidth / 2 - TextStringWidth("PLAY!"), wheight / 3 - TextStringWidth("PLAY!"), 2 * TextStringWidth("PLAY!"), 2 * h, "PLAY!")) { 
        ifinitCover = FALSE; 
    } 
 
    SetPointSize(pointsize); 
    setButtonColors("White", "White", "Golden", "Golden", 0); 
    if (!ifinitCover && ifinitOption && button(GenUIID(0), wwidth / 2 - TextStringWidth("New Game"), wheight / 2, 2 * TextStringWidth("New Game"), h, "New Game")) { 
        chooseMode = TRUE; 
    } 
 
    if (!ifinitCover && ifinitOption && button(GenUIID(0), wwidth / 2 - TextStringWidth("New Game"), wheight / 2 - 2 * h, 2 * TextStringWidth("New Game"), h, "Continue")) { 
        /*readMode(); 
        bil_list = readBilliardInfo(GameMode); 
        readPlayerInfo(player1, player2); 
        if (ifOffFrame(bil_list)) initMotherBil(); 
        ifinitCover = FALSE; 
        ifinitOption = FALSE; 
        ifshowHelp = FALSE; */
        readMode();
        if (GameMode == 0 || GameMode == 1 || GameMode == 2) {
            bil_list = readBilliardInfo(GameMode);
            readPlayerInfo(player1, player2);
            if (ifOffFrame(bil_list)) initMotherBil();
            ifinitCover = FALSE;
            ifinitOption = FALSE;
            ifshowHelp = FALSE;
            mciSendString(TEXT("close coverSound"), NULL, 0, NULL);
        }
        else {
            noHistoryFile();
        }
    } 
 
    if (!ifinitCover && ifinitOption && button(GenUIID(0), wwidth / 2 - TextStringWidth("New Game"), wheight / 2 - 4 * h, 2 * TextStringWidth("New Game"), h, "Help")) { 
        ifinitOption = FALSE; 
        chooseMode = FALSE; 
        ifshowHelp = TRUE; 
    } 
 
    if (!ifinitCover && ifinitOption && button(GenUIID(0), wwidth / 2 - TextStringWidth("New Game"), wheight / 2 - 6 * h, 2 * TextStringWidth("New Game"), h, "Exit Game")) { 
        exit(0); 
    } 
 
    if (ifshowHelp && button(GenUIID(0), wwidth / 2 - 2 * TextStringWidth("Back to Menu"), wheight / 4 + 0.2, 1.2 * TextStringWidth("Back to Menu"), h, "Back to Menu")) { 
        ifinitOption = TRUE; 
        ifshowHelp = FALSE; 
    } 
 
    if (ifshowHelp && helpChoice >= 1 && button(GenUIID(0), wwidth / 2, wheight / 4 + 0.2, 1.5 * TextStringWidth("Last"), h, "Last")) { 
        helpChoice--; 
    } 
 
    if (ifshowHelp && helpChoice < 2 && button(GenUIID(0), wwidth / 2 + 2 * TextStringWidth("Next"), wheight / 4 + 0.2, 1.5 * TextStringWidth("Next"), h, "Next")) { 
        helpChoice++; 
    } 
 
    if (chooseMode) { 
        if (button(GenUIID(0), wwidth / 2 + 2, wheight / 2 + h, 2 * TextStringWidth("Revised Snooker"), h, "POOL")) { 
            ifinitOption = FALSE; 
            GameMode = 0; 
            chooseMode = FALSE; 
            bil_list = initBilliards(); 
            initMotherBil(); 
            offset1 = 1; 
            offset2 = 1; 
            mciSendString(TEXT("close coverSound"), NULL, 0, NULL); 
        } 
        else if (button(GenUIID(0), wwidth / 2 + 2, wheight / 2, 2 * TextStringWidth("Revised Snooker"), h, "Side Pocket")) { 
            ifinitOption = FALSE; 
            GameMode = 1; 
            chooseMode = FALSE; 
            plcm = NULL; 
            initSidePoc(); 
            offset1 = 1; 
            offset2 = 1; 
            mciSendString(TEXT("close coverSound"), NULL, 0, NULL); 
        } 
        else if (button(GenUIID(0), wwidth / 2 + 2, wheight / 2 - h, 2 * TextStringWidth("Revised Snooker"), h, "Revised Snooker")) { 
            ifinitOption = FALSE; 
            GameMode = 2; 
            chooseMode = FALSE; 
            bil_list = initBilliards(); 
            offset1 = 1; 
            offset2 = 1; 
            mciSendString(TEXT("close coverSound"), NULL, 0, NULL); 
        } 
    } 
 
    if (!ifinitCover && !ifinitOption && !ifshowHelp && ifeditName && button(GenUIID(0), wwidth / 2 - 1.5*TextStringWidth("OKK") , wheight / 2 - 2.5 * fH, 3 * TextStringWidth("OKK"), 1.5 * fH, "Okk!")) { 
        ifeditName = FALSE; 
        if (GameMode == 2) snookerBreakOff = TRUE; 
    } 
 
    if (snookerBreakOff) { 
        if (button(GenUIID(0), wwidth / 2 - 3 * TextStringWidth("Me!"), wheight / 2 - 3 * fH, 2 * TextStringWidth("Me!"), h, "Me!")) { 
            player1->myTurn = TRUE; 
            player2->myTurn = FALSE; 
            snookerBreakOff = FALSE; 
        } 
        if (button(GenUIID(0), wwidth / 2 + 1.5 * TextStringWidth("Me!"), wheight / 2 - 3 * fH, 2 * TextStringWidth("Me!"), h, "Me!")) { 
            player2->myTurn = TRUE; 
            player1->myTurn = FALSE; 
            snookerBreakOff = FALSE; 
        } 
    } 
 
 
    if (selectQuit && button(GenUIID(0), wwidth / 2 - TextStringWidth("OK"), wheight / 2 - wheight / 12, 2 * TextStringWidth("OK"), h, "OK")) { 
        exit(0); 
    } 
 
    if (showRule && button(GenUIID(0), wwidth / 2 - TextStringWidth("OK"), wheight / 3 - 1.8 * h, 2 * TextStringWidth("OK"), h, "OK")) { 
        showRule = FALSE; 
    } 
 
    if (showIllst1 && button(GenUIID(0), wwidth / 2 - TextStringWidth("OK"), wheight / 2 - h, 2 * TextStringWidth("OK"), h, "OK")) { 
        showIllst1 = FALSE; 
    } 
 
    if (showIllst2 && button(GenUIID(0), wwidth / 2 - TextStringWidth("OK"), wheight / 2 - h, 2 * TextStringWidth("OK"), h, "OK")) { 
        showIllst2 = FALSE; 
    } 
 
    if (isGameOver) { 
        if (button(GenUIID(0), wwidth / 2 - 2.35 * TextStringWidth("Back to Menu"), wheight / 2 - cY / 4 - 1.2 * h, 1.5 * TextStringWidth("Back to Menu"), h, "Encore!")) { 
            bil_list = initBilliards(); 
            initMotherBil(); 
            offset1 = 1; 
            offset2 = 1; 
            isGameOver = FALSE; 
        } 
        if (button(GenUIID(0), wwidth / 2 - 0.75 * TextStringWidth("Back to Menu"), wheight / 2 - cY / 4 - 1.2 * h, 1.5 * TextStringWidth("Back to Menu"), h, "Back to Menu")) { 
            ifinitOption = TRUE; 
            ifshowHelp = FALSE; 
            chooseMode = FALSE; 
            ifeditName = TRUE; 
            isGameOver = FALSE; 
        } 
        if (button(GenUIID(0), wwidth / 2 + 0.85 * TextStringWidth("Back to Menu"), wheight / 2 - cY / 4 - 1.2 * h, 1.5 * TextStringWidth("Back to Menu"), h, "Exit")) { 
            exit(0); 
        } 
    } 
 
    if (ifChooseIfServe) { 
        drawChoiceBreakOff(); 
        if (upToChoose == 1) { 
            if (button(GenUIID(0), wwidth / 4 - TextStringWidth("YES"), wheight / 2 - h, 3 * TextStringWidth("YES"), h, "Me!")) { 
                player1->myTurn = TRUE; 
                player2->myTurn = FALSE; 
                ifChooseIfServe = FALSE; 
                serveSidePoc(); 
            } 
            else if (button(GenUIID(0), 3 * wwidth / 4 + TextStringWidth("YES"), wheight / 2 - h, 3 * TextStringWidth("YES"), h, "Me!")) { 
                player1->myTurn = FALSE; 
                player2->myTurn = TRUE; 
                ifChooseIfServe = FALSE; 
                serveSidePoc(); 
            } 
        } 
 
        else if (upToChoose == 2) { 
            if (button(GenUIID(0), 4 * wwidth / 3 - TextStringWidth("YES"), wheight / 2 - h, 2 * TextStringWidth("YES"), h, "YES")) { 
                player1->myTurn = FALSE; 
                player2->myTurn = TRUE; 
                ifChooseIfServe = FALSE; 
                serveSidePoc(); 
            } 
            else if (button(GenUIID(0), 4 * wwidth / 3 - TextStringWidth("YES"), wheight / 2 - 3 * h, 2 * TextStringWidth("YES"), h, "NO")) { 
                player1->myTurn = TRUE; 
                player2->myTurn = FALSE; 
                ifChooseIfServe = FALSE; 
                serveSidePoc(); 
            } 
        } 
    } 
 
    if (ifShowAbout == TRUE) {
        if (button(GenUIID(0), wwidth / 2 - 1.5 * TextStringWidth("Close"), wheight / 2 -2, 3 * TextStringWidth("Close"), 0.9 * h, "Close")) {
            ifShowAbout = FALSE;
        }   
    }
} 
 
 
void drawMenu() { 
 
    double wwidth = GetWindowWidth();
    double wheight = GetWindowHeight();
    double fH = GetFontHeight(); 
 
    setMenuColors("Floor", "White", "Brown", "Golden", 1); 
    static char* menuListSettings[] = { "Settings", 
        "Back to Menu | Ctrl-B", 
        "Quit | Ctrl-Q" }; 
 
    static char* menuListExtensions[] = { "Extensions", 
        "PathPreview | Ctrl-P", 
        "Music | Ctrl-M" }; 
 
    static char* menuListHelp[] = { "Help", 
        "Rules | Ctrl-R", 
        "Side", 
        "Pathpreview", 
        "About" }; 
 
    double w = TextStringWidth(menuListExtensions[0]) * 2; 
    double h = fH * 1.5; 
    double wlist = TextStringWidth(menuListExtensions[0]) * 2; 
    int selection; 
 
    drawMenuBar(0, GetWindowHeight() - h, GetWindowWidth(), h); 
 
    selection = menuList(GenUIID(0), 0, GetWindowHeight() - h, w, wlist, h, 
        menuListSettings, sizeof(menuListSettings) / sizeof(menuListSettings[0])); 
    if (selection == 1) { 
        ifinitOption = TRUE; 
        ifshowHelp = FALSE; 
        chooseMode = FALSE; 
        ifeditName = TRUE; 
        saveBilliardInfo(bil_list); 
        savePlayerInfo(player1, player2); 
        saveMode(); 
    } 
    if (selection == 2) { 
        saveBilliardInfo(bil_list); 
        savePlayerInfo(player1, player2); 
        saveMode(); 
        selectQuit = TRUE; 
    } 
 
 
    menuListExtensions[1] = enableExtension ? "Pathprev :)  |  Ctrl-p" : "Pathprev :(  |  Ctrl-p"; 
    menuListExtensions[2] = enableMusic ? "Music :)  | Ctrl-m" : "Music :(  |  Ctrl-m "; 
    selection = menuList(GenUIID(0), w, GetWindowHeight() - h, w, wlist, h, 
        menuListExtensions, sizeof(menuListExtensions) / sizeof(menuListExtensions[0])); 
    if (selection == 1) enableExtension = !enableExtension; 
    if (selection == 2) enableMusic = !enableMusic; 
 
    if (enableMusic) { 
        mciSendString(TEXT("open ..\\Music\\Saens.wav alias Saens type mpegvideo"), NULL, 0, NULL); 
        mciSendString(TEXT("play Saens repeat"), NULL, 0, NULL); 
    } 
    else { 
        mciSendString(TEXT("close Saens"), NULL, 0, NULL); 
    } 
 
 
    selection = menuList(GenUIID(0), 2 * w, GetWindowHeight() - h, w, wlist, h, 
        menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0])); 
    switch (selection) { 
    case 1: 
        showRule = TRUE; 
        break; 
    case 2: 
        showIllst1 = TRUE; 
        break; 
    case 3: 
        showIllst2 = TRUE; 
        break; 
    case 4: 
        ifShowAbout = TRUE; 
        break; 
    } 
} 
 
 
void displayRule() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    int pensize = GetPenSize(); 
    char* font = GetFont(); 
    int lines, i = 0; 
    char* line[15]; 
    static int mallocOnce = 0; 
 
    if (mallocOnce == 0) { 
        for (int i = 0; i < 15; i++) { 
            line[i] = (char*)malloc(200 * sizeof(char)); 
        } 
        mallocOnce++; 
    } 
 
    switch (GameMode) { 
    case 0: 
        line[0] = "  POOL (also called 8-ball or eightball) is a pool billiards played on a"; 
        line[1] = "billiard table with six pockets, cue sticks, and sixteen billiard balls:"; 
        line[2] = "a cue balland fifteen object balls."; 
        line[3] = "  The object balls include seven solid - colored balls numbered 1 through 7,"; 
        line[4] = "seven striped balls numbered 9 through 15, and the black 8 ball.After the"; 
        line[5] = "balls are scattered with a break shot, a player is assigned either the group"; 
        line[6] = "of solid or striped balls once they have legally pocketed a ball from that group."; 
        line[7] = "  The object of the game is to legally pocket the 8 ball in a called pocket, which"; 
        line[8] = "can only be done after all of the balls from a player's assigned group have been"; 
        line[9] = "cleared from the table."; 
        lines = 10; 
        break; 
    case 1: 
        line[0] = "  The aim of the game is to hit the lowest numbered ball on the table and pocket"; 
        line[1] = "balls in succession to eventually pocket the nine - ball.As long as the lowest "; 
        line[2] = "numbered ball on the table is contacted first by the cueball, and any one or more"; 
        line[3] = "of the object balls are pocketed in any of the 6 pockets with no foul being committed,"; 
        line[4] = "a player's inning continues."; 
        line[5] = "  The winner is the player who legally pockets the nine - ball.This can happen earlier"; 
        line[6] = "than the nine - ball being the sole remaining object ball on the table if it is pocketed"; 
        line[7] = "via a indrected way."; 
        lines = 8; 
        break; 
    case 2: 
        line[0] = "  The objective of the game is to score more points than one's opponent by potting object"; 
        line[1] = "balls in the correct order. When striker needs to pot a red ball, his/her pot can't be colored"; 
        line[2] = "but he/she can pot more than one red ball in one turn. When striker needs to pot a colored ball,"; 
        line[3] = "the cue ball must contact an lowest-points-ball directly or it can be made to bounce off one or"; 
        line[4] = "more cushions before hitting the required object ball."; 
        line[5] = "  The process of potting reds and colours alternately continues until the striker fails to pot the"; 
        line[6] = "desired object ball, at which point the opponent comes to the table to start the next turn.       "; 
        line[7] = "  points are listed as follows:"; 
        line[8] = "red(1), yellow(2), green (3), brown (4), blue (5), pink (6), black (7)"; 
        line[9] = "  pot order of colored ball:"; 
        line[10] = "yellow->green->brown->blue->pink->black"; 
        line[11] = "  When the final ball is potted, the player with the most points wins."; 
        lines = 12; 
        break; 
    } 
 
    double tw = TextStringWidth(line[6]); 
    double th = GetFontHeight(); 
 
    SetPenColor("Brown"); 
    drawRectangle(w / 2 - 1.2 * tw / 2, h / 3 - 4 * th, 1.2 * tw, 1.6 * lines * th + 3 * th, 1); 
    SetPenColor("Golden"); 
    SetPenSize(2); 
    drawRectangle(w / 2 - 1.2 * tw / 2, h / 3 - 4 * th, 1.2 * tw, 1.6 * lines * th + 3 * th, 0); 
 
    SetPenColor("White"); 
 
    for (i = 0; i < lines; i++) { 
        MovePen(w / 2 - tw / 2, h / 3 + (lines - 1 - i) * 1.2 * th); 
        DrawTextString(line[i]); 
    } 
} 
 
 
void displayIllst1() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    int pensize = GetPenSize(); 
    char* font = GetFont(); 
    static int mallocOnce = 0; 
    char* line1, * line2; 
 
    if (mallocOnce == 0) { 
        line1 = (char*)malloc(100 * sizeof(char)); 
        line2 = (char*)malloc(100 * sizeof(char)); 
        mallocOnce++; 
    } 
    line1 = "About Side: Through the adjustment of WASD on the keyboard,"; 
    line2 = "the mother ball can simulate the effect of rotating ball"; 
 
    double tw = TextStringWidth(line1); 
    double th = GetFontHeight(); 
 
    SetPenColor("Brown"); 
    drawRectangle(w / 2 - 1.2 * tw / 2, h / 2 - 2.5 * th, 1.2 * tw, 6 * th, 1); 
    SetPenColor("Golden"); 
    SetPenSize(2); 
    drawRectangle(w / 2 - 1.2 * tw / 2 - 0.01, h / 2 - 2.5 * th - 0.01, 1.2 * tw + 0.01, 6 * th + 0.01, 0); 
 
    SetPenColor("White"); 
    MovePen(w / 2 - tw / 2, h / 2 + 2 * th); 
    DrawTextString(line1); 
    MovePen(w / 2 - tw / 2, h / 2 + 1 * th); 
    DrawTextString(line2); 
} 
 
 
void displayIllst2() { 
 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    int pensize = GetPenSize(); 
    char* font = GetFont(); 
    static int mallocOnce = 0; 
    char* line1, * line2; 
 
    if (mallocOnce == 0) { 
        line1 = (char*)malloc(100 * sizeof(char)); 
        line2 = (char*)malloc(100 * sizeof(char)); 
        mallocOnce++; 
    } 
    line1 = "About pathpreview: Through recursive call to display futural ball movement and collision,"; 
    line2 = "you can choose whether to enable or not in the Extensions bar"; 
 
    double tw = TextStringWidth(line1); 
    double th = GetFontHeight(); 
 
    SetPenColor("Brown"); 
    drawRectangle(w / 2 - 1.2 * tw / 2, h / 2 - 2.5 * th, 1.2 * tw, 6 * th, 1); 
    SetPenColor("Golden"); 
    SetPenSize(2); 
    drawRectangle(w / 2 - 1.2 * tw / 2 - 0.01, h / 2 - 2.5 * th - 0.01, 1.2 * tw + 0.01, 6 * th + 0.01, 0); 
 
    SetPenColor("White"); 
    MovePen(w / 2 - tw / 2, h / 2 + 2 * th); 
    DrawTextString(line1); 
    MovePen(w / 2 - tw / 2, h / 2 + 1 * th); 
    DrawTextString(line2); 
} 
 
 
void archiveOK() { 
    char* tipText = "Archived Successful!"; 
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
 
 
void drawPlayer() { 
 
    SetPenColor("Brown"); 
    StartFilledRegion(1); 
    MovePen(1.2, 13.5); 
    DrawArc(0.8, 90, 90); 
    DrawLine(0, -9.8); 
    DrawLine(0.8, 0); 
    DrawLine(0, 10.6); 
    EndFilledRegion(); 
 
    StartFilledRegion(1); 
    MovePen(24.8, 1.1); 
    DrawArc(0.8, 270, 90); 
    DrawLine(0, 9.8); 
    DrawLine(-0.8, 0); 
    DrawLine(0, -10.6); 
    EndFilledRegion(); 
 
    for (int i = 1; i <= 7; i++) { 
        SetPenColor("Golden"); 
        StartFilledRegion(0.5); 
        drawCenteredCircle(0.8, 3.3 + 0.8 * (i - 1), 1.05 * R); 
        EndFilledRegion(); 
 
        StartFilledRegion(0.5); 
        drawCenteredCircle(25.2, 11.3 - 0.8 * (i - 1), 1.05 * R); 
        EndFilledRegion(); 
    } 
} 
 
 
void editName() { 
    double w = GetWindowWidth(); 
    double h = GetWindowHeight(); 
    double tw = TextStringWidth("abcdefghijk"); 
    double fH = GetFontHeight(); 
 
    SetPenColor("Wood"); 
    drawRectangle(w / 2 - 3 * tw / 2, h / 2 - 3 * fH, 3 * tw, 8 * fH, 1); 
    SetPenColor("Golden"); 
    SetPenSize(2); 
    drawRectangle(w / 2 - 3 * tw / 2, h / 2 - 3 * fH, 3 * tw, 8 * fH, 0); 
    setTextBoxColors("Golden", "White", "Brown", "Golden", 0); 
    MovePen(w / 2 - tw, h / 2 + 2.3 * fH); 
    DrawTextString("player#1"); 
    textbox(GenUIID(0), w / 2, h / 2 + 2 * fH, tw, 1.2 * fH, player1->name, sizeof(player1->name)); 
    MovePen(w / 2 - tw, h / 2 + 0.3*fH); 
    DrawTextString("player#2"); 
    textbox(GenUIID(0), w / 2, h / 2, tw, 1.2 * fH, player2->name, sizeof(player2->name)); 
 
} 
 
 
void drawBillSLD(struct billiard* op) { 
    char id[3]; 
 
    SetEraseMode(FALSE); 
    SetPenColor(op->color); 
    drawCenteredDisc(op->x, op->y, 0.885 * R); 
    SetPenColor("Black"); 
    SetPenSize(2); 
    MovePen(op->x + R, op->y); 
    DrawArc(R, 0, 360); 
 
    if (GameMode != 2) { 
        SetPenColor("White"); 
        drawCenteredDisc(op->x + R / 5.5, op->y + R / 4.5, R / 2.5); 
    } 
    if (op != bil_list && GameMode != 2) { 
        SetPenColor("Black"); 
        MovePen(op->x, op->y - 0.05 * R); 
        SetPointSize(10); 
        sprintf(id, "%d", op->id); 
        DrawTextString(id); 
    } 
} 
 
 
void drawBillSTP(struct billiard* op) { 
    char id[3]; 
 
    SetEraseMode(FALSE); 
    SetPenColor("White"); 
    drawCenteredDisc(op->x, op->y, 0.88 * R); 
    SetPenColor(op->color); 
    MovePen(op->x + 0.93 * R, op->y); 
    StartFilledRegion(1); 
    DrawArc(0.93 * R, 0, 45); 
    DrawLine(-1.33 * R, 0); 
    DrawArc(0.93 * R, 135, 75); 
    DrawLine(1.5 * R, 0); 
    DrawArc(0.93 * R, 330, 30); 
    EndFilledRegion(); 
    SetPenColor("Black"); 
    SetPenSize(2); 
    MovePen(op->x + R, op->y); 
    DrawArc(R, 0, 360); 
    SetPenColor("White"); 
    drawCenteredDisc(op->x + R / 5.5, op->y + R / 4.5, R / 2.5); 
    SetPenColor("Black"); 
    MovePen(op->x - 0.165 * R, op->y - 0.05 * R); 
    sprintf(id, "%d", op->id); 
    DrawTextString(id); 
} 
 
 
void drawBilliards(struct billiard* head) { 
    struct billiard* op = head; 
    int pensize = GetPointSize(); 
    char* font = GetFont(); 
    SetFont("Comic Sans MS"); 
 
    if (ifAllStop()) { 
        if (plcm == NULL) ifBillKnock = 1; 
    } 
 
    while (op != NULL) { 
        if (!ifOffFrame(op)) { 
            SetEraseMode(FALSE); 
            SetPenColor("Ivory Black"); 
            op->shadow[0] = cX / 2 + SHADOW_FACTOR * (op->x - cX / 2); 
            op->shadow[1] = cY / 2 + SHADOW_FACTOR * (op->y - cY / 2); 
            drawCenteredDisc(op->shadow[0], op->shadow[1], 0.85 * R); 
        } 
        op = op->next; 
    } 
 
    switch (GameMode) { 
    case 2: 
        for (op = head; op != NULL; op = op->next) { 
            if (ifPlcmMove && (op->id == plcm->id)) { 
                SetEraseMode(FALSE); 
                SetPenColor(op->color); 
                drawCenteredDiscDashed(op->x, op->y, 0.885 * R); 
                SetPenColor("Black"); 
                SetPenSize(2); 
                MovePen(op->x + R, op->y); 
                DrawArc(R, 0, 360); 
            } 
            drawBillSLD(op); 
        } 
        break; 
    default: 
        for (op = head; op != NULL; op = op->next) { 
            if (op->id >= 0 && op->id <= 8) { 
                if (ifPlcmMove && (op->id == plcm->id)) { 
                    SetEraseMode(FALSE); 
                    SetPenColor(op->color); 
                    drawCenteredDiscDashed(op->x, op->y, 0.885 * R); 
                    SetPenColor("Black"); 
                    SetPenSize(2); 
                    MovePen(op->x + R, op->y); 
                    DrawArc(R, 0, 360); 
                } 
                drawBillSLD(op); 
            } 
            else { 
                drawBillSTP(op); 
            } 
        } 
        break; 
    } 
    SetPointSize(pensize); 
    SetFont(font); 
} 
 
void printFreeHand(FILE* p, double x, double y, double w, double h, int size) { 
    SetPenSize(size); 
    int isHead, isContinue, ifEnd; 
    double sX, sY; 
    ifEnd = fscanf(p, "%d %lf %lf %d", &isHead, &sX, &sY, &isContinue); 
    MovePen(x + sX * w, y + sY * h); 
    while (ifEnd != EOF) { 
        ifEnd = fscanf(p, "%d %lf %lf %d", &isHead, &sX, &sY, &isContinue); 
        MovePen(x + sX * w, y + sY * h); 
        while (isContinue && ifEnd != EOF) { 
            ifEnd = fscanf(p, "%d %lf %lf %d", &isHead, &sX, &sY, &isContinue); 
            drawLineTo(x + sX * w, y + sY * h); 
        } 
    } 
}

