#include "gameview.h"

GameView::GameView(QWidget* parent):
    QWidget(parent),
    quitButton(new QuitButton(this)),
    dealerScore(new QLabel(this)),
    dealerScoreText(new QLabel(this)),
    cardBack(QPixmap(":/Cards2/Cards2/cardBack.png").scaled(100, 200)),
    hidden(1),
    playerHand(new HandView(this)),
    splitHand(nullptr),
    hasSplit(false),
    bustCount(0),
    dealerY(100),
    dealerStartX(648),
    currDealerX(dealerStartX),
    dealing(true),
    cardDimX(105),
    cardDimY(200),
    deckX(450),
    deckY(250),
    scoreLabel(new ScoreLabel(this)),
    toggle(new ToggleButton(this)),
    canRecommend(true)
{
    this->resize(1600, 900);
    setObjectName("gameview");
    scoreLabel->move(1275, 200);
    displaySetUp();
    slider = new CardSlider(cardDimX, cardDimY);

    connect(quitButton, &QuitButton::quit,
            this, &GameView::quitMessage);
    connect(toggle, &ToggleButton::pressed,
            this, &GameView::setAllowRecommendations);
    connect(this,&GameView::disableToggle,
            toggle,&ToggleButton::disable);
    connect(this,&GameView::flipToggle,
            toggle, &ToggleButton::nonButtonToggle);

    timer = new QTimer();
    connect(timer, &QTimer::timeout,
            slider, &CardSlider::moveCard);
    connect(slider, &CardSlider::sendCardPos,
            this, &GameView::updateCardPos);
    connect(slider, &CardSlider::stopTimer,
            this, &GameView::stopTimer);
}

void GameView::dealCards() {
    addCardsInOrder();
    dealNextCard();
}

void GameView::addCardsInOrder() {
    QQueue<CardLabel*> &playerCardLabels = playerHand->getPlayerCardLabels();

    for (int i = 0; !playerCardLabels.isEmpty() || !dealerCardLabels.isEmpty(); i++) {
        if (i % 2 == 0 && !playerCardLabels.isEmpty()) {
            addCardLabelToDealQueue(playerCardLabels.dequeue());
        } else if (i % 2 != 0 && !dealerCardLabels.isEmpty()) {
            addCardLabelToDealQueue(dealerCardLabels.dequeue());
        }
    }
    if (splitHand != nullptr) {
        QQueue<CardLabel*> &splitCardLabelsFromHand = splitHand->getPlayerCardLabels();
        while (!splitCardLabelsFromHand.isEmpty()){
            splitCardLabels.enqueue(splitCardLabelsFromHand.dequeue());
        }
    }
}

void GameView::displaySetUp(){
    quitButton->move(0, 0);
    dealerScoreText->setFont(QFont("Ubuntu", 24));
    dealerScoreText->setStyleSheet("color:white;");
    dealerScoreText->move(dealerStartX-10, dealerY-60);
    dealerScoreText->setText("Current Score");
    dealerScoreText->resize(250, 60);
    dealerScore->setFont(QFont("Ubuntu", 30));
    dealerScore->setStyleSheet("color:white;");
    dealerScore->move(dealerStartX + 200, dealerY - 60);
    dealerScore->setText("0");
    dealerScore->resize(60, 60);
    dealerScore->raise();
    dealerScore->show();

    //shown deck
    QLabel* label = new QLabel(this);
    label->setPixmap(cardBack);
    label->move(deckX,deckY);
}

void GameView::addCardLabelToDealQueue(CardLabel* cardLabel) {
    cardDealOrder.enqueue(cardLabel);
}

void GameView::moveCard(CardLabel* cardLabel, bool dealToSplitHand) {
    timer->stop();
    // Place card at Deck starting position
    currentCardLabel = cardLabel->getCardLabelPointer();

    int destX = cardLabel->getDestX();
    int destY = cardLabel->getDestY();
    currentCardLabel->setParent(this);
    currentCardLabel->raise();
    currentCardLabel->show();
    if (dealToSplitHand) {
        currentCardLabel->move(deckX, deckY);
        slider->setStartingPos(destX + 800, destY, deckX, deckY);
    }
    else {
        currentCardLabel->move(deckX, deckY);
        slider->setStartingPos(destX, destY, deckX, deckY);
    }

    timer->setInterval(17);
    timer->start();
}

void GameView::updateCardPos(int newX, int newY) {
    currentCardLabel->move(newX, newY);
}

void GameView::stopTimer() {
    timer->stop();
    dealNextCard();
}

void GameView::dealNextCard() {
    if (!cardDealOrder.isEmpty()) {
        CardLabel* nextCard = cardDealOrder.dequeue();
        moveCard(nextCard, false);
    } else if (!splitCardLabels.isEmpty()) {
        CardLabel* nextCard = splitCardLabels.dequeue();
        moveCard(nextCard, true);
    }
}

void GameView::quitMessage()
{
    emit displayMessage(QString("Would you like to quit?"),false);

    connect(quitButton, &QuitButton::quit,
            this, &GameView::SendQuit);
}

