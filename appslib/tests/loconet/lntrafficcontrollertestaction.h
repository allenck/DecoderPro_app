#ifndef LNTRAFFICCONTROLLERTESTACTION_H
#define LNTRAFFICCONTROLLERTESTACTION_H
#include "abstractaction.h"

class LnTrafficControllerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnTrafficControllerTestAction(QObject* parent);
public slots:
    void actionPerformed();
};

#endif // LNTRAFFICCONTROLLERTESTACTION_H
