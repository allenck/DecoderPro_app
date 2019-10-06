#include "sensorturnoutoperation.h"
#include "abstractturnout.h"
#include "sensorturnoutoperator.h"

//SensorTurnoutOperation::SensorTurnoutOperation(QObject *parent) :
//    CommonTurnoutOperation(parent)
//{
//}

/*static*/ /*public*/ /*final*/const  int SensorTurnoutOperation::defaultInterval = 300;
/*static*/ /*public*/ /*final*/const  int SensorTurnoutOperation::defaultMaxTries = 3;

/**
 * SensorTurnoutOperation class - specialization of TurnoutOperation to provide
 * automatic retry for a turnout with explicit feedback from sensor(s)
 * @author John Harper	Copyright 2005
 * @version $Revision: 17977 $
 */
///*public*/ class SensorTurnoutOperation extends CommonTurnoutOperation {


/*public*/ SensorTurnoutOperation::SensorTurnoutOperation(QString n, int i, int mt, QObject *parent) : CommonTurnoutOperation(n, i, mt, parent)
{
 //super(n, i, mt);
 feedbackModes = Turnout::ONESENSOR | Turnout::TWOSENSOR |Turnout::EXACT |Turnout::INDIRECT;
 setFeedbackModes(feedbackModes);
}

/**
 * constructor with default values - this creates the "defining instance" of
 * the operation type hence it cannot be deleted
 */
/*public*/ SensorTurnoutOperation::SensorTurnoutOperation(QObject *parent)
 : CommonTurnoutOperation("Sensor", defaultInterval, defaultMaxTries, parent)
{
   // this("Sensor", defaultInterval, defaultMaxTries);
feedbackModes = Turnout::ONESENSOR | Turnout::TWOSENSOR |Turnout::EXACT |Turnout::INDIRECT;
setFeedbackModes(feedbackModes);
}

/**
 * return clone with different name
 */
/*public*/ TurnoutOperation* SensorTurnoutOperation::makeCopy(QString n) {
    return new SensorTurnoutOperation(n, interval, maxTries);
}

/*public*/ int SensorTurnoutOperation::getDefaultInterval() {
    return defaultInterval;
}

/*public*/ int SensorTurnoutOperation::getDefaultMaxTries() {
    return defaultMaxTries;
}
/**
 * get a TurnoutOperator instance for this operation
 * @return	the operator
 */
/*public*/ TurnoutOperator* SensorTurnoutOperation::getOperator(AbstractTurnout* t) {
    return new SensorTurnoutOperator(t, interval, maxTries);
}

