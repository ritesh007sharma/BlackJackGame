#ifndef SCORELABEL_H
#define SCORELABEL_H
#include <QLabel>
#include <QLCDNumber>

class ScoreLabel:public QWidget
{
    Q_OBJECT
public:
    ScoreLabel(QWidget* parent);

private:
    QLCDNumber* wins;
    QLCDNumber* losses;
    QLabel* winText;
    QLabel* lossText;

public slots:
    void incrementWins();
    void incrementLosses();
};

#endif // SCORELABEL_H
