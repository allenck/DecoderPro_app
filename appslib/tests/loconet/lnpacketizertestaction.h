#ifndef LNPACKETIZERTESTACTION_H
#define LNPACKETIZERTESTACTION_H
#include "abstractaction.h"

class LnPacketizerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnPacketizerTestAction(QObject *parent);
public slots:
    void actionPerformed();
};

#endif // LNPACKETIZERTESTACTION_H
