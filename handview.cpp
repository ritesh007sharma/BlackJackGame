#include "handview.h"

HandView::HandView(QWidget* parent):
    QWidget(parent),
    playerScore(new QLabel(this)),
    currentScoreText(new QLabel(this)),
    playerStartX(655),
    playerY(550),
    currPlayerX(playerStartX),
    cardDimX(105),
    cardDimY(200),
    hasSplit(false),
    isRegularHand(true),
    hintButton(new HintButton(this)),
    gameButtons(new GameButtons(this)),
    card1(0),
    card2(0)
{
    setup();
}

HandView::HandView(QLabel* card, bool regHand, QWidget* parent):
    QWidget(parent),
    playerScore(new QLabel(this)),
    currentScoreText(new QLabel(this)),
    playerStartX(50),
    playerY(550),
    currPlayerX(playerStartX),
    cardDimX(105),
    cardDimY(200),
    hasSplit(true),
    isRegularHand(regHand),
    hintButton(new HintButton(this)),
    gameButtons(new GameButtons(this))
{
    card->setParent(this);
    playerLabels.push_back(card);
    card->show();
    if(!isRegularHand){
        playerLabels[0]->move(currPlayerX-5, playerY-2);
    }
    else{
        playerLabels[0]->move(currPlayerX, playerY);
    }

    currPlayerX+= cardDimX;
    setup();
}


void HandView::setup()
{
    this->resize(1600, 900);
    currentScoreText->setFont(QFont("Ubuntu", 24));
    currentScoreText->setStyleSheet("color:white;");
    currentScoreText->move(playerStartX-10, playerY-60);
    currentScoreText->setText("Current Score");
    currentScoreText->resize(250, 60);
    playerScore->setFont(QFont("Ubuntu", 30));
    playerScore->setStyleSheet("color:white;");
    playerScore->move(playerStartX + 200, playerY-60);
    playerScore->setText("0");
    playerScore->resize(60, 60);

    if(hasSplit)
    {
        hintButton->move(playerStartX, playerY - 130);
        gameButtons->move(playerStartX, playerY + cardDimY);
    }
    else
    {
        hintButton->move(playerStartX + 23, playerY - 130);
        gameButtons->move(playerStartX -(136), playerY + cardDimY);
    }

    hintButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-blue2.png);");
    gameButtons->setStyleSheet("border-image: url(:/pics/Pictures/cool-blue2.png);");

    connect(hintButton, &HintButton::hint,
            this,&HandView::sendHint);
    connect(gameButtons, &GameButtons::stayMove,
            this, &HandView::sendStay);
    connect(gameButtons, &GameButtons::hitMove,
            this, &HandView::sendHit);
    connect(gameButtons, &GameButtons::splitMove,
            this, &HandView::sendSplit);

    connect(this, &HandView::buttonToEnable,
            gameButtons, &GameButtons::enableButtonsTutorial);
}

void HandView::sendHit()
{
    emit hit(isRegularHand);
}

void HandView::sendHint()
{
    emit getHint(isRegularHand);
}

void HandView::sendStay()
{
    emit stay(isRegularHand);
}
void HandView::sendSplit()
{
    if(!hasSplit && playerLabels.size() == 2)
        if ((card1 - 1) / 4 == (card2 - 1)/4)
            emit split();
}

void HandView::playerHit(Card card, bool regHand, int score)
{
    if(regHand != isRegularHand)
    {
        return;
    }
    if(card2 == 0){
        if(card1 == 0){
            card1 = card.getCardID();
        }
        else{
            card2 = card.getCardID();
        }
    }
    QLabel* label = new QLabel(this);
    label->move(-500, -500);
    label->setPixmap(card.cImage);
    playerCardLabels.enqueue(new CardLabel(label, currPlayerX, playerY));
    playerLabels.push_back(label);
    currPlayerX += cardDimX;
    playerScore->setText(QString::number(score));
    label->show();
}

QQueue<CardLabel*>& HandView::getPlayerCardLabels() {
    return playerCardLabels;
}

void HandView::clear()
{
    for(int i = 0; i < playerLabels.size(); i++)
    {
        QLabel* l = playerLabels[i];
        delete l;
    }

    playerLabels.clear();
    currPlayerX = playerStartX;
    playerScore->setText("0");
}

void HandView::endTurn()
{

    gameButtons->disable();
    gameButtons->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
    hintButton->setDisabled(true);
    hintButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");

}

void HandView::enabledButtons(int enable){
     emit buttonToEnable(enable);
    //disable hint button for all tutorial to disabled
     hintButton->setDisabled(true);
     hintButton->setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
}


