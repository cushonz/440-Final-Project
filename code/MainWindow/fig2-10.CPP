#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "glut.h"
#include <random>
#include "config.h"


void Display();
void Init(void);
void sides();
void myKeyboard(unsigned char, int, int);
int pos = 0;

struct Player{
public:
    int pos = 0; //Center of screen; Origin

    void moveLeft() {
        this->pos--;
    }

    void moveRight() {
        this->pos++;
    }

    int getPos() {
        return this->pos;
    }
};

Player genplayer(int);
Player p;

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    //glutInitWindowPosition(100,100);
    glutCreateWindow("Breakout Game");
    glutDisplayFunc(Display);
    Init();
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
}
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //show sides function
    sides();
    
    // show player
    p = genplayer((WIN_WIDTH / 2)+ pos);
    pos = p.getPos();

    glFlush();

}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(1.0, 640.0, 0.0, 480.0);
}

struct GLintPoint {
public:
    GLint x, y;
};

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
#define NUM 20
    static GLintPoint List[NUM];
    static int last = -1;
    GLint x = mouseX;
    GLint y = 640 - mouseY; // flip the y value as always
    switch (theKey)
    {
    case GLUT_KEY_LEFT:
        p.moveLeft();
        break;
    case GLUT_KEY_RIGHT:
        p.moveRight();
        break;
    case 'E':
        exit(-1); //terminate the program
    default:
        break;       // do nothing
    }
}

void sides()
{
    //Create sides for the game
    //Makes the outside lines silver
    glColor3f(0.75f, 0.75f, 0.75f);
    //Left side
    glBegin(GL_QUADS);

    glVertex3f(20, 0, 0);

    glVertex3f(25, 0, 0);

    glVertex3f(25, WIN_HEIGHT, 0);

    glVertex3f(20, WIN_HEIGHT, 0);

    //Right Side

    glVertex3f(WIN_WIDTH - 25, 0, 0);

    glVertex3f(WIN_WIDTH - 20, 0, 0);

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
Player genplayer(int x)
{
    glColor3f(0.70f, 0.13f, 0.13f);
    Player pl = Player();
    glBegin(GL_QUADS);

    glVertex3f(x - PLAYER_WIDTH / 2, 0, 0);

    glVertex3f(x - PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

    glVertex3f(x + PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

    glVertex3f(x + PLAYER_WIDTH / 2, 0, 0);


    glEnd();
    return pl;
}


