//
//  Sargent.h
//  GMG
//
//  Created by Francisco Canseco on 15/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#ifndef __GMG__Sargent__
#define __GMG__Sargent__
#ifdef __APPLE__
#include <stdio.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include "Object.h";
#include "Character.h";
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;
class Sargent : public Character {
private:
    double aimX;
    double aimY;
public:
    Sargent (int x, int y, int w , int h, int he,int sX, int sY,int p, int d);
    void move();
    void draw(int mouseX, int mouseY);
    double getAimX();
    double getAimY();
};

#endif /* defined(__GMG__Sargent__) */
