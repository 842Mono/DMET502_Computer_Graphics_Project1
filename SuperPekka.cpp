#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <math.h>
#include <stdio.h>

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

int xMousePosition = 0;
int yMousePosition = 0;

int cpPowerUp[4][2]={{510,130},{485,135},{470,140},{480,150}};
int cPowerUp[4],nPowerUp = 3;
float uPowerUp = 0, xPowerUp = 0, yPowerUp = 0, blendPowerUp;
int delayPowerUp = 0;


    



void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glTranslated(xMousePosition-540,0,0);
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
        glVertex3d(0, 0, 0);
        glVertex3d(0, 40, 0);
        glVertex3d(10, 40, 0);
        glVertex3d(10, 0, 0);
    glEnd();
    glRotated(70, 0, 0, 1);
    glTranslated(-585, -95, 0);

    //sword
    glBegin(GL_POLYGON);
        glColor3f(0.2,0.2,0.2);
        glVertex3d(615, 95, 0);
        glVertex3d(615, 115, 0);
        glVertex3d(627, 115, 0);
        glVertex3d(627, 95, 0);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(0.35,0.35,0.35);
        glVertex3d(615, 115, 0);
        //
        glVertex3d(615, 120, 0);
        glVertex3d(620, 125, 0);
        glVertex3d(635, 145, 0);
        glVertex3d(635, 115, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(620, 125, 0);
        glVertex3d(615, 130, 0);
        glVertex3d(615, 155, 0);
        // glVertex3d(635, 149, 0);
        glVertex3d(635, 148, 0);
        glVertex3d(620, 125, 0);
    glEnd();

    //iterators
    int k;
    float x, y, u, blend;

    //right horn bottom
    int cp[4][2]={{570,120},{595,125},{605,130},{600,150}};
    int c[4],n=3;
    bezierCoefficients(n,c);
    glColor3f(0.0,0.0,1.0);
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
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
    glEnd();

    //right horn top
    int cp2[4][2]={{570,130},{595,135},{605,140},{600,150}};
    int c2[4],n2=3;
    bezierCoefficients(n2,c2);
    glColor3f(0.0,0.0,1.0);
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
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
    glBegin(GL_LINE_STRIP);
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
    glEnd();

    //left horn top {{570,130},{595,135},{605,140},{600,150}};
    int cp4[4][2]={{510,130},{485,135},{470,140},{480,150}};
    int c4[4],n4=3;
    bezierCoefficients(n4,c4);
    glColor3f(0.0,0.0,1.0);
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
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

    //log
    glPushMatrix();
    glBegin(GL_POLYGON);
        glColor3f(1.000,0.647,0.0);
        glVertex3d(0, 200, 0);
        glVertex3d(0, 250, 0);
        glVertex3d(250, 250, 0);
        glVertex3d(250, 200, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(1.000,0.549,0.0);
        glVertex3d(10, 210, 0);
        glVertex3d(10, 240, 0);
        glVertex3d(240, 240, 0);
        glVertex3d(240, 210, 0);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
        glVertex3d(30, 222, 0);
        glVertex3d(40, 232, 0);
        glVertex3d(50, 222, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(1.000,0.843,0.0);
        glVertex3d(115, 222, 0);
        glVertex3d(122, 232, 0);
        glVertex3d(137, 222, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.000,0.843,0.0);
        glVertex3d(184, 222, 0);
        glVertex3d(197, 232, 0);
        glVertex3d(200, 222, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.000,0.843,0.0);
        glVertex3d(70, 232, 0);
        glVertex3d(83, 222, 0);
        glVertex3d(90, 232, 0);
    glEnd();
    glPopMatrix();

    //powerup
    glPushMatrix();
    glTranslated(0,(int)yPowerUp,0);
    // fprintf(stdout, M_PI);
    // float anglerad = M_PI * angle / 180.0f;
    // float x = sinf(anglerad) * radius; 
    // float y = cosf(anglerad) * radius;

    //rage
    glColor3f(0.600,0.196,0.800);
    glBegin(GL_POLYGON);
        glVertex3d(10, 10, 0);
        glVertex3d(10, 45, 0);
        glVertex3d(35, 45, 0);
        glVertex3d(35, 10, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(17, 45, 0);
        glVertex3d(17, 55, 0);
        glVertex3d(28, 55, 0);
        glVertex3d(28, 45, 0);
    glEnd();

    //heal
    glColor3f(1.000, 0.843, 0.000);
    glBegin(GL_POLYGON);
        glVertex3d(25, 10, 0);
        glVertex3d(25, 45, 0);
        glVertex3d(50, 45, 0);
        glVertex3d(50, 10, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(32, 45, 0);
        glVertex3d(32, 55, 0);
        glVertex3d(43, 55, 0);
        glVertex3d(43, 45, 0);
    glEnd();
    glPopMatrix();


    glFlush();
}

void passiveMouseFunction(int x, int y)
{
    //fprintf(stdout, "x: %d \n", x);
    xMousePosition = x;
    yMousePosition = y;
    glutPostRedisplay();
}

void Animation()
{
    //fprintf(stdout, "%E\n", delayPowerUp);
    --delayPowerUp;
    if(delayPowerUp < 0)
    {
        delayPowerUp = 999999;
    }
    else if(delayPowerUp == 0)
    {
        for(int k=0;k<4;k++)
        {
            blendPowerUp = cPowerUp[k]*pow(uPowerUp,k)*pow(1-uPowerUp,nPowerUp-k);
            xPowerUp += cpPowerUp[k][0]*blendPowerUp;
            yPowerUp += cpPowerUp[k][1]*blendPowerUp;
        }
        uPowerUp += 0.01;
        if(uPowerUp >= 1.0)
        {
            uPowerUp = 0.0;
            xPowerUp = 0;
            yPowerUp = 0;
        }
        fprintf(stdout, "x: %E, y: %E\n", xPowerUp, yPowerUp);
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Super Pekka");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error %s\n", glewGetErrorString(err));
        exit(1);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    if (GLEW_ARB_vertex_program)
        fprintf(stdout, "Status: ARB vertex programs available.\n");
    
    if (glewGetExtension("GL_ARB_fragment_program"))
        fprintf(stdout, "Status: ARB fragment programs available.\n");
    
    if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
        fprintf(stdout, "Status: ARB point sprites available.\n");
    glutDisplayFunc(displayMe);
    glutPassiveMotionFunc(passiveMouseFunction);
    bezierCoefficients(nPowerUp,cPowerUp);
    glutIdleFunc(Animation);
    glClearColor(0.0f, 5.0f, 0.0f, 0.0f);
    gluOrtho2D(0.0, 1080, 0.0, 720);
    glutMainLoop();
    return 0;
}