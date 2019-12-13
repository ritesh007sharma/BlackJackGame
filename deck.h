#ifndef DECK_H
#define DECK_H

#include <QObject>
#include "card.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * Repersents a Deck of cards, ie all the cards that are curently
 * in a given deck.
 */
class Deck: public QObject
{
    Q_OBJECT
private:
  /**
   * The vector that holds all the cards
   */
  std::vector<Card> cards;
  /**
    * Numnber of cards currenlty in the deck
    */
  int deckSize;

public:
  /**
   * Contructs a deck with a size value as multiples of
   * 52. EX: size = 1 makes a deck of 52 cards
   */
  Deck(int size);

  /**
   * Gets a random card from the deck
   */
  Card getCard();

  /**
   * Gets a scepfiied copy of a card from the deck
   */
  Card getCard(int);

  void reset();
};

#endif
