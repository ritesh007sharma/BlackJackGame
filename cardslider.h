#ifndef CARDSLIDER_H
#define CARDSLIDER_H
    \
#include<QObject>
#include<Box2D/Box2D.h>
#include "math.h"

/**
 * Repersents a Deck of cards, ie all the cards that are curently
 * in a given deck.
 */
class CardSlider: public QObject
{
    Q_OBJECT

private:
  float x,y;
  int startX, startY;
  int cardWidth, cardHeight;
  int deckX, deckY;
  bool velXinitialSign, velYinitialSign;
  b2World* world;
  b2Body* body;

  double const SPEED_SCALE_FACTOR = 10;

  float acceleration(float veloicty, float distance);
  bool hasZeroVelocity(float velX, float velY);

signals:
  void sendCardPos(int newX, int newY);
  void stopTimer();

public:
  CardSlider(int _cardWidth, int _cardHeight);
  ~CardSlider();

  public slots:
  void moveCard();
  void setStartingPos(int startX, int startY, int deckX, int deckY);
  void resetWorld();
};

#endif
