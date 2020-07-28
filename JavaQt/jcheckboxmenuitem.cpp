#include "jcheckboxmenuitem.h"

JCheckBoxMenuItem::JCheckBoxMenuItem(QString text, QObject *parent)
    : AbstractAction(text, parent)
{
 setCheckable(true);
}
