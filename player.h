#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <QDebug>
#include <random>

using namespace std;

class Player
{

public:
    //Class Methods
    void chooseRandomLetter();
    void incrementScore();

    //Getter Setters
    string getPlayertype() const;
    void setPlayertype(const string &newPtype);

    char getPlayerLetter();
    void setPlayerLetter(char newPLetter);

    int getScore() const;
    void setScore(int newScore);

    Player(const string &color);

private:
    string ptype;
    char pLetter;
    int score;

};

#endif // PLAYER_H
