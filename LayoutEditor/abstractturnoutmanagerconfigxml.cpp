#include "abstractturnoutmanagerconfigxml.h"
#include "turnoutmanager.h"
#include "turnoutoperationmanagerxml.h"
#include "proxyturnoutmanager.h"
#include "turnoutoperationxml.h"
#include "instancemanager.h"

AbstractTurnoutManagerConfigXML::AbstractTurnoutManagerConfigXML(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("AbstractTurnoutManagerConfigXML");
 log->setDebugEnabled(true);
}
AbstractTurnoutManagerConfigXML::~AbstractTurnoutManagerConfigXML()
{
 delete log;
}

/**
 * Provides the abstract base and store functionality for
 * configuring TurnoutManagers, working with
 * AbstractTurnoutManagers.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement turnouts)
 * class, relying on implementation here to load the individual turnouts.
 * Note that these are stored explicitly, so the
 * resolution mechanism doesn't need to see *Xml classes for each
 * specific Turnout or AbstractTurnout subclass at store time.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 19100 $
// */
///*public*/ abstract class AbstractTurnoutManagerConfigXML extends AbstractNamedBeanManagerConfigXML {

//    /*public*/ AbstractTurnoutManagerConfigXML() {
//    }

/**
 * Default implementation for storing the contents of a
 * TurnoutManager and associated TurnoutOperation's
 * @param o QObject* to store, of type TurnoutManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AbstractTurnoutManagerConfigXML::store(QObject* o)
{
 QDomElement turnouts = doc.createElement("turnouts");
 setStoreElementClass(turnouts);
 TurnoutManager* tm = (TurnoutManager*) o;
 if (tm!=nullptr)
 {
  TurnoutOperationManagerXml* tomx = new TurnoutOperationManagerXml();
  QDomElement opElem = tomx->store((TurnoutOperationManager*)InstanceManager::getDefault("TurnoutOperationManager"));
  turnouts.appendChild(opElem);
  QStringListIterator iter(((AbstractTurnoutManager*)tm)->getSystemNameList());

  // don't return an element if there are not turnouts to include
  if (!iter.hasNext()) return QDomElement();

  QString defaultclosed = ((AbstractTurnoutManager*)tm)->getDefaultClosedSpeed();
  QString defaultthrown = ((AbstractTurnoutManager*)tm)->getDefaultThrownSpeed();
  QDomElement e1;
  turnouts.appendChild(e1=doc.createElement("defaultclosedspeed"));
  e1.appendChild(doc.createTextNode(defaultclosed));
  QDomElement e2;
  turnouts.appendChild(e2=doc.createElement("defaultthrownspeed"));
  e2.appendChild(doc.createTextNode(defaultthrown));

  // store the turnouts
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname==nullptr) log->error("System name nullptr during store");
   log->debug("system name is "+sname);
   Turnout* t = (Turnout*)((AbstractTurnoutManager*)tm)->getBySystemName(sname);
   QDomElement elem = doc.createElement("turnout");
   //elem.setAttribute("systemName", sname); // deprecated for 2.9.* series
   QDomElement e3;
   elem.appendChild(e3=doc.createElement("systemName"));
   e3.appendChild(doc.createTextNode(sname));
   log->debug("store turnout "+sname);

   storeCommon(t, elem);

   // include feedback info
   elem.setAttribute("feedback", ((AbstractTurnout*)t)->getFeedbackModeName());
   NamedBeanHandle<Sensor*>* s;
   s = ((AbstractTurnout*)t)->getFirstNamedSensor();
   if (s!=nullptr) elem.setAttribute("sensor1", s->getName());
   s = ((AbstractTurnout*)t)->getSecondNamedSensor();
   if (s!=nullptr) elem.setAttribute("sensor2", s->getName());

   // include turnout inverted
   elem.setAttribute("inverted", ((AbstractTurnout*)t)->getInverted()?"true":"false");

   if (((AbstractTurnout*)t)->canLock(Turnout::CABLOCKOUT | Turnout::PUSHBUTTONLOCKOUT))
   {
    // include turnout locked
    elem.setAttribute("locked",((AbstractTurnout*)t)->getLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT)?"true":"false");
    // include turnout lock mode
    QString lockOpr;
    if (((AbstractTurnout*)t)->canLock(Turnout::CABLOCKOUT) && t->canLock(Turnout::PUSHBUTTONLOCKOUT))
    {
     lockOpr = "both";
    }
    else if (((AbstractTurnout*)t)->canLock(Turnout::CABLOCKOUT))
    {
     lockOpr = "cab";
    }
    else if (((AbstractTurnout*)t)->canLock(Turnout::PUSHBUTTONLOCKOUT))
    {
     lockOpr = "pushbutton";
    }
    else
    {
     lockOpr = "none";
    }
    elem.setAttribute("lockMode", lockOpr);
    // include turnout decoder
    elem.setAttribute("decoder", ((AbstractTurnout*)t)->getDecoderName());
   }

   // include number of control bits, if different from one
   int iNum = ((AbstractTurnout*)t)->getNumberOutputBits();
   if (iNum!=1) elem.setAttribute("numBits",iNum);

   // include turnout control type, if different from 0
   int iType = ((AbstractTurnout*)t)->getControlType();
   if (iType!=0) elem.setAttribute("controlType",iType);

   // add operation stuff
   QString opstr = nullptr;
   TurnoutOperation* op = ((AbstractTurnout*)t)->getTurnoutOperation();
   if (((AbstractTurnout*)t)->getInhibitOperation())
   {
    opstr = "Off";
   }
   else if (op==nullptr)
   {
    opstr = "Default";
   }
   else if (op->isNonce())
   {	// nonce operation appears as subelement
    TurnoutOperationXml* adapter = TurnoutOperationXml::getAdapter(op);
    if (adapter != nullptr)
    {
     QDomElement nonceOpElem = adapter->store(doc,op);
     if (!opElem.isNull())
     {
      elem.appendChild(nonceOpElem);
     }
    }
   }
   else
   {
    opstr = op->getName();
   }
   if (opstr != nullptr)
   {
    elem.setAttribute("automate", opstr);
   }
   if((((AbstractTurnout*)t)->getDivergingSpeed()!=nullptr) && (((AbstractTurnout*)t)->getDivergingSpeed()!=("")) && !((AbstractTurnout*)t)->getDivergingSpeed().contains("Global"))
   {
    QDomElement e1;
    elem.appendChild(e1=doc.createElement("divergingSpeed"));
    e1.appendChild(doc.createTextNode(((AbstractTurnout*)t)->getDivergingSpeed()));
   }
   if((((AbstractTurnout*)t)->getStraightSpeed()!=nullptr) && (((AbstractTurnout*)t)->getStraightSpeed()!=("")) && !((AbstractTurnout*)t)->getStraightSpeed().contains("Global"))
   {
    QDomElement e2;
    elem.appendChild(e2=doc.createElement("straightSpeed"));
    e2.appendChild(doc.createTextNode(((AbstractTurnout*)t)->getStraightSpeed()));
   }

   // add element
   turnouts.appendChild(elem);
  }
 }
 return turnouts;
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param turnouts The top-level element being created
 */
