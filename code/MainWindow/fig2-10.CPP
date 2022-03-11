#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "glut.h"
#include <random>
#include "config.h"


void Display();
void Init(void);
void sides();
void displayPlayer();
void displayBall();
void displayBricks();
void myKeyboard(unsigned char, int, int);
void playerMove(int, int, int);
void recomputeFrame(int value);
void createBricks();

struct Ball {
public:
    int intX = WIN_WIDTH / 2; //Center of screen; Origin
    int intY = 5 + BALL_RADIUS;

    // 4 directions allowed
    int direction = 0;

    void changeDirection(int dir) {
        direction = dir;
    }

    void move() {
        // up right
        if (direction == 0) {
            intX+=2;
            intY+= 2;

        }
        // up left
        if (direction == 1) {
            intX-= 2;
            intY+=2;

        }
        // down right 
        if (direction == 2) {
            intX+= 2;
            intY-= 2;

        }
        // down left
        if (direction == 3) {
            intX-= 2;
            intY-= 2;

        }

    }

    int getX() {
        return this->intX;
    }

    int getY() {
        return this->intY;
    }

};

struct Player {
public:
    int pos = WIN_WIDTH / 2; //Center of screen; Origin

    void moveLeft() {
        this->pos-=5;
    }

    void moveRight() {
        this->pos+=5;
    }

    int getPos() {
        return this->pos;
    }
};

struct Brick {
public:
    
    int intX;
    int intY;

    // brick level and life
    int level = 0;
    bool brickLife = true;


    Brick() {

        intX = 0;
        intY = 0;
    }
    void hit() {
        
        if (brickLife) {
            level++;


            if (level == 3) {
                brickLife = false;
            }
        }
    }

    int getX() {
        return this->intX;
    }

    int getY() {
        return this->intY;
    }

    int getLevel() {
        return this->level;
    }

    bool isLife() {
        return this->brickLife;
    }

    void setX(int x) {
        intX = x;
    }
    void setY(int y) {
        intY = y;
    }
};

// creates player, ball, and bricks
Player p;
Ball b;
Brick bricks[BRICK_ROWS * BRICK_COLS];


void main(int argc, char** argv)
{
    createBricks();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Breakout Game");
    glutDisplayFunc(Display);
    Init();
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(playerMove);
    glutMainLoop();

}

void recomputeFrame(int value) {
    glutPostRedisplay();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);


    //show sides function
    sides();

    // display player
    displayPlayer();

    // display ball
    displayBall();

    //display bricks
    displayBricks();

    b.move();


    glutSwapBuffers();
    
    glutTimerFunc(TIMER, recomputeFrame, 0);

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


void playerMove(int theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
    case GLUT_KEY_LEFT:
        p.moveLeft();
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        p.moveRight();
        glutPostRedisplay();
        break;
    default:
        break;       // do nothing
    }
}

// to be able to exit
void myKeyboard( unsigned char theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
    case 'E':
    case 'e':
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

// display for the player bar
void displayPlayer()
{

    glColor3f(0.70f, 0.13f, 0.13f);

    glBegin(GL_QUADS);

    glVertex3f(p.getPos() - PLAYER_WIDTH / 2, 0, 0);

    glVertex3f(p.getPos() - PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

    glVertex3f(p.getPos() + PLAYER_WIDTH / 2, PLAYER_HEIGHT, 0);

    glVertex3f(p.getPos() + PLAYER_WIDTH / 2, 0, 0);


    glEnd();

}

// display for the ball
void displayBall() {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // use GL_LINE if no fill

    glBegin(GL_POLYGON);

    glColor3f(0.53f, 0.8f, 0.98f);

    for (int j = 0; j < CIRCLE_SEGMENTS; j++) {
        float const theta = 2.0f * 3.1415926f * (float)j / (float)CIRCLE_SEGMENTS;
        float const x = BALL_RADIUS * cosf(theta);
        float const y = BALL_RADIUS * sinf(theta);
        glVertex2f(x + b.getX(), y + b.getY());
    }
    glEnd();

}

void createBricks() {

    int currX = 30;
    int currY = WIN_HEIGHT - 40;
    int brickWidth = (WIN_WIDTH - 60 - (BRICK_COLS - 1) * 5) / BRICK_COLS;

    int n = 0;

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            bricks[n].setX(currX + brickWidth / 2);
            bricks[n].setY( currY + 5);
            n++;
            currX += brickWidth + 5;
        }
        currY -= 15;
        currX = 30;
    }
}

void displayBricks() {

    int brickWidth = (WIN_WIDTH - 60 - (BRICK_COLS - 1) * 5) / BRICK_COLS;

    glBegin(GL_QUADS);
    for (int i = 0; i < BRICK_COLS * BRICK_ROWS; i++) {

        // if it hits a brick that is out of lives then it skips it
        if (!bricks[i].isLife()) {
            continue;
        }

        if (bricks[i].getLevel() == 0) {
            glColor3f(0.0f, 0.0f, 0.5f);
        }
        else if (bricks[i].getLevel() == 1) {
            glColor3f(0.2f, 0.6f, 0.41f);
        }
        else if (bricks[i].getLevel() == 2) {
            glColor3f(0.5f, 0.0f, 0.5f);
        }

        // draw brick
        glVertex3f(bricks[i].getX() - brickWidth / 2, bricks[i].getY() - 5, 0);

        glVertex3f(bricks[i].getX() + brickWidth / 2, bricks[i].getY() - 5, 0);

        glVertex3f(bricks[i].getX() + brickWidth / 2, bricks[i].getY() + 5, 0);

        glVertex3f(bricks[i].getX() - brickWidth / 2, bricks[i].getY() + 5, 0);

        
    }
    glEnd();
    
}

