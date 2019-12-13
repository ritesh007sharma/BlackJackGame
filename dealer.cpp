#include "dealer.h"

Dealer::Dealer() {} ;

Dealer::Dealer(Hand _hand) : hand(_hand) {}

Hand Dealer::getHand() {
  return hand;
}

void Dealer::hit(Card card) {
  hand.addCard(card);
}

bool Dealer::canHit() {
  return hand.calculateValue() < 17;
}

void Dealer::assignNewHand(Hand newHand) {
  hand = newHand;
}

void Dealer::reset(){
    hand.clear();
}

int Dealer::handValue()
{
   return hand.calculateValue();
}
