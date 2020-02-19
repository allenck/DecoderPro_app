#include "defaultconditionalmanager.h"
#include "defaultlogixmanager.h"
#include "instancemanager.h"
#include "logix.h"
#include "defaultconditional.h"
#include "../LayoutEditor/sensorgroupframe.h"
#include "sensorgroupconditional.h"
#include "defaultlogix.h"
#include "loggerfactory.h"
//#include "pattern.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

DefaultConditionalManager::DefaultConditionalManager(QObject *parent) :
    ConditionalManager(parent)
{
 setObjectName("DefaultConditionalManager");
 // --- Conditional Where Used processes ---

 /**
  * Maintain a list of conditionals that refer to a particular conditional.
  * @since 4.7.4
  */
  conditionalWhereUsed = QMap<QString, QList<QString> >();
 registerSelf();
}
/**
 * Basic Implementation of a ConditionalManager.
 * <P>
 * Note that Conditionals always have an associated parent Logix.
 * <P>
 * Logix system names must begin with IX, and be followed by a
 * string, usually, but not always, a number. The system names of Conditionals
 * always begin with the parent Logix's system name, then there is a capital C
 * and a number.
 *<P>
 * Conditional system names are set automatically when the Conditional is created.
 * All alphabetic characters in a Conditional system name must be upper case. This
 * is enforced when a new Conditional is created via LogixTableAction.java.
 *
 * @author      Dave Duchamp Copyright (C) 2007
 * @author      Pete Cresman Copyright (C) 2009
 * @version	$Revision: 18102 $
 */
///*public*/ class DefaultConditionalManager extends AbstractManager
//    implements ConditionalManager, java.beans.PropertyChangeListener {

///*public*/ DefaultConditionalManager() {
//    super();
//}
/*static*/ DefaultConditionalManager* DefaultConditionalManager::_instance = NULL;


/*public*/ int DefaultConditionalManager::getXMLOrder(){
    return Manager::CONDITIONALS;
}

/*public*/ QString DefaultConditionalManager::getSystemPrefix() { return "I"; }
/*public*/ char DefaultConditionalManager::typeLetter() { return 'X'; }

/**
 * Method to create a new Conditional if the Conditional does not exist
 *   If the parent Logix cannot be found, the userName cannot be checked, but
 *		the Conditional is still created. The scenario can happen when a Logix
 *      is loaded from a file after its Conditionals.
 * @return NULL if a Conditional with the same systemName or userName
 *       already exists, or if there is trouble creating a new Conditional
 */
/*public*/ Conditional* DefaultConditionalManager::createNewConditional(QString systemName, QString userName) {
    // check that Conditional with same system name does not already exist
    Conditional* c = getBySystemName(systemName);
    if (c!=NULL) {
        return NULL;
    }
    if (userName != NULL && userName.length() > 0) {
        c = getByUserName(userName);
        if (c!=NULL) {
            if (systemName==(c->getSystemName())) {
                return NULL;
            }
        }
    }
    if (userName == NULL) log->error("User name is NULL!");
    if (systemName != NULL && systemName.length() > 0)
    {
     c = getBySystemName(systemName);
     if (c!=NULL)
     {
         return NULL;
     }
    }
    // Get the potential parent Logix
    Logix* lgx = getParentLogix(systemName);
    if (lgx == NULL) {
        log->error(tr("Unable to find the parent logix for conditional '%1'").arg(systemName));
        return NULL;
    }

    // Check the user name
    if (userName != NULL && userName.length() > 0) {
        c = getByUserName(lgx, userName);
        if (c != NULL) {
            return NULL;        // Duplicate user name within the parent Logix
        }
    }
    // Conditional does not exist, create a new Conditional
    if (systemName == NULL) return NULL; // needs name in this case
    if (systemName.startsWith(SensorGroupFrame::ConditionalSystemPrefix)) {
        c = (Conditional*)new SensorGroupConditional(systemName, userName);
    } else {
        c = (Conditional*)new DefaultConditional(systemName, userName);
    }
    // save in the maps
//    Register(c);
    bool addCompleted = lgx->addConditional(systemName, c);
    if (!addCompleted) {
        return NULL;
    }
    return c;
}

