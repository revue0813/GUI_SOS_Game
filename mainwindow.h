#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include "board.h"
#include "player.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    string currentPlayer;
    Board gameBoard;
    Player bluePlayer;
    Player redPlayer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populateGameBoard();
    void findButtonCell(QPushButton *targetButton, int &row, int &column);
    void changeGameInfoText(const QString &gameInfoQString);
    void changeTurnInfoText(const QString &turnInfoQString);
    void switchPlayerTurn();
    void endGame();
    void handleHumanMove(int row, int col, QPushButton *targetButton);
    void handleComputerMove();
    void addStartButtonBack();
    void outputButtonsInfo();

    void saveBoardToJson(const Board &board);

    void loadBoardFromJson(Board &board);
    void updateGameBoardButtons();
    void removeSaveFile(const QString &filePath);
private slots:
    void on_startGameButton_clicked();
    void on_boardSizeSpinBox_valueChanged(int arg1);
    void on_newButton_clicked();
    void on_gameMode_selected();
    void on_bluePlayerComboBox_activated(int index);
    void on_redPlayerComboBox_activated(int index);
    void on_blueLetterComboBox_activated(int index);
    void on_redLetterComboBox_activated(int index);
    void on_saveGameButton_clicked();
    void on_loadGameButton_clicked();
};
#endif // MAINWINDOW_H
