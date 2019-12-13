#include<cardlabel.h>

CardLabel::CardLabel(QLabel* _cardLabel, int _destX, int _destY) :
    cardLabel(_cardLabel),
    destX(_destX), destY(_destY)
{
}

CardLabel::~CardLabel() {
    delete cardLabel;
}

//CardLabel& CardLabel::operator=(const CardLabel &_cardLabel) {
//    cardLabel = _cardLabel.cardLabel;
//    // cardLabel->x = _cardLabel.x;
//}

int CardLabel::getDestX() {
    return destX;
}

int CardLabel::getDestY() {
    return destY;
}

QLabel* CardLabel::getCardLabelPointer() {
    return cardLabel;
}
