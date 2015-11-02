//
//  Button.h
//  GameSargentoGorrito
//
//  Created by Francisco Canseco on 01/11/15.
//  Copyright (c) 2015 Francisco Canseco. All rights reserved.
//

#ifndef __GameSargentoGorrito__Button__
#define __GameSargentoGorrito__Button__
#ifdef __APPLE__
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


class Button : public Object {
private:
    string title;
    int target;
public:
    Button(int x,int y, int w, int h, string s, int t);
    string getTitle();
    void setTitle(string s);
    int getTarget(Object o);
    void draw();
};

#endif /* defined(__GameSargentoGorrito__Button__) */
