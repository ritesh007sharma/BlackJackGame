#ifndef HANDVIEW_H
#define HANDVIEW_H

#include <QWidget>
#include <QLabel>
#include "card.h"
#include "gamebuttons.h"
#include "quitbutton.h"
#include "hintbutton.h"
#include "playeroptions.h"
#include "cardlabel.h"
#include <QQueue>

class HandView: public QWidget
{
    Q_OBJECT
private:

    QLabel* playerScore;
    QLabel* currentScoreText;
    GameButtons* gameButtons;
    HintButton* hintButton;
    const int playerStartX;
    const int playerY;
    int currPlayerX;
    const int cardDimX;
    const int cardDimY;
    bool hasSplit;
    bool isRegularHand;

    void setup();

    QQueue<CardLabel*> playerCardLabels;

public:
    HandView(QWidget* parent);
    HandView(QLabel* card, bool regHand, QWidget* parent);
    int card1;
    int card2;
    std::vector<QLabel*> playerLabels;
    PlayerOptions recommended;
    QQueue<CardLabel*>& getPlayerCardLabels();
    void clear();
signals:
    void quitButtonPressed();
    void hit(bool isRegularHand); //passes a bool that is true if on original hand, false if on split
    void stay(bool isRegularHand); //passes bool (same as above)
    void split();
    void getHint(bool isRegularHand);
    // void sendCurrCardLabel(CardLabel* cardLabel);

    void buttonToEnable(int);

private slots:
    void sendHit();
    void sendStay();
    void sendSplit();
    void sendHint();

public slots:
    void playerHit(Card, bool, int handValue);
    void endTurn();
    //void reset();
    void enabledButtons(int);
};


#endif // HANDVIEW_H
