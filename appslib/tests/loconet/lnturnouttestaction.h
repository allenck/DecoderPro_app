#ifndef LNTURNOUTTESTACTION_H
#define LNTURNOUTTESTACTION_H
#include "abstractaction.h"

class LnTurnoutTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnTurnoutTestAction(QObject *parent);
public slots:
    void actionPerformed();
};

#endif // LNTURNOUTTESTACTION_H
