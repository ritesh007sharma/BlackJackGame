#include "deck.h"

Deck::Deck(int size)
{
  deckSize = 52*size;
  for (size_t i = 0; i < 52*size; i++)
  {
    cards.push_back(Card(i%52 + 1));
  }

  srand(time(nullptr)+(getpid()));
}

Card Deck::getCard()
{
  int random = rand()%deckSize;
  Card cardToReturn = cards[random];

  cards.erase(cards.begin()+random);
  deckSize--;
  return cardToReturn;
}

Card Deck::getCard(int cardVal)
{
    return Card(cardVal);
}

void Deck::reset()
{
    cards.clear();
    for (size_t i = 0; i < deckSize; i++)
    {
      cards.push_back(Card(i%52+1));
    }

    srand(time(nullptr)+(getpid()));
}
