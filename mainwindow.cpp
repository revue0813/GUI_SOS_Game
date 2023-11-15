#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

//MainWindow Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bluePlayer("Blue") //Initialize Players in constructor
    , redPlayer("Red")
{
    ui->setupUi(this);

    //connect simple game mode radio button to on_game_mode_selected slot
    connect(ui->simpleGameRadioButton
            , &QRadioButton::clicked
            , this
            , &MainWindow::on_gameMode_selected);

    //connect general game mode radio button to on_game_mode_selected slot
    connect(ui->generalGameRadioButton
            , &QRadioButton::clicked
            , this
            , &MainWindow::on_gameMode_selected);

    // Check if game board is not null
    qDebug() << "gameBoardGridLayout status: " << ui->gameBoardGridLayout;

}

//MainWindow Deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

//Populates game board on gameBoardGridLayout
void MainWindow::populateGameBoard()
{
    //qDebug() << "POPULATING GAME BOARD";
    //qDebug() << "Board size is " << gameBoard.getBoardSize();

    for (int i = 0; i < gameBoard.getBoardSize(); ++i)
    {
        for (int j = 0; j < gameBoard.getBoardSize(); ++j)
        {
            //qDebug() << "Getting board element at (" << i << ", " << j << ")\n";

            //Create new push button and set properties
            QPushButton *button = new QPushButton(QString(gameBoard.getBoardElement(i, j)),this);
            button->setFixedSize(33, 33);
            button->setVisible(true);
            ui->gameBoardGridLayout->addWidget(button, i, j);

            //Connect new buttons to on_newButton_clicked slot
            connect(button, &QPushButton::clicked, this, &MainWindow::on_newButton_clicked);
        }
    }
}

//Find the button associated with cell passed into args
void MainWindow::findButtonCell(QPushButton *targetButton, int &row, int &column)
{
    row = 0;
    column = 0;

    //get game board layout
    QGridLayout *layout = ui->gameBoardGridLayout;

    //Search for Cell in layout
    for (int r = 0; r < layout->rowCount(); ++r)
    {
        for (int c = 0; c < layout->columnCount(); ++c)
        {
            QLayoutItem *item = layout->itemAtPosition(r, c);
            if (item->widget() == targetButton)
            {
                //Change row and col to reflect button location
                row = r;
                column = c;
                return; //Exit the loop once the button is found
            }
        }
    }
}

//Change the game info text
void MainWindow::changeGameInfoText(const QString &gameInfoQString)
{
    //Check for existing label
    QLabel *existingLabel = ui->centralwidget->findChild<QLabel *>("gameInfoLabel");
    QPushButton *existingPushButton = ui->centralwidget->findChild<QPushButton *>("startGameButton");

    if (existingLabel || existingPushButton)
    {
        if (existingLabel)
        {
            //qDebug() << "Found existing Label!";
            ui->infoLayout->removeWidget(existingLabel);
            delete existingLabel; //Remove the label and free memory
        }
        else if (existingPushButton)
        {
            //qDebug() << "Found existing Label!";
            ui->infoLayout->removeWidget(existingPushButton);
            delete existingPushButton; //Remove the push button and free memory
        }
    }

    //Create a new Label
    QLabel *gameInfoLabel = new QLabel;
    gameInfoLabel->setObjectName("gameInfoLabel");
    gameInfoLabel->setAlignment(Qt::AlignCenter);
    gameInfoLabel->setText(gameInfoQString);

    //Place Label in infoLayout
    ui->infoLayout->addWidget(gameInfoLabel);
}

//Change the Turn info text
void MainWindow::changeTurnInfoText(const QString &turnInfoQString)
{
    // Find existing Label in central widget
    QLabel *existingLabel = ui->centralwidget->findChild<QLabel *>("turnInfoLabel");

    if (existingLabel)
    {
        //qDebug() << "Found existing Label!";
        ui->turnLayout->removeWidget(existingLabel); //remove existing label
        delete existingLabel;
    }

    //Create new label and set properties
    QLabel *turnLabel = new QLabel;
    turnLabel->setObjectName("turnInfoLabel");
    //qDebug() << "Set the object name as turnInfoLabel";
    turnLabel->setAlignment(Qt::AlignCenter);
    turnLabel->setText(turnInfoQString);

    //Add label to turnLayout
    ui->turnLayout->addWidget(turnLabel);
}

//Changes player turn (Blue or Red)
void MainWindow::switchPlayerTurn()
{
    if (currentPlayer == "Blue")
    {
        currentPlayer = "Red";
    }
    else if (currentPlayer == "Red")
    {
        currentPlayer = "Blue";
    }

    //update turnLayout to reflect new player turn
    QString qStringTurnInfo = QString::fromStdString(currentPlayer
                                                     + " Players turn");
    changeTurnInfoText(qStringTurnInfo);

    //qDebug() << "Switched Player to " << currentPlayer;
}