//sends to main window to quit the game
void GameView::SendQuit()
{
    emit quitButtonPressed();
}

void GameView::flipDealerCard(int score)
{
    dealerScore->setText(QString::number(score));
    dealerLabels[1]->setPixmap(hidden.cImage);
}
void GameView::resetTutorial()
{
    slider->resetWorld();
    dealing = true;
    timer->stop();

    //splitHand = nullptr;
    for(QLabel* l : dealerLabels){
        delete l;
    }
    resetHandView();
    quitButton->raise();
    toggle->raise();
    dealerLabels.clear();
    cardDealOrder.clear();
    dealerCardLabels.clear();
    playerHand->getPlayerCardLabels().clear();
    currDealerX = dealerStartX;
    dealerScore->setText("0");
    emit resetTutorialSignal();

    dealCards();
    dealing = false;
}
void GameView::reset()
{
    slider->resetWorld();
    dealing = true;
    timer->stop();
    for(QLabel* l : dealerLabels){
        delete l;
    }
    resetHandView();
    quitButton->raise();
    toggle->raise();
    dealerLabels.clear();
    cardDealOrder.clear();
    dealerCardLabels.clear();
    playerHand->getPlayerCardLabels().clear();

    currDealerX = dealerStartX;
    dealerScore->setText("0");
    emit resetGame();

    dealCards();
    dealing = false;

}
void GameView::resetTutorialSeqeunce()
{

    slider->resetWorld();
    dealing = true;
    timer->stop();

    //splitHand = nullptr;
    for(QLabel* l : dealerLabels){
        delete l;
    }
    resetHandView();
    quitButton->raise();
    toggle->raise();
    dealerLabels.clear();
    cardDealOrder.clear();
    dealerCardLabels.clear();
    playerHand->getPlayerCardLabels().clear();
    currDealerX = dealerStartX;
    dealerScore->setText("0");
    emit resetTutorialSignal();
    //emit resetGame();
    dealCards();
    dealing = false;
}


void GameView::playerHit(Card card, bool isRegularHand, int score)
{
    emit handHit(card, isRegularHand, score);
    if (!timer->isActive()) {

        if (!dealing){
            dealCards();
        }
    }
    else{

        if(splitHand && !splitHand->getPlayerCardLabels().isEmpty()){
            //cardDealOrder.enqueue(splitHand->getPlayerCardLabels().dequeue());
            splitCardLabels.enqueue(splitHand->getPlayerCardLabels().dequeue());
        }
    }
}

void GameView::faceUpDealer(Card card, int value)
{
    QLabel* label = new QLabel(this);
    label->move(-500, 500);
    label->setPixmap(card.cImage);
    // label->move(currDealerX, dealerY);
    dealerCardLabels.enqueue(new CardLabel(label, currDealerX, dealerY));


    if (!timer->isActive()) {
        if (!dealing) dealCards();
    }
    else {
        cardDealOrder.enqueue(dealerCardLabels.dequeue());
    }

    currDealerX += cardDimX;
    dealerScore->setText(QString::number(value));
    dealerLabels.push_back(label);
    label->show();
}

void GameView::faceDownDealer(Card card)
{
    QLabel* label = new QLabel(this);
    label->setPixmap(cardBack);
    label->move(-500, -500);
    // label->move(currDealerX, dealerY);
    dealerCardLabels.enqueue(new CardLabel(label, currDealerX, dealerY));

    hidden = card;
    currDealerX += cardDimX;
    dealerLabels.push_back(label);
    label->show();
}

void GameView::sendHit(bool mainHand)
{
    if(timer->isActive()){
        return;
    }

    if(!isCorrectDecision(PlayerOptions::Hit, mainHand) && canRecommend)
        if(!genericYesNoMessage("You chose to hit, but this is not the optimal choice.\nWould you like to continue?"))
            return;
    emit hit(mainHand);
}

void GameView::sendStay(bool mainHand)
{
    if(timer->isActive()){
        return;
    }
    if(!isCorrectDecision(PlayerOptions::Stand, mainHand) && canRecommend)
    {
        if(!genericYesNoMessage("You chose to stay, but this is not the optimal choice."
                                "\nWould you like to continue?"))
        {
            return;
        }
    }
    if(mainHand)
        playerHand->endTurn();
    else
        splitHand->endTurn();
    emit stay(mainHand);
}
void GameView::sendSplit()
{
    if (!timer->isActive()) {
        if(!isCorrectDecision(PlayerOptions::Yes, true) && canRecommend)
            if(!genericYesNoMessage("You chose to split, but this is not the optimal choice.\nWould you like to continue?"))
                return;
        QLabel* first = new QLabel();
        QLabel* second = new QLabel();
        first->setPixmap(*playerHand->playerLabels[0]->pixmap());
        second->setPixmap(*playerHand->playerLabels[1]->pixmap());

        HandView* temp = new HandView(first, true, this);
        splitHand = new HandView(second, false, this);
        splitHand->move(800, 0);
        playerHand->clear();
        delete playerHand;
        playerHand = temp;
        playerHand->raise();
        playerHand->show();
        splitHand->show();
        splitHand->raise();
        toggle->raise();
        hasSplit=true;
        connectButtons(splitHand);
        connectButtons(playerHand);
        quitButton->raise();
        emit split();
    }
}

