#include <list>
#include <algorithm>
#include <iostream>
#include "game.h"
using namespace std;

Game :: Game(int diff,float scr) //score could be passed in for 'continue' mechanic
{
    const char *DifficultyLevels[4] = {"Super Hard","Hard","Medium","Easy"}; // Increase color range to 'make harder'

    this -> remaining_hearts = diff; //difficulty can/will both set the amount of health the player starts with and the max amount of block hp
    this -> score = scr;
};

void Game :: gainPoint(float amount)
{
    this -> score += (amount*this->multiplier);
}

bool Game :: takeDamage()
{
    this->remaining_lives -=1;
    return isDead();
    
};

bool Game :: isDead()
{
    if (this -> remaining_lives == 0)
    {
        return false;
    }
    else
        return true;
};