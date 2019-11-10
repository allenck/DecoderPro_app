#ifndef LOCONETTHROTTLETESTACTION_H
#define LOCONETTHROTTLETESTACTION_H
#include "abstractaction.h"

class Logger;
class LocoNetThrottleTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LocoNetThrottleTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // LOCONETTHROTTLETESTACTION_H
