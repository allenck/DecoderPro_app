#ifndef LNPACKETIZERTESTACTION_H
#define LNPACKETIZERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnPacketizerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnPacketizerTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // LNPACKETIZERTESTACTION_H
