#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QStackedWidget>
#include "ui_mainwindow.h"
#include "gameview.h"
#include "deck.h"
#include "tutorial.h"
#include "titlescreen.h"
#include "quitbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TitleScreen* titleScreen;
    GameView* gameView;
    Tutorial* tutorial;

    void displaySetUp();



//    /**
//     * Starts the game in game mode
//     */
//    void GameMode();
//    /**
//     * Starts the tutorial of the game
//     */
//    void TutorialMode();
    void ToGameScreen();
    void ToTitleScreen();
    QGridLayout* layout;
    QStackedWidget* stackedWidget;


};
#endif // MAINWINDOW_H
