#ifndef JRADIOBUTTONMENUITEM_H
#define JRADIOBUTTONMENUITEM_H
#include "abstractaction.h"

class JRadioButtonMenuItem : public AbstractAction
{
public:
    JRadioButtonMenuItem(QString text, QObject* parent);
};

#endif // JRADIOBUTTONMENUITEM_H
