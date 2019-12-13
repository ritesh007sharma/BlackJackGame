#include "scorelabel.h"

ScoreLabel::ScoreLabel(QWidget* parent):
    QWidget(parent),
    wins(new QLCDNumber(this)),
    losses(new QLCDNumber(this)),
    winText(new QLabel(this)),
    lossText(new QLabel(this))
{
    wins->resize(120, 130);
    losses->resize(120, 130);
    wins->setDigitCount(2);
    losses->setDigitCount(2);
    winText->resize(120, 60);
    lossText->resize(120, 60);
    winText->setText("Wins");
    lossText->setText("Losses");
    QFont font("Ubuntu", 30, 30);
    winText->setFont(font);
    lossText->setFont(font);
    wins->move(0, 60);
    losses->move(120, 60);
    lossText->move(120, 0);
    this->setStyleSheet("background-color:white;");
}

void ScoreLabel::incrementWins()
{
    wins->display(wins->intValue() + 1);
}

void ScoreLabel::incrementLosses()
{
    losses->display(losses->intValue() + 1);
}
