#include "tutorial.h"

Tutorial::Tutorial():splitOccured(false),bustCount(0),stayCount(0),tutorialMode(1), deck(4)
{
    makeStrings();
}

void Tutorial::tutorialButtonClicked()
{
    tutorialLevel();
    tutoriallevel3hit = false;
}
void Tutorial::tutorialLevel()
{
    if(tutorialMode == 1)
    {
        tutorialLevel1();
    }
    else if(tutorialMode == 2)
    {
       tutorialLevel2();
    }
    else
    {
        tutorialLevel3();
    }
}

void Tutorial::tutorialLevel1()
{
    emit sendPopup(welcome, true);
    emit sendPopup(turnExplan, true);
    dealCards(1);
    emit sendRecommended(getAnswer(true), true);
    QTimer::singleShot(3000, this, &Tutorial::sendPopUpsWithDelayTutorial1);
}

void Tutorial::sendPopUpsWithDelayTutorial1() {
    emit sendPopup(buttonOptions, true);
    setButtonsOnOrOff(0,"hit");
    emit sendPopup(cardValues, true);
}

void Tutorial::sendCardValues()
{   //old
    setButtonsOnOrOff(0,"hit");
    emit sendPopup(cardValues, true);
}

void Tutorial::tutorialLevel2()
{
    emit sendPopup(Tutoriallevel2start,true);
    dealCards(2);
    QTimer::singleShot(3000, this, &Tutorial::sendPopUpsWithDelayTutorial2);
}

void Tutorial::sendPopUpsWithDelayTutorial2() {
    enabledButtonsTutorial(0, "stay");
    emit sendPopup(tutorialLevel2dealcards,true);
}

void Tutorial::tutorialLevel3()
{
    emit sendPopup(tutoriallevel3start, true);
    dealCards(3);

    QTimer::singleShot(3000, this, &Tutorial::sendPopUpsWithDelayTutorial3);
}

void Tutorial::sendPopUpsWithDelayTutorial3() {
    enabledButtonsTutorial(0, "split");
    emit sendPopup(tutoriallevel3dealcards,true);
}

void Tutorial::gameButtonPressed()
{
    tutorialMode=0;
    dealStartingHand();
}

void Tutorial::dealStartingHand()
{
    Card playerCardF = deck.getCard();
    p1.hit(playerCardF, true);
    emit dealPlayerCard(playerCardF, true, p1.handValue(true));
    Card dealerCardF = deck.getCard();
    dl.hit(dealerCardF);
    emit dealFaceupDealer(dealerCardF,dl.handValue());

    Card playerCardS = deck.getCard();
    p1.hit(playerCardS, true);
    emit dealPlayerCard(playerCardS, true, p1.handValue(true));

    Card dealerCardS = deck.getCard();
    dl.hit(dealerCardS);

    emit dealFaceDownDealer(dealerCardS);
    emit sendRecommended(getAnswer(true), true);
}


void Tutorial::generateGameRules()
{
    gameRules = "BlackJack Rules: \n"
                "1.The goal of blackjack is to beat the dealer without going over 21. \n"
                "2.Face cards are worth 10. Aces are worth 1 or 11, depending on which one makes a better hand. \n"
                "3.Each player starts out with two hands, one of the dealers cards is hidden till the end. \n"
                "4.To hit is to ask for another card.To stand is to hold your current total and end your turn.\n"
                "5.To split is when both of the players cards are the same and the pair is split into two hands. You can only split on the first move.\n"
                "6.If you go over 21, you bust and the dealer wins regardless of their hand. \n "
                "7.The dealer will hit until their cards total 17 or higher."
                "8.If you are dealt 21, then you get a blackjack!";


}
void Tutorial::generateButtonOPtions()
{
    buttonOptions = "Now that you have your cards you need to decide what to do! \nRemember the goal is to be the closer to 21 then "
                    "the dealer without going over. Your different options are to either hit, stay, or split. When you hit you "
                    "draw another card and it gets added to your score. If you stay this ends your turn and it becomes the dealers turn."
                    "You can split if both of your cards are the same to form two seperate hands.";
}
void Tutorial::generateWelcome()
{
    welcome = "Hi there! Welcome to CLoudKingdom's BlackJack Tutorial! \n Lets Start by teaching you the basic rules of BlackJack. \n"
              "The goal of blackjack is to \"beat\" the dealer. \n This is accomplished by having the total sum of your cards being "
              "closer to 21 than the dealer. \nHowever, if your cards are greater than 21 you lose! \n\nLets do a practice game and I "
              "will teach you how to play:)\n -The One and only CloudKingdom Bot";
}
void Tutorial::generateTurnExplan()
{
    turnExplan="The game starts by the dealer giving one card to you, face up, one card to itself, face up. Then the dealer "
               "gives you your second card face up and deals themselves their second card face down. Lets watch and see what happens!";
}
void Tutorial::generateCardVals()
{
    cardValues = "Lets look at your cards! You have a 6 and a 5. That means you have a score of 11! All face cards are worth 10 and "
                 "each numbered card is equal to its number.  If we look at the dealer's card we see that they have a king. "
                 "That means we know the dealer has at least 10 points. Lets go ahead and hit!";
}
void Tutorial::generateQueen()
{
    queen = "It looks like you drew a king! That means you have a score of 21! Thats the best score that you can get! Since "
            "you cant get a better score why dont you hit the stay button to lock in your score!";
}

