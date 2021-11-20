#ifndef __MANAGER_H_
#define __MANAGER_H_

#include "default.h"
#include "Referee.h"

class Manager
{
public:
    void Menu();

protected:
    void Play(int GameMode); // Play the game
    void Menu_SelectModeAndPlay();
    void Menu_SelectDifficulty();

private:
    int GameCount;
    int Difficulty;
    Referee Game;
};

#endif