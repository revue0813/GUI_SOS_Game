#include "board.h"


using namespace std;

void Board::computerMakeRandomMove(int &row, int &col)
{
    do
    {
        row = rand() % getBoardSize();
        col = rand() % getBoardSize();
        //qDebug() << "Trying at " << row << "," << col;
    } while (!isCellEmpty(row, col));
    //qDebug() << "Found empty cell at " << row << "," << col;
}

//Checks if SOS is on board
bool Board::checkForSOS(int &sosCount)
{
    bool sosFound = false;

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            if (toupper(gameBoard[i][j]) == 'S')
            {
                // Check horizontal
                if (j + 2 < boardSize && toupper(gameBoard[i][j + 1]) == 'O' && toupper(gameBoard[i][j + 2]) == 'S')
                {
                    // Check if sos has been scored already (General game logic)
                    if (gameBoard[i][j] == 's' && gameBoard[i][j + 1] == 'o' && gameBoard[i][j + 2] == 's')
                    {

                    }
                    else {
                        // Make SOS lowercase to show it's been scored on
                        gameBoard[i][j] = 's';
                        gameBoard[i][j + 1] = 'o';
                        gameBoard[i][j + 2] = 's';
                        sosFound = true;
                        sosCount += 1;
                    }
                }
                // Check vertical
                if (i + 2 < boardSize && toupper(gameBoard[i + 1][j]) == 'O' && toupper(gameBoard[i + 2][j]) == 'S')
                {
                    if (gameBoard[i][j] == 's' && gameBoard[i + 1][j] == 'o' && gameBoard[i + 2][j] == 's')
                    {

                    }
                    else
                    {
                        gameBoard[i][j] = 's';
                        gameBoard[i + 1][j] = 'o';
                        gameBoard[i + 2][j] = 's';
                        sosFound = true;
                        sosCount += 1;
                    }
                }
                // Check diagonal (top-left to bottom-right)
                if (i + 2 < boardSize && j + 2 < boardSize && toupper(gameBoard[i + 1][j + 1]) == 'O' && toupper(gameBoard[i + 2][j + 2]) == 'S')
                {
                    if (gameBoard[i][j] == 's' && gameBoard[i + 1][j + 1] == 'o' && gameBoard[i + 2][j + 2] == 's')
                    {

                    }
                    else {
                        gameBoard[i][j] = 's';
                        gameBoard[i + 1][j + 1] = 'o';
                        gameBoard[i + 2][j + 2] = 's';
                        sosFound = true;
                        sosCount += 1;
                    }
                }
                // Check diagonal (top-right to bottom-left)
                if (i + 2 < boardSize && j - 2 >= 0 && toupper(gameBoard[i + 1][j - 1]) == 'O' && toupper(gameBoard[i + 2][j - 2]) == 'S')
                {
                    if (gameBoard[i][j] == 's' && gameBoard[i + 1][j - 1] == 'o' && gameBoard[i + 2][j - 2] == 's')
                    {

                    }
                    else {
                        gameBoard[i][j] = 's';
                        gameBoard[i + 1][j - 1] = 'o';
                        gameBoard[i + 2][j - 2] = 's';
                        sosFound = true;
                        sosCount += 1;
                    }
                }
            }
        }
    }
    return sosFound;
}



//Checks if board is full
bool Board::boardFull() const
{
    for (int row = 0; row < boardSize; ++row)
    {
        for (int col = 0; col < boardSize; ++col)
        {
            if (gameBoard[row][col] == ' ')
            {
                // There is an empty cell, so the board is not full
                return false;
            }
        }
    }

    // All cells are occupied, so the board is full
    return true;
}

//Checks if cell is empty
bool Board::isCellEmpty(int &row, int &col)
{
    if (gameBoard[row][col] == ' ')
    {
        //qDebug() << row << "," << col << "has a " << gameBoard[row][col];
        return true;
    }
    else
    {
        return false;
    }
}

//Returns element inside of cell
char Board::getBoardElement(int row, int col) const
{
    return gameBoard[row][col];
}
void Board::setBoardElement(int row, int col, char value)
{
    //qDebug() << "The element to set is " << row << "," << col;
    gameBoard[row][col] = value;
}

//boardSize getter setter
int Board::getBoardSize() const
{
    return boardSize;
}
void Board::setBoardSize(int newBoardSize)
{
    boardSize = newBoardSize;
}

//gameMode getter setter
string Board::getGameMode() const
{
    return gameMode;
}
void Board::setGameMode(string newGameMode)
{
    gameMode = newGameMode;
}

//gameBoard getter initializer
vector<vector<char>> Board::getGameBoard() const
{
    return gameBoard;
}
void Board::initializeBoard()
{
    gameBoard = vector<vector<char>>(boardSize, vector<char>(boardSize, ' '));
}

//Default Constructor
Board::Board() : boardSize(3), gameMode("Simple")
{
}