void Tutorial::generateFirstStay()
{
    firstStay = "By staying, you have ended your turn and started the dealer's turn. You might think you have won, but you haven't "
                "just yet! Even though your score is 21, the dealer could also get a score of 21 and you and dealer could tie. "
                "Lets watch and see what happens!";
}

void Tutorial::generateDealerBust()
{
    dealerBustString = "Yay! The dealer hit and got a total card score of 22. The dealer has busted and you have won with a card score of 20.Good Job you won!"
                       " Go on to the next part of the tutorial.";
}
void Tutorial::generateTutoriallevel2start()
{
    Tutoriallevel2start = "Welcome to part 2 of the tutorial. Now you're probably wondering how to decide between staying or hitting. "
                          "Lets deal some cards out.";
}
void Tutorial::generateTutorialLevel2dealcards()
{
    tutorialLevel2dealcards = "Now that you have gotten cards, lets check your card score. With an 7 and an ace, your score is 18. Aces in this game counts as either one or 11. Because we already have a 7 lets go with the higher score to get 18. Based on statistics, it is a general"
                               "rule of thumb that you stay on scores 17 and above and stay on scores 16 and below. Lets end our turn by staying and see what the dealer gets. ";
}
void Tutorial::generateTutorialLevel2dealerwins()
{
    tutorialLevel2dealerwins = "The dealer hit and got a 3 to get a total score of 19 and has chosen to stay. Looks like the dealer has won! Even though we lost, it was only by a slim chance. Lets go to the next part of the tutorial!";
}
void Tutorial::generatetutoriallevel3start()
{
    tutoriallevel3start = "Welcome to the last part of this tutorial. Here you will learn how splitting the hand works. Lets deal some cards out. ";
}

