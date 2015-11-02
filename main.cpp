//
//  main.cpp
//  Sargento Gorrito
//  Developed by Francisco Canseco and Alfredo Hinojosa

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

#include "Button.h"
#include "Object.h"
using namespace std;
//Cosas Nuevas
vector <Button> arrButtons;
Object mouse(-2,-2,1,1);
Button b(450,460,300,80,"HOLA",1);
//Termina Cosas Nuevas

int pointsDealer=0;
// Strings
string mainTitle="Sargento Gorrito";
string s1="Dealer:";
string s2="Player:";
string s3="D-Deal H-Hit S-Stand Esc-Salir";
string s4="Autor: Francisco Canseco Dominguez Matricula: A01034948";
string sA="Autor: Alfredo Hinojosa Huerta Matricula: A01036053";
string s5="Points Dealer = ";
string s6="Points Player = ";
string s7="Score Dealer = ";
string s8="Score Player = ";
bool corre=false;
int pointsPlayer=0;
int sP = 0; // Score del player
int sD = 0; // Score del dealer

// VARIANBLES DE CARTAS FRANK
int rotacionCartas = 0;
int rotacionTotal = 0;

// ANGULO PARA ROTACION FONDO
int angulo = 0;
bool girando = false;

void timer(int value){

    if(girando && angulo <= 360){
        angulo = rotacionCartas;
    } else {
        angulo = 0;
        girando = false;
    }

    if (rotacionTotal>0){
       rotacionCartas+=10;
        rotacionTotal-=10;
    }
    else{
        rotacionCartas=0;
    }
    glutPostRedisplay();
    glutTimerFunc(10, timer, 1);
}

void init(void)
{
    corre=false;
    glClearColor(0,.47,0,1); // Background color
    //glEnable(GL_DEPTH_TEST);
}

// Display buttons
void paintButton(int posX, int posY){

    glPushMatrix(); // Draws the border of the button
    glTranslatef(450 + posX, 400 + posY, 0);
    glColor3f(0,0,0);
    glRectf(0,0,300,80);
    glPushMatrix(); // Draws the inner part of the button
    glColor3f(1,1,1);
    glTranslatef(15, 4, 0);
    glScalef(.9, .9, 1);
    glRectf(0,0,300,80);
    glPopMatrix();
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLineWidth(1.0);
    glColor3f(1,1,1);

    //--------------- Display mainTitle string
    glPushMatrix();
    glTranslatef(1200/(mainTitle.size()), 8.0*800/9.0, 1);
    glScaled(0.6-(mainTitle.size()*.005), 0.6-(mainTitle.size()*.005), 0.6);
    for (int k=0;k<mainTitle.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, mainTitle[k]);
    glPopMatrix();

    //--------------- Display buttons
    // Paint button 1
    paintButton(0, 60);
    b.draw();
    // Paint button 2
    paintButton(0, -60);

    // Paint button 3
    paintButton(0, -180);
    
    glutSwapBuffers();
}


void reshape (int w, int h)
{   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION); // Projection type
    glLoadIdentity ();

    // The coordiantes of the game
    // X goes from 0 to 1200
    // Y goes from 0 to 800
    // Near and far from -600 to 600
    glOrtho(0, 1200, 0, 800, -600  , 600);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);

}

void myMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN){

    } else if (state == GLUT_UP){

    }
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{    switch (theKey)
    {
        case 'd':
        case 'D':
            rotacionTotal = 360;
            girando = true;
            break;
        case 'h':
        case 'H':
            rotacionTotal = 360;
            girando = true;
            break;
        case 's':
        case 'S':
            rotacionTotal = 360;
            girando = true;
            break;
        case 27:
            exit(-1); //terminate the program
        default:
            break; // do nothing
    }
}

void checkButtons(){
    int val=-1;
    for(Button b : arrButtons){
        if (b.getTarget(mouse)>-1){
            val = b.getTarget(mouse);
            break;
        }
    }
    switch (val) {
        case -1:
            break;
        case 1:
            cout << "Play game!!" << endl;
            break;
        default:
            break;
    }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 800); // Size of the window, using globals
    glutInitWindowPosition(200,0); // Starting point of the screen
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); // Doble buffer for animations
    glutCreateWindow("Sargento Gorrito: El juego");
    init(); // Initialize all the game variables
    glutDisplayFunc(display);
    glutTimerFunc(5, timer, 1);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    glutPostRedisplay();
    return EXIT_SUCCESS;
}

