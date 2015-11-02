//
//  Object.h
//  GameSargentoGorrito
//
//  Created by Francisco Canseco on 01/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#ifndef __GameSargentoGorrito__Object__
#define __GameSargentoGorrito__Object__
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

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


class Object {
private:
    int posX;
    int posY;
    int width;
    int height;
public:
    Object(int x,int y, int w, int h);
    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
    void setPosX(int x);
    void setPosY(int y);
    void setWidth(int w);
    void setHeight(int h);
    bool checkColision(Object o);
    
};

#endif /* defined(__GameSargentoGorrito__Object__) */
