//
//  main.cpp
//  BlackJack
//
//  Created by Francisco Canseco on 18/09/15.
//  Created by Alfredo Hinojosa
//  Copyright (c) 2015 Ma. Guadalupe Roque. All rights reserved.
//

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

int pointsDealer=0;
string mensaje="Deal?";
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

GLsizei winWidth =1200, winHeight =800;

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
    glClearColor(0,.47,0,1); // Color de la ventada, el fondo naranja

}

void display(){
    //actSize();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Dibuja el cuadro del fondo
    glPushMatrix();
    glColor3f(0.82, 0.62, 0.39); // Color cafe
    glTranslatef(550,  400, 0);
    glRotatef(angulo + 20, 0.0, 0.0, 1.0);
    glutSolidCube(800);
    glPopMatrix();


    //CARTA QUE TAPA LA PRIMERA DEL DEALER
    if(corre){
        glColor4f(1, 0, 0, 1);
        float x =winWidth/20.0;
        glRectf(x, (5.5*winHeight/7.0) - winHeight/100.0 , x+winWidth/10.0, (4.0*winHeight/7.0)+winHeight/100.0);
    }


    glLineWidth(1.0);
    glColor3f(1,1,1);

    //--------------- Despliega Mensaje
    glPushMatrix();
    glTranslatef(winWidth/(mensaje.size()), 8.0*winHeight/9.0, 1);
    glScaled(0.6-(mensaje.size()*.005), 0.6-(mensaje.size()*.005), 0.6);

    for (int k=0;k<mensaje.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, mensaje[k]);
    glPopMatrix();

    //--------------- Despliega Nombre D
    glLineWidth(3.5);
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(winWidth/20.0, 5.5*winHeight/7.0, 1);
    glScaled(0.5, 0.5, 0.5);
    for (int k=0;k<s1.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s1[k]);
    glPopMatrix();
    glColor3f(0,0,1);
    //--------------- Despliega Nombre P

    glPushMatrix();
    glTranslatef(winWidth/20.0, 3.5*winHeight/7.0, 1);
    glScaled(0.5, 0.5, 0.5);
    for (int k=0;k<s2.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s2[k]);
    glPopMatrix();
    glColor3f(1,1,1);
    //--------------- Despliega Instrucciones
    glLineWidth(1.0);
    glPushMatrix();
    glTranslatef(winWidth/20.0, winHeight/6.0, 1);
    glScaled(0.5, 0.5, 0.5);
    for (int k=0;k<s3.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s3[k]);
    glPopMatrix();
    //--------------- Despliega Nombre Autor

    glPushMatrix();
    glTranslatef(winWidth/40.0, winHeight/10, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<s4.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s4[k]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(winWidth/40.0, winHeight/30, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<sA.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, sA[k]);
    glPopMatrix();


    //--------------- Despliega Puntos D

    if(!corre){
        glPushMatrix();
        glTranslatef(winWidth/1.7, 5.5*winHeight/7.0, 1);
        glScaled(0.3, 0.3, 0.3);
        for (int k=0;k<s5.size(); k++)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s5[k]);
        glPopMatrix();
    }

    //--------------- Despliega Score D

    glPushMatrix();
    glTranslatef(winWidth/1.7, 4.6*winHeight/7.0, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<s7.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s7[k]);
    glPopMatrix();


    //--------------- Despliega Puntos P

    if(!corre){
        glPushMatrix();
        glTranslatef(winWidth/1.7, 3.5*winHeight/7.0, 1);
        glScaled(0.3, 0.3, 0.3);
        for (int k=0;k<s6.size(); k++)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s6[k]);
        glPopMatrix();
    }

    //--------------- Despliega Score P

    glPushMatrix();
    glTranslatef(winWidth/1.7, 4.1*winHeight/7.0, 1);
    glScaled(0.3, 0.3, 0.3);
    for (int k=0;k<s8.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s8[k]);
    glPopMatrix();

      glutSwapBuffers();
}


void reshape (int w, int h)
{   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION); // Tipo de proyecion
    glLoadIdentity ();
    glOrtho(0, 1200, 0, 800, -600  , 600);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
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



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(winWidth, winHeight); // Ajusta el ancho y alto de la ventana
    glutInitWindowPosition(200,0); // Posicion en la que aparece la ventana en la pantalla
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); // Doble buffer para animacion
    glutCreateWindow("Blackjack");
    init(); // Inicializa todas las variables
    glutDisplayFunc(display);
    glutTimerFunc(5, timer, 1);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    glutPostRedisplay();
    return EXIT_SUCCESS;
}

