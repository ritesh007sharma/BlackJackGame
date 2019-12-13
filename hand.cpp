#include "hand.h"

Hand::Hand(): aceCount(0)
{
}

Hand::Hand(const Hand& rhs)
{
    aceCount =rhs.aceCount;
    cards = rhs.cards;
}

Hand & Hand::operator=(Hand rhs)
{
    std::swap(cards, rhs.cards);
    std::swap(aceCount, rhs.aceCount);
    return *this;
}

Hand::Hand(Card c1, Card c2):
    aceCount(0)
{
    cards.push_back(c1);
    cards.push_back(c2);
    if(c1.getCardID() > 47)
        aceCount++;
    if(c2.getCardID() > 47)
        aceCount++;
}

void Hand::addCard(Card hit)
{
    cards.push_back(hit);


    if(hit.getCardID() > 48)
    {
        aceCount++;
    }
}

int Hand::calculateValue()
{
    int aces = aceCount;
    int total = 0;
    for(Card c : cards)
    {
        if(c.getCardID() > 48)
        {
            total += 11;
        }
        else if(c.getCardID() > 32)
        {
            total += 10;
        }
        else
        {
            total += ((c.getCardID()-1) / 4) + 2;
        }
    }
    while(aces > 0 && total > 21)
    {
        total-= 10;
        aces--;
    }
    return total;
}

int Hand::getDealerValue()
{
    Card c = cards[0];
    if(c.getCardID() > 48)
    {
        return 11;
    }
    else if(c.getCardID() > 32)
    {
        return 10;
    }
    return ((c.getCardID()-1) / 4) + 2;
}

int Hand::getChart()
{
    if(aceCount > 0)
    {
        //if 2 aces, prevent the calculation from thinking the value is 12
        if(aceCount == 2 && cards.size() == 2) return 3;
        else if (isSoft()) return 1;
    }
    //return 2 for split chart
    if((cards[0].getCardID()-1)/4 == (cards[1].getCardID()-1)/4 && cards.size() == 2)
    {
        return 2;
    }
    return 0;
}

void Hand::clear()
{
    cards.clear();
    aceCount=0;
}

void Hand::removeCard(int index)
{
    cards.erase(cards.begin()+index);
}

Card Hand::getCard(int index)
{
    return cards[index];
}

bool Hand::hasAce() {
    return aceCount > 0;
}

bool Hand::isSoft()
{
    int aces = aceCount;
    int total = 0;
    for(Card c : cards)
    {
        if(c.getCardID() > 48)
        {
            total += 11;
        }
        else if(c.getCardID() > 32)
        {
            total += 10;
        }
        else
        {
            total += ((c.getCardID()-1) / 4) + 2;
        }
    }
    while(aces > 0 && total > 21)
    {
        total-= 10;
        aces--;
    }
    return aces != 0;
}
