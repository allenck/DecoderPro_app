#ifndef JCHECKBOXMENUITEM_H
#define JCHECKBOXMENUITEM_H
#include "abstractaction.h"

class JCheckBoxMenuItem : public AbstractAction
{
public:
    JCheckBoxMenuItem(QString text, QObject*parent);
};

#endif // JCHECKBOXMENUITEM_H
