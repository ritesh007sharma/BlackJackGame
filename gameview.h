#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "deck.h"
#include "gamebuttons.h"
#include "quitbutton.h"
#include "hintbutton.h"
#include "handview.h"
#include "playeroptions.h"
#include <cardslider.h>
#include <cardlabel.h>
#include "scorelabel.h"
#include "togglebutton.h"

#include <QMessageBox>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <qdebug.h>
#include <QGridLayout>
#include <QTimer>
#include <QQueue>

class GameView: public QWidget
{
    Q_OBJECT

private:
    void displaySetUp();

    QuitButton* quitButton;
    QLabel* dealerScore;
    QLabel* dealerScoreText;
    QPixmap cardBack;
    Card hidden;
    HandView* playerHand;
    HandView* splitHand;
    bool hasSplit;
    int bustCount;
    const int dealerY;
    const int dealerStartX;
    int currDealerX;
    const int cardDimX;
    const int cardDimY;
    const int deckX;
    const int deckY;
    std::vector<QLabel*> dealerLabels;
    QQueue<CardLabel*> dealerCardLabels;
    bool dealing;

    QTimer* timer;
    CardSlider* slider;
    QQueue<CardLabel*> splitCardLabels;
    QQueue<CardLabel*> cardDealOrder;
    QLabel* currentCardLabel;
    void moveCard(CardLabel* cardLabel, bool dealToSplitHand);
    void dealNextCard();
    void addCardLabelToDealQueue(CardLabel* cardLabel);
    void addCardsInOrder();


    ScoreLabel* scoreLabel;
    ToggleButton* toggle;
    bool canRecommend;
    void waitForDealAnimation();

    void resetHandView();
    void splitHandView();
    void connectButtons(HandView*);
    bool genericYesNoMessage(QString message);
    bool isCorrectDecision(PlayerOptions, bool);

public:
    GameView(QWidget* parent);

signals:
    void quitButtonPressed();
    void hit(bool isRegularHand); //passes a bool that is true if on original hand, false if on split
    void stay(bool isRegularHand); //passes bool (same as above)
    void split();
    void getHint(bool);
    void resetGame();
    void resetTutorialSignal();
    void handHit(Card, bool, int);
    void disableToggle(bool);
    void flipToggle(bool);


private slots:
    void SendQuit();
    void quitMessage();

public slots:
    void sendHit(bool);
    void sendStay(bool);
    void sendSplit();
    void sendHint(bool);
    void displayMessage(QString, bool);
    void tieGame();
    void faceUpDealer(Card, int handValue);
    void playerHit(Card, bool, int handValue);
    void flipDealerCard(int handValue);
    void faceDownDealer(Card);
    void playerBust(bool);
    void doubleBust();
    void dealerWins();
    void dealerBust();
    void playerWins();
    void reset();
    void incrementWinLoss(bool);
    void resetTutorial();

    void resetTutorialSeqeunce();

    void getRecommended(PlayerOptions, bool);

    void updateCardPos(int newX, int newY);
    void stopTimer();

    void setAllowRecommendations();
    void disableRec();
    void enableRec();

    /**
     *For enabling/diabling buttons while in tutorial mode.
     */
    void enabledButtons(int hand, QString enable);
    void dealCards();


//    void updateCardPos(int newX, int newY);
//    void stopTimer();
};

#endif // GAMEVIEW_H
