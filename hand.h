#ifndef HAND_H
#define HAND_H

#include <QObject>
#include <vector>
#include "card.h"

class Hand: public QObject
{
    Q_OBJECT
private:
    int aceCount;


    std::vector<Card> cards;
    bool isSoft();

public:
    /**
     * @brief Constructs a Hand, setting the ace count to 0.
     */
    Hand();

    /**
     * @brief Constructs a Hand with two initial cards.
     */
    Hand(Card, Card);

    /**
     * @brief Hand copy constructor.
     * @param Hand to copy.
     */
    Hand(const Hand& rhs);

    /**
     * @brief Hand copy equals operator.
     * @param Hand to copy.
     * @return
     */
    Hand & operator=(Hand rhs);

    /**
     * @brief Adds a card to the hand.
     */
    void addCard(Card);

    /**
     * @brief Removes card at the specified index.
     */
    void removeCard(int);

    /**
     * @brief Returns the card at the specified index.
     * @return The card at the index.
     */
    Card getCard(int);

    /**
     * @brief Returns the blackjack value of the hand.
     * @return Hand value.
     */
    int calculateValue();

    /**
     * @brief Returns the value of the dealer's face-up card.
     * @return Value of dealer's face-up card.
     */
    int getDealerValue();

    /**
     * @brief Based on the hand, determines which answer key
     * chart to use.
     * @return 2 for split, 1 for soft total, 0 for hard total.
     */
    int getChart();

    /**
     * @brief Clears the hand.
     */
    void clear();

    /**
     * @brief Returns whether or not the hand contains an ace.
     * @return true if the hand has an ace.
     */
    bool hasAce();

};

#endif // HAND_H
