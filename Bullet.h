//
//  Bullet.h
//  GMG
//
//  Created by Francisco Canseco on 15/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#ifndef __GMG__Bullet__
#define __GMG__Bullet__
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
class Bullet : public Character {
private:
public:
    Bullet (int x, int y, int w , int h,double sX, double sY);
    void move();
    void draw();
};
#endif /* defined(__GMG__Bullet__) */
