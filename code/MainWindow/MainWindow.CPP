#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
/*#include <iostream.h> */
#include "glut.h"
#include <random>
#include "config.h"

void Display();
void Init(void);

void main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	//glutInitWindowPosition(100,100);
	glutCreateWindow("Breakout Game");
   glutDisplayFunc(Display);
   Init();
	glutMainLoop();
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

    //show sides function
    //sides();

    // show player
    player(WIN_WIDTH / 2);


	/*glBegin(GL_POINTS);
		glVertex2i(100,50);
		glVertex2i(100,130);
	 glVertex2i(150,130);
glEnd();*/

   glFlush();
   
}

void Init()
{
	glClearColor(0.0,0.0,0.0,0);
   glColor3f(0.0f,0.0f,0.0f);
   glPointSize(4.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(1.0,640.0,0.0,480.0);
}

void sides()
{
    //Create sides for the game
    //Makes the outside lines silver
    glColor3f(0.75f, 0.75f, 0.75f);
    //Left side
    glBegin(GL_QUADS);

    glVertex3f(20, 20, 0);

    glVertex3f(25, 20, 0);

    glVertex3f(25, WIN_HEIGHT, 0);

    glVertex3f(20, WIN_HEIGHT, 0);

    //Right Side

    glVertex3f(WIN_WIDTH - 25, 20, 0);

    glVertex3f(WIN_WIDTH - 20, 20, 0);

    glVertex3f(WIN_WIDTH - 20, WIN_HEIGHT, 0);

    glVertex3f(WIN_WIDTH - 25, WIN_HEIGHT, 0);

    //Top 

    glVertex3f(20, WIN_HEIGHT, 0);

    glVertex3f(WIN_WIDTH - 20, WIN_HEIGHT, 0);

    glVertex3f(WIN_WIDTH - 20, WIN_HEIGHT - 5, 0);

    glVertex3f(20, WIN_HEIGHT - 5, 0);
    glEnd();
}

// creates the player bar
void player(int x)
{
    glColor3f(0.70f, 0.13f, 0.13f);

    glBegin(GL_QUADS);

       /* glVertex3f(x - PLAYER_WIDTH / 2, 0, 0);

        glVertex3f(x - PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

        glVertex3f(x + PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

        glVertex3f(x + PLAYER_WIDTH / 2, 0, 0); */

        glVertex3f(100, 150, 0);

        glVertex3f(100, 200, 0);

        glVertex3f(150, 200, 0);

        glVertex3f(150, 150, 0);

    glEnd();
}


