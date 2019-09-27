#ifndef LNPORTCONTROLLERTESTACTION_H
#define LNPORTCONTROLLERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnPortControllerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnPortControllerTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};
#endif // LNPORTCONTROLLERTESTACTION_H