// /*abstract*/ /*public*/ void setStoreElementClass(QDomElement turnouts);

/**
 * Create a TurnoutManager object of the correct class, then
 * register and fill it->
 * @param turnouts Top level QDomElement to unpack.
 */
// /*abstract*/ /*public*/ bool load(QDomElement turnouts);

/**
 * Utility method to load the individual Turnout objects.
 * If there's no additional info needed for a specific turnout type,
 * invoke this with the parent of the set of Turnout elements.
 * @param turnouts QDomElement containing the Turnout elements to load.
 * @return true if succeeded
 */
//@SuppressWarnings("unchecked")
/*public*/ bool AbstractTurnoutManagerConfigXML::loadTurnouts(QDomElement turnouts, QDomElement /*perNode*/)
{
 bool result = true;
 QDomNodeList operationList = turnouts.elementsByTagName("operations");
 if (operationList.size()>1)
 {
  log->warn("unexpected extra elements found in turnout operations list");
  result = false;
 }
 if (operationList.size()>0)
 {
  TurnoutOperationManagerXml* tomx = new TurnoutOperationManagerXml();
  tomx->load(operationList.at(0).toElement(), QDomElement());
 }
 QDomNodeList turnoutList = turnouts.elementsByTagName("turnout");
 if (log->isDebugEnabled()) log->debug("Found "+QString::number(turnoutList.size())+" turnouts");
 ProxyTurnoutManager* tm = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();

 try
 {
  if (!turnouts.firstChildElement("defaultclosedspeed").isNull())
  {
   QString closedSpeed = turnouts.firstChildElement("defaultclosedspeed").text();
   if (closedSpeed!=nullptr && closedSpeed!=(""))
   {
    tm->setDefaultClosedSpeed(closedSpeed);
   }
  }
 }
 catch (JmriException ex)
 {
  log->error(ex.getMessage());
 }

 try
 {
  if (!turnouts.firstChildElement("defaultthrownspeed").isNull())
  {
   QString thrownSpeed = turnouts.firstChildElement("defaultthrownspeed").text();
   if (thrownSpeed!=nullptr && thrownSpeed!=(""))
   {
    tm->setDefaultThrownSpeed(thrownSpeed);
   }
  }
 }
 catch (JmriException ex)
 {
  log->error(ex.getMessage());
 }

 for (int i=0; i<turnoutList.size(); i++)
 {
  QDomElement elem = turnoutList.at(i).toElement();
  QString sysName = getSystemName(elem);
  if ( sysName == "" )
  {
   log->error("unexpected nullptr in systemName "+elem.tagName());
   result = false;
   break;
  }
  QString userName = getUserName(elem);
  if (log->isDebugEnabled()) log->debug("create turnout: ("+sysName+")("+(userName==nullptr?"<nullptr>":userName)+")");
  Turnout* t = (Turnout*)tm->getBySystemName(sysName);
  if (t==nullptr)
  {
   t = tm->newTurnout(sysName, userName);
   //Nothing is logged in the console window as the newTurnoutFunction already does this.
                //log->error("Could not create turnout: '"+sysName+"' user name: '"+(userName==nullptr?"":userName)+"'");
   if (t==nullptr)
   {
    result = false;
    continue;
   }
   //result = false;
   //continue;
  }
  else if (userName!=nullptr)
   t->setUserName(userName);

  // Load common parts
  loadCommon(t, elem);

  // now add feedback if needed
  QString a;
  a = elem.attribute("feedback");
  if (a!=nullptr)
  {
   try
   {
    ((AbstractTurnout*)t)->setFeedbackMode(a);
   }
   catch (IllegalArgumentException e)
   {
    log->error("Can not set feedback mode: '"+a+"' for turnout: '"+sysName+"' user name: '"+(userName==nullptr?"":userName)+"'");
    result = false;
   }
  }
  a = elem.attribute("sensor1");
  if (a!=nullptr)
  {
   try
   {
    ((AbstractTurnout*)t)->provideFirstFeedbackSensor(a);
   }
   catch (JmriException e)
   {
    result = false;
   }
  }
  a = elem.attribute("sensor2");
  if (a!=nullptr)
  {
   try
   {
    ((AbstractTurnout*)t)->provideSecondFeedbackSensor(a);
   }
   catch (JmriException e)
   {
    result = false;
   }
  }

  // check for turnout inverted
  ((AbstractTurnout*)t)->setInverted(elem.attribute("inverted", "false")=="true");

  // check for turnout decoder
  a = turnoutList.at(i).toElement().attribute("decoder");
  if (a!=nullptr)
  {
   ((AbstractTurnout*)t)->setDecoderName(a);
  }

  // check for turnout lock mode
  a = turnoutList.at(i).toElement().attribute("lockMode");
  if (a != nullptr)
  {
   if (a==("both"))
    ((AbstractTurnout*)t)->enableLockOperation(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
   if (a==("cab"))
   {
    ((AbstractTurnout*)t)->enableLockOperation(Turnout::CABLOCKOUT, true);
    ((AbstractTurnout*)t)->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, false);
   }
   if (a==("pushbutton"))
   {
    ((AbstractTurnout*)t)->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, true);
    ((AbstractTurnout*)t)->enableLockOperation(Turnout::CABLOCKOUT, false);
   }
  }

  // check for turnout locked
  a = turnoutList.at(i).toElement().attribute("locked");
  if (a!=nullptr)
  {
   ((AbstractTurnout*)t)->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, a==("true"));
  }


  // number of bits, if present - if not, defaults to 1
  a = turnoutList.at(i).toElement().attribute("numBits");
  if (a==nullptr)
  {
  ((AbstractTurnout*)t)->setNumberOutputBits(1);
  }
  else
  {
   int iNum = a.toInt();
   if ( (iNum==1) || (iNum==2) )
   {
    ((AbstractTurnout*)t)->setNumberOutputBits(iNum);
   }
   else
   {
    log->warn("illegal number of output bits for control of turnout "+sysName);
    ((AbstractTurnout*)t)->setNumberOutputBits(1);
    result = false;
   }
  }

  // control type, if present - if not, defaults to 0
  a = turnoutList.at(i).toElement().attribute("controlType");
  if (a==nullptr)
  {
   ((AbstractTurnout*)t)->setControlType(0);
  }
  else
  {
   int iType = a.toInt();
   if (iType>=0)
   {
    ((AbstractTurnout*)t)->setControlType(iType);
   }
   else
   {
    log->warn("illegal control type for control of turnout "+sysName);
    ((AbstractTurnout*)t)->setControlType(0);
    result = false;
   }
  }

  // operation stuff
  QDomNodeList myOpList = turnoutList.at(i).toElement().elementsByTagName("operation");
  if (myOpList.size()>0)
  {
   if (myOpList.size()>1)
   {
    log->warn("unexpected extra elements found in turnout-specific operations");
    result = false;
   }
   TurnoutOperation* toper = TurnoutOperationXml::loadOperation(myOpList.at(0).toElement());
   ((AbstractTurnout*)t)->setTurnoutOperation(toper);
  }
  else
  {
   a = turnoutList.at(i).toElement().attribute("automate");
   if (a!=nullptr)
   {
    QString str = a;
    if (str==("Off"))
    {
     ((AbstractTurnout*)t)->setInhibitOperation(true);
    }
    else if (str!=("Default"))
    {
     TurnoutOperation* toper = TurnoutOperationManager::getInstance()->getOperation(str);
     ((AbstractTurnout*)t)->setTurnoutOperation(toper);
    }
   }
  }

  //  set initial state from sensor feedback if appropriate
  ((AbstractTurnout*)t)->setInitialKnownStateFromFeedback();
  try
  {
   ((AbstractTurnout*)t)->setDivergingSpeed("Global");
   if (!elem.firstChildElement("divergingSpeed").isNull())
   {
    QString speed = elem.firstChildElement("divergingSpeed").text();
    if (speed!=nullptr && speed!=("") && !speed.contains("Global"))
    {
     ((AbstractTurnout*)t)->setDivergingSpeed(speed);
    }
   }
  }
  catch (JmriException ex)
  {
    log->error(ex.toString());
  }

  try
  {
   ((AbstractTurnout*)t)->setStraightSpeed("Global");
   if (!elem.firstChildElement("straightSpeed").isNull())
   {
    QString speed = elem.firstChildElement("straightSpeed").text();
    if (speed!=nullptr && speed!=("") && !speed.contains("Global"))
    {
     ((AbstractTurnout*)t)->setStraightSpeed(speed);
    }
   }
  }
  catch (JmriException ex)
  {
   log->error(ex.toString());
  }
 }
 return result;
}

/*public*/ int AbstractTurnoutManagerConfigXML::loadOrder() const{
    return ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getXMLOrder();
}
