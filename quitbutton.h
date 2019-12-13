#ifndef QUITBUTTON_H
#define QUITBUTTON_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include "ui_mainwindow.h"
#include <iostream>


class QuitButton : public QWidget
{
    Q_OBJECT

public:
     QuitButton(QWidget* parent);

private:
    QPushButton *quitButton;

private slots:
    void on_quit_clicked();

signals:
    void quit();
};

#endif // QUITBUTTON_H
