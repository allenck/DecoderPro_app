#include "jcheckboxmenuitem.h"

JCheckBoxMenuItem::JCheckBoxMenuItem(QString text, QObject *parent)
    : AbstractAction(text, parent)
{
 setCheckable(true);
}
/*public*/ JCheckBoxMenuItem::JCheckBoxMenuItem(ImageIcon* icon) {
        // compiled code
    }
