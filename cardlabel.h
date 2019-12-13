#ifndef CARDLABEL_H
#define CARDLABEL_H
#include <QLabel>

class CardLabel: public QLabel {
  private:
    QLabel* cardLabel;
    int destX, destY;

  public:
    CardLabel(QLabel* _cardLabel, int _destX, int _destY);
    ~CardLabel();
//    CardLabel& operator = (const CardLabel &cardLabel);
    int getDestX();
    int getDestY();
    QLabel* getCardLabelPointer();
};

#endif // CARDLABEL_H
