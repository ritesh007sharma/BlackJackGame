#ifndef ANSWERKEY_H
#define ANSWERKEY_H

#include "deck.h"
#include "hand.h"
#include "card.h"
#include "playeroptions.h"
#include <QObject>

/**
 * Repersents a Deck of cards, ie all the cards that are curently
 * in a given deck.
 */
class AnswerKey: public QObject
{
  Q_OBJECT

private:
  /**
   * @brief Case if the player's hand contains no aces (hard total).
   * Returns true if the player should hit, otherwise returns false.
   * @param playerHand
   * @param dealerHand
   * @return true if the player should hit, otherwise false.
   */
  bool shouldHitHardTotal(Hand playerHand, Hand dealerHand);

  /**
   * @brief Case if the player's hand contains an ace (soft total)
   * Returns true if the player should hit, otherwise returns false.
   * @param playerHand
   * @param dealerHand
   * @return true if the player should hit, otherwise false.
   */
  bool shouldHitSoftTotal(Hand playerHand, Hand dealerHand);

  /**
   * @brief Case if the player's hand can split.
   * Returns true if the player should split, otherwise false.
   * @param playerHand
   * @param dealerHand
   * @return true if the player should split, otherwise false.
   */
  bool shouldSplit(Hand playerHand, Hand dealerHand);

public:
  AnswerKey();

  /**
   * @brief Returns player's best decision based on the player's hand
   * and the dealer's upcard.
   *
   * @param playerHand
   * @param dealerHand
   * @param indicates whether the player can split, has a soft total, or hard total.
   * @return The player's best decision.
   */
  PlayerOptions getAnswer(Hand playerHand, Hand dealerHand, int option);
};

#endif