//Ends the game and performs clean up
void MainWindow::endGame()
{
    // Disable all buttons in the game board
    for (int row = 0; row < ui->gameBoardGridLayout->rowCount(); ++row)
    {
        for (int col = 0; col < ui->gameBoardGridLayout->columnCount(); ++col)
        {
            QLayoutItem *item = ui->gameBoardGridLayout->itemAtPosition(row, col);
            if (item && item->widget())
            {
                QPushButton *button = qobject_cast<QPushButton *>(item->widget());
                if (button)
                {
                    button->setEnabled(false);
                }
            }
        }
    }

    //Enable and show disabled and hidden items respectively
    ui->simpleGameRadioButton->setEnabled(true);
    ui->generalGameRadioButton->setEnabled(true);
    ui->boardSizeSpinBox->setEnabled(true);

    ui->blueScoreLabel->show();
    ui->blueScoreSpinBox->show();
    ui->redScoreLabel->show();
    ui->redScoreSpinBox->show();

    //Add start new game button to gameInfoLayout
    addStartButtonBack();

    //Game board is full and game mode is General
    if (gameBoard.boardFull() && gameBoard.getGameMode() == "General")
    {
        if (bluePlayer.getScore() == redPlayer.getScore())
        {
            changeTurnInfoText(QString::fromStdString("Cats Game... Score is tied... Nobody wins... Click Start Game to play again."));
            return;
        }
        else if (bluePlayer.getScore() > redPlayer.getScore())
        {
            changeTurnInfoText(QString::fromStdString("Blue Player Wins! Click Start Game to play again."));
            return;
        }
        else if (bluePlayer.getScore() < redPlayer.getScore())
        {
            changeTurnInfoText(QString::fromStdString("Red Player Wins! Click Start Game to play again."));
            return;
        }
    }

    //Game board is full and game mode is Simple
    else if (gameBoard.boardFull() && gameBoard.getGameMode() == "Simple")
    {
        changeTurnInfoText(QString::fromStdString("Cats Game... Nobody wins... Click Start Game to play again."));
        return;
    }

    //Simple Game winner
    QString winner = QString::fromStdString(currentPlayer + " Player has Won!!! Click Start Game to play again.");

    changeTurnInfoText(winner);

}

//Handles a player turn
void MainWindow::handleHumanMove(int row, int col, QPushButton *targetButton)
{
    // Check if the selected cell is already occupied (Blue Player)
    if (gameBoard.isCellEmpty(row, col) && currentPlayer == "Blue")
    {
        // Update the game board with the player's move
        gameBoard.setBoardElement(row, col, bluePlayer.getPlayerLetter());

        // Update the visual representation in the UI
        QString buttonText(bluePlayer.getPlayerLetter());
        targetButton->setText(buttonText);
    }
    // Red Player
    else if (gameBoard.isCellEmpty(row, col) && currentPlayer == "Red")
    {
        gameBoard.setBoardElement(row, col, redPlayer.getPlayerLetter());

        QString buttonText(redPlayer.getPlayerLetter());
        targetButton->setText(buttonText);
    }

    // Move is in occupied space
    else
    {
        QString qStringErrorText = QString::fromStdString(currentPlayer
                                                          + "Player has made an invalid move. Try again.");
        changeTurnInfoText(qStringErrorText);
        //qDebug() << currentPlayer << " made an invalid move. Try again";
        return;
    }

    // Check for win conditions, e.g., after each move
    int sosCount = 0;
    if (gameBoard.checkForSOS(sosCount))
    {
        qDebug() << currentPlayer << " has scored!";
        qDebug() << "There are" << sosCount << "SOS's";
        //qDebug() << "The game Mode is " << gameBoard.getGameMode();
        //General game logic
        if (gameBoard.getGameMode() == "General")
        {
            if (currentPlayer == "Blue")
            {
                do
                {
                //qDebug() << "Player score before increment: " << bluePlayer.getScore();
                bluePlayer.incrementScore();
                ui->blueScoreSpinBox->setValue(bluePlayer.getScore());
                //qDebug() << "Player score after increment: " << bluePlayer.getScore();
                sosCount -= 1;
                }while (sosCount != 0);
            }
            else
            {
                do
                {
                redPlayer.incrementScore();
                ui->redScoreSpinBox->setValue(redPlayer.getScore());
                sosCount -= 1;
                }while (sosCount != 0);
            }
        }
        else
        {
            endGame();
            return;
        }

    }
    if (gameBoard.boardFull())
    {
        endGame();
        return;
    }

    // Switch to the next player's turn
    switchPlayerTurn();

    // If computer handle the computer turn
    if (currentPlayer == "Blue" && bluePlayer.getPlayertype() == "Computer")
    {
        handleComputerMove();
    }
    else if (currentPlayer == "Red" && redPlayer.getPlayertype() == "Computer")
    {
        handleComputerMove();
    }
}

