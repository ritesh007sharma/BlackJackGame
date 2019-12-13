#include "card.h"

Card::Card(int cardValue)
{
  cardID=cardValue;
  int temp = cardValue++;
  std::string pathToCard = ":/Cards2/Cards2/c"+std::to_string(temp)+".png";

  cImage = QPixmap(QString::fromStdString(pathToCard)).scaled(100, 200);
}

Card::Card(const Card& rhs)
{
    cardID = rhs.cardID;
    cImage = rhs.cImage;
}

Card & Card::operator=(Card rhs)
{
    std::swap(cardID, rhs.cardID);
    std::swap(cImage, rhs.cImage);
    return *this;
}


 int Card::getCardID()
 {
   return cardID;
 }

