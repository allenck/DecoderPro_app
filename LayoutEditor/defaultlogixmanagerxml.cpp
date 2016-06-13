#include "defaultlogixmanagerxml.h"
#include "logixmanager.h"
#include "logix.h"
#include "instancemanager.h"
#include "defaultlogixmanager.h"
#include "defaultlogix.h"

DefaultLogixManagerXml::DefaultLogixManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("DefaultLogixManagerXml");
}
/**
 * Provides the functionality for
 * configuring LogixManagers
 * <P>
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @version $Revision: 18102 $
 */
///*public*/ class DefaultLogixManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

///*public*/ DefaultLogixManagerXml() {
//}

/**
 * Default implementation for storing the contents of a
 * LogixManager
 * @param o Object to store, of type LogixManager
 * @return QDomElementcontaining the complete info
 */
/*public*/ QDomElement DefaultLogixManagerXml::store(QObject* o)
{
 QDomElement logixs = doc.createElement("logixs");
 setStoreElementClass(logixs);
 LogixManager* tm = (LogixManager*) o;
 if (tm!=NULL)
 {
  QStringListIterator iter (tm->getSystemNameList());

  // don't return an element if there are not Logix to include
  if (!iter.hasNext()) return QDomElement();

  // store the Logix
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname==NULL) log->error("System name NULL during store");
   log->debug("logix system name is "+sname);
   Logix* x = ((DefaultLogixManager*)tm)->getBySystemName(sname);
   bool enabled = ((DefaultLogix*)x)->getEnabled();
   QDomElement elem = doc.createElement("logix");
   elem.setAttribute("systemName", sname);
   QDomElement e1;
   elem.appendChild(e1=doc.createElement("systemName"));
   e1.appendChild(doc.createTextNode(sname));

   // store common part
   storeCommon(x, elem);

   if (enabled) elem.setAttribute("enabled","yes");
   else elem.setAttribute("enabled","no");
   // save child Conditionals
   int numConditionals = ((DefaultLogix*)x)->getNumConditionals();
   if (numConditionals>0)
   {
    QString cSysName = "";
    QDomElement cElem = QDomElement();
    for (int k = 0;k<numConditionals;k++)
    {
     cSysName = ((DefaultLogix*)x)->getConditionalByNumberOrder(k);
     cElem = doc.createElement("logixConditional");
     cElem.setAttribute("systemName",cSysName);
     cElem.setAttribute("order",(k));
     elem.appendChild(cElem);
    }
   }
   logixs.appendChild(elem);
  }
 }
 return (logixs);
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param logixs The top-level element being created
 */
/*public*/ void DefaultLogixManagerXml::setStoreElementClass(QDomElement logixs) {
    logixs.setAttribute("class","jmri.managers.configurexml.DefaultLogixManagerXml");
}

/*public*/ void DefaultLogixManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

/**
 * Create a LogixManager object of the correct class, then
 * register and fill it.
 * @param logixs Top level QDomElementto unpack.
 * @return true if successful
 */
/*public*/ bool DefaultLogixManagerXml::load(QDomElement logixs) throw (Exception) {
    // create the master object
    replaceLogixManager();
    // load individual logixs
    loadLogixs(logixs);
    return true;
}

/**
 * Utility method to load the individual Logix objects.
 * If there's no additional info needed for a specific logix type,
 * invoke this with the parent of the set of Logix elements.
 * @param logixs QDomElementcontaining the Logix elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ void DefaultLogixManagerXml::loadLogixs(QDomElement logixs) {
    QDomNodeList logixList = logixs.elementsByTagName("logix");
    if (log->isDebugEnabled()) log->debug("Found "+QString::number(logixList.size())+" logixs");
    LogixManager* tm = InstanceManager::logixManagerInstance();

    for (int i=0; i<logixList.size(); i++)
    {

        QString sysName = getSystemName(logixList.at(i).toElement());
        if (sysName == NULL) {
            log->warn("unexpected NULL in systemName "+logixList.at(i).toElement().tagName());
            break;
        }

        QString userName = NULL;
        //bool enabled = true;
        QString yesno = "";
        if (logixList.at(i).toElement().attribute("userName") != NULL) {
            userName = logixList.at(i).toElement().attribute("userName");
        }
        if (logixList.at(i).toElement().attribute("enabled") != NULL) {
            yesno = logixList.at(i).toElement().attribute("enabled");
        }
        if (log->isDebugEnabled()) log->debug("create logix: ("+sysName+")("+
                                    (userName==NULL?"<NULL>":userName)+")");
        Logix* x = ((DefaultLogixManager*)tm)->createNewLogix(sysName, userName);
        if (x!=NULL) {
            // load common part
            loadCommon(x, logixList.at(i).toElement());

            // set enabled/disabled if attribute was present
            if ( (yesno!="")  ) {
                if (yesno==("yes")) ((DefaultLogix*)x)->setEnabled(true);
                else if (yesno==("no"))((DefaultLogix*)x)->setEnabled(false);
            }
            // load conditionals, if there are any
            QDomNodeList logixConditionalList = logixList.at(i).toElement().elementsByTagName("logixConditional");
            if (logixConditionalList.size()>0) {
                // add conditionals
                for (int n=0; n<logixConditionalList.size(); n++) {
                    if (logixConditionalList.at(n).toElement().attribute("systemName") == NULL) {
                        log->warn("unexpected NULL in systemName "+logixConditionalList.at(n).toElement().tagName()+
                                            " "+logixConditionalList.at(n).toElement().tagName());
                        break;
                    }
                    QString cSysName = logixConditionalList.at(n).toElement()
                                                        .attribute("systemName");
                    int cOrder = logixConditionalList.at(n).toElement()
                                                        .attribute("order").toInt();
                    // add conditional to logix
                    ((DefaultLogix*)x)->addConditional(cSysName,cOrder);
                }
            }
        }
    }
}

/**
 * Replace the current LogixManager, if there is one, with
 * one newly created during a load operation. This is skipped
 * if they are of the same absolute type.
 */
/*protected*/ void DefaultLogixManagerXml::replaceLogixManager() {
    LogixManager* instance = InstanceManager::logixManagerInstance();
    const char*  className = instance->metaObject()->className();
    if (className == "DefaultLogixManager")
        return;
    // if old manager exists, remove it from configuration process
    if (InstanceManager::logixManagerInstance() != NULL)
        ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->deregister(InstanceManager::logixManagerInstance() );

    // register new one with InstanceManager
    DefaultLogixManager* pManager = DefaultLogixManager::instance();
    InstanceManager::setLogixManager((LogixManager*)pManager);
    // register new one for configuration
    ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->registerConfig(pManager, Manager::LOGIXS);
}

/*public*/ int DefaultLogixManagerXml::loadOrder(){
    return ((DefaultLogixManager*)InstanceManager::logixManagerInstance())->getXMLOrder();
}
