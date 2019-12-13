#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "deck.h"
#include "hand.h"
#include "card.h"

class player: public QObject
{
    Q_OBJECT
private:
    /**
     * The player's hand.
     */
    Hand hand;

    /**
     * The player's other hand upon splitting.
     */
    Hand handSplit;

public:
    player();

    /**
     * @brief Adds a car to the player's hand.
     * @param card
     */
    void hit(Card card, bool);

    /**
     * @brief Splits the player's hand, removing the
     * second card from the first hand and adding it
     * to the player's split hand.
     */
    void splitting();

    /**
     * @brief Clears the hand.
     */
    void reset();

    /**
     * @brief The player's hand value.
     * @return the player's hand value.
     */
    int handValue(bool);

    /**
     * @brief Returns the player's hand.
     * @return the player's hand.
     */
    Hand getHand();

    /**
     * @return the split hand.
     */
    Hand getSplitHand();
};

#endif // PLAYER_H
