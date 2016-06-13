#ifndef NOFEEDBACKTURNOUTOPERATOR_H
#define NOFEEDBACKTURNOUTOPERATOR_H
#include "turnoutoperator.h"
#include "libPr3_global.h"

class AbstractTurnout;
class LIBPR3SHARED_EXPORT NoFeedbackTurnoutOperator : public TurnoutOperator
{
    Q_OBJECT
public:
    //explicit NoFeedbackTurnoutOperator(QObject *parent = 0);
    /*public*/ NoFeedbackTurnoutOperator(AbstractTurnout* t, long i, int mt, QObject *parent = 0);
    /*public*/ void run();

signals:
    
public slots:
private:
    long interval;
    int maxTries;
    int tries;
};

#endif // NOFEEDBACKTURNOUTOPERATOR_H
