#include "rawturnoutoperation.h"
#include "nofeedbackturnoutoperation.h"
#include "../LayoutEditor/rawturnoutoperator.h"

//RawTurnoutOperation::RawTurnoutOperation(QObject *parent) :
//    CommonTurnoutOperation(parent)
//{
//}
/**
 * RawTurnoutOperation class - specialization of TurnoutOperation to provide
 * automatic retry for a turnout with no feedback by sending raw NMRA commands
 * to the turnout.
 * This class is based on the NoTurnoutOperation class.
 * @author Paul Bender
 * @version $Revision: 17977 $
 */
///*public*/ class RawTurnoutOperation extends CommonTurnoutOperation {


/*
 * Default values and constraints
 */

/*static*/ /*public*/ /*final*/ int RawTurnoutOperation::defaultInterval = 300;
/*static*/ /*public*/ /*final*/ int RawTurnoutOperation::defaultMaxTries = 1;

/*public*/ RawTurnoutOperation::RawTurnoutOperation(QString n, int i, int mt, QObject *parent)
 : CommonTurnoutOperation(n, i, mt, parent)
{
 //super(n, i, mt);
 common();
 setFeedbackModes(feedbackModes);
}

/**
 * constructor with default values - this creates the "defining instance" of
 * the operation type hence it cannot be deleted
 */
/*public*/ RawTurnoutOperation::RawTurnoutOperation(QObject *parent)
 : CommonTurnoutOperation("Raw", defaultInterval, defaultMaxTries)
{
 //this("Raw", defaultInterval, defaultMaxTries);
 common();
}
void RawTurnoutOperation::common()
{
 // This class should only be used with DIRECT, ONESENSOR or TWOSENSOR
        // feedback modes.
 /*final*/ int feedbackModes =
              Turnout::DIRECT | Turnout::EXACT | Turnout::INDIRECT
            | Turnout::ONESENSOR | Turnout::TWOSENSOR;

}

/**
 * return clone with different name
 */
/*public*/ TurnoutOperation* RawTurnoutOperation::makeCopy(QString n) {
    return new NoFeedbackTurnoutOperation(n, interval, maxTries);
}

/*public*/ int RawTurnoutOperation::getDefaultInterval() {
    return defaultInterval;
}

/*public*/ int RawTurnoutOperation::getDefaultMaxTries() {
    return defaultMaxTries;
}

/*static*/ /*public*/ int RawTurnoutOperation::getDefaultIntervalStatic() {
    return defaultInterval;
}

/*static*/ /*public*/ int RawTurnoutOperation::getDefaultMaxTriesStatic() {
    return defaultMaxTries;
}

/**
 * get a TurnoutOperator instance for this operation
 * @return	the operator
 */
/*public*/ TurnoutOperator* RawTurnoutOperation::getOperator(AbstractTurnout* t) {
    return new RawTurnoutOperator(t, interval, maxTries);
}
