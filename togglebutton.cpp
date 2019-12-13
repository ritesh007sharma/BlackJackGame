#include "togglebutton.h"

ToggleButton::ToggleButton(QWidget* parent):
    QPushButton(parent),
    on(false)
{
    move(1240, 40);
    resize(320, 140);
    setFont(QFont("Ubuntu", 25, 70));
    connect(this, &QPushButton::pressed,
            this, &ToggleButton::toggled);
    toggled();
}

void ToggleButton::toggled()
{
    on = !on;
    if(!on){
        setText("Turn on\nrecommendations");
        setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
    }
    else{
        setText("Turn off\nrecommendations");
        setStyleSheet("border-image: url(:/pics/Pictures/cool-blue2.png);");
    }
    show();

}
void ToggleButton::nonButtonToggle(bool b)
{
    if(!b){
        setText("Turn on\nrecommendations");
        setStyleSheet("border-image: url(:/pics/Pictures/cool-grey2.png);");
    }
    else
    {
        setText("Turn off\nrecommendations");
        setStyleSheet("border-image: url(:/pics/Pictures/cool-blue2.png);");
    }
    show();
}

void ToggleButton::disable(bool b)
{
    setEnabled(b);
}
