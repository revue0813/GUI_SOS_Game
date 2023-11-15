#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "board.h"
#include <QDebug>


using namespace std;

class Player
{

public:
    Player(const string &color);

    //Getter Setters
    void setScore(int newScore);
    int getScore() const;
    void setPlayertype(const string &newPtype);
    string getPlayertype() const;
    void setPlayerLetter(char newPLetter);
    char getPlayerLetter();

    //Class Methods
    void incrementScore();
    void computerMakeMove(Board &board, QGridLayout boardLayout);
    char chooseRandomLetter();
    void makeRandomMove();

private:
    string ptype;
    char pLetter;
    int score;

};

#endif // PLAYER_H
