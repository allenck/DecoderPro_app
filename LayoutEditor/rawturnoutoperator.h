#ifndef RAWTURNOUTOPERATOR_H
#define RAWTURNOUTOPERATOR_H
#include "turnoutoperator.h"
#include "liblayouteditor_global.h"

class Logger;
class AbstractTurnout;
class CommandStation;
class LIBLAYOUTEDITORSHARED_EXPORT RawTurnoutOperator : public TurnoutOperator
{
    Q_OBJECT
public:
    //explicit RawTurnoutOperator(QObject *parent = 0);
    /*public*/ RawTurnoutOperator(AbstractTurnout* t, long i, int mt, QObject *parent = 0);
    /*public*/ void run();

signals:

public slots:
private:
    long interval;
    int maxTries;
    int tries;// = 0;
    int address;// = 0;
    CommandStation* c;
    Logger* log;
    /*private*/ void sendCommand();

};

#endif // RAWTURNOUTOPERATOR_H
