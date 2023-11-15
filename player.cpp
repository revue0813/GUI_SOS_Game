#include "player.h"

char Player::chooseRandomLetter()
{
    // Get random value even or ood
    srand(static_cast<unsigned int>(time(nullptr)));
    int random_value = rand();
    random_value = random_value % 2;

    qDebug() << "Random letter value is " << random_value;

    if (random_value == 0)
    {
        return 'S';
    }
    else
    {
        return 'O';
    }
}

void Player::incrementScore()
{
    score += 1;
}

char Player::getPlayerLetter()
{
    return pLetter;
}
void Player::setPlayerLetter(char newPLetter)
{
    pLetter = newPLetter;
}

string Player::getPlayertype() const
{
    return ptype;
}
void Player::setPlayertype(const string &newPtype)
{
    ptype = newPtype;
}

int Player::getScore() const
{
    return score;
}
void Player::setScore(int newScore)
{
    score = newScore;
}

//Default Constructor
Player::Player(const string &color) : ptype("Human"), pLetter('S'), score(0)
{
}
