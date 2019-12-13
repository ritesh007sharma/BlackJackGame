#ifndef HINTBUTTON_H
#define HINTBUTTON_H

#include <QWidget>
#include <QPushButton>
class HintButton : public QWidget
{
    Q_OBJECT
private:
    QPushButton *hintButton;
public:
    HintButton(QWidget* parent);
private slots:
    void hintClicked();
signals:
    void hint();
};

#endif // HINTBUTTON_H
