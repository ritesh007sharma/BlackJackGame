#include "player.h"

player::player()
{
}
void player::hit(Card c, bool notSplitHand)
{
    if(notSplitHand)
    {
        hand.addCard(c);
    }else
    {
        handSplit.addCard(c);
    }
}

void player::splitting()
{
    //adding the second card to the seperate hand
    handSplit.addCard(hand.getCard(1));
    //removing the second card from the original hand
    hand.removeCard(1);
}
void player::reset()
{
    hand.clear();
    handSplit.clear();
}
int player::handValue(bool whichHand)
{
    if(whichHand)
    {
        return hand.calculateValue();
    }else
    {
        return handSplit.calculateValue();
    }
}
Hand player::getHand() {
  return hand;
}

Hand player::getSplitHand() {
  return handSplit;
}
