#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "QPushButton"
#include "QGridLayout"

using namespace std;

class Board
{
public:
    Board();

    //Getter setters
    void initializeBoard();
    vector<vector<char>> getGameBoard() const;

    string getGameMode() const;
    void setGameMode(string newGameMode);

    void setBoardSize(int newBoardSize);
    int getBoardSize() const;

    void setBoardElement(int row, int col, char value);
    char getBoardElement(int row, int col) const;

    //Class functions
    bool isCellEmpty(int &row, int &col);
    bool boardFull() const;
    bool checkForSOS(int &sosCount);
    void computerMakeRandomMove(int &row, int &col);

    std::vector<std::pair<int, int> > findAllSOS();
private:
    vector<vector<char>> gameBoard;
    int boardSize;
    string gameMode;

};

#endif // BOARD_H
