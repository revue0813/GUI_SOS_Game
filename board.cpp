#include "board.h"

//Returns true if game board is empty
bool Board::isEmpty() const
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            if (gameBoard[i][j] != ' ')
            {
                // There is a non-empty cell, so the board is not empty
                return false;
            }
        }
    }

    // All cells are empty, so the board is empty
    return true;
}

//Debug command for showing all cells of a game board with values
void Board::showBoardInfo()
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            qDebug() << "Getting board element at (" << i << "," << j << ")\n";
            qDebug() << "Element is" << gameBoard[i][j];
        }
    }
}

//Returns json of game board
QJsonObject Board::toJson() const
{
    QJsonObject json;

    // Convert boardSize and gameMode
    json["boardSize"] = boardSize;
    json["gameMode"] = QString::fromStdString(gameMode);

    // Convert gameBoard to a nested QJsonArray
    QJsonArray boardArray;
    for (const auto& row : gameBoard)
    {
        QJsonArray rowArray;
        for (char cell : row)
        {
            rowArray.append(QString(cell));
        }
        boardArray.append(rowArray);
    }
    json["gameBoard"] = boardArray;

    return json;
}

//Clears game board and takes new game board from file
void Board::fromJson(const QJsonObject& json)
{
    // Retrieve boardSize and gameMode
    boardSize = json["boardSize"].toInt();
    gameMode = json["gameMode"].toString().toStdString();

    // Retrieve gameBoard from the nested QJsonArray
    QJsonArray boardArray = json["gameBoard"].toArray();
    gameBoard.clear();
    for (const auto& row : boardArray)
    {
        QJsonArray rowArray = row.toArray();
        std::vector<char> rowVector;
        for (const auto& cell : rowArray)
        {
            rowVector.push_back(cell.toString().at(0).toLatin1());
            qDebug() << "Cell Value: " << cell.toString().at(0).toLatin1();
        }
        gameBoard.push_back(rowVector);
    }
}

//Sets row and col to random cell inside board
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
