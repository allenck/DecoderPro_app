#include "defaultconditionalmanagerxml.h"
#include "conditionalmanager.h"
#include "instancemanager.h"
#include "defaultconditional.h"
#include "conditionalvariable.h"
#include "conditionalaction.h"
#include "defaultconditionalaction.h"
#include "defaultconditionalmanager.h"
#include <QDomNode>
#include <QDomNamedNodeMap>
#include <QDomAttr>
#include "logix.h"
#include "conditionaleditbase.h"

DefaultConditionalManagerXml::DefaultConditionalManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log =  new Logger("DefaultConditionalManagerXml");
 setObjectName("DefaultConditionalManagerXml");
}
/**
 * Provides the functionality for
 * configuring ConditionalManagers
 * <P>
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Pete Cressman Copyright (C) 2009, 2011
 * @version $Revision: 20237 $
 */
///*public*/ class DefaultConditionalManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

///*public*/ DefaultConditionalManagerXml() {
//}

/**
 * Default implementation for storing the contents of a
 * ConditionalManager
 * @param o Object to store, of type ConditionalManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement DefaultConditionalManagerXml::store(QObject* o)
{
 QDomElement conditionals = doc.createElement("conditionals");
 setStoreElementClass(conditionals);
 ConditionalManager* tm = (ConditionalManager*) o;
 if (tm!=NULL)
 {
  QStringListIterator iter(tm->getSystemNameList());

  // don't return an element if there are not conditionals to include
  if (!iter.hasNext()) return QDomElement();

  // store the conditionals
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname==NULL) log->error("System name NULL during store");
   log->debug("conditional system name is "+sname);
   Conditional* c = ((DefaultConditionalManager*)tm)->getBySystemName(sname);
   QDomElement elem = doc.createElement("conditional");
   elem.setAttribute("systemName", sname);
   QDomElement e1;
   elem.appendChild(e1=doc.createElement("systemName"));
   e1.appendChild(doc.createTextNode(sname));

   // store common parts
   storeCommon(c, elem);
   elem.setAttribute("antecedent", ((DefaultConditional*)c)->getAntecedentExpression());
   elem.setAttribute("logicType",((DefaultConditional*)c)->getLogicType());

   if (((DefaultConditional*)c)->getTriggerOnChange())
   {
    elem.setAttribute("triggerOnChange", "yes");
   }
   else
   {
    elem.setAttribute("triggerOnChange", "no");
   }

   // save child state variables
   QList <ConditionalVariable*>* variableList = ((DefaultConditional*)c)->getCopyOfStateVariables();
   for (int k=0; k < variableList->size(); k++)
   {
    ConditionalVariable* variable = variableList->at(k);
    QDomElement vElem = doc.createElement("conditionalStateVariable");
    int oper = variable->getOpern();
    if (oper == Conditional::OPERATOR_AND && variable->isNegated()) {
        oper = Conditional::OPERATOR_AND_NOT;    // backward compatibility
    } else if (oper == Conditional::OPERATOR_NONE && variable->isNegated()) {
        oper = Conditional::OPERATOR_NOT;        // backward compatibility
    }
    vElem.setAttribute("operator",(oper));
    if (variable->isNegated())
        vElem.setAttribute("negated","yes");
    else
        vElem.setAttribute("negated","no");
    vElem.setAttribute("type",(variable->getType()));
    vElem.setAttribute("systemName", variable->getName());
    vElem.setAttribute("dataString", variable->getDataString());
    vElem.setAttribute("num1",(variable->getNum1()));
    vElem.setAttribute("num2",(variable->getNum2()));
    if (variable->doTriggerActions())
        vElem.setAttribute("triggersCalc","yes");
    else
        vElem.setAttribute("triggersCalc","no");
    elem.appendChild(vElem);
   }
   // save action information
   QList<ConditionalAction*>* actionList = ((DefaultConditional*)c)->getCopyOfActions();
   for (int k=0; k < actionList->size(); k++)
   {
    ConditionalAction* action = actionList->at(k);
    QDomElement aElem = doc.createElement("conditionalAction");
    aElem.setAttribute("option",(action->getOption()));
    aElem.setAttribute("type",(action->getType()));
    aElem.setAttribute("systemName",action->getDeviceName());
    aElem.setAttribute("data",(action->getActionData()));
    // To allow regression of config files back to previous releases
    // add "delay" attribute
    //try {
    bool bOk;
    ((DefaultConditionalAction*)action)->getActionString().toInt(&bOk);
        aElem.setAttribute("delay",((DefaultConditionalAction*)action)->getActionString());
    //} catch (NumberFormatException* nfe) {
    if(!bOk)
    {
     aElem.setAttribute("delay","0");
    }
    aElem.setAttribute("string",((DefaultConditionalAction*)action)->getActionString());
    elem.appendChild(aElem);
    }
    conditionals.appendChild(elem);
   }
  }
  return (conditionals);
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param conditionals The top-level element being created
 */