//Handles a computer turn
void MainWindow::handleComputerMove()
{
    int row = -1, col = -1;
    //COMPUTER LOGIC MAGIC HERE
    if (currentPlayer == "Blue")
    {
        //Make the move
        gameBoard.computerMakeRandomMove(row, col);

        char newLetter = redPlayer.chooseRandomLetter();

        gameBoard.setBoardElement(row, col, newLetter);

        qDebug() << "Set element" << row << "," << col << "to" << newLetter;

        //Update the UI
        QLayoutItem *buttonItem = ui->gameBoardGridLayout->itemAtPosition(row, col);
        if (buttonItem)
        {
            //qDebug() << "Found button converting...";
            QPushButton *finalButton = qobject_cast<QPushButton *>(buttonItem->widget());
            QString buttonText(newLetter);
            finalButton->setText(buttonText);
            //qDebug() << "Should've placed a " << bluePlayer.getPlayerLetter() << " at " << row << ", " << col;
        }
    }
    else
    {
        gameBoard.computerMakeRandomMove(row, col);

        //qDebug() << "RANDOM MOVE WAS " << row << "," << col;

        char newLetter = redPlayer.chooseRandomLetter();

        gameBoard.setBoardElement(row, col, newLetter);

        qDebug() << "Set element" << row << "," << col << "to" << newLetter;

        //Update the UI
        QLayoutItem *buttonItem = ui->gameBoardGridLayout->itemAtPosition(row, col);
        if (buttonItem)
        {
            //qDebug() << "Found button converting...";
            QPushButton *finalButton = qobject_cast<QPushButton *>(buttonItem->widget());
            QString buttonText(newLetter);
            finalButton->setText(buttonText);
            //qDebug() << "Should've placed a " << redPlayer.getPlayerLetter() << " at " << row << ", " << col;
        }
    }

    // Check for win conditions, e.g., after each move
    int sosCount = 0;
    if (gameBoard.checkForSOS(sosCount))
    {
        //qDebug() << currentPlayer << " has scored!";
        //qDebug() << "The game Mode is " << gameBoard.getGameMode();
        //General game logic
        if (gameBoard.getGameMode() == "General")
        {
            if (currentPlayer == "Blue")
            {
                do
                {
                //qDebug() << "Player score before increment: " << bluePlayer.getScore();
                bluePlayer.incrementScore();
                ui->blueScoreSpinBox->setValue(bluePlayer.getScore());
                //qDebug() << "Player score after increment: " << bluePlayer.getScore();
                sosCount -= 1;
                }while (sosCount != 0);
            }
            else
            {
                do
                {
                redPlayer.incrementScore();
                ui->redScoreSpinBox->setValue(redPlayer.getScore());
                sosCount -= 1;
                }while (sosCount != 0);
            }
        }
        else
        {
            endGame();
            return;
        }

    }
    if (gameBoard.boardFull())
    {
        endGame();
        return;
    }
    switchPlayerTurn();
}

//Add start game button back to ui
void MainWindow::addStartButtonBack()
{
    //Check for existing label
    QLabel *existingLabel = ui->centralwidget->findChild<QLabel *>("gameInfoLabel");

    if (existingLabel)
    {
        //qDebug() << "Found existing Label!";
        ui->infoLayout->removeWidget(existingLabel);
        delete existingLabel; //Remove the label and free memory
    }

    QPushButton *newStartGameButton = new QPushButton("Start New Game", this); //create new start game button
    newStartGameButton->setObjectName("startGameButton");
    newStartGameButton->setFixedSize(newStartGameButton->sizeHint()); //set size of new start game button to text size
    connect(newStartGameButton, &QPushButton::clicked, this, &MainWindow::on_startGameButton_clicked);
    ui->infoLayout->addWidget(newStartGameButton); //add button to game board layout
}


//DEBUG STUFF
//DEBUG BUTTON INFO (used to debug gameBoardGridLayout buttons)
void MainWindow::outputButtonsInfo()
{
    QLayoutItem *item;
    QPushButton *button;

    for (int row = 0; row < ui->gameBoardGridLayout->rowCount(); ++row)
    {
        for (int col = 0; col < ui->gameBoardGridLayout->columnCount(); ++col)
        {
            item = ui->gameBoardGridLayout->itemAtPosition(row, col);
            if (item)
            {
                // Check if the item is a QPushButton
                if ((qobject_cast<QPushButton *>(item->widget())) != nullptr)
                {
                qDebug() << "Button at (" << row << ", " << col << ")";
                }
            }
        }
    }
}


//SLOTS

