//  
//  view.c
//  
//  funcs involved in three-dimensional transformation and projection.
//  v0.1, 28 May 2021

#include "univLib.h"
#include "view.h"
#include "draw.h"
#include "userIntr.h"

double* martixMult(double martix[][4], double vectorT[]) {
    int i, j;
    double* ansT = (double*)malloc(4 * sizeof(double));

    for (i = 0; i < 4; i++) {
        ansT[i] = 0;
        for (j = 0; j < 4; j++) {
            ansT[i] += martix[i][j] * vectorT[j];
        }
    }
    return ansT;
}
double* rotAroundX(double vectorT[], double rad){

}


double* spheToRect(double vectorT[4]) { //  input formed as rou, theta, phi
    double* rect;
    rect = (double*)malloc(4 * sizeof(double));
    double projXOY = vectorT[0] * sin(vectorT[1]);
    rect[0] = projXOY * cos(vectorT[2]);
    rect[1] = projXOY * sin(vectorT[2]);
    rect[2] = vectorT[0] * cos(vectorT[1]);
    return rect;
}

void drawGradientPara(double ini[3], double fin[3], double posi[4][2], int layer, double fill) {
    int cycle = 0;
    double subPosi[4][2], delta[2][2], deltaClr[3], color[3] = { ini[0], ini[1], ini[2] };
   
    delta[0][0] = (posi[1][0] - posi[0][0]) / layer;
    delta[0][1] = (posi[1][1] - posi[0][1]) / layer;
    delta[1][0] = (posi[2][0] - posi[3][0]) / layer;
    delta[1][1] = (posi[2][1] - posi[3][1]) / layer;

    deltaClr[0] = (fin[0] - ini[0]) / layer;
    deltaClr[1] = (fin[1] - ini[1]) / layer;
    deltaClr[2] = (fin[2] - ini[2]) / layer;

    subPosi[0][0] = posi[0][0] - delta[0][0];
    subPosi[1][0] = posi[0][0];
    subPosi[2][0] = posi[3][0];
    subPosi[3][0] = posi[3][0] - delta[1][0];

    subPosi[0][1] = posi[0][1] - delta[0][1];
    subPosi[1][1] = posi[0][1];
    subPosi[2][1] = posi[3][1];
    subPosi[3][1] = posi[3][1] - delta[1][1];



    for (cycle; cycle < layer; cycle++) {
        subPosi[1][0] += delta[0][0];
        subPosi[1][0] += delta[0][1];
        subPosi[2][0] += delta[1][0];
        subPosi[2][0] += delta[1][1];
        
        subPosi[0][0] += delta[0][0];
        subPosi[0][0] += delta[0][1];
        subPosi[3][0] += delta[1][0];
        subPosi[3][0] += delta[1][1];

        color[0] += deltaClr[0];
        color[1] += deltaClr[1];
        color[2] += deltaClr[2];

        defineTempColor(color);

        SetPenColor("tempColor");
        StartFilledRegion(fill);
        MovePen(subPosi[0][0], subPosi[0][1]);
        drawLineTo(subPosi[1][0], subPosi[1][1]);
        drawLineTo(subPosi[2][0], subPosi[2][1]);
        drawLineTo(subPosi[3][0], subPosi[3][1]);
        drawLineTo(subPosi[0][0], subPosi[0][1]);

        EndFilledRegion();
    }
}

void defineTempColor(double tempRGB[3]) {
    InitColors();
    DefineColor("tempColor", tempRGB[0], tempRGB[1], tempRGB[2]);
}

