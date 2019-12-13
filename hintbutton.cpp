#include "hintbutton.h"

HintButton::HintButton(QWidget* parent):
    QWidget(parent),
    hintButton(new QPushButton(this))

{
    setStyleSheet("QWidget { border-image: url(:/pics/orangebutton); }");
    hintButton->setText("Get Hint");
    hintButton->setFont(QFont("Ubuntu", 22, 70));
    hintButton->setMinimumSize(150,60);

    QObject::connect(this->hintButton, &QPushButton::clicked,
                 this,&HintButton::hintClicked);
}

void HintButton::hintClicked()
{
    emit hint();
}
