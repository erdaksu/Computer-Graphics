/////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include <string>
#include <windows.h>
#include <time.h>
#include <vector>
#include <mmsystem.h>
#include "SOIL.h"
#include <time.h>
#pragma comment(lib, "SOIL")
#define KEY_UP 101
#define KEY_DOWN 103
#define KEY_LEFT 100
#define KEY_RIGHT 102
#define RAINSIZE 10
/////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
float tx = 0.0, ty = 0.0;
float tx1 = 0.0, ty1 = 0.0;
float tx2 = 0.0, ty2 = 0.0;
float sx = 0.0, sy = 0.0;
float theta = 0.0;
int counter = 0;
int frame = 0;
int mode;
float winWidth = 1200;
float winHeight = 800;
int winWidth1 = 1600, winHeight1 = 1000;
char textBuffer[200];
bool drawBoundingBoxes = false;
bool drawBoundingCircles = false;
time_t t;

int starTween[10][2];
int uberTween[10][2];
int tweenPoly[10][2];
float proportion = 0.0;
/////////////////////////////////////////////////////////////////////////////////////////////////
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);

	starTween[0][0] = 175;
	starTween[0][1] = 300;
	starTween[1][0] = 250;
	starTween[1][1] = 300;
	starTween[2][0] = 275;
	starTween[2][1] = 350;
	starTween[3][0] = 300;
	starTween[3][1] = 300;
	starTween[4][0] = 375;
	starTween[4][1] = 300;
	starTween[5][0] = 325;
	starTween[5][1] = 250;
	starTween[6][0] = 350;
	starTween[6][1] = 150;
	starTween[7][0] = 275;
	starTween[7][1] = 225;
	starTween[8][0] = 200;
	starTween[8][1] = 150;
	starTween[9][0] = 225;
	starTween[9][1] = 250;

	uberTween[0][0] = 200;
	uberTween[0][1] = 350;
	uberTween[1][0] = 250;
	uberTween[1][1] = 350;
	uberTween[2][0] = 250;
	uberTween[2][1] = 250;
	uberTween[3][0] = 325;
	uberTween[3][1] = 250;
	uberTween[4][0] = 325;
	uberTween[4][1] = 350;
	uberTween[5][0] = 375;
	uberTween[5][1] = 350;
	uberTween[6][0] = 375;
	uberTween[6][1] = 250;
	uberTween[7][0] = 375;
	uberTween[7][1] = 150;
	uberTween[8][0] = 200;
	uberTween[8][1] = 150;
	uberTween[9][0] = 200;
	uberTween[9][1] = 250;
}
void tween(int source[10][2], int destination[10][2], int numPoints, double proportion, int tweenPoly[10][2])
{

	for (int p = 0; p < numPoints; p++)
	{
		// get the source point
		double sourceX = source[p][0];
		double sourceY = source[p][1];

		// get the destination point
		double destinationX = destination[p][0];
		double destinationY = destination[p][1];

		// get the difference between source and destination
		double differenceX = (destinationX - sourceX);
		double differenceY = (destinationY - sourceY);

		// tween point is source position + proportion
	 // of distance between source and destination
		double tweenX = sourceX + (differenceX * proportion);
		double tweenY = sourceY + (differenceY * proportion);

		// create point with tween co-ordinates in tween array
		tweenPoly[p][0] = int(tweenX);
		tweenPoly[p][1] = int(tweenY);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////// 
class  Point {
public:
	float x;
	float y;
};
class SpriteTexture {
public:
	int textureIndex; // the index of the texture in memory
	char name[50]; // the filename of the texture (.png file)
};
class Sprite {
public:
	float x = 0; // position variable onlu used in drawing background sprites
	float y = 0;// position variable onlu used in drawing background sprites
	float width = 0, startWidth = 0;// width and startwidth used for scaling
	float height = 0, startHeight = 0;// height and startheight used for scaling
	int textureIndex;// index of texture in memory
	bool mirrored = true;// notes whether sprite shown will be mirrored around y axis
	float r = 1, g = 1, b = 1, a = 1;// red green blue and alpha (transparent) colour components 
	float tx = 0, ty = 0, sx = 1, sy = 1, rz = 0;// translation, scaling and rotation variables
	bool alive = false;// alive variable used in games
	//sprite animation variables
	int numAnimFrames = 0;// the number of frames in the animation
	int animCounter = 0;// a counter to loop through animation frames
	int animInterval = 10;// the inetrval between changing frames
	float animSheetDx, animSheetDy;// width and height factors used to extract images from spritesheets internally
	vector<Point>imageOffsetList;// a growable array of imageoffset to use a spritesheet
	// collision detection variables
	float colx = 0, coly = 0;// center of collision shape
	float colStartWidth = 0;// collision shape start width
	float colStartHeight = 0;// collision shape start height
	float colWidth, colHeight;// collision shape width and height
	float colRadius, colStartRadius; // collision shape startradius and radius for circular collision detection
	// self steering variables
	float startVectorX = 1, startVectorY = 0; // start direction vector
	float forwardVectorX = 1, forwardVectorY = 0; // forward vector
	float backVectorX = -1, backVectorY = 0; // back vector
	float leftVectorX = 0, leftVectorY = 1; // left vector
	float rightVectorX = 0, rightVectorY = -1; // right vector
	float speed = 0; // sprite speed
	float turnAngle = 0; // amount sprite can turn by per frame
	// explosion variables
	float explRotateInc = 0; // amount explosion sprite will rotate per frame
	float explScaleInc = 1; // amount explosion sprite will scale per frame
	float explTransparencyInc = 0; // amount explosion sprite will decrement transparency per frame
};
#include "SpriteFunctions-V2.h"
SpriteTexture backgroundTexture, characterTexture, characterTexture1;
Sprite background1, characterSprite, characterSprite1;
/////////////////////////////////////////////////////////////////////////////////////////////////
float star[10][2] = {
	{ 9.510565163,3.090169944 },
	{ 2.938926261,4.045084972 },
	{ 0,10 },
	{ -2.938926261,4.045084972 },
	{ -9.510565163,3.090169944 },
	{ -4.755282581,-1.545084972 },
	{ -5.877852523,-8.090169944 },
	{ 0,-5 },
	{ 5.877852523,-8.090169944 },
	{ 4.755282581,-1.545084972 }
};
void drawStar(float xc, float yc)
{
	glBegin(GL_POLYGON);
	for (int i = 1; i < 4; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 3; i < 6; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 5; i < 8; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 7; i < 10; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(xc + star[9][0], yc + star[9][1]);
	glVertex2d(xc + star[0][0], yc + star[0][1]);
	glVertex2d(xc + star[1][0], yc + star[1][1]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(xc + star[9][0], yc + star[9][1]);
	glVertex2d(xc + star[1][0], yc + star[1][1]);
	glVertex2d(xc + star[3][0], yc + star[3][1]);
	glVertex2d(xc + star[5][0], yc + star[5][1]);
	glVertex2d(xc + star[7][0], yc + star[7][1]);
	glEnd();
	glColor3f(1, 1, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 10; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	}
	glEnd();
}
struct drop {
	float x = 400;
	float y = 400;
	float inc = 0.01;
	float radius = 5;
	float scale = 1.0;
	float rotationAngle = 0;
	float rotationInc = 1;
	float r, g, b, a;
};
drop rain[RAINSIZE];;
void initRain()
{
	for (int i = 0; i < RAINSIZE; i++) {
		rain[i].x = rand() % winWidth1;
		rain[i].y = rand() % winHeight1;
		rain[i].inc = 3 + (float)(rand() % 20000) / 1000.0;
		rain[i].r = (float)(rand() % 1000) / 1000.0;
		rain[i].g = (float)(rand() % 1000) / 1000.0;
		rain[i].b = (float)(rand() % 1000) / 1000.0;
		rain[i].a = 0.5;
		rain[i].scale = (float)(rand() % 20000) / 1000.0;
		rain[i].rotationAngle = (float)(rand() % 3000) / 1000.0;
		rain[i].rotationInc = (float)(rand() % 10000) / 1000.0;
		if ((rand() % 100) > 50) {
			rain[i].rotationInc = -rain[i].rotationInc;
		}
	}
}
float rotationAngle = 0;
void drawParticleShape(int i)
{
	glPushMatrix();
	glTranslatef(rain[i].x, rain[i].y, 0.0);
	glScalef(rain[i].scale, rain[i].scale, 1);
	glTranslatef(-rain[i].x, -rain[i].y, 0.0);
	glTranslatef(rain[i].x, rain[i].y, 0.0);
	glRotatef(rain[i].rotationAngle, 0, 0, 1);
	glTranslatef(-rain[i].x, -rain[i].y, 0.0);
	glColor3f(1, 1, 0);
	drawStar(rain[i].x, rain[i].y);
	glPopMatrix();
	rain[i].rotationAngle += rain[i].rotationInc;
}
void drawDrop(int i)
{
	glLineWidth(2);
	drawParticleShape(i);
	rain[i].y -= rain[i].inc;
	if (rain[i].y < 0) {
		rain[i].y = winHeight;
	}
}
void drawRain()
{
	for (int i = 0; i < RAINSIZE; i++)
	{
		drawDrop(i);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void uberlogo()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(400, 200);
	glVertex2i(400, 600);
	glVertex2i(500, 600);
	glVertex2i(500, 400);
	glVertex2i(600, 400);
	glVertex2i(600, 600);
	glVertex2i(700, 600);
	glVertex2i(700, 200);
	glEnd();

}
void phone()
{
	glBegin(GL_POLYGON); 
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(400, 100);
	glVertex2i(400, 700);
	glVertex2i(800, 700);
	glVertex2i(800, 100);
	glEnd();

	glBegin(GL_POLYGON); 
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(420, 120);
	glVertex2i(420, 680);
	glVertex2i(780, 680);
	glVertex2i(780, 120);
	glEnd();

	glBegin(GL_POLYGON); 
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(550, 100);
	glVertex2i(550, 200);
	glVertex2i(650, 200);
	glVertex2i(650, 100);
	glEnd();

	sprintf_s(textBuffer, "UBER APP");
	renderSpacedBitmapString(540, 650, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);

	sprintf_s(textBuffer, "ORDER A UBER");
	renderSpacedBitmapString(510, 500, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);

	sprintf_s(textBuffer, "PRICE £15");
	renderSpacedBitmapString(510, 480, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);

	sprintf_s(textBuffer, "CLICK TO CONFIRM");
	renderSpacedBitmapString(490, 280, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
}
void sun(int x, int y)
{
	float th;
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.8, 0.0);
	for (int i = 0; i < 360; i++)
	{
		th = i * 3.142 / 180;
		glVertex2f(x + 120 * cos(th), y + 120 * sin(th));
	}
	glEnd();
}
void moon(int x, int y)
{
	float th;
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	for (int i = 0; i < 360; i++)
	{
		th = i * 3.142 / 180;
		glVertex2f(x + 120 * cos(th), y + 120 * sin(th));
	}
	glEnd();
}
void cloud(int x, int y)
{
	float th;
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	for (int i = 0; i < 360; i++)
	{
		th = i * 3.142 / 180;
		glVertex2f(x + 40 * cos(th), y + 30 * sin(th));
	}
	glEnd();
}
void clouds()
{
	cloud(-400, 720);
	cloud(-420, 700);
	cloud(-380, 700);

	cloud(-200, 720);
	cloud(-220, 700);
	cloud(-180, 700);

	cloud(0, 770);
	cloud(-20, 750);
	cloud(20, 750);

	cloud(200, 770);
	cloud(180, 750);
	cloud(220, 750);

	cloud(400, 720);
	cloud(380, 700);
	cloud(420, 700);

	cloud(600, 770);
	cloud(580, 750);
	cloud(620, 750);

	cloud(800, 770);
	cloud(780, 750);
	cloud(820, 750);

	cloud(1000, 720);
	cloud(980, 700);
	cloud(1020, 700);
}
void rain1(double radius, double xc, double yc)
{
	int i;
	double angle = 2 * 3.1415 / 20;
	double x = 0, y = 0;

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);

	for (i = 0; i < 20; i++)
	{
		x = radius * cos(i * angle) + xc;
		y = radius * sin(i * angle) + yc;
		glVertex2f(x, y);
	}
	glEnd();
}
void circle(double radius, double xc, double yc)
{
	int i;
	double angle = 2 * 3.1415 / 20;
	double x = 0, y = 0;

	glBegin(GL_LINE_LOOP);

	for (i = 0; i < 20; i++)
	{
		x = radius * cos(i * angle) + xc;
		y = radius * sin(i * angle) + yc;
		glVertex2f(x, y);
	}
	glEnd();
}
void square()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(105, 130);
	glVertex2i(130, 130);
	glVertex2i(130, 105);
	glVertex2i(105, 105);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(395, 130);
	glVertex2i(420, 130);
	glVertex2i(420, 105);
	glVertex2i(395, 105);
	glEnd();
}
void squareuber()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(50, 100);
	glVertex2i(100, 100);
	glVertex2i(100, 50);
	glVertex2i(50, 50);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(60, 60);
	glVertex2i(60, 90);
	glVertex2i(70, 90);
	glVertex2i(70, 70);
	glVertex2i(80, 70);
	glVertex2i(80, 90);
	glVertex2i(90, 90);
	glVertex2i(90, 60);
	glEnd();
}
void wheel(int x, int y)
{
	float th;
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < 360; i++)
	{
		th = i * 3.142 / 180;
		glVertex2f(x + 40 * cos(th), y + 40 * sin(th));
	}
	glEnd();
}
void wheel2(int x, int y)
{
	float th;
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 360; i++)
	{
		th = i * 3.142 / 180;
		glVertex2f(x + 30 * cos(th), y + 30 * sin(th));
	}
	glEnd();
}
void car()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(25, 125);
	glVertex2f(25, 200);
	glVertex2f(50, 225);
	glVertex2f(475, 225);
	glVertex2f(500, 200);
	glVertex2f(500, 125);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(100, 225);
	glVertex2f(100, 250);
	glVertex2f(150, 300);
	glVertex2f(275, 300);
	glVertex2f(325, 250);
	glVertex2f(325, 225);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(125, 250);
	glVertex2f(150, 275);
	glVertex2f(200, 275);
	glVertex2f(200, 250);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(225, 250);
	glVertex2f(225, 275);
	glVertex2f(275, 275);
	glVertex2f(300, 250);
	glEnd();

	wheel(125, 125);
	wheel(400, 125);

	wheel2(125, 125);
	wheel2(400, 125);
}
///////////////////////////////////////////////////////////////////////////////////////////////// 
void buildings()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(10, 330);
	glVertex2i(10, 750);
	glVertex2i(55, 800);
	glVertex2i(100, 750);
	glVertex2i(100, 330);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex2i(160, 330);
	glVertex2i(160, 620);
	glVertex2i(250, 650);
	glVertex2i(340, 620);
	glVertex2i(340, 330);
	glEnd();

	glBegin(GL_POLYGON); 
	glColor3f(0.3, 0.3, 0.3);
	glVertex2i(560, 330);
	glVertex2i(560, 500);
	glVertex2i(650, 550);
	glVertex2i(740, 500);
	glVertex2i(740, 330);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2i(750, 330);
	glVertex2i(750, 500);
	glVertex2i(840, 550);
	glVertex2i(930, 500);
	glVertex2i(930, 330);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1000, 330);
	glVertex2i(1000, 650);
	glVertex2i(1050, 700);
	glVertex2i(1100, 650);
	glVertex2i(1100, 330);
	glEnd();
}
void buildings2()
{
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2i(560, 330);
	glVertex2i(560, 500);
	glVertex2i(650, 550);
	glVertex2i(740, 500);
	glVertex2i(740, 330);
	glEnd();
}
void background11()
{
	glBegin(GL_POLYGON); //background colour
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(0, 0);
	glVertex2i(0, 1200);
	glVertex2i(1200, 1200);
	glVertex2i(1200, 0);
	glEnd();

	glBegin(GL_POLYGON); //road
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(0, 70);
	glVertex2i(0, 320);
	glVertex2i(1200, 320);
	glVertex2i(1200, 70);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(0, 240);
	glVertex2i(0, 260);
	glVertex2i(100, 260);
	glVertex2i(100, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(200, 240);
	glVertex2i(200, 260);
	glVertex2i(300, 260);
	glVertex2i(300, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(400, 240);
	glVertex2i(400, 260);
	glVertex2i(500, 260);
	glVertex2i(500, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(600, 240);
	glVertex2i(600, 260);
	glVertex2i(700, 260);
	glVertex2i(700, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(800, 240);
	glVertex2i(800, 260);
	glVertex2i(900, 260);
	glVertex2i(900, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1000, 240);
	glVertex2i(1000, 260);
	glVertex2i(1100, 260);
	glVertex2i(1100, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(0, 120);
	glVertex2i(0, 140);
	glVertex2i(100, 140);
	glVertex2i(100, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(200, 120);
	glVertex2i(200, 140);
	glVertex2i(300, 140);
	glVertex2i(300, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(400, 120);
	glVertex2i(400, 140);
	glVertex2i(500, 140);
	glVertex2i(500, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(600, 120);
	glVertex2i(600, 140);
	glVertex2i(700, 140);
	glVertex2i(700, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(800, 120);
	glVertex2i(800, 140);
	glVertex2i(900, 140);
	glVertex2i(900, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1000, 120);
	glVertex2i(1000, 140);
	glVertex2i(1100, 140);
	glVertex2i(1100, 120);
	glEnd();
}
void background2() //MAIN CITY BACKGROUND
{
	glBegin(GL_POLYGON); //background colour
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(0, 0);
	glVertex2i(0, 1200);
	glVertex2i(1200, 1200);
	glVertex2i(1200, 0);
	glEnd();

	glBegin(GL_POLYGON); //road
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(0, 70);
	glVertex2i(0, 320);
	glVertex2i(1200, 320);
	glVertex2i(1200, 70);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(0, 240);
	glVertex2i(0, 260);
	glVertex2i(100, 260);
	glVertex2i(100, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(200, 240);
	glVertex2i(200, 260);
	glVertex2i(300, 260);
	glVertex2i(300, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(400, 240);
	glVertex2i(400, 260);
	glVertex2i(500, 260);
	glVertex2i(500, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(600, 240);
	glVertex2i(600, 260);
	glVertex2i(700, 260);
	glVertex2i(700, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(800, 240);
	glVertex2i(800, 260);
	glVertex2i(900, 260);
	glVertex2i(900, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1000, 240);
	glVertex2i(1000, 260);
	glVertex2i(1100, 260);
	glVertex2i(1100, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(0, 120);
	glVertex2i(0, 140);
	glVertex2i(100, 140);
	glVertex2i(100, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(200, 120);
	glVertex2i(200, 140);
	glVertex2i(300, 140);
	glVertex2i(300, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(400, 120);
	glVertex2i(400, 140);
	glVertex2i(500, 140);
	glVertex2i(500, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(600, 120);
	glVertex2i(600, 140);
	glVertex2i(700, 140);
	glVertex2i(700, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(800, 120);
	glVertex2i(800, 140);
	glVertex2i(900, 140);
	glVertex2i(900, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1000, 120);
	glVertex2i(1000, 140);
	glVertex2i(1100, 140);
	glVertex2i(1100, 120);
	glEnd();

	buildings();
	sun(1200, 800);

}
void background3() //HOUSE BACKGROUND
{
	glBegin(GL_POLYGON); //background colour
	glColor3f(0.0, 0.0, 0.3);
	glVertex2i(0, 0);
	glVertex2i(0, 1200);
	glVertex2i(1200, 1200);
	glVertex2i(1200, 0);
	glEnd();

	glBegin(GL_POLYGON); //road
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(0, 70);
	glVertex2i(0, 320);
	glVertex2i(1200, 320);
	glVertex2i(1200, 70);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(0, 240);
	glVertex2i(0, 260);
	glVertex2i(100, 260);
	glVertex2i(100, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(200, 240);
	glVertex2i(200, 260);
	glVertex2i(300, 260);
	glVertex2i(300, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(400, 240);
	glVertex2i(400, 260);
	glVertex2i(500, 260);
	glVertex2i(500, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(600, 240);
	glVertex2i(600, 260);
	glVertex2i(700, 260);
	glVertex2i(700, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(800, 240);
	glVertex2i(800, 260);
	glVertex2i(900, 260);
	glVertex2i(900, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1000, 240);
	glVertex2i(1000, 260);
	glVertex2i(1100, 260);
	glVertex2i(1100, 240);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(0, 120);
	glVertex2i(0, 140);
	glVertex2i(100, 140);
	glVertex2i(100, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(200, 120);
	glVertex2i(200, 140);
	glVertex2i(300, 140);
	glVertex2i(300, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(400, 120);
	glVertex2i(400, 140);
	glVertex2i(500, 140);
	glVertex2i(500, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(600, 120);
	glVertex2i(600, 140);
	glVertex2i(700, 140);
	glVertex2i(700, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(800, 120);
	glVertex2i(800, 140);
	glVertex2i(900, 140);
	glVertex2i(900, 120);
	glEnd();

	glBegin(GL_POLYGON); //road lines top
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1000, 120);
	glVertex2i(1000, 140);
	glVertex2i(1100, 140);
	glVertex2i(1100, 120);
	glEnd();

	buildings2();
	moon(1200, 800);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void scene1()
{
	drawBackgroundSprite(background1);
	glPushMatrix();
	glTranslatef(500, 400, 0);
	glTranslatef(75, 75, 0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glScalef(5, 5, 0);
	glTranslatef(-75, -75, 0);
	squareuber();
	glPopMatrix();
	theta += 5;
	sprintf_s(textBuffer, "3D UBER LOGO");
	renderSpacedBitmapString(50, 50, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
}
void scene2()
{
	sprintf_s(textBuffer, "3");
	renderSpacedBitmapString(600, 400, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
}
void scene3()
{
	sprintf_s(textBuffer, "2");
	renderSpacedBitmapString(600, 400, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
}
void scene4()
{
	sprintf_s(textBuffer, "1");
	renderSpacedBitmapString(600, 400, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
}
void scene5() 
{
	background2();
	sprintf_s(textBuffer, "NEED A RIDE?");
	renderSpacedBitmapString(400, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clouds();
	glPopMatrix();
	drawCharacterSprite(characterSprite);
	tx += 0.5; ty += 0;
}
void scene6()
{
	background2();
	sprintf_s(textBuffer, "CALL AN UBER");
	renderSpacedBitmapString(400, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clouds();
	glPopMatrix();
	drawCharacterSprite1(characterSprite1);
	tx += 0.5; ty += 0;
}
void scene7()
{
	drawBackgroundSprite(background1);
	sprintf_s(textBuffer, "SIMPLY SET UP YOUR PICK UP LOCATION AND DESTINATION");
	renderSpacedBitmapString(50, 50, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	tx = 0; ty = 0;
	phone();
}
void scene8()
{
	background11();
	sprintf_s(textBuffer, "ONE OF OUR THOUSANDS OF DRIVERS WILL BE AT YOUR LOCATION IN LESS THAN 10 MINUTES");
	renderSpacedBitmapString(50, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clouds();
	glPopMatrix();
	tx += 0.5; ty = 0;
	glPushMatrix();
	glTranslatef(tx1, ty1, 0);
	car();
	glPopMatrix();
	tx1 += 8; ty1 = 0;
}
void scene9()
{
	background2();
	sprintf_s(textBuffer, "WHO WILL SAFELY PICK YOU UP FROM YOUR LOCATION");
	renderSpacedBitmapString(350, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clouds();
	glPopMatrix();
	drawCharacterSprite(characterSprite);
	tx += 0.5; ty = 0;
	car();
}
void scene10()
{
	background2();
	sprintf_s(textBuffer, "GET IN");
	renderSpacedBitmapString(350, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clouds();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(tx2, ty2, 0);
	drawCharacterSprite(characterSprite);
	glPopMatrix();
	tx2 += -1.5; ty2 += -1.5;
	tx += 0.5; ty = 0;
	car();
	tx1 = 0.0, ty1 = 0.0;

}
void scene11()
{
	background2();
	sprintf_s(textBuffer, "WELCOME SIR, LETS GO");
	renderSpacedBitmapString(350, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clouds();
	glPopMatrix();
	tx += 0.5; ty = 0;
	glPushMatrix();
	glTranslatef(tx1, ty1, 0);
	car();
	glPopMatrix();
	tx1 += 5; ty1 = 0;
}
void scene12()
{
	background11();
	sprintf_s(textBuffer, "OUR UBER DRIVER WILL TAKE YOU TO YOUR DESTINATION");
	renderSpacedBitmapString(50, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	clouds();
	glPopMatrix();
	tx += 0.5; ty = 0;
	glPushMatrix();
	glTranslatef(tx1, ty1, 0);
	car();
	glPopMatrix();
	tx1 += 5; ty1 = 0;
}
void scene13() {

	background3();
	sprintf_s(textBuffer, "WE HAVE ARRIVED");
	renderSpacedBitmapString(50, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	car();
	clouds();
	glPushMatrix();
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	glPopMatrix();
}
void scene14()
{
	background3();
	clouds();
	sprintf_s(textBuffer, "THANK YOU");
	renderSpacedBitmapString(350, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(tx2, ty2, 0);
	drawCharacterSprite(characterSprite);
	glPopMatrix();
	tx2 += 1.2; ty2 += 1.2;
	tx += 0.5; ty = 0;
	car();
	tx1 = 0.0, ty1 = 0.0;
	glPushMatrix();
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	glPopMatrix();
	
}
void scene15()
{
	background3();
	drawCharacterSprite1(characterSprite1);
	clouds();
	sprintf_s(textBuffer, "CHECK YOUR APP AND LEAVE A RATING");
	renderSpacedBitmapString(350, 600, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	glPopMatrix();
	tx += 0.5; ty = 0;
	glPushMatrix();
	glTranslatef(tx1, ty1, 0);
	car();
	glPopMatrix();
	tx1 += 8; ty1 = 0;
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	rain1(rand() % 20, rand() % (int)winWidth, rand() % (int)winHeight);
	glPopMatrix();
}
void scene16()
{
	drawBackgroundSprite(background1);
	sprintf_s(textBuffer, "RATE OR TIP YOUR DRIVER ;)");
	renderSpacedBitmapString(600, 400, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	drawRain();
	glFlush();
}
void scene17()
{
	drawBackgroundSprite(background1);
	sprintf_s(textBuffer, "THANK YOU FOR WATCHING");
	renderSpacedBitmapString(450, 500, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	sprintf_s(textBuffer, "UBER ADVERT");
	renderSpacedBitmapString(450, 470, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	sprintf_s(textBuffer, "CREATED BY");
	renderSpacedBitmapString(450, 440, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	sprintf_s(textBuffer, "ERDEM AKSU M00622599");
	renderSpacedBitmapString(450, 410, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i;

	if(counter < 150) {
		scene1();
	}
	else if (counter < 180) {
		scene2();
	}
	else if (counter < 210) {
		scene3();
	}
	else if (counter < 240) {
		scene4();
	}
	else if (counter < 350) {
		scene5();
	}
	else if (counter < 450) {
		scene6();
	}
	else if (counter < 550) {
		scene7();
	}
	else if (counter < 650) {
		scene8();
	}
	else if (counter < 750) {
		scene9();
	}
	else if (counter < 850) {
		scene10();
	}
	else if (counter < 950) {
		scene11();
	}
	else if (counter < 1050) {
		scene12();
	}
	else if (counter < 1150) {
		scene13();
	}
	else if (counter < 1250) {
		scene14();
	}
	else if (counter < 1350) {
		scene15();
	}
	else if (counter < 1450) {
		scene16();
	}
	else if ((counter >= 1550) && (counter < 1650))
	{
		drawBackgroundSprite(background1);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);

		for (i = 0; i < 10; i++)
			glVertex2i(starTween[i][0], starTween[i][1]);
		glEnd();
		sprintf_s(textBuffer, "BECAUSE OF ALL THE HIGH USERS RATINGS");
		renderSpacedBitmapString(450, 410, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	}
	else if (counter < 1750)
	{
		drawBackgroundSprite(background1);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 10; i++)
			glVertex2i(uberTween[i][0], uberTween[i][1]);
		glEnd();
		sprintf_s(textBuffer, "...");
		renderSpacedBitmapString(450, 410, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
	}
	else if (counter < 1850)
	{
		drawBackgroundSprite(background1);
		glColor3f(1.0, 0.0, 0.0);
		tween(starTween, uberTween, 10, proportion, tweenPoly);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 10; i++)
			glVertex2i(tweenPoly[i][0], tweenPoly[i][1]);
		glEnd();
		proportion += 0.01;

		if (proportion > 1.0) proportion = 1.0;
	}
	else if (counter < 1950)
	{
		drawBackgroundSprite(background1);
		glColor3f(1.0, 0.0, 0.0);
		tween(starTween, uberTween, 10, proportion, tweenPoly);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 10; i++)
			glVertex2i(tweenPoly[i][0], tweenPoly[i][1]);
		glEnd();

		sprintf_s(textBuffer, "UBER THE BEST CAR HIRING COMPANY IN LONDON");
		renderSpacedBitmapString(450, 410, GLUT_BITMAP_TIMES_ROMAN_24, textBuffer);
		proportion += 0.007;

		if (proportion >= 1.0) proportion = 1.0;
	}
	else if (counter < 2050)
	{
	scene17();
	}
	else if (counter < 2100) {
		counter = 0;
		tx = 0; ty = 0;
		tx1 = 0.0, ty1 = 0.0;
		tx2 = 0.0, ty2 = 0.0;
		sx = 0.0, sy = 0.0;
		theta = 0;
		frame = 0;
		proportion = 0.0;
	}
	counter++;
	glFlush();
	glutSwapBuffers();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(30, Timer, value);
}
int main(int argc, char** argv)
{
	srand(1);
	initRain();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ERDEM AKSU UBER ADVERT");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(30, Timer, 0);
	char  name[50] = "backgroundbitmap.png";
	initSpriteTexture(name, &backgroundTexture.textureIndex);

	strcpy_s(name, "ch1.png");
	initSpriteTexture(name, &characterTexture.textureIndex);

	strcpy_s(name, "ch2.png");
	initSpriteTexture(name, &characterTexture1.textureIndex);

	initSprite(&characterSprite, characterTexture.textureIndex, 0, 0, (float)winWidth, (float)winHeight);
	initSprite(&characterSprite1, characterTexture1.textureIndex, 0, 0, (float)winWidth, (float)winHeight);
	initSprite(&background1, backgroundTexture.textureIndex, 0, 0, (float)winWidth, (float)winHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
