#ifndef CARD_H
#define CARD_H

#include <QLabel>
#include <QPixmap>
#include <string>


/**
 *Card class repersents an indivdual playing card
 *from the standard 52 card deck.
 */
class Card: public QLabel
{
  Q_OBJECT

private:
  /**
   *Repersents the value of the card encoded as an int
   * Where 0-51 is the possible values
   */
  int cardID;


public:
    /**
     *Contrsocts are card object with a given int value
     * as the card value
     */
//    Card();
    Card(int cardValue);
    QPixmap cImage;
    Card(const Card& rhs);
    Card & operator=(Card rhs);

    /**
     * Getter for returning the value of the card
     */
    int getCardID();
};
#endif
