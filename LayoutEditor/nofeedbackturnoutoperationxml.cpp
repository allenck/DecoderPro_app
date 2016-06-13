#include "nofeedbackturnoutoperationxml.h"
#include "nofeedbackturnoutoperation.h"

NoFeedbackTurnoutOperationXml::NoFeedbackTurnoutOperationXml(QObject *parent) : CommonTurnoutOperationXml(parent)
{
 setObjectName("NoFeedbackTurnoutOperationXml");
}
/**
 * Concrete subclass to save/restore NoFeedbackTurnoutOperation object
 * to/from XML. Most of the work is done by CommonTurnoutOperationXml
 * @author John Harper	Copyright 2005
 *
 */
//public class NoFeedbackTurnoutOperationXml extends CommonTurnoutOperationXml {

/**
 * called for a newly-constructed object to load it from an XML element
 * @param e the XML element of type "turnoutOperation"
 */
/*public*/ TurnoutOperation* NoFeedbackTurnoutOperationXml::loadOne(QDomElement /*e*/)
{
// try
// {
//  Class<?> myOpClass = Class.forName("jmri.NoFeedbackTurnoutOperation");
//  return super.loadOne(e, myOpClass.getConstructor(new Class[]{String.class, int.class, int.class}),
//                NoFeedbackTurnoutOperation.getDefaultIntervalStatic(),
//                NoFeedbackTurnoutOperation.getDefaultMaxTriesStatic());
// }
// catch (ClassNotFoundException e1)
// {
//  log.error("while creating NoFeedbackTurnoutOperation", e1);
//  return NULL;
// }
// catch (NoSuchMethodException e2)
// {
//  log.error("while creating NoFeedbackTurnoutOperation", e2);
//  return NULL;
// }
    //return new TurnoutOperation("");
    return new NoFeedbackTurnoutOperation();

}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(NoFeedbackTurnoutOperation.class.getName());
//}