void GameView::sendHint(bool mainHand)
{
    emit getHint(mainHand);
}

void GameView::playerBust(bool hand)
{
    scoreLabel->incrementLosses();
    if(hasSplit)
    {
        if(hand)
        {
            playerHand->endTurn();
            displayMessage("Your left hand busted!",true);

        }else
        {
            splitHand->endTurn();
            displayMessage("Your Right hand busted!", true);
        }
    }else
    {
        playerHand->endTurn();
        displayMessage("You busted!",true);

        reset();
    }
}
void GameView::doubleBust()
{
    scoreLabel->incrementLosses();
    playerHand->endTurn();
    if(splitHand)
    {
        splitHand->endTurn();
    }
    displayMessage("You busted!",true);

    reset();
}

void GameView::dealerWins()
{
    scoreLabel->incrementLosses();
    displayMessage("You Lost!", true);

    reset();
}

void GameView::dealerBust()
{
    scoreLabel->incrementWins();
    displayMessage("You Won!", true);

    reset();
}

void GameView::playerWins()
{
    scoreLabel->incrementWins();
    displayMessage("You Won!", true);

    reset();
}


void GameView::tieGame()
{
    displayMessage("Tie!", true);

    reset();
}

bool GameView::genericYesNoMessage(QString message)
{
    QMessageBox msg;
    msg.setMinimumSize(200,200);
    msg.setModal(true);
    msg.setText(message);

    QPushButton* yesButton= msg.addButton(tr("Yes"),QMessageBox::AcceptRole);
    QPushButton* noButton= msg.addButton(tr("No"),QMessageBox::RejectRole);
    msg.exec();
    return msg.clickedButton() == yesButton;
}

void GameView::displayMessage(QString message, bool hint)
{
    QMessageBox msg;
    msg.setMinimumSize(200,200);
    msg.setModal(true);
    msg.setText(message);
    if(hint)
    {
        msg.addButton(tr("Okay"),QMessageBox::AcceptRole);
        msg.exec();
    } else
    {
        QPushButton* yesButton= msg.addButton(tr("Yes"),QMessageBox::AcceptRole);
        QPushButton* noButton= msg.addButton(tr("No"),QMessageBox::RejectRole);
        msg.exec();
        if(msg.clickedButton()==yesButton)
        {
            //reset();
            SendQuit();
        }
        if(msg.clickedButton()==noButton)
        {
            msg.close();
            //SendQuit();
        }
    }
}

void GameView::resetHandView()
{
    if(playerHand)
        playerHand->clear();
    delete playerHand;
    if(splitHand)
        splitHand->clear();
    delete splitHand;
    splitHand = nullptr;
    playerHand = new HandView(this);
    playerHand->show();
    playerHand->raise();
    playerHand->move(0, 0);
    connectButtons(playerHand);
}

void GameView::connectButtons(HandView* hand)
{
    connect(hand, &HandView::hit,
            this ,&GameView::sendHit);
    connect(hand, &HandView::stay,
            this ,&GameView::sendStay);
    connect(hand, &HandView::split,
            this,&GameView::sendSplit);
    connect(hand, &HandView::getHint,
            this ,&GameView::sendHint);
    connect(this, &GameView::handHit,
            hand, &HandView::playerHit);
}

void GameView::getRecommended(PlayerOptions optimal, bool isRegHand)
{
    if(isRegHand)
    {
        playerHand->recommended = optimal;
    }
    else
    {
        splitHand->recommended = optimal;
    }
}

bool GameView::isCorrectDecision(PlayerOptions choice, bool hand)
{
    HandView* currentHand = playerHand;
    if(!hand){
        currentHand = splitHand;
    }
    return choice == currentHand->recommended;
}

void GameView::setAllowRecommendations()
{
    canRecommend = !canRecommend;
}

void GameView::incrementWinLoss(bool win)
{
    if(win)
    {
        scoreLabel->incrementWins();
    }
    else
    {
        scoreLabel->incrementLosses();
    }
}
void GameView::disableRec()
{
    canRecommend = false;
    emit disableToggle(false);
    emit flipToggle(false);
}
void GameView::enableRec()
{
   canRecommend = true;
   emit disableToggle(true);
   emit flipToggle(true);
}

void GameView::enabledButtons(int hand, QString enable){
    if(hand==0){
        if(enable=="hit"){playerHand->enabledButtons(0);}
        if(enable=="stay"){playerHand->enabledButtons(1);}
        if(enable=="split"){playerHand->enabledButtons(2);}
    }else{
        if(enable=="hit"){splitHand->enabledButtons(0);}
    }


}