/*public*/ void DefaultConditionalManagerXml::setStoreElementClass(QDomElement conditionals) {
    conditionals.setAttribute("class","jmri.managers.configurexml.DefaultConditionalManagerXml");
}

/*public*/ void DefaultConditionalManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

/**
 * Create a ConditionalManager object of the correct class, then
 * register and fill it.
 * @param conditionals Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool DefaultConditionalManagerXml::load(QDomElement conditionals)  throw (Exception){
    // create the master object
    replaceConditionalManager();
    // load individual logixs
    loadConditionals(conditionals);
    return true;
}

/**
 * Utility method to load the individual Logix objects.
 * If there's no additional info needed for a specific logix type,
 * invoke this with the parent of the set of Logix elements.
 * @param conditionals QDomElement containing the Logix elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ void DefaultConditionalManagerXml::loadConditionals(QDomElement conditionals)
{
 QDomNodeList conditionalList = conditionals.elementsByTagName("conditional");
 if (log->isDebugEnabled())
  log->debug("Found "+QString::number(conditionalList.size())+" conditionals");
 ConditionalManager* tm = (ConditionalManager*)InstanceManager::getDefault("ConditionalManager");

 for (int i=0; i<conditionalList.size(); i++)
 {
  QDomElement condElem = conditionalList.at(i).toElement();
  QString sysName = getSystemName(condElem);
  if (sysName == "")
  {
   log->warn("unexpected NULL in systemName "+condElem.tagName());
   break;
  }

  // omitted username is treated as empty, not null
  QString userName = getUserName(condElem);
  if (userName == "") {
      userName = "";
  }

  if (log->isDebugEnabled()) log->debug("create conditional: ("+sysName+")("+
                            (userName==""?"<NULL>":userName)+")");
  Conditional* c = ((DefaultConditionalManager*)tm)->createNewConditional(sysName, userName);
  if (c==nullptr)
  {
      // Check for parent Logix
      Logix* x = tm->getParentLogix(sysName);
      if (x == nullptr) {
          log->warn(tr("Conditional '%1' has no parent Logix").arg(sysName));  // NOI18N
          continue;
      }

      // Found a potential parent Logix, check the Logix index
      bool inIndex = false;
      for (int j = 0; j < x->getNumConditionals(); j++) {
          QString cName = x->getConditionalByNumberOrder(j);
          if (sysName == (cName)) {
              inIndex = true;
              break;
          }
      }
      if (!inIndex) {
          log->warn(tr("Conditional '%1' is not in the Logix index").arg(sysName));  // NOI18N
          continue;
      }

      // Create the condtional
      c = tm->createNewConditional(sysName, userName);
  }

  if (c == nullptr) {
      // Should never get here
      log->error(tr("Conditional '%1' cannot be created").arg(sysName));  // NOI18N
      continue;
  }

  // load common parts
  loadCommon(c, condElem);

  QString ant = "";
  int logicType = Conditional::ALL_AND;
  if (condElem.attribute("antecedent") != "")
  {
   QString antTemp = condElem.attribute("antecedent");  // NOI18N
   ant = ConditionalEditBase::translateAntecedent(antTemp, true);
  }
  if (condElem.attribute("logicType") != "")
  {
       logicType =
           condElem.attribute("logicType").toInt();
  }
  ((DefaultConditional*)c)->setLogicType(logicType, ant);

  // load state variables, if there are any
  QDomNodeList conditionalVarList = conditionalList.at(i).toElement().
                                   elementsByTagName("conditionalStateVariable");

  if (conditionalVarList.size() == 0) {
       log->warn("No state variables found for conditional "+sysName);
  }
  QList <ConditionalVariable*>* variableList = new QList <ConditionalVariable*> ();
  for (int n=0; n<conditionalVarList.size(); n++)
  {
    ConditionalVariable* variable = new ConditionalVariable();
    if (conditionalVarList.at(n).toElement().attribute("operator") == "")
    {
     log->warn("unexpected NULL in operator "+conditionalVarList.at(n).toElement().tagName()+
               " "+conditionalVarList.at(n).toElement().tagName());
    }
    else
    {
     int oper = conditionalVarList.at(n).toElement().attribute("operator").toInt();
     if (oper == Conditional::OPERATOR_AND_NOT)
     {
      variable->setNegation(true);
      oper = Conditional::OPERATOR_AND;
     }
     else if (oper == Conditional::OPERATOR_NOT)
     {
      variable->setNegation(true);
      oper = Conditional::OPERATOR_NONE;
     }
     variable->setOpern(oper);
    }
    if (conditionalVarList.at(n).toElement().attribute("negated") != "")
    {
     if ("yes"==(conditionalVarList.at(n).toElement().attribute("negated")))
      variable->setNegation(true);
     else
      variable->setNegation(false);
    }
    variable->setType(conditionalVarList.at(n).toElement()
                                       .attribute("type").toInt());
    variable->setName(conditionalVarList.at(n).toElement()
                                       .attribute("systemName"));
    if (conditionalVarList.at(n).toElement().attribute("dataString") != "")
    {
      variable->setDataString(conditionalVarList.at(n).toElement()
                                           .attribute("dataString"));
    }
    if (conditionalVarList.at(n).toElement().attribute("num1") != "")
    {
     variable->setNum1(conditionalVarList.at(n).toElement()
                                           .attribute("num1").toInt());
    }
    if (conditionalVarList.at(n).toElement().attribute("num2") != NULL)
    {
     variable->setNum2(conditionalVarList.at(n).toElement()
                                           .attribute("num2").toInt());
    }
    variable->setTriggerActions(true);
    if (conditionalVarList.at(n).toElement().attribute("triggersCalc") != "")
    {
     if ("no"==(conditionalVarList.at(n).toElement()
                                   .attribute("triggersCalc")))
      variable->setTriggerActions(false);
    }
    variableList->append(variable);
   }
   ((DefaultConditional*)c)->setStateVariables(variableList);

   // load actions - there better be some
   QDomNodeList conditionalActionList = conditionalList.at(i).toElement().
                                   elementsByTagName("conditionalAction");

   // Really OK, since a user may use such conditionals to define a reusable
   // expression of state variables.  These conditions are then used as a
   // state variable in other conditionals.  (pwc)
   //if (conditionalActionList.size() == 0) {
   //    log->warn("No actions found for conditional "+sysName);
   //}
   QList <ConditionalAction*>* actionList = new QList <ConditionalAction*> ();
   QString attr = "";
   for (int n=0; n<conditionalActionList.size(); n++)
   {
    DefaultConditionalAction* action = new DefaultConditionalAction();
    QString str_attr = attributes(conditionalActionList.at(n).toElement());

    attr = conditionalActionList.at(n).toElement().attribute("option");
    if ( attr != NULL)
    {
     action->setOption(attr.toInt());
    }
    else
    {
     log->warn("unexpected NULL in option "+conditionalActionList.at(n).toElement().tagName()+
               " "+ str_attr); //conditionalActionList.at(n).toElement().tagName());
    }
    // actionDelay is removed.  delay data is stored as a String to allow
    // such data be referenced by internal memory.
    // For backward compatibility, set delay "int" as a string
    attr = conditionalActionList.at(n).toElement().attribute("delay");
    if (attr != "")
    {
     action->setActionString(attr);
    }
    attr = conditionalActionList.at(n).toElement().attribute("type");
    if ( attr != "")
    {
     action->setType(attr.toInt());
    }
    else
    {
     log->warn("unexpected NULL in type "+conditionalActionList.at(n).toElement().tagName()+
               " "+ str_attr); //conditionalActionList.at(n).toElement().tagName());
    }
    attr = conditionalActionList.at(n).toElement().attribute("systemName");
    if ( attr != "")
    {
     action->setDeviceName(attr);
    }
    else
    {
     log->warn("unexpected NULL in systemName "+conditionalActionList.at(n).toElement().tagName()+
               " "+ str_attr); //conditionalActionList.at(n).toElement().tagName());
    }
    attr = conditionalActionList.at(n).toElement().attribute("data");
    if ( attr != "")
    {
     action->setActionData(attr.toInt());
    }
    else
    {
     log->warn("unexpected NULL in action data "+conditionalActionList.at(n).toElement().tagName()+
               " "+ str_attr); //conditionalActionList.at(n).toElement().tagName());
    }
    attr = conditionalActionList.at(n).toElement().attribute("string");
    if ( attr != "")
    {
     action->setActionString(attr);
    }
    else
    {
     log->warn("unexpected NULL in action string "+conditionalActionList.at(n).toElement().tagName()+
               " "+ str_attr);
    }
    actionList->append(action);
   }
   ((DefaultConditional*)c)->setAction(actionList);

   // 1/16/2011 - trigger for execution of the action list changed to execute each
   // time state is computed.  Formerly execution of the action list was done only
   // when state changes.  All conditionals are upgraded to this new policy.
   // However, for conditionals with actions that toggle on change of state
   // the old policy should be used.
   bool triggerOnChange = false;
   if (conditionalList.at(i).toElement().attribute("triggerOnChange") != "")
   {
    if ("yes"==(conditionalList.at(i).toElement().attribute("triggerOnChange")))
    {
     triggerOnChange = true;
    }
   }
   else
   {
       /* Don't upgrade -Let old be as is
       for (int k=0; k<actionList.size(); k++){
           ConditionalAction action = actionList.get(k);
           if (action.getOption()==Conditional::ACTION_OPTION_ON_CHANGE){
               triggerOnChange = true;
               break;
           }
       }
       */
   triggerOnChange = true;
  }
  ((DefaultConditional*)c)->setTriggerOnChange(triggerOnChange);
 }
}

