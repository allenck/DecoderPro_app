#ifndef LNTRAFFICROUTERTESTACTION_H
#define LNTRAFFICROUTERTESTACTION_H
#include "abstractaction.h"

class LnTrafficRouterTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnTrafficRouterTestAction(QObject* parent);

public slots:
    void actionPerformed();
};

#endif // LNTRAFFICROUTERTESTACTION_H
