#ifndef COMMONTURNOUTOPERATION_H
#define COMMONTURNOUTOPERATION_H
#include "turnoutoperation.h"

class TurnoutOperation;
class TurnoutOperator;
class AbstractTurnout;
class LIBPR3SHARED_EXPORT CommonTurnoutOperation : public TurnoutOperation
{
    Q_OBJECT
public:
    //explicit CommonTurnoutOperation(QObject *parent = 0);
    /*
     * Parameters of this object
     */
    int interval;					// time between attempts
    int maxTries;					// no of times to try

    /*
     * Default values and constraints
     */

    static /*public final*/const int minInterval = 100;
    static /*public final*/const int maxInterval = 5000;		// let's not get silly...
    static /*public final*/const int intervalStepSize = 50;
    static /*public final*/const int minMaxTries = 1;
    static /*public final*/const int maxMaxTries = 10;
    /*public*/ CommonTurnoutOperation(QString n, int i, int mt, QObject *parent = 0);
    virtual /*public*/ /*abstract*/ TurnoutOperator* getOperator(AbstractTurnout* t) =0;
    /*public*/ int getInterval();
    /*public*/ int getMaxTries();
    /*public*/ /*abstract*/ virtual int getDefaultInterval() = 0;
    /*public*/ /*abstract*/ virtual int getDefaultMaxTries() = 0;

    /*public*/ bool equivalentTo(TurnoutOperation* other);
    /*public*/ void setInterval(int newInterval);
    /*public*/ void setMaxTries(int newMaxTries);

signals:
    
public slots:
    
};

#endif // COMMONTURNOUTOPERATION_H