/**
 * Do not insist that Conditional user names are unique,
 * unlike the usual NamedBean support
 */
//@Override
/*protected*/ void DefaultConditionalManager::handleUserNameUniqueness(Conditional* s) {
    // eventually needs error checking and reporting
}

/**
 * Regex patterns to derive the logix system name from the conditional system name
 * The 3 route patterns deal with Route Logix names that end with a number,
 * such as Logix RTX123 with Conditional RTX1231T.
 */
/*private*/ /*static*/ /*final*/ QStringList DefaultConditionalManager::PATTERNS = QStringList()
  <<  "(.*?)(C\\d+$)"               // Standard IX
  <<  "(.*?)([1-9]{1}[ALT]$)"       // LRoute/Route, 1-9
  <<  "(.*?)([0-9]{2}[ALT]$)"       // LRoute/Route, 10-99
  <<  "(.*?)([0-9]{3}[ALT]$)";        // LRoute/Route, 100-999


/**
 * Parses the Conditional system name to get the parent Logix system name,
 * then gets the parent Logix, and returns it.  For sensor groups, the parent
 * Logix name is 'SYS'.  LRoutes and exported Routes (RTX prefix) require
 * special logic
 *
 * @param name - system name of Conditional (must be trimmed and upper case)
 * @return the parent Logix or NULL
 */
//@Override
/*public*/ Logix* DefaultConditionalManager::getParentLogix(QString name)
{
 if (name == NULL || name.length() < 4)
 {
  return NULL;
 }
#if 0
 // Check for standard names
 for (QString pattern : PATTERNS)
 {
  Pattern* r = Pattern::compile(pattern);
  Matcher* m = r->matcher(name);
  if (m->find())
  {
   Logix* lgx = ((LogixManager*) InstanceManager::getDefault("LogixManager"))->getBySystemName(m->group(1));
   if (lgx != NULL)
   {
       return lgx;
   }
  }
 }
#else
 foreach (QString regex, PATTERNS)
 {
  QRegularExpression re(regex);
  QRegularExpressionMatch match = re.match(name);
  if(match.hasMatch())
  {
   Logix* lgx = (Logix*)((LogixManager*) InstanceManager::getDefault("LogixManager"))->getBySystemName(match.captured(1));
   if (lgx != NULL)
   {
       return lgx;
   }
  }
 }
#endif
 // Now try non-standard names using a brute force scan
 LogixManager* logixManager = (LogixManager*) InstanceManager::getDefault("LogixManager");
 for (QString xName : logixManager->getSystemNameList())
 {
  Logix* lgx = logixManager->getLogix(xName);
  for (int i = 0; i < lgx->getNumConditionals(); i++)
  {
   QString cdlName = lgx->getConditionalByNumberOrder(i);
   if (cdlName == (name)) {
       return lgx;
   }
  }
 }
 return NULL;
}

/**
 * Remove an existing Conditional. Parent Logix must have been deactivated
 * before invoking this.
 */
/*public*/ void DefaultConditionalManager::deleteConditional(Conditional* c) {
    deregister(c);
}

/**
 * Method to get an existing Conditional.
 *	First looks up assuming that name is a User Name. Note: the parent Logix
 *		must be passed in x for user name lookup.
 *	If this fails, or if x == NULL, looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 * @param x - parent Logix (may be NULL)
 * @param name - name to look up
 * @return NULL if no match found
 */
/*public*/ Conditional* DefaultConditionalManager::getConditional(Logix* x,QString name) {
    Conditional* c = NULL;
    if (x != NULL) {
        c = getByUserName(x,name);
        if (c!=NULL) return c;
    }
    return getBySystemName(name);
}

