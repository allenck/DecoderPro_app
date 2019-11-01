#ifndef LNTURNOUTTESTACTION_H
#define LNTURNOUTTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnTurnoutTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnTurnoutTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // LNTURNOUTTESTACTION_H
