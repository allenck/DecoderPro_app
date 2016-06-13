#include "defaultconditionalmanager.h"
#include "defaultlogixmanager.h"
#include "instancemanager.h"
#include "logix.h"
#include "defaultconditional.h"
#include "../LayoutEditor/sensorgroupframe.h"
#include "sensorgroupconditional.h"
#include "defaultlogix.h"

DefaultConditionalManager::DefaultConditionalManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("DefaultConditionalManager");
 log = new Logger("DefaultConditionalManager");
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
    if (systemName != NULL && systemName.length() > 0) {
        c = getBySystemName(systemName);
        if (c!=NULL) {
            return NULL;
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
    Register(c);
    return c;
}

/**
 * Parses the Conditional system name to get the parent Logix system name, then
 *    gets the parent Logix, and returns it.
 * @param name - system name of Conditional (must be trimmed and upper case)
 */
/*public*/ Logix* DefaultConditionalManager::getParentLogix(QString name) {
    if (name.length()<4) return NULL;
    for (int i = name.length()-1;i>2;i--) {
        if (name.at(i) == 'C') {
            return ((DefaultLogixManager*)InstanceManager::logixManagerInstance())->getBySystemName(
                                                name.mid(0,i));
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
    LogixManager* logixManager = InstanceManager::logixManagerInstance();
    QStringListIterator iter(((DefaultLogixManager*) logixManager)->getSystemNameList());
    while (iter.hasNext()) {
        // get the next Logix
        QString sName = iter.next();     //sName a logix nams
        Logix* x = ((DefaultLogixManager*) logixManager)->getBySystemName(sName);
        if (x == NULL) {
            break;
        }
        for (int i=0; i< ((DefaultLogix*)x)->getNumConditionals(); i++)  {
            sName = ((DefaultLogix*)x)->getConditionalByNumberOrder(i);   // sName now a conditional name
            if (sName == NULL) {
                break;
            }
            Conditional* c = ((DefaultConditionalManager*)InstanceManager::conditionalManagerInstance())->getBySystemName(sName);
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

/*public*/ Conditional* DefaultConditionalManager::getBySystemName(QString name) {
    if (name == NULL) return NULL;
    return (Conditional*)_tsys->value(name);
}

/**
 * Get a list of all Conditional system names with the specified Logix parent
 */
/*public*/ QStringList* DefaultConditionalManager::getSystemNameListForLogix(Logix* /*x*/) {
    log->error("getSystemNameListForLogix - Not implemented yet.");
    return NULL;
}

/*static*/ /*public*/ DefaultConditionalManager* DefaultConditionalManager::instance() {
    if (_instance == NULL) {
        _instance = new DefaultConditionalManager();
    }
    return (_instance);
}