//When the start game button is clicked (released)
void MainWindow::on_startGameButton_clicked()
{
    // Remove all game board buttons from game board
    QLayoutItem *item;
    while ((item = ui->gameBoardGridLayout->takeAt(0)) != nullptr)
    {
        delete item->widget(); // Delete the button
        delete item;           // Delete the layout item
    }

    qDebug() << "You pressed the Start button";
    outputButtonsInfo();

    currentPlayer = "Blue"; //Blue player starts
    bluePlayer.setScore(0); //Reset scores to 0
    redPlayer.setScore(0);
    ui->blueScoreSpinBox->setValue(bluePlayer.getScore());
    ui->redScoreSpinBox->setValue(redPlayer.getScore());

    //Old hiding
    //ui->startGameButton->hide();
    gameBoard.initializeBoard();
    populateGameBoard();

    outputButtonsInfo();

    //change gameMode to QString from String
    QString qStringGameMode = QString::fromStdString("You started a new "
                                                     + gameBoard.getGameMode()
                                                     + " Game!");
    changeGameInfoText(qStringGameMode);

    QString qStringTurnInfo = QString::fromStdString(currentPlayer
                                                     + " Players turn");
    changeTurnInfoText(qStringTurnInfo);

    //Hide game options
    ui->simpleGameRadioButton->setEnabled(false);
    ui->generalGameRadioButton->setEnabled(false);
    ui->boardSizeSpinBox->setEnabled(false);

    //Hide the score for a simple game
    if (gameBoard.getGameMode() == "Simple")
    {
        ui->blueScoreLabel->hide();
        ui->blueScoreSpinBox->hide();
        ui->redScoreLabel->hide();
        ui->redScoreSpinBox->hide();
    }

    if (bluePlayer.getPlayertype() == "Computer")
    {
        handleComputerMove();
        ui->blueLetterComboBox->hide();
    }

}

//When a change is made to the boardSize spinbox
void MainWindow::on_boardSizeSpinBox_valueChanged(int arg1)
{
    //Check board size before change
    qDebug() << "changing boardsize to " << arg1;

    gameBoard.setBoardSize(arg1);

    //Check board size after change
    qDebug() << "Board size is " << gameBoard.getBoardSize();
}

//When a button on the game board is clicked
void MainWindow::on_newButton_clicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());

    int row;
    int col;
    char letter;

    findButtonCell(clickedButton, row, col);

    handleHumanMove(row, col, clickedButton);

    //qDebug() << currentPlayer << " Player clicked " << row << ", " << col;

    //qDebug() << "The value at " << row << ", " << col
    //         << " is " << gameBoard.getBoardElement(row, col);

    //qDebug() << "The value at " << row << ", " << col
    //         << " is " << gameBoard.getBoardElement(row, col);

}

//When a gameMode is selected
void MainWindow::on_gameMode_selected()
{
    if (ui->simpleGameRadioButton->isChecked())
    {
        qDebug() << "Simple Game selected!";
        gameBoard.setGameMode("Simple");
        qDebug() << "gameMode is " << gameBoard.getGameMode();
    }
    else if (ui->generalGameRadioButton->isChecked())
    {
        qDebug() << "General Game selected!";
        gameBoard.setGameMode("General");
        qDebug() << "gameMode is " << gameBoard.getGameMode();
    }
}

//When the Blue player type combobox is activated
void MainWindow::on_bluePlayerComboBox_activated(int index)
{
    if (index == 0)
    {
        bluePlayer.setPlayertype("Human");
    }
    else if (index == 1)
    {
        bluePlayer.setPlayertype("Computer");
    }
    qDebug() << "Blue Player has changed to " << bluePlayer.getPlayertype();
}

//When the Red player type comobox is activated
void MainWindow::on_redPlayerComboBox_activated(int index)
{
    if (index == 0)
    {
        redPlayer.setPlayertype("Human");
    }
    else if (index == 1)
    {
        redPlayer.setPlayertype("Computer");
    }
    qDebug() << "Red Player has changed to " << redPlayer.getPlayertype();
}

//When the Blue player letter combobox is activated
void MainWindow::on_blueLetterComboBox_activated(int index)
{
    if (index == 0)
    {
        bluePlayer.setPlayerLetter('S');
    }
    else if (index == 1)
    {
        bluePlayer.setPlayerLetter('O');
    }
    qDebug() << "Blue Player has changed letter to " << bluePlayer.getPlayerLetter();
}

//When the Red player letter combobox is activated
void MainWindow::on_redLetterComboBox_activated(int index)
{
    if (index == 0)
    {
        redPlayer.setPlayerLetter('S');
    }
    else if (index == 1)
    {
        redPlayer.setPlayerLetter('O');
    }
    qDebug() << "Red Player has changed letter to " << redPlayer.getPlayerLetter();
}
