#ifndef LOCONETMESSAGEEXCEPTIONTESTACTION_H
#define LOCONETMESSAGEEXCEPTIONTESTACTION_H
#include "abstractaction.h"

class Logger;
class LocoNetMessageExceptionTestAction : public AbstractAction
{
 Q_OBJECT
public:
    LocoNetMessageExceptionTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // LOCONETMESSAGEEXCEPTIONTESTACTION_H
