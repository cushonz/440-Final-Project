#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
/*#include <iostream.h> */
#include "glut.h"
#include <random>
#include <vector>
#include "config.h"

class Brick {
public:
    //Brick(int, bool, float, float);
    //~Brick();
    int health;
    bool hasItem; //drops item on death
    float posx1, posy1, posx2, posy2;

    Brick(int H, bool I, float x1, float y1, float x2, float y2) {
        this->health = H;
        this->hasItem = I;
        this->posx1 = x1;
        this->posy1 = y1;
        this->posx2 = x2;
        this->posy2 = y2;
    }
    ~Brick() {}
};

void Display();
void Init(void);
void player(int);
void sides();
void drawLevel(int);
std::vector<Brick> createBricks(int);
void drawBricks(std::vector<Brick>);


void main(int argc, char** argv)
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
    sides();

    // show player
    player(WIN_WIDTH / 2);

    drawLevel(1);


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
void player(int x)
{
    glColor3f(0.70f, 0.13f, 0.13f);

    glBegin(GL_QUADS);

    glVertex3f(x - PLAYER_WIDTH / 2, 0, 0);

     glVertex3f(x - PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

     glVertex3f(x + PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

     glVertex3f(x + PLAYER_WIDTH / 2, 0, 0);


    glEnd();
}

void drawLevel(int level) {
    if (level == 1) {
        drawBricks(createBricks(3));
    } else if (level == 2) {
        drawBricks(createBricks(4));
    }
    else if (level == 3) {
        drawBricks(createBricks(5));
    }
    else if (level == 4) {
        drawBricks(createBricks(6));
    }
    else if (level == 5) {
        drawBricks(createBricks(7));
    }
}

std::vector<Brick> createBricks(int rows) {
    std::vector<Brick> brick_list;
    float x1 = 35, y1 = WIN_HEIGHT - 50, x2 = 55, y2 = WIN_HEIGHT - 45;
    int health = rows;
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < 27; k++) {
            Brick newBrick(health, false, x1, y1, x2, y2);
            brick_list.push_back(newBrick);
            x1 += 21;
            x2 += 21;
        }
        health--;
        x1 = 35;
        x2 = 55;
        y1 -= 7;
        y2 -= 7;

    }
    return brick_list;
}

void drawBricks(std::vector<Brick> brick_list) {
    for (std::vector<Brick>::iterator it = brick_list.begin(); it != brick_list.end(); it++) {
        if (it->health == 1) {
            glColor3f(0.7f, 1.5f, 0.2f);
        }
        else if (it->health == 2) {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        else if (it->health == 3) {
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        else if (it->health == 4) {
            glColor3f(0.05f, 0.05f, 1.0f);
        }
        glRectf(it->posx1, it->posy1, it->posx2, it->posy2);
        
    }
}


