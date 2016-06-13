#include "nofeedbackturnoutoperator.h"
#include "abstractturnout.h"

//NoFeedbackTurnoutOperator::NoFeedbackTurnoutOperator(QObject *parent) :
//    TurnoutOperator(parent)
//{
//}
///*public*/ class NoFeedbackTurnoutOperator extends TurnoutOperator {



/*public*/ NoFeedbackTurnoutOperator::NoFeedbackTurnoutOperator(AbstractTurnout* t, long i, int mt, QObject* parent) : TurnoutOperator(t,parent)
{
    //super(t);
 interval = i;
 maxTries = mt;
 tries = 0;
}

/**
 * Do the automation for a turnout with no feedback. This means try
 * maxTries times at an interval of interval. Note the call to
 * operatorCheck each time we're about to actually do something -
 * if we're no longer the current operator this throws
 * TurnoutOperatorException which just terminates the thread.
 */
/*public*/ void NoFeedbackTurnoutOperator::run()
{
    try {
        operatorCheck();
        myTurnout->forwardCommandChangeToLayout();
        while (++tries < maxTries) {
            try {
                QThread::msleep(interval);
            } catch (InterruptedException e) {
                QThread::currentThread()->exit(); // retain if needed later
            }
            operatorCheck();
            myTurnout->forwardCommandChangeToLayout();
        }
        myTurnout->setKnownStateToCommanded();
    } catch (TurnoutOperatorException e) { }
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(NoFeedbackTurnoutOperator.class.getName());
//}