/*public*/ Conditional* DefaultConditionalManager::getConditional(QString name) {
    Conditional* c = getBySystemName(name);
    if (c == NULL) {
        c = getByUserName(name);
    }
    return c;
}

/*public*/ Conditional* DefaultConditionalManager::getByUserName(QString key) {
    if (key == NULL)  return NULL;
    LogixManager* logixManager = (LogixManager*)InstanceManager::getDefault("LogixManager");
    QStringListIterator iter(((DefaultLogixManager*) logixManager)->getSystemNameList());
    while (iter.hasNext()) {
        // get the next Logix
        QString sName = iter.next();     //sName a logix nams
        Logix* x = (Logix*)((DefaultLogixManager*) logixManager)->getBySystemName(sName);
        if (x == NULL) {
            break;
        }
        for (int i=0; i< ((DefaultLogix*)x)->getNumConditionals(); i++)  {
            sName = ((DefaultLogix*)x)->getConditionalByNumberOrder(i);   // sName now a conditional name
            if (sName == NULL) {
                break;
            }
            Conditional* c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getBySystemName(sName);
            if (c == NULL) {
                break;
            }
            if (key==(c->getUserName()))
            {
                return c;
            }
        }
    }
    return NULL;
}

/*public*/ Conditional* DefaultConditionalManager::getByUserName(Logix* x,QString key) {
    if (x == NULL) return NULL;
    for (int i = 0;i<((DefaultLogix*)x)->getNumConditionals();i++) {
        Conditional* c = getBySystemName(((DefaultLogix*)x)->getConditionalByNumberOrder(i));
        if (c!=NULL) {
            QString uName = c->getUserName();
            if (key==(uName)) return c;
        }
    }
    return NULL;
}

//@Override
/*public*/ Conditional* DefaultConditionalManager::getBySystemName(QString name) {
    if (name == NULL) {
        return NULL;
    }
    Logix* lgx = getParentLogix(name);
    if (lgx == NULL) {
        return NULL;
    }
    return lgx->getConditional(name);
//@        return (Conditional) _tsys.get(name);
}

/**
 * Get a list of all Conditional system names with the specified Logix
 * parent
 */
//@Override
/*public*/ QStringList DefaultConditionalManager::getSystemNameListForLogix(Logix* x) {
//        log.error("getSystemNameListForLogix - Not implemented yet.");
//        return NULL;
    if (x == NULL) {
        return QStringList();
    }
    QStringList nameList = QStringList();

    for (int i = 0; i < x->getNumConditionals(); i++) {
        nameList.append(x->getConditionalByNumberOrder(i));
    }
    nameList.sort();


    return nameList;
}

/**
 * Get a list of all Conditional system names
 * Overrides the bean method
 * @since 4.7.4
 * @return a list of conditional system names regardless of parent Logix
 */
//@Override
/*public*/ QStringList DefaultConditionalManager::getSystemNameList() {
 QStringList nameList = QStringList();

    LogixManager* logixManager = (LogixManager*)InstanceManager::getDefault("LogixManager");
    for (QString xName : logixManager->getSystemNameList()) {
        Logix* lgx = logixManager->getLogix(xName);
        for (int i = 0; i < lgx->getNumConditionals(); i++) {
            nameList.append(lgx->getConditionalByNumberOrder(i));
        }
    }
    nameList.sort();
    return nameList;
}

/*static*/ /*public*/ DefaultConditionalManager* DefaultConditionalManager::instance() {
    if (_instance == NULL) {
        _instance = new DefaultConditionalManager();
    }
    return (_instance);
}

/**
 * Return a copy of the entire map.  Used by
 * {@link jmri.jmrit.beantable.LogixTableAction#buildWhereUsedListing}
 * @since 4.7.4
 * @return a copy of the map
 */
