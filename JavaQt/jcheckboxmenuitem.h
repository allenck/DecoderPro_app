#ifndef JCHECKBOXMENUITEM_H
#define JCHECKBOXMENUITEM_H
#include "abstractaction.h"
#include "imageicon.h"

class JCheckBoxMenuItem : public AbstractAction
{
public:
    JCheckBoxMenuItem(QString text, QObject*parent);
    /*public*/ JCheckBoxMenuItem(ImageIcon* icon, QObject *parent);
};

#endif // JCHECKBOXMENUITEM_H
