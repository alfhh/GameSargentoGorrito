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
#include <vector>
#include "Button.h"
#include "Object.h"

#include "Bullet.h"
#include "Sperm.h"
#include "Sargent.h"
#include "imageloader.h" // Used to load textures
using namespace std;
// Bitmaps
GLubyte Heart[] = {0x00,0x00,0x00,0x00,
    0x00,0x03,0x80,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x0F,0xE0,0x00,
    0x00,0x1F,0xF0,0x00,
    0x00,0x3F,0xF8,0x00,
    0x00,0x7F,0xFC,0x00,
    0x00,0xFF,0xFE,0x00,
    0x01,0xFF,0xFF,0x00,
    0x03,0xFF,0xFF,0x80,
    0x07,0xFF,0xFF,0xC0,
    0x07,0xFF,0xFF,0xC0,
    0x0F,0xFF,0xFF,0xE0,
    0x0F,0xFF,0xFF,0xE0,
    0x1F,0xFF,0xFF,0xF0,
    0x1F,0xFF,0xFF,0xF0,
    0x3F,0xFF,0xFF,0xF8,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x7F,0xFF,0xFF,0xFC,
    0x3F,0xFE,0xFF,0xF8,
    0x3F,0xFE,0xFF,0xF8,
    0x1F,0xFC,0x7F,0xF0,
    0x01,0x37,0xFF,0xFF,
    0x00,0x00,0x00,0x00,};

//-----------------------------------Bottones
vector <Button> arrButtons;
vector <Bullet> arrBullets;
vector <Object> walls;
vector <Sperm> arrSperm;
Sperm sp(800,800);
Object mouse(-2,-2,1,1);
// Buttons of room 0 = Menu
Button b(450,460,300,80,"Menu Principal",1);
Button b2(450, 320, 300, 80, "Opciones", 2);
Button b3(450, 180, 300, 80, "Laboratorio", 99);
bool labMenu;

// Buttons of room 1 = Game room
Button bEsc(450, 420, 300, 80, "Salir del juego", 0);
Button bEnc(450, 280, 300, 80, "Laboratorio", 9);

Button bNext(1000, 480, 150, 80, "--> ", 10);
Button bPrev(1000, 350, 150, 80, "<-- ", 11);

int virusIndex = 0;

//-----------------------------------Bottones

// -------------------------------------- FRANKS
Sargent s(450,400,50,50,100,0,0,0,0);
Bullet bu(450,400,20,20,0,0);
int pointsPlayer=0;

int rotacionCartas = 0; //TODO change this
int rotacionTotal = 0;

// -------------------------------------- FRANKS
int shoot=0;
// - Textures
static GLuint texName[22]; // TODO UPDATE THIS

// Timer
char tiempo[] = {'0',':','0','0','.','0'};
int sec = 0; // used for the timer

// Game info
int score = 0;

// Strings
string mainTitle="Sargento Gorrito";
string labelLife = "100%";
string labelScore = "Puntuacion = 123,456";
string labelPause = "En pausa";

// Textures
GLuint _textureId; //The id of the texture
int entradaY;
// Player
int playerxcor;
int playerycor;
int playerSpeed = 10;

// Rooms
int actualRoom;

// Virus
GLuint startList;

// Flags
bool timerRunning = false;
bool onPause = false; // If true paints pause screen

// Previous stuff
bool corre=false;
int sP = 0; // Score del player
int sD = 0; // Score del dealer
int angulo = 0;
bool girando = false;

