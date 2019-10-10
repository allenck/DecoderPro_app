#include "commonturnoutoperation.h"

/**
 * CommonTurnoutOperation class - specialization of TurnoutOperation to contain
 * common properties and methods for concrete subclasses
 * @author John Harper
 * @version $Revision: 17977 $
 */
///*public*/ abstract class CommonTurnoutOperation extends TurnoutOperation {


/*public*/ CommonTurnoutOperation::CommonTurnoutOperation(QString n, int i, int mt, QObject *parent) : TurnoutOperation(n, parent)
{
    //super(n);
    interval = getDefaultInterval();
    maxTries = getDefaultMaxTries();
    setInterval(i);
    setMaxTries(mt);
}

/**
 * get a TurnoutOperator instance for this operation
 * @return	the operator
 */

/*public*/ int CommonTurnoutOperation::getInterval() { return interval; }

/*public*/ int CommonTurnoutOperation::getMaxTries() { return maxTries; }

/*public*/ bool CommonTurnoutOperation::equivalentTo(TurnoutOperation* other)
{
 if (this->metaObject()->className() ==other->metaObject()->className())
 {
  return interval==((CommonTurnoutOperation*)other)->interval &&
            maxTries==((CommonTurnoutOperation*)other)->maxTries;
 } else return false;
}

/**
 * set new value for interval. do nothing if not in range.
 * @param newInterval
 */
/*public*/ void CommonTurnoutOperation::setInterval(int newInterval)
{
 if (newInterval>=minInterval && newInterval<=maxInterval)
 {
  interval = newInterval;
 }
}

/**
 * set new value for MaxTries. do nothing if not in range.
 * @param newMaxTries
 */
/*public*/ void CommonTurnoutOperation::setMaxTries(int newMaxTries)
{
 if (newMaxTries>=minMaxTries && newMaxTries<=maxMaxTries)
 {
  maxTries = newMaxTries;
 }
}
int CommonTurnoutOperation::getDefaultInterval() { return 1;}
int CommonTurnoutOperation::getDefaultMaxTries() {return 1;}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CommonTurnoutOperation.class.getName());
//}
