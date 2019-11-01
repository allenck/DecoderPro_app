#ifndef LNTRAFFICCONTROLLERTESTACTION_H
#define LNTRAFFICCONTROLLERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnTrafficControllerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnTrafficControllerTestAction(QObject* parent);
public slots:
    void actionPerformed();

private:
    static Logger* log;
};

#endif // LNTRAFFICCONTROLLERTESTACTION_H
