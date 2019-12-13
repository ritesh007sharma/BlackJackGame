#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H
#include <QPushButton>
#include <QWidget>

class ToggleButton : public QPushButton
{
    Q_OBJECT
private:
    bool on;
public:
    ToggleButton(QWidget* parent);
public slots:
    void toggled();
    void disable(bool b);
    void nonButtonToggle(bool b);

signals:
    void hintSwitch(bool);
};

#endif // TOGGLEBUTTON_H
