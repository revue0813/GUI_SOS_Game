#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>


using namespace std;

class Board
{
public:
    Board();

    //Class functions
    bool isCellEmpty(int &row, int &col);
    bool boardFull() const;
    bool checkForSOS(int &sosCount);
    void computerMakeRandomMove(int &row, int &col);

    //Getter setters
    void initializeBoard();
    vector<vector<char>> getGameBoard() const;

    string getGameMode() const;
    void setGameMode(string newGameMode);

    void setBoardSize(int newBoardSize);
    int getBoardSize() const;

    void setBoardElement(int row, int col, char value);
    char getBoardElement(int row, int col) const;

private:
    vector<vector<char>> gameBoard;
    string gameMode;
    int boardSize;

};

#endif // BOARD_H