void Tutorial::generatetutoriallevel3dealcards()
{
    tutoriallevel3dealcards = "Lets take a look at your cards. You dealer has a score of 9 and you have a score of 16. Now because both of your cards are the same, so you have the option to split. Lets go ahead and split to form two seperate hands.";
}
//unused??
void Tutorial::generateTutorialLevel3split()
{
    setButtonsOnOrOff(0,"hit");
    setButtonsOnOrOff(1,"hit");

    tutorialLevel3split = "Now that you have split. Lets go ahead and hit on both hands";
}
void Tutorial::generatetutorialLevel3advice()
{
    tutorialLevel3advice = "Now that you have split you hand lets take a look at each of each of your card scores. Your first hand has a score of 18 and your second hand has a score of 16. As we learned earlier we should stay on the first hand and hit on the second hand. So lets go ahead and stay on the first hand and hit on the second hand.";
}
void Tutorial::generatetutorialLevel3playerbust()
{
    tutorialLevel3playerbust = "Oh no! You have busted, lets see what the dealer gets.";

}
void Tutorial::generatetutorialLevel3dealerwins()
{
    tutorialLevel3dealerwins = "Looks like the dealer won with a score of 19. Thank you for playing our tutorial. Please click the quit button to go back to the main menu where you can either go through the tutorial again or play the actual game. ";
}
void Tutorial::makeStrings()
{
    generateWelcome();
    generateCardVals();
    generateTurnExplan();
    generateButtonOPtions();
    generateQueen();
    generateFirstStay();
    generateDealerBust();
    generateTutoriallevel2start();
    generateTutorialLevel2dealcards();
    generateTutorialLevel2dealerwins();
    generatetutoriallevel3start();
    generatetutoriallevel3dealcards();
    generatetutorialLevel3advice();
    generatetutorialLevel3playerbust();
    generatetutorialLevel3dealerwins();
}
void Tutorial::dealCards(int sequence)
{

    if(sequence == 1)
    {
        Card ccd = deck.getCard(17);
        p1.hit(ccd, true);
        emit dealPlayerCard(ccd,true, p1.handValue(true));

        //deals card to dealer face up
        Card ccc = deck.getCard(47);
        dl.hit(ccc);
        emit dealFaceupDealer(ccc,dl.handValue());

        Card cc = deck.getCard(13);
        p1.hit(cc, true);
        emit dealPlayerCard(cc,true, p1.handValue(true));

        Card ddd = deck.getCard(1);
        dl.hit(ddd);
        emit dealFaceDownDealer(ddd);
    }
    else if(sequence == 2)
    {
        //player gets a 7
        Card ccd = deck.getCard(23);
        p1.hit(ccd, true);
        emit dealPlayerCard(ccd,true, p1.handValue(true));

        //dealer gets a 6
        Card ccc = deck.getCard(19);
        dl.hit(ccc);
        emit dealFaceupDealer(ccc,dl.handValue());

        Card cc = deck.getCard(50);
        p1.hit(cc, true);
        emit dealPlayerCard(cc,true, p1.handValue(true));

        //dealer gets an 10
        Card ddd = deck.getCard(34);
        dl.hit(ddd);
        emit dealFaceDownDealer(ddd);
    }
    else
    {
        //player gets a 8
        Card ccd = deck.getCard(26);
        p1.hit(ccd, true);
        emit dealPlayerCard(ccd,true, p1.handValue(true));

        //dealer gets a 9
        Card ccc = deck.getCard(30);
        dl.hit(ccc);
        emit dealFaceupDealer(ccc,dl.handValue());

        //player gets a 8
        Card cc = deck.getCard(27);
        p1.hit(cc, true);
        emit dealPlayerCard(cc,true, p1.handValue(true));

        //dealer gets an 10
        Card ddd = deck.getCard(45);
        dl.hit(ddd);
        emit dealFaceDownDealer(ddd);
    }
}
void Tutorial::split()
{
    splitOccured=true;
    p1.splitting();

    if(tutorialMode == 3)
    {
        //player gets a 9
        Card a1 = deck.getCard(46);
        p1.hit(a1,true);
        emit dealPlayerCard(a1,true, 18);



        //gets a 9
        Card a2 = deck.getCard(28);
        p1.hit(a2,false);
        emit dealPlayerCard(a2,false,16);
        hit(true);
        hit(false);
        setButtonsOnOrOff(0,"stay");
        setButtonsOnOrOff(1,"hit");
        sendPopup(tutorialLevel3advice,true);

    tutoriallevel3hit  = true;
    }
    else
    {
        hit(true);
        hit(false);
    }
}
void Tutorial::hit(bool handname)
{
    if(tutorialMode==1)
    {
        //player gets a 10 to get 21
        Card sdf = deck.getCard(48);
        p1.hit(sdf, true);
        emit dealPlayerCard(sdf,true, 21);
        setButtonsOnOrOff(0,"stay");
        emit sendPopup(queen, true);

    }
    else if(tutorialMode ==3)
    {
        if(tutoriallevel3hit)
        {
            //gets an 8
            emit incrementScore(false);
            Card a3 = deck.getCard(32);
            p1.hit(a3,false);
            emit dealPlayerCard(a3,false,26);
            emit playerBust(false);
            emit sendPopup(tutorialLevel3playerbust,true);
            emit flipDealerCard(19);
            setButtonsOnOrOff(0,"split");
            emit sendPopup(tutorialLevel3dealerwins,true);
        }
    }
    else
    {
        Card playerHitCard = deck.getCard();
        p1.hit(playerHitCard, handname);
        emit dealPlayerCard(playerHitCard, handname,p1.handValue(handname));
        if(!splitOccured)
        {
            if(p1.handValue(handname)>21)
            {
                emit flipDealerCard(dl.handValue());
                emit doubleBust();
                return;
                //bustCount++;
            }
        }else
        {
            if(p1.handValue(handname)>21)
            {
                bustCount++;
                //emit playerBust(handname);
                if(bustCount==2)
                {
                    emit flipDealerCard(dl.handValue());
                    emit doubleBust();
                    return;
                }else if(stayCount==1&&bustCount==1)
                {
                    emit playerBust(handname);
                    emit flipDealerCard(dl.handValue());
                    dealerTurn();
                    return;
                }else
                {
                    emit playerBust(handname);
                    return;
                }
            }
        }
        PlayerOptions po = getAnswer(handname);
        emit sendRecommended(getAnswer(handname), handname);
    }
}

