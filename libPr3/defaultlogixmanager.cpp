#include "defaultlogixmanager.h"
#include "decimalformat.h"
#include "conditional.h"
#include "logix.h"
#include "defaultlogix.h"
#include "instancemanager.h"
#include "entryexitpairs.h"
#include "oblockmanager.h"
#include "warrantmanager.h"
#include "signalheadmanager.h"
#include "signalmastmanager.h"
#include "loggerfactory.h"

/*static*/ DefaultLogixManager* DefaultLogixManager::_instance = nullptr;

DefaultLogixManager::DefaultLogixManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("DefaultLogixManager");
 setProperty("JavaClassName", "jmri.managers.DefaultLogixManager");

 paddedNumber = new DecimalFormat("0000");
 registerSelf();

 InstanceManager::turnoutManagerInstance()->addVetoableChangeListener(this);
 InstanceManager::sensorManagerInstance()->addVetoableChangeListener(this);
 InstanceManager::memoryManagerInstance()->addVetoableChangeListener(this);
 ((AbstractProxyManager*)InstanceManager::getDefault("SignalHeadManager"))->addVetoableChangeListener(this);
 ((AbstractProxyManager*)InstanceManager::getDefault("SignalMastManager"))->addVetoableChangeListener(this);
 ((AbstractManager*)InstanceManager::getDefault("BlockManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
 InstanceManager::lightManagerInstance()->addVetoableChangeListener(this);
 ((AbstractManager*)InstanceManager::getDefault("ConditionalManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
 ((AbstractManager*) InstanceManager::getDefault("WarrantManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
 ((AbstractManager*)InstanceManager::getDefault("OBlockManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
 ((AbstractManager*)InstanceManager::getDefault("EntryExitPairs"))->VetoableChangeSupport::addVetoableChangeListener(this);
}
/**
 * Basic Implementation of a LogixManager.
 * <P>
 * Note that Logix system names must begin with IX, and be followed by a
 * string, usually, but not always, a number. All alphabetic characters
 * in a Logix system name must be upper case. This is enforced when a Logix
 * is created.
 * <P>
 * The system names of Conditionals belonging to a Logix begin with the
 * Logix's system name, then there is a capital C and a number.
 *
 * @author      Dave Duchamp Copyright (C) 2007
 * @version	$Revision: 18102 $
 */
///*public*/ class DefaultLogixManager extends AbstractManager
//    implements LogixManager, java.beans.PropertyChangeListener {

///*public*/ DefaultLogixManager() {
//    super();
//}

/*public*/ int DefaultLogixManager::getXMLOrder() const{
    return Manager::LOGIXS;
}

/*public*/ QString DefaultLogixManager::getSystemPrefix() const { return "I"; }
/*public*/ QChar DefaultLogixManager::typeLetter() const { return 'X'; }

/**
 * Method to create a new Logix if the Logix does not exist
 *   Returns nullptr if a Logix with the same systemName or userName
 *       already exists, or if there is trouble creating a new Logix.
 */
/*public*/ Logix* DefaultLogixManager::createNewLogix(QString systemName, QString userName) {
    // Check that Logix does not already exist
    Logix* x;
    if (userName!= "" ) {
        x = (Logix*)getByUserName(userName)->self();
        if (x!=nullptr) return nullptr;
    }
    x = (Logix*)getBySystemName(systemName)->self();
    if (x==nullptr) x = (Logix*)getBySystemName(systemName.toUpper())->self();   // for compatibility?
    if (x!=nullptr) return nullptr;
    // Logix does not exist, create a new Logix
    x = (Logix*)new DefaultLogix(systemName,userName);
    // save in the maps
    AbstractManager::Register(x);

    // Keep track of the last created auto system name
    updateAutoNumber(systemName);

 return x;
}

/*public*/ Logix* DefaultLogixManager::createNewLogix(QString userName) {
 return createNewLogix(getAutoSystemName(), userName);
}

/**
 * Remove an existing Logix and delete all its conditionals.
 * Logix must have been deactivated
 * before invoking this.
 */
/*public*/ void DefaultLogixManager::deleteLogix(Logix* x) {
    // delete conditionals if there are any
    int numConditionals = x->getNumConditionals();
    if (numConditionals>0) {
        Conditional* c = nullptr;
        for (int i = 0;i<numConditionals;i++) {
            c = static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"))->getBySystemName(
                    x->getConditionalByNumberOrder(i));
            static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"))->deleteConditional(c);
        }
    }
    // delete the Logix
    AbstractManager::deregister(x);
    x->dispose();
}

/**
 * Activate all Logixs that are not currently active
 * This method is called after a configuration file is loaded.
 */
/*public*/ void DefaultLogixManager::activateAllLogixs() {
    // Guarantee Initializer executes first.
 Logix* x = nullptr;
    NamedBean* nb = getBySystemName(/*LRouteTableAction::LOGIX_INITIALIZER*/"RTXINITIALIZER");
    if (nb!=nullptr) {
     x = (DefaultLogix*) nb->self();
        x->activateLogix();
        x->setGuiNames();
    }
    // iterate thru all Logixs that exist
    QStringListIterator iter(AbstractManager::getSystemNameList());
    while (iter.hasNext()) {
        // get the next Logix
        QString sysName = iter.next();
        if (sysName==nullptr) {
            log->error("System name nullptr when activating Logixs");
            break;
        }
        if (sysName==(/*LRouteTableAction.LOGIX_INITIALIZER*/"RTXINITIALIZER")) {
            continue;
        }
        x = (Logix*)getBySystemName(sysName)->self();
        if (x==nullptr) {
            log->error("Error getting Logix *"+sysName+"* when activating Logixs");
            break;
        }
        if (loadDisabled) {
            // user has requested that Logixs be loaded disabled
            log->warn("load disabled set - will not activate logic for: " + x->getDisplayName());
            x->setEnabled(false);
        }
        if (x->getEnabled()){
            //System.out.println("logix set enabled");
            x->activateLogix();
        }
        x->setGuiNames();
    }
    // reset the load switch
    loadDisabled = false;
}

/**
 * Method to get an existing Logix.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns nullptr.
 */
/*public*/ Logix* DefaultLogixManager::getLogix(QString name) {
    Logix* x = (Logix*)getByUserName(name)->self();
    if (x!=nullptr) return x;
    return (Logix*)getBySystemName(name)->self();
}

/*public*/ NamedBean *DefaultLogixManager::getBySystemName(QString name)  {
    return /*(Logix*)*/_tsys->value(name);
}

/*public*/ NamedBean *DefaultLogixManager::getByUserName(QString key)  {
    return /*(Logix*)*/_tuser->value(key);
}

/**
 * Support for loading Logixs in a disabled state to debug loops
 */
/*public*/ void DefaultLogixManager::setLoadDisabled(bool s) {loadDisabled = s;}

/*static*/ /*public*/ DefaultLogixManager* DefaultLogixManager::instance() {
    if (_instance == nullptr) {
        _instance = new DefaultLogixManager();
    }
    return (_instance);
}

//@Override
//@Nonnull
/*public*/ QString DefaultLogixManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "Logixes" : "Logix");
}

/*public*/ QString DefaultLogixManager::getNamedBeanClass()const {
    return "Logix";
}

/*static*/ Logger* DefaultLogixManager::log = LoggerFactory::getLogger("DefaultLogixManager");
//}
