#include "player.h"

// In player.cpp
QJsonObject Player::toJson() const {
    QJsonObject playerJson;
    playerJson["ptype"] = QString::fromStdString(ptype);
    playerJson["score"] = score;

    return playerJson;
}

void Player::fromJson(const QJsonObject &playerJson)
{
    if (playerJson.contains("ptype") && playerJson["ptype"].isString())
    {
        ptype = playerJson["ptype"].toString().toStdString();
    }
    else
    {
        qDebug() << "Error: Invalid or missing 'name' field in player JSON.";
    }

    if (playerJson.contains("score") && playerJson["score"].isDouble())
    {
        score = static_cast<int>(playerJson["score"].toDouble());
    }
    else
    {
        qDebug() << "Error: Invalid or missing 'score' field in player JSON.";
    }

    // Add other player-specific fields as needed
}

void Player::chooseRandomLetter()
{
    // Use the random_device to seed the random number generator
    std::random_device rd;

    // Use the random device to seed the random number generator engine
    std::default_random_engine generator(rd());

    // Create a distribution to generate either 0 or 1
    std::uniform_int_distribution<int> distribution(0, 1);

    // Generate the random value (0 or 1)
    int random_value = distribution(generator);

    qDebug() << "Random letter value is " << random_value;

    if (random_value == 0)
    {
        pLetter = 'S';
    }
    else
    {
        pLetter = 'O';
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
