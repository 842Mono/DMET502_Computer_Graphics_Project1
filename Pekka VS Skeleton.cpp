//there are audio files needed
//download from here https://drive.google.com/open?id=0B0f0nmVh2CHdRXAzMEhPdTVlZWM
//there's a zipped file and a non-zipped folder. your choice.



//change the GL headers accordingly
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "stdlib.h"

//audio was done using SDL
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

void bezierCoefficients(int n,int *c)
{
	int k,i;
	for(k=0;k<=n;k++)
	{
		c[k]=1;
		for(i=n;i>=k+1;i--)
		    c[k]*=i;
		for(i=n-k;i>=2;i--)
			c[k]/=i;
	}
}

int resPekka[2];
int* bezierPekka(float t, int* p0,int* p1,int* p2,int* p3)
{
	resPekka[0]=pow((1-t),3)*p0[0]+3*t*pow((1-t),2)*p1[0]+3*pow(t,2)*(1-t)*p2[0]+pow(t,3)*p3[0];
	resPekka[1]=pow((1-t),3)*p0[1]+3*t*pow((1-t),2)*p1[1]+3*pow(t,2)*(1-t)*p2[1]+pow(t,3)*p3[1];
	return resPekka;
}
int p0Pekka[2];
int p1Pekka[2];
int p2Pekka[2];
int p3Pekka[2];
int tarPekka=4;
float tPekka = 0;


int res[2];
int* bezier(float t, int* p0,int* p1,int* p2,int* p3)
{
	res[0]=pow((1-t),3)*p0[0]+3*t*pow((1-t),2)*p1[0]+3*pow(t,2)*(1-t)*p2[0]+pow(t,3)*p3[0];
	res[1]=pow((1-t),3)*p0[1]+3*t*pow((1-t),2)*p1[1]+3*pow(t,2)*(1-t)*p2[1]+pow(t,3)*p3[1];
	return res;
}
int p0[2];
int p1[2];
int p2[2];
int p3[2];
int tar=4;
float t = 0;


void print(int x, int y, char *string, int len)
{
	int i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//loop to display character by character
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
}

int xMousePosition = 0;
int yMousePosition = 0;

int cppowerup[4][2]={{510,130},{485,135},{470,140},{480,150}};
int cpowerup[4],npowerup = 3;
float upowerup = 0, xpowerup = 0, ypowerup = 0, blendpowerup;
int delaypowerup = 0;

int damage = 250;

bool start = false;

float downward = 850;
float downward2 = 1150;
float downward3 = 1450;

int hzl1;
int hzl2;
int hzl3;

bool powerup1 = false;
bool powerup2 = false;
bool powerup3 = false;

int powerupControl;

int skelLeftLeg = -50;
int skelRightLeg = -50;

int breathe = -1;

int deathXpos = -1;

Mix_Chunk* arenaStart;
Mix_Chunk* pSpawn;
Mix_Chunk* pStep;
Mix_Chunk* pattk;
Mix_Chunk* pWin;
Mix_Music* music1;
Mix_Chunk* heal;
Mix_Chunk* logSound;


int pekkaSTrX = 615, pekkaSTrY = 95, pekkaSRot = 0;
int rArmX0 = 0, rArmX1 = 0, rArmX2 = 10, rArmX3 = 10,
rArmY0 = 0, rArmY1 = 40, rArmY2 = 40, rArmY3 = 0;

bool won = false;
int counterWon = 500;
bool a1Done = false;
bool a2Done = false;
bool a3Done = false;

int pekkaSteps = 500;

double backgroundR = 0.7;
double backgroundG = 0.5;
double backgroundB = 0.2;

int sndDel = 1999;

int alterCount = 9999;
bool alter = false;

bool alter1 = false;
bool alter2 = false;
bool alter3 = false;



