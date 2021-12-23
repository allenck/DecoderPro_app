#include "commonturnoutoperationxml.h"
#include "commonturnoutoperation.h"
#include "turnoutoperation.h"

CommonTurnoutOperationXml::CommonTurnoutOperationXml(QObject *parent) :
    TurnoutOperationXml(parent)
{
}

/**
 * Concrete subclass to save/restore NoFeedbackTurnoutOperation object
 * to/from XML.
 * @author John Harper	Copyright 2005
 *
 */
///*public*/ abstract class CommonTurnoutOperationXml extends TurnoutOperationXml {

/*public*/ QDomElement CommonTurnoutOperationXml::store(QDomDocument doc, QObject* op)
{
    CommonTurnoutOperation* myOp = (CommonTurnoutOperation*)op;
    //QDomElement elem = super.store(op);
    QDomElement elem = TurnoutOperationXml::store(doc, op);
    elem.setAttribute("interval", myOp->getInterval());
    elem.setAttribute("maxtries", myOp->getMaxTries());
    return elem;
}

/**
 * called for a newly-constructed object to load it from an XML element
 * @param e the XML element of type "turnoutOperation"
 */
/*public*/ TurnoutOperation* CommonTurnoutOperationXml::loadOne(QDomElement e, /*Constructor<?> constr, */int di, int dmt)
{
 int interval = di;
 int maxTries = dmt;
//		boolean noDelete = false;
 TurnoutOperation* result = NULL;
 if (e.attribute("name") == "")
 {
  log.warn("unexpected NULL in name "+e.tagName()+" "/*+e.getAttributes()*/);
  return NULL;
 }
 QString name = e.attribute("name");
 if (e.attribute("interval") != NULL)
 {
  try
  {
   bool bOk;
   interval = e.attribute("interval").toInt(&bOk);
   if(!bOk) throw new NumberFormatException();
  } catch(NumberFormatException ex) { }
 }
 if (e.attribute("maxtries") != "")
 {
  try
  {
   bool bOk;
   maxTries = e.attribute("maxtries").toInt(&bOk);
   if(!bOk) throw new NumberFormatException();

   } catch(NumberFormatException ex) { }
  }
    // constructor takes care of enrolling the new operation
//    try {
//        result = (TurnoutOperation)constr.newInstance(new Object[]{name, Integer.valueOf(interval), Integer.valueOf(maxTries)});
//    } catch (InstantiationException* e1) {
//        log.error("while creating CommonTurnoutOperation", e1);
//        return NULL;
//    } catch (IllegalAccessException e2) {
//        log.error("while creating CommonTurnoutOperation", e2);
//        return NULL;
//    } catch (java.lang.reflect.InvocationTargetException e3) {
//        log.error("while creating CommonTurnoutOperation", e3);
//        return NULL;
//    }
    if (log.isDebugEnabled()) log.debug("create turnout operation: ("+name+")");
    return result;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CommonTurnoutOperationXml.class.getName());
//}
