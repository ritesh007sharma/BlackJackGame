#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //cannot change size of window
    setFixedSize(1600,900);
    centralWidget()->show();

    titleScreen= new TitleScreen(this);
    gameView = new GameView(this);
    tutorial= new Tutorial();
    centralWidget()->setObjectName("central");

    //connection between start window and Start Game press
    //will eventually need to also connect to playing just game
    connect(titleScreen, &TitleScreen::startGameButtonClicked,
            this, &MainWindow::ToGameScreen);
    connect(titleScreen, &TitleScreen::startGameButtonClicked,
            gameView, &GameView::enableRec);
    connect(titleScreen, &TitleScreen::startGameButtonClicked,
            gameView, &GameView::reset);

    //When tutorial is changed, switches to game screen and starts tutorial
    connect(titleScreen, &TitleScreen::tutorialButtonClicked,
            this, &MainWindow::ToGameScreen);
    connect(titleScreen, &TitleScreen::tutorialButtonClicked,
            tutorial, &Tutorial::setTutorialLvl);
    connect(titleScreen,&TitleScreen::tutorialButtonClicked,
            gameView, &GameView::disableRec);
    connect(titleScreen, &TitleScreen::tutorialButtonClicked,
            gameView, &GameView::resetTutorial);

    connect(tutorial, &Tutorial::incrementScore,
            gameView, &GameView::incrementWinLoss);

    //connects when the game is quit
    connect(gameView, &GameView::quitButtonPressed,
            this, &MainWindow::ToTitleScreen);
    connect(gameView, &GameView::hit,
            tutorial, &Tutorial::hit);
    connect(gameView, &GameView::stay,
            tutorial, &Tutorial::stay);
    connect(gameView, &GameView::split,
            tutorial, &Tutorial::split);
    connect(gameView, &GameView::getHint,
            tutorial, &Tutorial::hint);
    connect(gameView, &GameView::resetGame,
            tutorial, &Tutorial::resetRound);
    connect(gameView, &GameView::resetTutorialSignal,
            tutorial, &Tutorial::resetRoundTutorial);
    connect(tutorial,&Tutorial::resetBoard,
            gameView,&GameView::resetTutorialSeqeunce);
    connect(tutorial, &Tutorial::dealFaceupDealer,
            gameView, &GameView::faceUpDealer);
    connect(tutorial, &Tutorial::dealPlayerCard,
            gameView, &GameView::playerHit);
    connect(tutorial, &Tutorial::sendRecommended,
            gameView, &GameView::getRecommended);
    connect(tutorial, &Tutorial::sendPopup,
            gameView, &GameView::displayMessage);
    connect(tutorial, &Tutorial::flipDealerCard,
            gameView, &GameView::flipDealerCard);
    connect(tutorial, &Tutorial::dealFaceDownDealer,
            gameView, &GameView::faceDownDealer);
    connect(tutorial, &Tutorial::dealerBust,
            gameView, &GameView::dealerBust);
    connect(tutorial, &Tutorial::dealerWins,
            gameView, &GameView::dealerWins);
    connect(tutorial, &Tutorial::playerBust,
            gameView, &GameView::playerBust);
    connect(tutorial, &Tutorial::doubleBust,
            gameView, &GameView::doubleBust);
    connect(tutorial, &Tutorial::playerWins,
            gameView, &GameView::playerWins);
    connect(tutorial, &Tutorial::tie,
            gameView, &GameView::tieGame);


    connect(tutorial, &Tutorial::enabledButtonsTutorial,
            gameView, &GameView::enabledButtons);

    centralWidget()->setBackgroundRole(QPalette::Base);

     stackedWidget= new QStackedWidget();
     stackedWidget->addWidget(titleScreen);
     stackedWidget->addWidget(gameView);


     layout = new QGridLayout;
     layout->addWidget(stackedWidget);
     ui->centralwidget-> setLayout(layout);

     ToTitleScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displaySetUp(){
}

void MainWindow::ToGameScreen(){
    centralWidget()->setStyleSheet("GameView#gameview {background-color: green;}");
    setStyleSheet("QWidget#central {background-image: url(:/Backgrounds/gameBackground);}");
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::ToTitleScreen(){
    centralWidget()->setStyleSheet("border-image: url(:/Backgrounds/Pictures/sb4.0.png); padding : 0px; ");
    stackedWidget->setCurrentIndex(0);
}