void log(int hzlIn, float downwardIn, bool powerupIn, bool alter)
{

    if(!alter)
    {
        glPushMatrix();
        //left
        glTranslated(0,downwardIn,0);
        glBegin(GL_POLYGON);
            glColor3f(1.000,0.647,0.0);
            glVertex3d(0, 0, 0);
            glVertex3d(0, 50, 0);
            glVertex3d(hzlIn - 150, 50, 0);
            glVertex3d(hzlIn - 150, 00, 0);
        glEnd();
        glBegin(GL_POLYGON);
            glColor3f(1.000,0.549,0.0);
            glVertex3d(10, 10, 0);
            glVertex3d(10, 40, 0);
            glVertex3d(hzlIn - 150 - 10, 40, 0);
            glVertex3d(hzlIn - 150 - 10, 10, 0);
        glEnd();

        //right
        glBegin(GL_POLYGON);
            glColor3f(1.000,0.647,0.0);
            glVertex3d(hzlIn + 150, 0, 0);
            glVertex3d(hzlIn + 150, 50, 0);
            glVertex3d(1080, 50, 0);
            glVertex3d(1080, 0, 0);
        glEnd();
        glBegin(GL_POLYGON);
            glColor3f(1.000,0.549,0.0);
            glVertex3d(hzlIn + 150 + 10, 10, 0);
            glVertex3d(hzlIn + 150 + 10, 40, 0);
            glVertex3d(1070, 40, 0);
            glVertex3d(1070, 10, 0);
        glEnd();
    }
    else
    {
        glPushMatrix();
        glTranslated(0,downwardIn,0);

        //left
        glBegin(GL_POLYGON);
        glColor3f(0.000,0.0,0.0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 50, 0);
        glVertex3d(hzlIn - 150, 50, 0);
        glVertex3d(hzlIn - 150, 00, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(10, 10, 0);
        glVertex3d(10, 40, 0);
        glVertex3d(hzlIn - 150 - 10, 40, 0);
        glVertex3d(hzlIn - 150 - 10, 10, 0);
    glEnd();

    //right
    glBegin(GL_POLYGON);
        glVertex3d(hzlIn + 150, 0, 0);
        glVertex3d(hzlIn + 150, 50, 0);
        glVertex3d(1080, 50, 0);
        glVertex3d(1080, 0, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(hzlIn + 150 + 10, 10, 0);
        glVertex3d(hzlIn + 150 + 10, 40, 0);
        glVertex3d(1070, 40, 0);
        glVertex3d(1070, 10, 0);
    glEnd();


        //left
        glBegin(GL_LINES);
            glColor3f(0.000,0.047,1.0);
            glVertex3d(0, 0, 0);
            glVertex3d(0, 50, 0);


            glVertex3d(0, 50, 0);
            glVertex3d(hzlIn - 150, 50, 0);

            glVertex3d(0, 0, 0);
            glVertex3d(hzlIn - 150, 00, 0);


            glVertex3d(0, 0, 0);
            glVertex3d(hzlIn - 150, 50, 0);

            glVertex3d(hzlIn - 150, 00, 0);
            glVertex3d(0, 50, 0);

            glVertex3d(hzlIn - 150, 50, 0);
            glVertex3d(hzlIn - 150, 00, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(10, 10, 0);
            glVertex3d(10, 40, 0);


            glVertex3d(10, 10, 0);
            glVertex3d(hzlIn - 150 - 10, 40, 0);

            glVertex3d(hzlIn - 150 - 10, 10, 0);
            glVertex3d(10, 40, 0);


            glVertex3d(10, 10, 0);
            glVertex3d(hzlIn - 150 - 10, 40, 0);

            glVertex3d(10, 40, 0);
            glVertex3d(hzlIn - 150 - 10, 10, 0);


            glVertex3d(hzlIn - 150 - 10, 40, 0);
            glVertex3d(hzlIn - 150 - 10, 10, 0);
        glEnd();

        //right
        glBegin(GL_LINES);
            glVertex3d(hzlIn + 150, 0, 0);
            glVertex3d(hzlIn + 150, 50, 0);


            glVertex3d(hzlIn + 150, 0, 0);
            glVertex3d(1080, 0, 0);

            glVertex3d(1080, 50, 0);
            glVertex3d(hzlIn + 150, 50, 0);


            glVertex3d(hzlIn + 150, 0, 0);
            glVertex3d(1080, 50, 0);

            glVertex3d(1080, 0, 0);
            glVertex3d(hzlIn + 150, 50, 0);

            glVertex3d(1080, 50, 0);
            glVertex3d(1080, 0, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(hzlIn + 150 + 10, 10, 0);
            glVertex3d(hzlIn + 150 + 10, 40, 0);


            glVertex3d(hzlIn + 150 + 10, 10, 0);
            glVertex3d(1070, 10, 0);

            glVertex3d(1070, 40, 0);
            glVertex3d(hzlIn + 150 + 10, 40, 0);


            glVertex3d(hzlIn + 150 + 10, 10, 0);
            glVertex3d(1070, 40, 0);
            
            glVertex3d(hzlIn + 150 + 10, 40, 0);
            glVertex3d(1070, 10, 0);

            glVertex3d(1070, 40, 0);
            glVertex3d(1070, 10, 0);
        glEnd();




    }


    /*
    //triangles
    glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
        glVertex3d(30, 222, 0);
        glVertex3d(40, 232, 0);
        glVertex3d(50, 222, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.000,0.843,0.0);
        glVertex3d(70, 232, 0);
        glVertex3d(83, 222, 0);
        glVertex3d(90, 232, 0);
    glEnd();
    if(hzlIn > 137 + 150)
    {
        glBegin(GL_POLYGON);
            glColor3f(1.000,0.843,0.0);
            glVertex3d(115, 222, 0);
            glVertex3d(122, 232, 0);
            glVertex3d(137, 222, 0);
        glEnd();
    }
    if(hzlIn > 200 + 150)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
            glVertex3d(184, 222, 0);
            glVertex3d(197, 232, 0);
            glVertex3d(200, 222, 0);
        glEnd();
    }
    if(hzlIn > 275 + 150 || hzlIn < 275 - 150)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
            glVertex3d(267, 232, 0);
            glVertex3d(278, 222, 0);
            glVertex3d(281, 232, 0);
        glEnd();
    }
    if(hzlIn > 309 + 150 || hzlIn < 309 - 150)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
            glVertex3d(300, 232, 0);
            glVertex3d(307, 222, 0);
            glVertex3d(318, 232, 0);
        glEnd();
    }
    if(hzlIn > 375 + 150 || hzlIn < 375 - 150)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
            glVertex3d(360, 232, 0);
            glVertex3d(377, 222, 0);
            glVertex3d(389, 232, 0);
        glEnd();
    }
    if(hzlIn > 420 + 150 || hzlIn < 420 - 150)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
            glVertex3d(402, 232, 0);
            glVertex3d(420, 222, 0);
            glVertex3d(437, 232, 0);
        glEnd();
    }
    if(hzlIn > 478 + 150 || hzlIn < 478 - 150)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
            glVertex3d(467, 224, 0);
            glVertex3d(480, 230, 0);
            glVertex3d(485, 225, 0);
        glEnd();
    }
    if(hzlIn > 309 + 150 || hzlIn < 309 - 150)
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
            glVertex3d(520, 226, 0);
            glVertex3d(530, 221, 0);
            glVertex3d(545, 230, 0);
        glEnd();
    }*/


    if(powerupIn)
    {
        //powerup
        glPushMatrix();
        glTranslated(hzlIn-15,res[1], 0);
        // fprintf(stdout, M_PI);
        // float anglerad = M_PI * angle / 180.0f;
        // float x = sinf(anglerad) * radius; 
        // float y = cosf(anglerad) * radius;

        //rage
        glColor3f(0.600,0.196,0.800);
        glBegin(GL_POLYGON);
            glVertex3d(0, 10, 0);
            glVertex3d(0, 45, 0);
            glVertex3d(25, 45, 0);
            glVertex3d(25, 10, 0);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(7, 45, 0);
            glVertex3d(7, 55, 0);
            glVertex3d(18, 55, 0);
            glVertex3d(18, 45, 0);
        glEnd();

        //heal
        glColor3f(1.000, 0.843, 0.000);
        glBegin(GL_POLYGON);
            glVertex3d(15, 10, 0);
            glVertex3d(15, 45, 0);
            glVertex3d(40, 45, 0);
            glVertex3d(40, 10, 0);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(22, 45, 0);
            glVertex3d(22, 55, 0);
            glVertex3d(33, 55, 0);
            glVertex3d(33, 45, 0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}


void displayMe(void)
{



    // glBegin(GL_POLYGON);
    //     glVertex3d(33, 45, 0);
    // (downward < damage + 20 && downward > damage -20) && (xMousePosition > hzl1 - 40 && xMousePosition < hzl1 + 40)
    // glEnd();
    glClear(GL_COLOR_BUFFER_BIT);


    glBegin(GL_POLYGON);
    glColor3f(backgroundR, backgroundG, backgroundB);
        glVertex3d(-10, -10, 0);
        glVertex3d(-10, 730, 0);
        glVertex3d(1090, 730, 0);
        glVertex3d(1090, -10, 0);
    glEnd();


    //skeleton
    if(!won)
    {
        glPushMatrix();
        glTranslated(520,600,0);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINES);
            float xSkel, ySkel, zSkel, tSkel;
            for(tSkel = 0; tSkel < 360; tSkel +=1)
            {
                xSkel = 7*sin(tSkel);
                ySkel = 7*cos(tSkel);
                zSkel = 0;
                glVertex3f(xSkel,ySkel,zSkel);
            }
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(0, -7, 0);
            glVertex3d(0, -40, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(-13, -15, 0);
            glVertex3d(13, -15, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(-10, -25, 0);
            glVertex3d(10, -25, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(-8, -40, 0);
            glVertex3d(8, -40, 0);
        glEnd();
        //legs
        glBegin(GL_LINES);
            glVertex3d(-6, -40, 0);
            glVertex3d(-6, skelLeftLeg, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(6, -40, 0);
            glVertex3d(6, skelRightLeg, 0);
        glEnd();
        //sword
        glColor3f(0.7,0.7,0.7);
        glBegin(GL_LINES);
            glVertex3d(20, -15, 0);
            glVertex3d(20, 15, 0);
        glEnd();
        //hands
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINES);
            glVertex3d(-13, -15, 0);
            glVertex3d(-15, -25, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(13, -15, 0);
            glVertex3d(20, -5, 0);
        glEnd();

        glPopMatrix();
    }

    if(start)
    {
        //log
        log(hzl1, downward, powerup1, alter1);
        log(hzl2, downward2, powerup2, alter2);
        log(hzl3, downward3, powerup3, alter3);





    }
    else
    {
        glBegin(GL_POLYGON);
            glColor3f(0,0,0.8);
            glVertex3d(450, 335, 0);
            glVertex3d(450, 400, 0);
            glVertex3d(560, 400, 0);
            glVertex3d(560, 335, 0);
        glEnd();
        glPushMatrix();
        //glScalef(2.0,1.0,1.0);
        glColor3f(1.000, 1.0, 1.000);
        char start[6];
        start[0] = 'S';
        start[1] = 't';
        start[2] = 'a';
        start[3] = 'r';
        start[4] = 't';
        start[5] = '!';
        print(480,360,start,6);

        glColor3f(1.000, 1.0, 1.000);
        char subttl[] = "Get That Skeleton!!";
        print(420,160,subttl,19);


        glColor3f(1.000, 1.0, 1.000);
        char topttl[] = "miniPEKKA VS Skeleton";
        print(380,680,topttl,21);

        glPopMatrix();
    }
    

    if(damage > 100)
    {
        glPushMatrix();
        if(damage < 400)
        {
            if(start)
                glTranslated(resPekka[0],0,0);
            glTranslated(xMousePosition-540,0,0);
        }
        else
        {
            glTranslated(-50,0,0);
        }
        glTranslated(0,damage,0);

        //body
        glBegin(GL_POLYGON);
            glColor3f(0.3,0.3,0.3);
            glVertex3d(500, 50, 0);
            glVertex3d(500, 100, 0);
            glVertex3d(580, 100, 0);
            glVertex3d(580, 50, 0);
        glEnd();

        //head
        glBegin(GL_POLYGON);
            glColor3f(0.4,0.4,0.4);
            glVertex3d(510, 90, 0);
            glVertex3d(510, 140, 0);
            glVertex3d(570, 140, 0);
            glVertex3d(570, 90, 0);
        glEnd();

        //left arm
        glBegin(GL_POLYGON);
            glColor3f(0.4,0.4,0.4);
            glVertex3d(485, 80, 0);
            glVertex3d(485, 100, 0);
            glVertex3d(505, 100, 0);
            glVertex3d(505, 80, 0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.4,0.4,0.4);
            glVertex3d(488, 60, 0);
            glVertex3d(488, 100, 0);
            glVertex3d(498, 100, 0);
            glVertex3d(498, 60, 0);
        glEnd();

        //right arm
        glBegin(GL_POLYGON);
            glColor3f(0.4,0.4,0.4);
            glVertex3d(575, 80, 0);
            glVertex3d(575, 100, 0);
            glVertex3d(595, 100, 0);
            glVertex3d(595, 80, 0);
        glEnd();

        glTranslated(585, 95, 0);
        glRotated(-70, 0,0,1);
        glBegin(GL_POLYGON);
            glColor3f(0.4,0.4,0.4);
            glVertex3d(rArmX0, rArmY0, 0);
            glVertex3d(rArmX1, rArmY1, 0);
            glVertex3d(rArmX2, rArmY2, 0);
            glVertex3d(rArmX3, rArmY3, 0);
        glEnd();
        glRotated(70, 0, 0, 1);
        glTranslated(-585, -95, 0);

        //sword
        glPushMatrix();
        glTranslated(pekkaSTrX, pekkaSTrY, 0);
        glRotated(pekkaSRot, 0, 0, 1);
        glBegin(GL_POLYGON);
            glColor3f(0.2,0.2,0.2);
            glVertex3d(0, 0, 0);
            glVertex3d(0, 20, 0);
            glVertex3d(17, 20, 0);
            glVertex3d(17, 0, 0);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.35,0.35,0.35);
            glVertex3d(0, 20, 0);
            //
            glVertex3d(0, 25, 0);
            glVertex3d(5, 30, 0);
            glVertex3d(20, 50, 0);
            glVertex3d(20, 20, 0);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3d(5, 30, 0);
            glVertex3d(0, 35, 0);
            glVertex3d(0, 60, 0);
            // glVertex3d(635, 149, 0);
            glVertex3d(20, 53, 0);
            glVertex3d(5, 30, 0);
        glEnd();
        glPopMatrix();

        //iterators
        int k;
        float x, y, u, blend;

        //right horn bottom
        int cp[4][2]={{570,120},{595,125},{605,130},{600,150}};
        int c[4],n=3;
        bezierCoefficients(n,c);
        glColor3f(0.0,0.0,1.0);
        glLineWidth(5.0);
        glBegin(GL_POLYGON);
            for(u=0;u<1.0;u+=0.01)
            {
                x=0;y=0;
                for(k=0;k<4;k++)
                {
                    blend=c[k]*pow(u,k)*pow(1-u,n-k);
                    x+=cp[k][0]*blend;
                    y+=cp[k][1]*blend;
                }
                glVertex2f(x,y);
            }

        //right horn top
        int cp2[4][2]={{570,130},{595,135},{605,140},{600,150}};
        int c2[4],n2=3;
        bezierCoefficients(n2,c2);

            for(u=0;u<1.0;u+=0.01)
            {
                x=0;y=0;
                for(k=0;k<4;k++)
                {
                    blend=c2[k]*pow(u,k)*pow(1-u,n2-k);
                    x+=cp2[k][0]*blend;
                    y+=cp2[k][1]*blend;
                }
                glVertex2f(x,y);
            }
        glEnd();

        //left bottom horn ={{570,120},{595,125},{605,130},{600,150}};
        int cp3[4][2]={{510,120},{485,125},{475,130},{480,150}};
        int c3[4],n3=3;
        bezierCoefficients(n3,c3);
        glColor3f(0.0,0.0,1.0);
        glLineWidth(5.0);
        //glBegin(GL_LINE_STRIP);
        glBegin(GL_POLYGON);
            for(u=0;u<1.0;u+=0.01)
            {
                x=0;y=0;
                for(k=0;k<4;k++)
                {
                    blend=c3[k]*pow(u,k)*pow(1-u,n3-k);
                    x+=cp3[k][0]*blend;
                    y+=cp3[k][1]*blend;
                }
                glVertex2f(x,y);
            }
        //glEnd();

        //left horn top {{570,130},{595,135},{605,140},{600,150}};
        int cp4[4][2]={{510,130},{485,135},{470,140},{480,150}};
        int c4[4],n4=3;
        bezierCoefficients(n4,c4);
        glColor3f(0.0,0.0,1.0);
        glLineWidth(5.0);
        //glBegin(GL_LINE_STRIP);
            for(u=0;u<1.0;u+=0.01)
            {
                x=0;y=0;
                for(k=0;k<4;k++)
                {
                    blend=c4[k]*pow(u,k)*pow(1-u,n4-k);
                    x+=cp4[k][0]*blend;
                    y+=cp4[k][1]*blend;
                }
                glVertex2f(x,y);
            }
        glEnd();

        float z;
        int t;
        //left leg top
        glTranslated(520,40,0);
        glColor3f(0.4,0.4,0.4);
        glBegin(GL_LINES);
            for(t = 0; t < 360; t +=1)
            {
                x = 5*sin(t);
                y = 20*cos(t);
                z = 0;
                glVertex3f(x,y,z);
            }
        glEnd();

        //right leg top
        glTranslated(40,0,0);
        glColor3f(0.4,0.4,0.4);
        glBegin(GL_LINES);
            for(t = 0; t < 360; t +=1)
            {
                x = 5*sin(t);
                y = 20*cos(t);
                z = 0;
                glVertex3f(x,y,z);
            }
        glEnd();
        
        glPopMatrix();
    }
    else
    {
        damage = -98984;
        glPushMatrix();
        if(deathXpos == -1)
            deathXpos = xMousePosition;
        glTranslated(deathXpos,0,0);
        glBegin(GL_LINES);
        glColor3f(0.855, 0.439, 0.839);
        float xPekkaE, yPekkaE, zPekkaE, tPekkaE;
        for(tPekkaE = 0; tPekkaE < 360; tPekkaE +=1)
        {
            xPekkaE = 20*sin(tPekkaE);
            yPekkaE = 3*cos(tPekkaE);
            zPekkaE = 0;
            glVertex3f(xPekkaE,yPekkaE,zPekkaE);
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        
        glColor3f(1.000, 1.0, 1.000);
        char start[8];
        start[0] = 'Y';
        start[1] = 'o';
        start[2] = 'u';
        start[3] = ' ';
        start[4] = 'l';
        start[5] = 'o';
        start[6] = 's';
        start[7] = 'e';
        print(480,360,start,8);
        glPopMatrix();
    }

    if(won)
    {
        glColor3f(1.000, 1.0, 1.000);
        char start[19];
        start[0] = 'Y';
        start[1] = 'o';
        start[2] = 'u';
        start[3] = ' ';
        start[4] = 'a';
        start[6] = 'r';
        start[7] = 'e';
        start[8] = ' ';
        start[9] = 'L';
        start[10] = 'e';
        start[11] = 'g';
        start[12] = 'e';
        start[13] = 'n';
        start[14] = 'd';
        start[15] = 'a';
        start[16] = 'r';
        start[17] = 'y';
        start[18] = '!';
        print(380,360,start,19);  
    }

    

    
    glFlush();
}

void passiveMouseFunction(int x, int y)
{
    //fprintf(stdout, "x: %d \n", x);
    xMousePosition = x;
    yMousePosition = y;

    //fprintf(stdout, "%f  %d  %d %d\n", downward, hzl1, damage, x);

    glutPostRedisplay();
}

void Animation()
{
    if(start)
    {
        if(damage == 350) //0.294, 0.000, 0.510
        {
            if(backgroundR > 0.255f)
                backgroundR -= 0.001;
            if(backgroundR < 0.255f)
                backgroundR += 0.001;

            if(backgroundG > 0.0f)
                backgroundG -= 0.001;
            if(backgroundG < 0.0f)
                backgroundG += 0.001;

            if(backgroundB > 0.510f)
                backgroundB -= 0.001;
            if(backgroundB < 0.510f)
                backgroundB += 0.001;
        }

        if(damage == 300)
        {
            if(backgroundR < 1.0f)
                backgroundR += 0.0005;
            if(backgroundG > 0.0f)
                backgroundG -= 0.0005;
            if(backgroundB > 0.0f)
                backgroundB -= 0.0005;
        }

        if(damage == 250)
        {
            if(backgroundR > 0.0f)
                backgroundR -= 0.0005;
            if(backgroundG < 1.0f)
                backgroundG += 0.0005;
            if(backgroundB > 0.0f)
                backgroundB -= 0.0005;
        }

        if(damage == 200)
        {
            if(backgroundR > 0.7f)
                backgroundR -= 0.0005;
            if(backgroundR < 0.7f)
                backgroundR += 0.0005;

            if(backgroundG > 0.5f)
                backgroundG -= 0.0005;
            if(backgroundG < 0.5f)
                backgroundG += 0.0005;

            if(backgroundB > 0.2f)
                backgroundB -= 0.0005;
            if(backgroundB < 0.2f)
                backgroundB += 0.0005;
        }

        if(damage == 150)
        {
            if(backgroundR > 0.1f)
                backgroundR -= 0.0005;
            if(backgroundR < 0.1f)
                backgroundR += 0.0005;

            if(backgroundG > 0.1f)
                backgroundG -= 0.0005;
            if(backgroundG < 0.1f)
                backgroundG += 0.0005;

            if(backgroundB > 0.1f)
                backgroundB -= 0.0005;
            if(backgroundB < 0.1f)
                backgroundB += 0.0005;
        }
    }

    if(start && pekkaSteps != 0 && !won)
    {
        --pekkaSteps;
        if(pekkaSteps == 0)
        {
            pekkaSteps = 350;
            Mix_PlayChannel(7, pStep, 1);
        }
    }

    //fprintf(stdout, "%f  %d  %d %d\n", downward, hzl1, damage, xMousePosition);
    if(damage != 400 && powerup1 && (downward < damage + 40 && downward > damage -40) && (xMousePosition > hzl1 - 40 && xMousePosition < hzl1 + 40))
    {
        powerup1 = false; //fprintf(stdout, "!!!\n");
        damage += 50;
        if(Mix_PlayChannel(-1, heal, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    }
    if(damage != 400 && powerup2 && (downward2 < damage + 40 && downward2 > damage -40) && (xMousePosition > hzl2 - 40 && xMousePosition < hzl2 + 40))
    {
        powerup2 = false; //fprintf(stdout, "???\n");
        damage += 50;
        if(Mix_PlayChannel(-1, heal, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    }
    if(damage != 400 && powerup3 && (downward3 < damage + 40 && downward3 > damage -40) && (xMousePosition > hzl3 - 40 && xMousePosition < hzl3 + 40))
    {
        powerup3 = false; //fprintf(stdout, "[[]]\n");
        damage += 50;
        if(Mix_PlayChannel(-1, heal, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    }

    if(damage != 400 && breathe < 0)
        if( ( (downward < damage + 40 && downward > damage -40) && (xMousePosition < hzl1 - 150 || xMousePosition > hzl1 + 150))  ||
        ((downward2 < damage + 40 && downward2 > damage -40) && (xMousePosition < hzl2 - 150 || xMousePosition > hzl2 + 150)) ||
        ((downward3 < damage + 40 && downward3 > damage -40) && (xMousePosition < hzl3 - 150 || xMousePosition > hzl3 + 150)) )
        {
            //fprintf(stdout, "[[]]\n");
            damage -= 50;
            breathe = 1000;
            if(Mix_PlayChannel(-1, logSound, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }

    if(!won && damage == 400)
    {
        //Mix_Pause(7);
        Mix_HaltMusic();
        if(Mix_PlayChannel(-1, pattk, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        won = true;
      
    }

    if(won)
    {
        //xstd::cout << sndDel << std::endl;
            sndDel -= 1;
    }

    if(sndDel <= 0 && !a1Done)
    {
        if(Mix_PlayChannel(-1, pWin, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        a1Done = true;
    }

    // if(won && !a3Done)
    // {
    //     counterWon -= 1;
    // }

    // if(!a1Done && counterWon == 0) //lift hand
    // {
    //     pekkaSRot = 10;
    //     pekkaSTrY = 20;
    //     rArmY1 = 60;
    //     rArmY2 = 60;
    //     counterWon = 500;
    //     a1Done = true;
    // }

    // if(!a2Done && counterWon == -100) //hit
    // {
    //     counterWon = 500;
    //     a2Done = true;
    // }

    // if(!a3Done && counterWon == -200) //rest
    // {
    //     counterWon = 500;
    //     a3Done = true;
    // }

    /*
    int pekkaSTrX = 615, pekkaSTrY = 95,
        pekkaSRot = 0;
    int rArmX0 = 0, rArmX1 = 0, rArmX2 = 10, rArmX3 = 10,
        rArmY0 = 0, rArmY1 = 40, rArmY2 = 40, rArmY3 = 0;
    */

    if(breathe >= 0)
        --breathe;

    int* ppowerup = bezier(t,p0,p1,p2,p3);
    t += 0.001;
    if (t >= 1)
        t = 0;

    int* pPekka = bezierPekka(tPekka,p0Pekka,p1Pekka,p2Pekka,p3Pekka);
    tPekka += 0.002;
    if (tPekka >= 1)
    {
        tPekka = 0;
        if(start && skelLeftLeg == -50)
        {
            skelLeftLeg = -60;
            skelRightLeg = -50;
        }
        else if(start)
        {
            skelLeftLeg = -50;
            skelRightLeg = -60;
        }
    }

    if(start && damage < 400)
    {
        downward -= 0.2;
        downward2 -= 0.2;
        downward3 -= 0.2;

        if(downward <= -100.0)
        {
            alter1 = alter;
            powerup1 = false;
            downward = 800;
            hzl1 = rand() % 580 + 250;
            if(--powerupControl == 0)
            {
                powerupControl = 6;
                powerup1 = true;
            }
        }
        if(downward2 <= -100.0)
        {
            alter2 = alter;
            powerup2 = false;
            downward2 = 800;
            hzl2 = rand() % 580 + 250;
            if(--powerupControl == 0)
            {
                powerupControl = 6;
                powerup2 = true;
            }
        }
        if(downward3 <= -100.0)
        {
            alter3 = alter;
            powerup3 = false;
            downward3 = 800;
            hzl3 = rand() % 580 + 250;
            if(--powerupControl == 0)
            {
                powerupControl = 6;
                powerup3 = true;
            }
        }
    }

    --alterCount;
    if(alterCount == 0)
    {
        alter = !alter;
        alterCount = 9999;
    }

    glutPostRedisplay();    
}

void mouseClicks(int b, int s, int x, int y)
{
    std::cout << x << " " << y << " " << (x >= 450 || x <= 560) << std::endl;
    if
    (
        !start &&
        b == GLUT_LEFT_BUTTON &&
        s == GLUT_DOWN &&
        (x >= 450 && x <= 560) &&
        (y >= 335 && y <= 400)
    )
	{
        start = true;
        Mix_PlayMusic(music1, 1);
        if(Mix_PlayChannel(-1, pSpawn, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    }
}

int main(int argc, char** argv) //change to void main()
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pekka VS Skeleton");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error %s\n", glewGetErrorString(err));
        exit(1);
    }
    std::cout << "Status: Using GLEW" << glewGetString(GLEW_VERSION) << std::endl;
    
    if (GLEW_ARB_vertex_program)
        std::cout << "Status: ARB vertex programs available.\n";
    
    if (glewGetExtension("GL_ARB_fragment_program"))
        fprintf(stdout, "Status: ARB fragment programs available.\n");
    
    if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
        fprintf(stdout, "Status: ARB point sprites available.\n");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
        arenaStart = Mix_LoadWAV("Pekkas Playhouse.flac");
        music1 = Mix_LoadMUS("Clash Royale Battle 03 OST [EXTENDED].mp3");
        pSpawn = Mix_LoadWAV("pekka spawn.flac");
        pStep = Mix_LoadWAV("Pekka step.flac");
        pattk = Mix_LoadWAV("Pekka attack.flac");
        pWin = Mix_LoadWAV("Epic card sound effect.flac");
        heal = Mix_LoadWAV("HEAL SOUND!.flac");
        logSound = Mix_LoadWAV("Clash Royale Log Sound Effect.flac");
        Mix_VolumeChunk(pSpawn, 20);
        Mix_VolumeChunk(heal, 50);
        Mix_VolumeChunk(pattk, 40);
        Mix_VolumeChunk(pWin, 70);
        Mix_VolumeChunk(pStep, 20);
        if(Mix_PlayChannel(-1, arenaStart, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    glutDisplayFunc(displayMe);
    glutPassiveMotionFunc(passiveMouseFunction);
    glutMouseFunc(mouseClicks);
    //bezierCoefficients(npowerup,cpowerup);
	p0[0]=0;
	p0[1]=0;

	p1[0]=0;
	p1[1]=80;
	
	p2[0]=20;
	p2[1]=80;
	
	p3[0]=20;
    p3[1]=0;
    
    p0Pekka[0]=0;
	p0Pekka[1]=100;

	p1Pekka[0]=50;
	p1Pekka[1]=200;
	
	p2Pekka[0]=-50;
	p2Pekka[1]=200;
	
	p3Pekka[0]=0;
    p3Pekka[1]=0;

    srand(time(NULL));    
    
    hzl1 = rand() % 580 + 250;
    hzl2 = rand() % 580 + 250;
    hzl3 = rand() % 580 + 250;
    powerupControl = rand() %4 + 2;

    //fprintf(stdout, "%d\n", hzl1);
    
    glutIdleFunc(Animation);
    glClearColor(0.0f, 0.2f, 0.0f, 0.0f);
    gluOrtho2D(0.0, 1080, 0.0, 720);
    glutMainLoop();

    //Mix_FreeChunk(effect1);

    Mix_FreeChunk(arenaStart);
    Mix_FreeChunk(pSpawn);
    Mix_FreeChunk(pStep);
    Mix_FreeChunk(pattk);
    Mix_FreeChunk(pWin);
    Mix_FreeChunk(heal);
    Mix_FreeChunk(logSound);
    Mix_FreeMusic(music1);
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}