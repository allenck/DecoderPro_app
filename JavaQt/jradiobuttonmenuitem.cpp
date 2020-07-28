#include "jradiobuttonmenuitem.h"

JRadioButtonMenuItem::JRadioButtonMenuItem(QString text, QObject* parent) : AbstractAction(text, parent)
{
 setCheckable(true);
}
