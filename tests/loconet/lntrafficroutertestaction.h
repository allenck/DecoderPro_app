#ifndef LNTRAFFICROUTERTESTACTION_H
#define LNTRAFFICROUTERTESTACTION_H
#include "abstractaction.h"
class Logger;
class LnTrafficRouterTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnTrafficRouterTestAction(QObject* parent);

public slots:
    void actionPerformed();
private:
    static Logger* log;

};

#endif // LNTRAFFICROUTERTESTACTION_H
