#include "turnoutoperationxml.h"
#include "nofeedbackturnoutoperationxml.h"
#include "rawturnoutoperationxml.h"
#include "sensorturnoutoperationxml.h"
#include "turnoutoperation.h"
#include "stringutil.h"

TurnoutOperationXml::TurnoutOperationXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
}
/**
 * Superclass for save/restore of TurnoutOperation subclasses in XML.
 * @author John Harper	Copyright 2005
 *
 */
///*public*/ abstract class TurnoutOperationXml extends jmri.configurexml.AbstractXmlAdapter {

/**
 * inherited methods
 * @see jmri.configurexml.XmlAdapter#load(org.jdom.Element)
 */
/*public*/ bool TurnoutOperationXml::load(QDomElement e) throw (Exception)
{
    loadOne(e);
    return true;
}

///*public*/ /*abstract*/ TurnoutOperation* TurnoutOperationXml::loadOne(QDomElement e);

/**
 * Load one operation, using the appropriate adapter
 * @param e	element for operation
 */
/*public*/ /*static*/ TurnoutOperation* TurnoutOperationXml::loadOperation(QDomElement e)
{
 TurnoutOperation* result = NULL;
 QString className = e.attribute("class");
 if (className=="")
 {
  //log.error("class name missing in turnout operation \""+e.tagName()+"\"");
 }
 else
 {
//  try
//  {
//   Class<?> adapterClass = Class.forName(className);
//   if (adapterClass != NULL)
//   {
//    TurnoutOperationXml* adapter = (TurnoutOperationXml*)adapterClass.newInstance();
//    result = adapter.loadOne(e);
//    if (result.getName().charAt(0)=='*')
//    {
//        result.setNonce(true);
//    }
//   }
//  }
//  catch (ClassNotFoundException e1)
//  {
//   log.error("while creating TurnoutOperation", e1);
//   return NULL;
//  }
//  catch (IllegalAccessException e2)
//  {
//   log.error("while creating CommonTurnoutOperation", e2);
//   return NULL;
//  }
//  catch (InstantiationException e3)
//  {
//   log.error("while creating TurnoutOperation", e3);
//   return NULL;
//  }
  if(className == "jmri.configurexml.turnoutoperations.NoFeedbackTurnoutOperationXml")
  {
   result = (TurnoutOperation*) new NoFeedbackTurnoutOperationXml();
   return result;
  }
  else if(className == "jmri.configurexml.turnoutoperations.RawTurnoutOperationXml")
  {
   result = (TurnoutOperation*) new RawTurnoutOperationXml();
   return result;
  }
  else if(className == "jmri.configurexml.turnoutoperations.SensorTurnoutOperationXml")
  {
   result = (TurnoutOperation*) new SensorTurnoutOperationXml();
   return result;
  }
  else
  {
   result = (TurnoutOperation*) new SensorTurnoutOperationXml();
   return result;
  }
 }
}

/**
 * @see jmri.configurexml.XmlAdapter#load(org.jdom.Element, java.lang.Object)
 */
/*public*/ void TurnoutOperationXml::load(QDomElement element, QObject* o) throw (Exception)
{
    log.error("Invalid method called");
}

/**
 * common part of store - create the element and store the name and the class
 * @param	o	TurnoutOperation object
 * @return	partially filled element
 */
/*public*/ QDomElement TurnoutOperationXml::store(QDomDocument doc, QObject* o) {
    TurnoutOperation* myOp = (TurnoutOperation*)o;
    QDomElement elem = doc.createElement("operation");
    elem.setAttribute("name", myOp->getName());
    //elem.setAttribute("class", this->getClass().getName());
    //elem.setAttribute("class", "?Placeholder?");
    elem.setAttribute("class", "jmri.configurexml.turnoutoperations."+ myOp->getName()+"TurnoutOperationXml");
    return elem;
}

/**
 * Given an instance of a concrete subclass of
 * the TurnoutOperation class, looks for a corresponding ...Xml
 * class and creates an instance of it. If anything goes wrong (no such
 * class, wrong constructors, instantiation error, ....) just return NULL
 * @param op	operation for which configurator is required
 * @return	the configurator
 */
/*static*/ /*public*/ TurnoutOperationXml* TurnoutOperationXml::getAdapter(TurnoutOperation* op)
{
    TurnoutOperationXml* adapter = NULL;
#if 0 // Done (See following)
    QStringList fullOpNameComponents = StringUtil::split(op->getClass().getName(),".");

    QStringList myNameComponents =
            QStringList() << "jmri"<<"configurexml"<<"turnoutoperations"<<"TurnoutOperationXml";
    myNameComponents[myNameComponents.length-1] =
        fullOpNameComponents[fullOpNameComponents.length-1];
    QString fullConfigName = QStringUtil.join(myNameComponents, ".") + "Xml";
    try {
        Class<?> configClass = Class.forName(fullConfigName);
        adapter = (TurnoutOperationXml)configClass.newInstance();
    } catch (Throwable e) {
    }		// too many to list!
    if (adapter==NULL) {
        log.warn("could not create adapter class "+fullConfigName);
    }
#endif
    QString className = QString(op->metaObject()->className());
    if(className == "NoFeedbackTurnoutOperation")
        adapter = (TurnoutOperationXml*) new NoFeedbackTurnoutOperationXml();
    else     if(className == "RawTurnoutOperation")
        adapter = (TurnoutOperationXml*) new RawTurnoutOperationXml();
    else     if(className == "SensorTurnoutOperation")
        adapter = (TurnoutOperationXml*) new SensorTurnoutOperationXml();


    return adapter;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TurnoutOperationXml.class.getName());
//}
