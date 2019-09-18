#ifndef LNPORTCONTROLLERTESTACTION_H
#define LNPORTCONTROLLERTESTACTION_H
#include "abstractaction.h"

class LnPortControllerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnPortControllerTestAction(QObject *parent);
public slots:
    void actionPerformed();
};

#endif // LNPORTCONTROLLERTESTACTION_H