//@Override
/*public*/ QMap<QString, QList<QString> > DefaultConditionalManager::getWhereUsedMap() {
    return QMap<QString, QList<QString> >(conditionalWhereUsed);
}

/**
 * Add a conditional reference to the array indicated by the target system name.
 * @since 4.7.4
 * @param target The system name for the target conditional
 * @param reference The system name of the conditional that contains the conditional reference
 */
//@Override
/*public*/ void DefaultConditionalManager::addWhereUsed(QString target, QString reference) {
    if (target.isNull() || target == ("")) {
        log->error("Invalid target name for addWhereUsed");
        return;
    }
    if (reference.isNull() || reference == ("")) {
        log->error("Invalid reference name for addWhereUsed");
        return;
    }

    if (conditionalWhereUsed.contains(target)) {
        QList<QString> refList = conditionalWhereUsed.value(target);
        if (!refList.contains(reference)) {
            refList.append(reference);
            conditionalWhereUsed.insert(target, refList); //replace
        }
    } else {
        QList<QString> refList = QStringList();
        refList.append(reference);
        conditionalWhereUsed.insert(target, refList);
    }
}

/**
 * Get a list of conditional references for the indicated conditional
 * @since 4.7.4
 * @param target The target conditional for a conditional reference
 * @return an ArrayList or NULL if none
 */
//@Override
/*public*/ QList<QString> DefaultConditionalManager::getWhereUsed(QString target) {
    if (target.isNull() || target == ("")) {
        log->error("Invalid target name for getWhereUsed");
        return QStringList();
    }
    return conditionalWhereUsed.value(target);
}

/**
 * Remove a conditional reference from the array indicated by the target system name.
 * @since 4.7.4
 * @param target The system name for the target conditional
 * @param reference The system name of the conditional that contains the conditional reference
 */
//@Override
/*public*/ void DefaultConditionalManager::removeWhereUsed(QString target, QString reference) {
    if (target.isNull() || target == ("")) {
        log->error("Invalid target name for removeWhereUsed");
        return;
    }
    if (reference.isNull() || reference == ("")) {
        log->error("Invalid reference name for removeWhereUsed");
        return;
    }

    if (conditionalWhereUsed.contains(target)) {
        QStringList refList = conditionalWhereUsed.value(target);
        refList.removeOne(reference);
        if (refList.size() == 0) {
            conditionalWhereUsed.remove(target);
        }
    }
}

/**
 * Display the complete structure, used for debugging purposes.
 * @since 4.7.4
 */
//@Override
/*public*/ void DefaultConditionalManager::displayWhereUsed() {
    log->info("- Display Conditional Where Used     ");
    //SortedSet<String> keys = new TreeSet<>(conditionalWhereUsed.keys());
    QList<QString> keys = conditionalWhereUsed.keys();
    for (QString key : keys) {
    log->info(tr("    Target: %1                  ").arg(key));
        QList<QString> refList = conditionalWhereUsed.value(key);
        for (QString ref : refList) {
        log->info(tr("      Reference: %1             ").arg(ref));
        }
    }
}

/**
 * Get the target system names used by this conditional
 * @since 4.7.4
 * @param reference The system name of the conditional the refers to other conditionals.
 * @return a list of the target conditionals
 */
//@Override
/*public*/ QList<QString> DefaultConditionalManager::getTargetList(QString reference) {
    QList<QString> targetList = QStringList();
    //SortedSet<String> keys = new TreeSet<>(conditionalWhereUsed.keySet());
    QStringList keys = conditionalWhereUsed.keys();
    for (QString key : keys) {
        QList<QString> refList = conditionalWhereUsed.value(key);
        for (QString ref : refList) {
            if (ref ==(reference)) {
                targetList.append(key);
            }
        }
    }
    return targetList;
}
/*private*/ /*final*/ /*static*/ Logger* DefaultConditionalManager::log = LoggerFactory::getLogger("DefaultConditionalManager");
