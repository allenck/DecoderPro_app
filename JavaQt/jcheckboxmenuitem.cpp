#include "jcheckboxmenuitem.h"

JCheckBoxMenuItem::JCheckBoxMenuItem(QString text, QObject *parent)
    : AbstractAction(text, parent)
{
 setCheckable(true);
}
/*public*/ JCheckBoxMenuItem::JCheckBoxMenuItem(ImageIcon* imageIcon, QObject *parent) : AbstractAction("", parent) {
        // compiled code

 setCheckable(true);

 QIcon icon = QIcon(QPixmap::fromImage( imageIcon->getImage()));
 setIcon(icon);
}
