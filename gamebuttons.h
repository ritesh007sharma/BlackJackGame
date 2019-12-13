#ifndef GAMEBUTTONS_H
#define GAMEBUTTONS_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>




class GameButtons : public QWidget
{
    Q_OBJECT

public:

    GameButtons(QWidget* parent);
    void disable();
    void enableButtonsTutorial(int button);
private:
     QPushButton * hitButton;
     QPushButton * stayButton;
     QPushButton * splitButton;
     void displaySetUp();


private slots:
     void hitButton_clicked();
     void stayButton_clicked();
     void splitButton_clicked();

signals:
     void hitMove();
     void stayMove();
     void splitMove();
};

#endif // GAMEBUTTONS_H
