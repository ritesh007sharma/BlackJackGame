#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "deck.h"
#include "dealer.h"
#include "player.h"
#include "card.h"
#include "answerkey.h"
#include "playeroptions.h"
#include <QTimer>
#include <QQueue>

class Tutorial: public QObject
{
    Q_OBJECT
private:

    bool splitOccured;
    int bustCount;
    int stayCount;

    QQueue<Card> playerHand;
    QQueue<Card> dealerHand;

    AnswerKey key;
    /**
     * lets the tutorial class know if it is in tutorial mode
     */
    int tutorialMode;
    /**
     * Player Object for interacting with the player within the game
     */
    player p1;

    /**
     * Dealer Object for interacting with the dealer
     */
    Dealer dl;

    /**
     * Deck object for keeping all the cards
     */
    Deck deck;

    /**
     * String to be displayed when user first starts the tutorial
     */
    QString welcome;

    /**
     * String that explains how you get the values from the cards in your hand
     */
    QString cardValues;

    /**
     * Explains how cards are dealt
     */
    QString turnExplan;

    /**
     * Explains what the different buttons do breifly
     */
    QString buttonOptions;

    QString queen;

    QString firstStay;
    QString Tutoriallevel2start;

    void generateFirstStay();



    void generateQueen();
    /**
     * Explains the overall rules of the game.
     */
    QString gameRules;

    /**
     * String displayed when a dealer busts.
     */
    QString dealerBustString;

    void generateDealerBust();
    /**
     * Makes the GameRules string
     */
    void generateGameRules();

    /**
     * Makes the turnExplan string
     */
    void generateTurnExplan();
    /**
     * Makes all the strings that will be used by the tutorial
     */
    void makeStrings();
    /**
     * makes the welcome string
     */
    void generateWelcome();
    /**
     * makes the cardValues string
     */
    void generateCardVals();

    /**
     * Deals the starting hand in the tutorial
     */
    void dealCards(int);

    /**
     * Makes the buttonOPtions
     */
    void generateButtonOPtions();


    /**
     * Deals the starting hands and updates the displayed hand values.
     */
    void dealStartingHand();

    /**
     * The dealer hits until it cannot, then a signal is emitted
     * indicating the outcome of the game.
     */
    void dealerTurn();


    void tutorialLevel1();
    void tutorialLevel2();
    void generateTutoriallevel2start();
    bool tutorialreset2;
    QString tutorialLevel2dealcards;
    void generateTutorialLevel2dealcards();
    QString tutorialLevel2dealerwins;
    void generateTutorialLevel2dealerwins();
    void tutorialLevel3();
    QString tutoriallevel3start;
    void generatetutoriallevel3start();
    QString tutoriallevel3dealcards;
    void generatetutoriallevel3dealcards();
    void tutorialLevel();
    QString tutorialLevel3split;
    void generateTutorialLevel3split();
    QString tutorialLevel3advice;
    void generatetutorialLevel3advice();
    QString tutorialLevel3playerbust;
    void generatetutorialLevel3playerbust();
    bool tutoriallevel3hit;
    QString tutorialLevel3dealerwins;
    void generatetutorialLevel3dealerwins();


    PlayerOptions getAnswer(bool);
    void setButtonsOnOrOff(int hand, QString buttonToEnable);


public:
    Tutorial();
signals:
    /**
     * sends the welcome string
     */
    void sendWelcome(QString);
    /**
     * Sends the card that needs to be displayed face up for the dealer
     */
    void dealFaceupDealer(Card,int);

    /**
     * Sends the card that needs to be displayed face down for the dealer
     */
    void dealFaceDownDealer(Card);

    /**
     * sends the cardValues string
     */
    void sendDealCards(QString);


    /**
     * sends the card that should be dealt to the player
     */
    void dealPlayerCard(Card, bool, int);
    /**
     * General signal for sending a string as a popup
     */
    void sendPopup(QString, bool);

    /**
     * Sends a signal to flip the dealer's card and to update the dealer's score.
     */
    void flipDealerCard(int);

    /**
     * Emits a signal to clear the hands and redeal cards.
     */
    void resetBoard();

    /**
     * Emits a signal to indicate a player has busted.
     */
    void playerBust(bool);

    /**
     * Emits a signal to indicate a dealer win.
     */
    void dealerWins();

    /**
     * Emits a signal to indicate a player win.
     */
    void playerWins();

    /**
     * Emits a signal to indicate a tie.
     */
    void tie();

    /**
     * Emits a signal to indicate a dealer bust.
     */
    void dealerBust();

    /**
     * Emits a signal to send a hint.
     */
    void sendHint(QString);

    void doubleBust();

    void sendRecommended(PlayerOptions, bool);

    void incrementScore(bool);

    /**
     * Sends signal of which buttons should be enabled in the view during tutorial mode
     */
    void enabledButtonsTutorial(int, QString);


public slots:

    /**
     * resets the deck
     */
    void internalReset();

    /**
     * Starts the tutorial sequnece when the tutiral buttonn is clicked
     */
    void tutorialButtonClicked();

    void split();

    /**
     * Slot for when the hit button is clicked
     */
    void hit(bool);

    /**
     * Slot for when the stay button is clicked.
     */
    void stay(bool);

    /**
     * Slot that resets the hands and redeals cards.
     */
    void resetRound();

    void resetRoundTutorial();

    /**
     * Slot that deals the cards.
     */
    void gameButtonPressed();
    /**
     * Slot for indicating the best possible move.
     */
    void hint(bool);
    void sendCardValues();
    void setTutorialLvl();
    void sendPopUpsWithDelayTutorial1();
    void sendPopUpsWithDelayTutorial2();
    void sendPopUpsWithDelayTutorial3();

};

#endif // TUTORIAL_H
