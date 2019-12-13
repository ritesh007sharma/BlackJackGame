#include "gamebuttons.h"

GameButtons::GameButtons(QWidget* parent):
    QWidget(parent),
    hitButton(new QPushButton(this)),
    stayButton(new QPushButton(this)),
    splitButton(new QPushButton(this))

{
    displaySetUp();

    QObject::connect(this->hitButton,&QPushButton::clicked,
                     this,&GameButtons::hitButton_clicked);
    QObject::connect(this->stayButton,&QPushButton::clicked,
                     this,&GameButtons::stayButton_clicked);
    QObject::connect(this->splitButton,&QPushButton::clicked,
                     this,&GameButtons::splitButton_clicked);
}

void GameButtons::displaySetUp(){
    QFont font("Ubuntu", 22, 70);
    hitButton->setFont(font);
    stayButton->setFont(font);
    splitButton->setFont(font);
    hitButton->setText("HIT");
    stayButton->setText("STAY");
    splitButton->setText("SPLIT");

    hitButton->setMinimumSize(150,60);
    stayButton->setMinimumSize(150,60);
    splitButton->setMinimumSize(150,60);

    hitButton->move(0,20);
    stayButton->move(160,20);
    splitButton->move(320,20);
}

void GameButtons::hitButton_clicked()
{
    emit hitMove();
}

void GameButtons::stayButton_clicked()
{
    emit stayMove();
}

void GameButtons::splitButton_clicked()
{

    emit splitMove();
}

void GameButtons::disable()
{
    hitButton->setDisabled(true);
    splitButton->setDisabled(true);
    stayButton->setDisabled(true);
}

void GameButtons::enableButtonsTutorial(int button){
    disable();

    if(button==0){
        hitButton->setEnabled(true);
        splitButton->setEnabled(false);
        stayButton->setEnabled(false);

        hitButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-blue2.png);");
        splitButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
        stayButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");


    }else if(button==1){
        hitButton->setEnabled(false);
        stayButton->setEnabled(true);
        splitButton->setEnabled(false);

        stayButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-blue2.png);");
        splitButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
        hitButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");


    }else{
        hitButton->setEnabled(false);
        stayButton->setEnabled(false);
        splitButton->setEnabled(true);

        hitButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
        stayButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
        splitButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-blue2.png);");
    }
}
