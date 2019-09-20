#ifndef LNPOWERMANAGERTESTACTION_H
#define LNPOWERMANAGERTESTACTION_H
#include "abstractaction.h"

class LnPowerManagerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnPowerManagerTestAction(QObject* parent);
public slots:
    void actionPerformed();
};

#endif // LNPOWERMANAGERTESTACTION_H