// helper routine to display contents of a QDomElement.
/*private*/ QString DefaultConditionalManagerXml::attributes(QDomElement e)
{
 QString str;
 QDomNamedNodeMap map = e.attributes();
 for(int i=0; i < map.count(); i++)
 {
  QDomAttr a = map.item(i).toAttr();
  str.append(" " + a.name() + "='" +a.value()+ "'\n");
 }
 return str;
}
/**
 * Replace the current ConditionalManager, if there is one, with
 * one newly created during a load operation. This is skipped
 * if they are of the same absolute type.
 */
/*protected*/ void DefaultConditionalManagerXml::replaceConditionalManager()
{
 if (QString(((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->metaObject()->className()) == ("DefaultConditionalManager"))
  return;
 // if old manager exists, remove it from configuration process
 if ((ConditionalManager*)InstanceManager::getNullableDefault("ConditionalManager") != NULL)
     ((ConfigureManager*) InstanceManager::getDefault("ConfigureManager"))->deregister(
            (ConditionalManager*)InstanceManager::getDefault("ConditionalManager") );
    // register new one with InstanceManager
    DefaultConditionalManager* pManager = DefaultConditionalManager::instance();
    InstanceManager::store(pManager, "ConditionalManager");
    InstanceManager::setDefault("ConditionalManager", pManager);
    // register new one for configuration
    ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(pManager, Manager::CONDITIONALS);
}

/*public*/ int DefaultConditionalManagerXml::loadOrder()const{
    return ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getXMLOrder();
}
