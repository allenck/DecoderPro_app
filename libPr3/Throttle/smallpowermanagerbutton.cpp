#include "smallpowermanagerbutton.h"

SmallPowerManagerButton::SmallPowerManagerButton(QWidget *parent) :
    PowerManagerButton(parent)
{
}
///*public*/ class SmallPowerManagerButton extends PowerManagerButton {
//	/*public*/ SmallPowerManagerButton() {
//		super();
//		setBorderPainted(false);
//	}

void SmallPowerManagerButton::loadIcons()
{
 powerOnIcon =  QIcon(":/resources/icons/throttles/GreenPowerLED.gif");
 powerOffIcon =  QIcon(":/resources/icons/throttles/RedPowerLED.gif");
 powerXIcon =  QIcon("resources/icons/throttles/YellowPowerLED.gif");
}
