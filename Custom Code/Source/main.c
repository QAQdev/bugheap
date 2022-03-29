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
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"

#include "draw.h"
#include "rule.h"
#include "collide.h"
#include "univLib.h"
#include "userIntr.h"
#include "archive.h"
#include "init.h"



void timerEvent(int timerID);

void Main() {

    SetWindowSize(1.3 * cX, 1.6 * cY);
    SetWindowTitle("Bug[Heap]");

    InitGraphics();
    InitGUI();

    registerMouseEvent(mouseEvent);
    registerKeyboardEvent(keyboardEvent);
    registerTimerEvent(timerEvent);
    registerCharEvent(CharEventProcess);
  
    initTable();
    initPlayers();
    initFlags();

    mciSendString(TEXT("open ..\\Music\\coverSound.wav alias coverSound type mpegvideo"), NULL, 0, NULL);
    mciSendString(TEXT("play coverSound repeat"), NULL, 0, NULL);

    startTimer(TIMER_CAL, DT);
    startTimer(TIMER_REF, RF);
}

void timerEvent(int timerID) {
    switch (timerID) {
    case TIMER_CAL:
        nextTimeInit(bil_list);
        break;
    case TIMER_REF:
        screenRefresh(bil_list);
        break;
    default:break;
    }
}