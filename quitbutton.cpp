#include "quitbutton.h"

QuitButton::QuitButton(QWidget* parent) :
    QWidget(parent),

    quitButton(new QPushButton(this))

{
    quitButton->setText("Quit Game");
    quitButton->setMinimumSize(250,90);
    quitButton->setFont(QFont("Ubuntu", 26, 70));
    quitButton->setObjectName("quitButton");
    setStyleSheet(" border-image: url(:/pics/Pictures/cool-red2.png)");

    QObject::connect(this->quitButton, &QPushButton::clicked,
                     this,&QuitButton::on_quit_clicked);
}


void QuitButton::on_quit_clicked()
{
    emit quit();

}
