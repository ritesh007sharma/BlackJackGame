
#ifndef DEALER_H
#define DEALER_H

#include "deck.h"
#include "hand.h"
#include "card.h"
#include <QObject>
#include "hand.h"

/**
 * Repersents a Deck of cards, ie all the cards that are curently
 * in a given deck.
 */
class Dealer: public QObject
{
  Q_OBJECT

private:
  /**
  * The dealer's cards, one is faced up and the other is faced down.
  */
  //Card facedUp, facedDown;

  /**
  * The dealer's hand.
  */
  Hand hand;

public:
  Dealer();

  /**
   * Constructs a dealer object with two cards, where one will be faced up and
   * the other faced down.
   */
  Dealer(Hand _hand);

  /**
  * Gets the faced up card.
  */
//  Card getFacedUpCard();
//  /**
//   * Sets the dealers face up card;
//   */
//  void setFaceUpCard(Card card);

  /**
  * Gets the faced down card.
  */
//  Card getFacedDownCard();
//  /**
//   * Sets the face down card.
//   */
//  void setFaceDownCard(Card card);
  /**
  * Gets the dealer's hand.
  */
  Hand getHand();

  /**
  * Adds a card to the dealer's hand.
  */
  void hit(Card card);

  /**
  * Indicate if the dealer can hit based on his current hand.
  */
  bool canHit();

  /**
  * Assigns the dealer a new starting hand.
  */
  void assignNewHand(Hand newHand);

  void reset();

  int handValue();

};

#endif
