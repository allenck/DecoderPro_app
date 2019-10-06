#include "nofeedbackturnoutoperation.h"
#include "nofeedbackturnoutoperator.h"

//NoFeedbackTurnoutOperation::NoFeedbackTurnoutOperation(QObject *parent) :
//    CommonTurnoutOperation(parent)
//{
//}
/**
 * NoFeedBackTurnoutOperation class - specialization of TurnoutOperation to provide
 * automatic retry for a turnout with no feedback
 * @author John Harper
 * @version $Revision: 17977 $
 */
//public class NoFeedbackTurnoutOperation extends CommonTurnoutOperation {
/*static*/ /*public*/ /*final*/const int NoFeedbackTurnoutOperation::defaultInterval = 300;
/*static*/ /*public*/ /*final*/ const int NoFeedbackTurnoutOperation::defaultMaxTries = 2;

/*public*/ NoFeedbackTurnoutOperation::NoFeedbackTurnoutOperation(QString n, int i, int mt, QObject *parent)
 : CommonTurnoutOperation(n, i, mt, parent)
{
 //super(n, i, mt);
 //feedbackModes = Turnout::DIRECT | Turnout::ONESENSOR | Turnout::TWOSENSOR| Turnout::INDIRECT | Turnout::EXACT | Turnout::MONITORING;

 setFeedbackModes(Turnout::DIRECT | Turnout::ONESENSOR | Turnout::TWOSENSOR| Turnout::INDIRECT | Turnout::EXACT | Turnout::MONITORING);
}

/**
 * constructor with default values - this creates the "defining instance" of
 * the operation type hence it cannot be deleted
 */
/*public*/ NoFeedbackTurnoutOperation::NoFeedbackTurnoutOperation(QObject *parent)
 : CommonTurnoutOperation("NoFeedback", defaultInterval, defaultMaxTries, parent)
{
 //this("NoFeedback", defaultInterval, defaultMaxTries);
 setFeedbackModes(Turnout::DIRECT | Turnout::ONESENSOR | Turnout::TWOSENSOR| Turnout::INDIRECT | Turnout::EXACT | Turnout::MONITORING);

}

/**
 * return clone with different name
 */
/*public*/ TurnoutOperation* NoFeedbackTurnoutOperation::makeCopy(QString n) {
    return new NoFeedbackTurnoutOperation(n, interval, maxTries);
}

/*public*/ int NoFeedbackTurnoutOperation::getDefaultInterval() {
    return defaultInterval;
}

/*public*/ int NoFeedbackTurnoutOperation::getDefaultMaxTries() {
    return defaultMaxTries;
}

/*static*/ /*public*/ int NoFeedbackTurnoutOperation::getDefaultIntervalStatic() {
    return defaultInterval;
}

/*static*/ /*public*/ int NoFeedbackTurnoutOperation::getDefaultMaxTriesStatic() {
    return defaultMaxTries;
}

/**
 * get a TurnoutOperator instance for this operation
 * @return	the operator
 */
/*public*/ TurnoutOperator* NoFeedbackTurnoutOperation::getOperator(AbstractTurnout* t)
{
 return new NoFeedbackTurnoutOperator(t, interval, maxTries);
}


//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(NoFeedbackTurnoutOperation.class.getName());
//}