void formato(int i){
    tiempo[0]=(sec/600)+'0';
    tiempo[2]=((sec%600)/100)+'0';
    tiempo[3]=((sec%100)/10)+'0';
    tiempo[5]=(sec%10)+'0';
}
int minSec=0;
int minsec2=0;
int secE=0;
void myTimer(int i) {
    if (timerRunning){
        minSec+=1;
        minsec2++;
        if (minSec==10){
            sec+=1;
            
            minSec=0;
        }
        if(minsec2==100){
            minsec2=0;
        }
        
    }

    if(actualRoom == 9){
        angulo = angulo % 360 + 1;
    }

    if (shoot>0){
        shoot++;
        if (shoot>10)
            shoot=0;
    }

    if (rotacionTotal>0){
       rotacionCartas+=10;
        rotacionTotal-=10;
    }
    else{
        rotacionCartas=0;
    }

    for (int i = 0 ; i < arrBullets.size();i++){
        for(int j = 0 ; j < walls.size();j++){
            if (walls[j].checkColision(arrBullets[i])){
                arrBullets.erase(arrBullets.begin()+i);
                break;
            }
        }
    }
    for (int i = 0 ; i < arrBullets.size();i++){
        for(int j = 0 ; j < arrSperm.size();j++){
            if (arrSperm[j].checkColision(arrBullets[i])){
                arrBullets.erase(arrBullets.begin()+i);
                arrSperm[j].changeHealth(-arrBullets[i].getDamage());
                if (arrSperm[j].getHealth()<=0){
                    arrSperm.erase(arrSperm.begin()+j);
                }
            }
        }
    }
    for (int i = 0 ; i < arrSperm.size();i++){
        if (arrSperm[i].getPosX()+arrSperm[i].getWidth()>1200){
            arrSperm[i].setSpeedX(-2);
        }
        if (arrSperm[i].getPosX()<0){
            arrSperm[i].setSpeedX(2);
        }
        if (arrSperm[i].getPosY()+arrSperm[i].getHeight()>725){
            arrSperm[i].setSpeedY(-2);
        }
        if (arrSperm[i].getPosY()<0){
            arrSperm[i].setSpeedY(2);
        }
    }
    for (int i = 0 ; i < arrSperm.size();i++){
        if (s.checkColision(arrSperm[i])){
            s.changeHealth(-arrSperm[i].getDamage());
            s.setHealthA(10);
            arrSperm.erase(arrSperm.begin()+i);
            cout << s.getHealth()<<endl;
        }
    }
    for (int i = 0 ; i < arrBullets.size();i++){
        arrBullets[i].move();
    }
    for (int i = 0 ; i < arrSperm.size();i++){
        arrSperm[i].move();
    }
    s.move();
    if(s.getPosX()<2||s.getPosX()+s.getWidth()>1200){
        s.setSpeedX(0);
    }
    if(s.getPosY()<2||s.getPosY()+s.getHeight()>725){
        s.setSpeedY(0);
    }
    if (minsec2==99){
        minsec2=0;
        entradaY = rand() % 725;
        if (rand()%2== 0){
            arrSperm.push_back(Sperm (-40,entradaY));
        }
        else{
            arrSperm.push_back(Sperm (1200,entradaY));
        }
        cout << arrSperm.size()<<endl;
    }
    glutTimerFunc(10,myTimer,i);
    formato(sec);
    glutPostRedisplay();

}

//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data

}

void loadImage(string nombreImagen, int numImagen)
{
    Image* image;
    //string ruta = "C:\\Users\\ferra_000\\Desktop\\GameSargentoGorrito\\img\\" + nombreImagen;
    string ruta = "/Users/frankcanseco/Documents/Github/GMG/GMG/GameSargentoGorrito/img/" + nombreImagen;
    cout<<"Ruta="<<ruta<<endl;
    image = loadBMP(ruta.c_str());
    loadTexture(image,numImagen);
    delete image;

}