void Tutorial::stay(bool hand)
{
    if(tutorialMode==1)
    {
        incrementScore(true);
        emit  sendPopup(firstStay, true);
        //dealer gets a 10
        Card csd = deck.getCard(48);
        emit flipDealerCard(22);
        dl.hit(csd);
        emit dealFaceupDealer(csd,dl.handValue());
        emit sendPopup(dealerBustString, true);

        tutorialMode = 2;
        internalReset();
        emit resetBoard();
    }
    else if(tutorialMode==2)
    {
        //dealer gets a 3
        incrementScore(false);
        Card csd = deck.getCard(6);
        emit flipDealerCard(19);
        dl.hit(csd);
        emit dealFaceupDealer(csd,dl.handValue());
        setButtonsOnOrOff(0,"stay");

        emit sendPopup(tutorialLevel2dealerwins,true);

        internalReset();
        tutorialMode = 3;
        emit resetBoard();
    }
    else
    if(splitOccured)
    {
        stayCount++;
        if(stayCount==1&&bustCount==0)
        {
            return;
        }else
        {
            emit flipDealerCard(dl.handValue());
            dealerTurn();
        }
    }else
    {
        emit flipDealerCard(dl.handValue());
        dealerTurn();
    }
}

void Tutorial::dealerTurn()
{
    while(dl.canHit())
    {
        Card ddd = deck.getCard();
        dl.hit(ddd);
        emit dealFaceupDealer(ddd, dl.handValue());
        if(dl.handValue()>21)
        {
            if(splitOccured){
                if(bustCount == 0){
                    //emit incrementScore(true);
                }
            }
            emit dealerBust();
            return;
        }
    }
    if(splitOccured)
    {
        if((dl.handValue()>p1.handValue(true)||p1.handValue(true)>21)&&(dl.handValue()>p1.handValue(false)||p1.handValue(false)>21))
        {
            incrementScore(false);
            emit dealerWins();
        }else if((dl.handValue()<p1.handValue(true)&&p1.handValue(true)<=21)||(dl.handValue()<p1.handValue(false)&&p1.handValue(false)<=21))
        {
            emit playerWins();
        }else
        {
            emit tie();
        }
    }else
    {
        if(dl.handValue()>(p1.handValue(true)))
        {
            emit dealerWins();
        }else if (dl.handValue()<p1.handValue(true))
        {
            emit playerWins();
        }else
        {
            emit tie();
        }
    }
}

void Tutorial::internalReset()
{
    bustCount = 0;
    stayCount = 0;
    splitOccured = false;
    deck.reset();
    p1.reset();
    dl.reset();
}

void Tutorial::resetRound()
{
    tutorialMode=0;
    internalReset();
    dealStartingHand();
}
void Tutorial::resetRoundTutorial()
{
    internalReset();
    tutorialButtonClicked();
}

PlayerOptions Tutorial::getAnswer(bool regHand)
{
    Hand currentHand = p1.getHand();
    if(!regHand)
    {
        currentHand = p1.getSplitHand();
    }

    PlayerOptions po = key.getAnswer(currentHand,dl.getHand(),currentHand.getChart());
    return po;
}

void Tutorial::hint(bool regHand)
{
    PlayerOptions answer = getAnswer(regHand);
    QString answerQstring;
    if (answer == PlayerOptions::Hit){
        answerQstring = "I, as the glourious CloudKingdoom Bot recommened that you hit!";
    }
    else if (answer == PlayerOptions::Stand)
    {
        answerQstring = "I, the cloud making master of CLoudKingdom, recommend that you stay";
    }
    else if (answer == PlayerOptions::Yes)
    {
        answerQstring= "A wise bot once said, you should split. I am that wise bot. Listen to me";
    }
    else
    {
        answerQstring = "On the third day the CloudKingdom Bot said: THough shall not split";
    }
    emit sendPopup(answerQstring, true);
}
void Tutorial::setTutorialLvl()
{
    tutorialMode=1;
}

void Tutorial::setButtonsOnOrOff(int hand, QString buttonToEnable){
    emit  enabledButtonsTutorial(hand, buttonToEnable);
}





