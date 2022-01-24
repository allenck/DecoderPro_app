#include "turnoutoperationmanagerxml.h"
#include "turnoutoperationxml.h"
#include "turnoutoperationmanager.h"
#include "loggerfactory.h"

TurnoutOperationManagerXml::TurnoutOperationManagerXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
}

/**
 * @author John Harper
 *
// */
///*public*/ class TurnoutOperationManagerXml extends jmri.configurexml.AbstractXmlAdapter {

//    /*public*/ TurnoutOperationManagerXml() {
//    }

/*public*/ void TurnoutOperationManagerXml::setStoreElementClass(QDomElement elem)
{
 //elem.setAttribute("class",getClass().getName());
    elem.setAttribute("class", "jmri.configurexml.turnoutoperations.NoFeedbackTurnoutOperationXml");
}

///*public*/ void TurnoutOperationManagerXml::load(QDomElement /*element*/, QObject /*o*/)
//{
// log->error("Invalid method called");
//}

//@SuppressWarnings("unchecked")
/*public*/ bool TurnoutOperationManagerXml::load(QDomElement sharedOperations, QDomElement perNodeOperations) throw (JmriConfigureXmlException)
{
 bool result = true;
 TurnoutOperationManager* manager = TurnoutOperationManager::getInstance();
 if (!sharedOperations.attribute("automate").isNull())
 {
//  try
//  {
   manager->setDoOperations(sharedOperations.attribute("automate")==("true"));
//  }
//  catch(NumberFormatException ex)
//  {
//   result = false;
//  }
 }
 QDomNodeList operationsList = sharedOperations.elementsByTagName("operation");
 if (log->isDebugEnabled()) log->debug("Found "+QString("%1").arg(operationsList.size())+" operations");
 for (int i=0; i<operationsList.size(); i++)
 {
  TurnoutOperationXml::loadOperation(operationsList.at(i).toElement());
 }
 return result;
}

/*public*/ QDomElement TurnoutOperationManagerXml::store(QObject* o)
{
 QDomElement elem = doc.createElement("operations");
 //if (o instanceof TurnoutOperationManager)
 if(qobject_cast<TurnoutOperationManager*>(o)!= NULL)
 {
  TurnoutOperationManager* manager = (TurnoutOperationManager*)o;
  elem.setAttribute("automate", (manager->getDoOperations()?"true":"false"));
  QList<TurnoutOperation*> operations = manager->getTurnoutOperations();
  for (int i=0; i<operations.length(); ++i)
  {
   TurnoutOperation* op = operations.at(i);
   if (!op->isNonce())
   {
    // nonces are stored with their respective turnouts
    TurnoutOperationXml* adapter = TurnoutOperationXml::getAdapter(op);
    if (adapter != NULL)
    {
     QDomElement opElem = adapter->store(doc,op);
     if (!opElem.isNull())
     {
      //elem.addContent(opElem);
      elem.appendChild(opElem);
     }
    }
   }
  }
 }
 return elem;
}

/*static*/ Logger* TurnoutOperationManagerXml::log = LoggerFactory::getLogger("TurnoutOperationManagerXml");
//}
