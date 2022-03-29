//  
//  view.h
//  
//  funcs involved in three-dimensional transformation and projection.
//  v0.1, 28 May 2021

#pragma once

double* martixMult(double martix[][4], double vectorT[]);
double* rotAroundX(double vectorT[], double rad);
double* rotAroundY(double vectorT[], double rad);
double* rotAroundZ(double vectorT[], double rad);

void drawGradientPara(double ini[3], double fin[3], double posi[4][2], int layer, double fill);
void defineTempColor(double tempRGB[3]);