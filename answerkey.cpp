#include "answerkey.h"

AnswerKey::AnswerKey() {
}

PlayerOptions AnswerKey::getAnswer(Hand playerHand, Hand dealerHand, int option) {
  if (option == 3)
    return PlayerOptions::Yes;
  else if (option == 0)
    return shouldHitHardTotal(playerHand, dealerHand) ? PlayerOptions::Hit : PlayerOptions::Stand;
  else if (option == 2)
  {
      if(shouldSplit(playerHand, dealerHand))
          return PlayerOptions::Yes;
      else
          return shouldHitHardTotal(playerHand, dealerHand) ? PlayerOptions::Hit : PlayerOptions::Stand;
  }
  else
    return shouldHitSoftTotal(playerHand, dealerHand) ? PlayerOptions::Hit : PlayerOptions::Stand;



}

bool AnswerKey::shouldHitHardTotal(Hand playerHand, Hand dealerHand) {
  int playerHandValue = playerHand.calculateValue();
  int dealerUpCardValue = dealerHand.getDealerValue();
  if (playerHandValue <= 11) return true;
  else if (playerHandValue == 12) {
    return dealerUpCardValue <= 3 || 7 <= dealerUpCardValue;
  } else if (playerHandValue <= 16) {
    return dealerUpCardValue > 6;
  } else return false;
}

bool AnswerKey::shouldHitSoftTotal(Hand playerHand, Hand dealerHand) {
    int playerNonAceCardValue = playerHand.calculateValue() - 11;
    int dealerUpCardValue = dealerHand.getDealerValue();

    if (playerNonAceCardValue <= 6) return true;
    else if (playerNonAceCardValue == 7)
      return 9 <= dealerUpCardValue;
    else return false;
}

bool AnswerKey::shouldSplit(Hand playerHand, Hand dealerHand) {
    int playerSplitCardValue = playerHand.calculateValue() / 2;
    int dealerUpCardValue = dealerHand.getDealerValue();

    if (3 >= playerSplitCardValue)
      return 4 <= dealerUpCardValue && dealerUpCardValue <= 7;
    else if (playerSplitCardValue == 4 ||
             playerSplitCardValue == 5 ||
             playerSplitCardValue == 10 )
      return false;
    else if (playerSplitCardValue == 8 || playerHand.hasAce())
      return true;
    else {
      if (playerSplitCardValue == 6) return 3 <= dealerUpCardValue && dealerUpCardValue <= 6;
      else if (playerSplitCardValue == 7) return dealerUpCardValue <= 7;
      else if (playerSplitCardValue == 9) {
        return dealerUpCardValue < 10 && dealerUpCardValue != 7;
      }
    }
    return false;
}