void init(void)
{
    //PlaySound(TEXT("C:\\Users\\ferra_000\\Desktop\\GameSargentoGorrito\\sonido\\background.wav"),
              //NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    GLUquadricObj *qobj;
    corre=false;
    labMenu = false;
    glClearColor(0,.47,0,1); // Background color
    arrButtons.push_back(b); // Button added to the array
    arrButtons.push_back(b2); // Button added to the array
    arrButtons.push_back(b3); // Button added to the array
    actualRoom = 0; // Default value 0 = mainMenu

    //arrButtons.push_back(b);
    walls.push_back(Object(0, 0,5,800));
    walls.push_back(Object(0, 0,1200,5));
    walls.push_back(Object(0, 725,1200,5));
    walls.push_back(Object(1195, 0,5,800));
    arrSperm.push_back(sp);
    // Player initial values
    //playerxcor = 540;
    //playerycor = 320;


    glEnable(GL_DEPTH);

    //---------------------------------------------- Textures
    GLuint i=0;
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    GLfloat ambientLight[] = {2.0f, 2.0f, 2.0f, 2.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    GLfloat directedLight[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
//    glEnable(GL_DEPTH_TEST);

    glGenTextures(18, texName); //Make room for our texture

    //Cargar todas las texturas
    loadImage("camogreen.bmp",i++);
    loadImage("burried.bmp",i++);
    loadImage("gamefont.bmp",i++);
    loadImage("quad.bmp",i++);
    loadImage("thelab.bmp",i++);
    loadImage("glass.bmp",i++);
    loadImage("textOne.bmp",i++);

    // --- Enfermedades

    loadImage("sida1.bmp",i++); //7
    loadImage("sida2.bmp",i++); //8
    loadImage("sida3.bmp",i++); //9
    loadImage("vph1.bmp",i++); //10
    loadImage("vph2.bmp",i++); //11
    loadImage("vph3.bmp",i++); // 12
    loadImage("gon1.bmp",i++); // 13
    loadImage("gon2.bmp",i++); // 14
    loadImage("gon3.bmp",i++); // 15
    loadImage("her1.bmp",i++); // 16
    loadImage("her2.bmp",i++); // 17
    loadImage("her3.bmp",i++); // 18

    //---------------------------------------------- Textures
    //---------------------------------------------- Quads

    startList = glGenLists(4);
    qobj = gluNewQuadric();


    // gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricDrawStyle(qobj, GLU_POINT); // son puntos
    gluQuadricNormals(qobj, GLU_SMOOTH); // sombreado suave
    glNewList(startList, GL_COMPILE); // precompilar
    gluSphere(qobj, .9, 25, 20);
    glEndList();

    gluQuadricDrawStyle(qobj, GLU_POINT); /* flat shaded */
    gluQuadricNormals(qobj, GLU_FLAT);
    glNewList(startList+3, GL_COMPILE);
    gluCylinder(qobj, 1.0, 0.0, 1.0, 15, 5);
    glEndList();

    gluQuadricDrawStyle(qobj, GLU_SILHOUETTE); /* all polygons wireframe */
    gluQuadricNormals(qobj, GLU_NONE);
    glNewList(startList+6, GL_COMPILE);
    gluDisk(qobj, 0.5, 1.0, 30, 1);
    glEndList();

    gluQuadricDrawStyle(qobj, GLU_SILHOUETTE); /* boundary only  */
    gluQuadricNormals(qobj, GLU_NONE);
    glNewList(startList+9, GL_COMPILE);
    gluPartialDisk(qobj, 0.0, 0.5, 20, 4, 0.0, 275.0);
    glEndList();

    gluQuadricDrawStyle(qobj, GLU_LINE); // son puntos
    gluQuadricNormals(qobj, GLU_SMOOTH); // sombreado suave
    glNewList(startList+2, GL_COMPILE); // precompilar
    gluSphere(qobj, 0.37, 25, 20);
    glEndList();

    //---------------------------------------------- Quads
}

// MAIN MENU
void room0() {
    glClearColor(0,.47,0,1); // Background color
    glColor3f(1,1,1);

    // ---------------------------- TEXTURES
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glPushMatrix();
    glTranslatef(600, 400, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-600.0f, -600.0f, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(600.0f, -600.0f, 0);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(600.0f, 600.0f, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-600.0f, 600.0f, 0);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    // ---------------------------- TEXTURES

    //--------------- Display mainTitle string
    glPushMatrix();
    glTranslatef(1200/(mainTitle.size()), 8.0*800/9.0, 1);
    glScaled(0.6-(mainTitle.size()*.005), 0.6-(mainTitle.size()*.005), 0.6);
    for (int k=0;k<mainTitle.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, mainTitle[k]);
    glPopMatrix();

    //--------------- Display buttons
    b.draw(); // Button1
    b2.draw(); // Button 2
    b3.draw(); // Button 3

}

// HEALTH MANUAL
void manual(){
    glClearColor(.99,.93,.75,1); // Background color
    glColor3f(1,1,1);

    // ---------------------------- TEXTURES
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[4]);
    glPushMatrix();
    glTranslatef(600, 400, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-600.0f, -600.0f, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(600.0f, -600.0f, 0);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(600.0f, 600.0f, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-600.0f, 600.0f, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(600, 400, 0);


    // ---------------------------- TEXTURES
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-550.0f, -300.0f, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(300.0f, -300.0f, 0);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(300.0f, 300.0f, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-550.0f, 300.0f, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // ---------------------------- TEXTURES

    glPushMatrix();
    glTranslatef(-120, 0, 0);

    glColor3f(1,1,1);
    glPointSize(5);

    glPushMatrix(); // -------------- DISPLAY IMAGE
    glRotated(angulo, 0, 1, 0);
    glTranslatef(0,150,0);
    glScalef(100,100,100);
    glColor3f(1.0, 0.0, 0.0);
    glCallList(startList + virusIndex); // <- Esfera 1
    glColor3f(1,1,1);
    if(virusIndex == 0)
        glCallList(startList+2); // <- Esfera 2
    glPopMatrix();

    // ------------------------ INFO

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-250, -100, 0);
    glBindTexture(GL_TEXTURE_2D, texName[ 7 + virusIndex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-128.0f, -128.0f, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(128.0f, -128.0f, 0);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(128.0f, 128.0f, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-128.0f, 128.0f, 0);
    glEnd();
    glPopMatrix(); // ------------------------- TEXT1

    glPushMatrix();
    glTranslatef(0, -100, 0);
    glBindTexture(GL_TEXTURE_2D, texName[8 + virusIndex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-128.0f, -128.0f, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(128.0f, -128.0f, 0);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(128.0f, 128.0f, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-128.0f, 128.0f, 0);
    glEnd();
    glPopMatrix(); // ------------------------- TEXT2

    glPushMatrix();
    glTranslatef(250, -100, 0);
    glBindTexture(GL_TEXTURE_2D, texName[ 9 + virusIndex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-128.0f, -128.0f, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(128.0f, -128.0f, 0);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(128.0f, 128.0f, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-128.0f, 128.0f, 0);
    glEnd();
    glPopMatrix(); // ------------------------- TEXT3

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // ------------------------ INFO

    glPopMatrix();
    glPopMatrix();

    bNext.draw();
    bPrev.draw();
    // ---------------------------- TEXTURES
}

// Draw the player
void drawPlayer(){
    glColor3f(1, 0,0);
    glRectf(0, 0, 60, 80);
}

// FIRST LEVEL
void room1() {
    glClearColor(1,1,1,1); // Background color
    score = 0; // Reset the score of the player

    // ---------------------------- TEXTURES
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glPushMatrix();
    glTranslatef(600, 400, -100);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-600.0f, -600.0f, 0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(600.0f, -600.0f, 0);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(600.0f, 600.0f, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-600.0f, 600.0f, 0);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glPushMatrix();
    glTranslatef(600, 765, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-600.0f, -35.0f, 0);

    glTexCoord2f(9.0f, 0.0f);
    glVertex3f(600.0f, -35.0f, 0);

    glTexCoord2f(9.0f,9.0f);
    glVertex3f(600.0f, 35.0f, 0);

    glTexCoord2f(0.0f, 9.0f);
    glVertex3f(-600.0f, 35.0f, 0);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    // ---------------------------- TEXTURES

    // Navbar
    glColor3f(0,0,0);
    //glRectf(0, 730, 1200, 800); // Draws the black navbar
    glColor3f(1,0,0); // Color red
    glRasterPos2d(20, 750); // Position of the heart
    glBitmap(32, 32, 0,0, 10, 0, Heart); // Draws the heart

    glPushMatrix(); // --------------------Matrix used to have all inside the navbar
    glTranslatef(60, 750, 0);

    glPushMatrix(); // Displays the timer
    glTranslatef(1000, 0, 0);
    glColor3f(1,1,1); // Color white
    glScaled(.3, .3, .3);
    for (int k=0;k<6; k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, tiempo[k]);
    glPopMatrix();

    glPushMatrix(); // Displays the score
    glTranslatef(350, 0, 0);
    glColor3f(1,1,1); // Color white
    glScaled(.3, .3, .3);
    for (int k=0;k<labelScore.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, labelScore[k]);
    glPopMatrix();

    glPushMatrix(); // Diplay percentage of the player's life
    glColor3f(0,0,1); // Color white
    glScaled(.3, .3, .3);
    for (int k=0;k<labelLife.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, labelLife[k]);
    glPopMatrix();

    glPopMatrix(); // -------------------------------------------------------- NAVBAR

    // ----------------------------- Player
    s.draw(mouse.getPosX(), mouse.getPosY());
    for (Bullet aux:arrBullets){
        aux.draw();
    }
    for (int i = 0 ; i < arrSperm.size() ;i++){
        arrSperm[i].draw();
    }
    //------------------------------ Player

    if(onPause) { // Display the pause window

        glColor3f(.92, .92, .92); // Color gray
        glPushMatrix();
        glTranslatef(600, 400, 0);

        // ---------------------------- TEXTURES
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texName[3]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-250.0f, -250.0f, 0);

        glTexCoord2f(5.0f, 0.0f);
        glVertex3f(250.0f, -250.0f, 0);

        glTexCoord2f(5.0f,5.0f);
        glVertex3f(250.0f, 250.0f, 0);

        glTexCoord2f(0.0f, 5.0f);
        glVertex3f(-250.0f, 250.0f, 0);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        // ---------------------------- TEXTURES


        glPushMatrix(); // Pause label
        glTranslatef(-90, 180, 0);
        glColor3f(0,0,0); // Color black
        glScaled(.3, .3, .3);
        for (int k=0;k<labelPause.size(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, labelPause[k]);
        glPopMatrix();
        glPopMatrix();
        bEsc.draw();
        bEnc.draw();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glLineWidth(1.0);

    switch (actualRoom) {
        case 0: // Paints the main menu
            room0();
            break;
        case 1: // Paints the first level
            room1();
            break;
        case 9:
            manual();
            break;
        default:
            break;
    }
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

void checkButtons(){
    int val=-1;
    for(Button b : arrButtons){
        if(actualRoom == 0){
                if (b.getTarget(mouse) > -1){
                val = b.getTarget(mouse);
                cout << "entro" << endl;
                break;
            } else if (b2.getTarget(mouse) > -1){
                val = b2.getTarget(mouse);
                cout << "entro" << endl;
                break;
            } else if (b3.getTarget(mouse) > -1){
                val = b3.getTarget(mouse);
                cout << "entro" << val << endl;
                break;
            }
        } else if(actualRoom == 1){
            if ((bEsc.getTarget(mouse) > -1) && onPause){
                val = bEsc.getTarget(mouse);
                cout << "entro" << endl;
                break;
            } else if ((bEnc.getTarget(mouse) > -1) && onPause){
                val = bEnc.getTarget(mouse);
                cout << "entro" << endl;
                break;
            }
        } else if(actualRoom == 9){
            if ((bPrev.getTarget(mouse) > -1) && onPause){
                val = bPrev.getTarget(mouse);
                cout << "entro" << endl;
                break;
            } else if ((bNext.getTarget(mouse) > -1) && onPause){
                val = bNext.getTarget(mouse);
                cout << "entro" << endl;
                break;
            }
        }
    }

    switch (val) {
        case -1:
            break;
        case 0:
            cout << "Go to room 0" << endl;
            timerRunning = false;
            onPause = false;
            actualRoom = 0;
            break;
        case 1:
            cout << "Go to room 1" << endl;
            actualRoom = 1;
            timerRunning = true;
            sec = 0;
            break;
        case 2:
            cout << "Go to room Opciones" << endl;
            break;
        case 9:
            cout << "Go to room Enciclopedia";
            timerRunning = false;
            actualRoom = 9;
            break;
        case 99:
            labMenu = true;
            onPause = true;
            actualRoom = 9;
            break;
        case 10:
            virusIndex+=3;
            virusIndex = (virusIndex > 9) ? 9 : virusIndex;
            cout << "Go Next " << virusIndex << endl;
            break;
        case 11:
            virusIndex-=3;
            virusIndex = (virusIndex < 0) ? 0 : virusIndex;
            cout << "Go Prev " << virusIndex << endl;
            break;
        default:
            break;
    }
}


void myMouse(int button, int state, int x, int y)
{
    // Fix of y
    y = (y * 800) / glutGet(GLUT_WINDOW_HEIGHT);
    y = 800 - y;
    x = (x * 1200) / glutGet(GLUT_WINDOW_WIDTH);

    if (state == GLUT_DOWN){

    }
    else
        if (state == GLUT_UP) // Check if button is clicked
        {
            mouse.setPosX(x);
            mouse.setPosY(y);
            cout << "The position of the mouse X: " << mouse.getPosX() <<" and Y: " << mouse.getPosY() << endl;
            //cout << "The position of the button X: " << arrButtons[0].getPosX() <<" and Y: " << arrButtons[0].getPosY() << endl;
            if (actualRoom==1&&!onPause){
                if (shoot==0){
                    shoot=1;
                    arrBullets.push_back(Bullet(s.getPosX()+s.getWidth()*.25, s.getPosY()+s.getHeight()*.25,20,20,s.getAimX(),s.getAimY()));
                }
            }
            checkButtons();
        }
}
void myMousePassive(int x, int y){
    y = (y * 800) / glutGet(GLUT_WINDOW_HEIGHT);
    y = 800 - y;
    x = (x * 1200) / glutGet(GLUT_WINDOW_WIDTH);
    mouse.setPosX(x);
    mouse.setPosY(y);
}


void myKeyboard(unsigned char theKey, int x, int y)
{
    y = (y * 800) / glutGet(GLUT_WINDOW_HEIGHT);
    y = 800 - y;
    if(actualRoom == 0){ // Main menu
            switch (theKey) {
            case 27:
                exit(-1); //terminate the program
            default:
                break; // do nothing
        }
    } else if(actualRoom == 1){ // Game room
        switch (theKey) {
            case 'w':
            case 'W': // Movement upward
                if(s.getPosY() + s.getHeight() < 725){
                    s.setSpeedY(5);
                }
                else{
                    s.setSpeedY(0);
                }
                break;
            case 's':
            case 'S': // Movement downward
                if(s.getPosY() > 0){
                    s.setSpeedY(-5);
                }
                else{
                    s.setSpeedY(0);
                }
                break;
            case 'a':
            case 'A': // Go left
                if(s.getPosX() > 0){
                    s.setSpeedX(-5);
                }
                else{
                    s.setSpeedX(0);
                }
                break;
            case 'd':
            case 'D': // Go right
                if(s.getPosX() + s.getWidth() < 1200){
                    s.setSpeedX(5);
                }
                else{
                    s.setSpeedX(0);
                }
                break;
            case 27: // Pause game
                onPause = !onPause;
                timerRunning = !timerRunning;
                break;
            default:
                break; // do nothing
        }
    } else if(actualRoom == 9){ // Enciclopedia room
        switch (theKey) {
            case 27:
                if(labMenu){
                    actualRoom = 0;
                    onPause = false;
                } else {
                    actualRoom = 1;
                    timerRunning = false;
                    onPause = true;
                }
                break;
            default:
                break; // do nothing
        }
    }
}

void myKeyboardUp(unsigned char theKey, int x, int y)
{
    if(actualRoom == 1){ // Game room
        switch (theKey) {
            case 'w':
            case 'W': // Movement upward
                if(s.getPosY() + s.getHeight() < 725){
                    s.setSpeedY(0);
                }
                else{
                    s.setSpeedY(0);
                }
                break;
            case 's':
            case 'S': // Movement downward
                if(s.getPosY() > 0){
                    s.setSpeedY(0);
                }
                else{
                    s.setSpeedY(0);
                }
                break;
            case 'a':
            case 'A': // Go left
                if(s.getPosX() > 0){
                    s.setSpeedX(0);
                }
                else{
                    s.setSpeedX(0);
                }
                break;
            case 'd':
            case 'D': // Go right
                if(s.getPosX() + s.getWidth() < 1200){
                    s.setSpeedX(0);
                }
                else{
                    s.setSpeedX(0);
                }
                break;
                break; // do nothing
        }
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
    glutTimerFunc(5, myTimer, 0);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutPassiveMotionFunc(myMousePassive);
    glutKeyboardFunc(myKeyboard);
    glutKeyboardUpFunc(myKeyboardUp);
    glutMainLoop();
    glutPostRedisplay();
    return EXIT_SUCCESS;
}

//-------------------------------------------- IMAGE LOADER

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}

//-------------------------------------------- IMAGE LOADER
