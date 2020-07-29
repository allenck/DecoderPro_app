#ifndef JRADIOBUTTONMENUITEM_H
#define JRADIOBUTTONMENUITEM_H
#include "abstractaction.h"

class JRadioButtonMenuItem : public AbstractAction
{
    Q_OBJECT
public:
    JRadioButtonMenuItem(QString text, QObject* parent);
};

#endif // JRADIOBUTTONMENUITEM_H
