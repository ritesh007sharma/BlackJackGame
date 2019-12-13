#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>


class TitleScreen : public QWidget
{
     Q_OBJECT
public:
    TitleScreen(QWidget* parent);

private:

    /**
     * @brief The tutorial button.
     */
    QPushButton* tutorialButton;

    /**
     * @brief The game button.
     */
    QPushButton* gameButton;

    /**
     * @brief Sets the title and buttons on the window.
     */
    void displaySetUp();

private slots:
    /**
     * @brief Slot for when the tutorial button is clicked.
     */
    void on_tutorialButton_clicked();

    /**
     * @brief Slot for when the start game button is clicked.
     */
    void on_start_GameButton_clicked();

signals:
    /**
     * @brief Indicates the tutorial button was clicked.
     */
    void tutorialButtonClicked();

    /**
     * @brief Indicates the start game button was clicked.
     */
    void startGameButtonClicked();

};
#endif // TITLESCREEN_H
