#include "largepowermanagerbutton.h"

LargePowerManagerButton::LargePowerManagerButton(QWidget *parent) :
    PowerManagerButton(parent)
{
}
// /*public*/ class LargePowerManagerButton extends PowerManagerButton {

/*public*/ LargePowerManagerButton::LargePowerManagerButton(bool fullText, QWidget* parent) : PowerManagerButton(fullText, parent){
    //super(fullText);
}

///*public*/ LargePowerManagerButton() {
//    super();
//}

void LargePowerManagerButton::loadIcons() {
    powerOnIcon =  QIcon(":/resources/icons/throttles/power_green.png");
    powerOffIcon =  QIcon("resources/icons/throttles/power_red.png");
    powerXIcon =  QIcon("resources/icons/throttles/power_yellow.png");
}
