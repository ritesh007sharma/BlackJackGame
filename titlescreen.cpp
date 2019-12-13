#include "titlescreen.h"

TitleScreen::TitleScreen(QWidget* parent):
    QWidget(parent, Qt::FramelessWindowHint),
    //instatiating the buttons
    gameButton(new QPushButton(this)),
    tutorialButton(new QPushButton(this))
{    
    displaySetUp();
    QObject::connect(this -> gameButton, &QPushButton::clicked,
                     this, &TitleScreen::on_start_GameButton_clicked);
    QObject::connect(this -> tutorialButton, &QPushButton::clicked,
                     this, &TitleScreen::on_tutorialButton_clicked);
}

void TitleScreen::displaySetUp(){
    QFont font("Ubuntu", 30, 70);
    this->setStyleSheet("background-image: url(:/Backgrounds/Pictures/sb4.0.png);");
    //sets the text
    gameButton->setText("Start Game");
    tutorialButton->setText("Tutorial");
    gameButton->setFont(font);
    tutorialButton->setFont(font);
    gameButton->setMinimumSize(300,120);
    tutorialButton->setMinimumSize(300,120);

    //organizes them on the screen
    gameButton->move(300,700);
    tutorialButton->move(900, 700);

    setStyleSheet("QPushButton { border-image: url(:/pics/Pictures/cool-blue2.png); }");
}

void TitleScreen::on_start_GameButton_clicked(){

    emit startGameButtonClicked();
}

void TitleScreen::on_tutorialButton_clicked(){
    emit tutorialButtonClicked();
}
