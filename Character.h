//
//  Character.h
//  GMG
//
//  Created by Francisco Canseco on 15/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#ifndef __GMG__Character__
#define __GMG__Character__
#ifdef __APPLE__
#include <stdio.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include "Object.h";
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
class Character : public Object {
private:
    int health;
    int speedX;
    int speedY;
    int points;
    int damage;
public:
    Character (int x, int y, int w , int h, int he,int sX, int sY,int p, int d);
    int getHealth();
    void changeHealth(int h);
    int getSpeedX();
    void setSpeedX(int sX);
    int getSpeedY();
    void setSpeedY(int sY);
    int getPoints();
    void disPlayPoints();
    int getDamage();
    void move();
};
#endif /* defined(__GMG__Character__) */
