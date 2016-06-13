#include "turnoutoperator.h"
#include "abstractturnout.h"

//TurnoutOperator::TurnoutOperator(QObject *parent) :
//    QThread(parent)
//{
//}
/**
 * Some (not much) common machinery for the concrete turnout operator
 * classes.
 * @author John Harper	Copyright 2005
 *
 */
//public abstract class TurnoutOperator extends Thread {


/*protected*/ TurnoutOperator::TurnoutOperator(AbstractTurnout* t, QObject *parent) : QThread(parent)
{
 myTurnout = t;
 setObjectName("Operating turnout "+t->getSystemName());
}

/*protected*/ void TurnoutOperator::operatorCheck() throw (TurnoutOperatorException)
{
 if (myTurnout->getCurrentOperator()!= this)
 {
  //throw new TurnoutOperatorException();
 }
}

/**
 * Exception thrown when the turnout's operator has changed while the
 * operator is running. This implies that another operation has been
 * started and that this one should just quietly stop doing its thing.
 */
//	static public class TurnoutOperatorException extends java.lang.Exception { }

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TurnoutOperator.class.getName());
//}
