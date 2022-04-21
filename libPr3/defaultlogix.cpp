#include "defaultlogix.h"
#include "logger.h"
#include "exceptions.h"
#include "instancemanager.h"
#include "jmrisimplepropertylistener.h"
#include "../libPr3/logix.h"
#include "conditional.h"
#include "conditionalvariable.h"
#include "signalhead.h"
#include "abstractlightmanager.h"
#include "signalmast.h"
#include "defaultsignalmastmanager.h"
#include "abstractmemorymanager.h"
#include "jmritwostatepropertylistener.h"
#include "jmriclockpropertylistener.h"
#include "jmrimultistatepropertylistener.h"
#include "defaultconditional.h"
#include "defaultconditionalmanager.h"
#include "../Tables/lroutetableaction.h"
#include "abstractsignalheadmanager.h"
#include "simpletimebase.h"
#include "oblock.h"
#include "oblockmanager.h"
#include "entryexitpairs.h"
#include "warrantmanager.h"
#include "warrant.h"
#include "abstractnamedbean.h"
#include "destinationpoints.h"
#include "conditionalaction.h"
#include "vptr.h"
#include "jmriexception.h"

//DefaultLogix::DefaultLogix(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * Class providing the basic logic of the Logix interface.
 *
 * @author	Dave Duchamp Copyright (C) 2007
 * @version     $Revision: 21308 $
 * @author Pete Cressman Copyright (C) 2009
 */
///*public*/ class DefaultLogix extends AbstractNamedBean
//    implements Logix, java.io.Serializable {

/*public*/ DefaultLogix::DefaultLogix(QString systemName, QObject *parent) :
    Logix(systemName, "", parent)
{
 //super(systemName, userName);
 log = new Logger("DefaultLogix");
 _conditionalSystemNames = new QStringList();
 _listeners = new QList<JmriSimplePropertyListener*>();
 _conditionalMap = QMap<QString, Conditional*>();

 /**
  *  Operational instance variables (not saved between runs)
  */
 mEnabled = true;

 _isActivated = false;
}

/*public*/ DefaultLogix::DefaultLogix(QString systemName, QString userName, QObject *parent) :
    Logix(systemName, userName, parent)
{
 //super(systemName, userName);
 log = new Logger("DefaultLogix");
 _conditionalSystemNames = new QStringList();
 _listeners = new QList<JmriSimplePropertyListener*>();
 _conditionalMap = QMap<QString, Conditional*>();

 /**
  *  Operational instance variables (not saved between runs)
  */
 mEnabled = true;

 _isActivated = false;
}

///*public*/ DefaultLogix(String systemName) {
//    super(systemName);
//}


/**
 * Get number of Conditionals for this Logix
 */
/*public*/ int DefaultLogix::getNumConditionals() {
    return _conditionalSystemNames->size();
}

/**
 * Move 'row' to 'nextInOrder' and shift all between 'row' and 'nextInOrder'
 * up one position   ( row > nextInOrder )
 */
/*public*/ void DefaultLogix::swapConditional(int nextInOrder, int row) {
    if (row <= nextInOrder) {
        return;
    }
    QString temp = _conditionalSystemNames->at(row);
    for (int i = row; i > nextInOrder; i--)
    {
        _conditionalSystemNames->replace(i, _conditionalSystemNames->at(i-1));
    }
    _conditionalSystemNames->replace(nextInOrder, temp);
}

/**
 * Returns the system name of the conditional that will calculate in the
 * specified order. This is also the order the Conditional is listed in
 * the Add/Edit Logix dialog->
 * If 'order' is greater than the number of Conditionals for this Logix,
 * and empty String is returned.
 * @param order - order in which the Conditional calculates.
 */
/*public*/ QString DefaultLogix::getConditionalByNumberOrder(int order)
{
 try
 {
  if(order < 0 || order >= _conditionalSystemNames->count())
   throw new IndexOutOfBoundsException("invalid order");
  return _conditionalSystemNames->at(order);
 }
 catch (IndexOutOfBoundsException ioob)
 {
  return "";
 }
}

/**
 * Add a Conditional to this Logix Returns true if Conditional was
 * successfully added, returns false if the maximum number of conditionals
 * has been exceeded.
 *
 * @param systemName The Conditional system name
 * @param order      - the order this conditional should calculate in if
 *                   order is negative, the conditional is added at the end
 *                   of current group of conditionals
 */
//@Override
/*public*/ bool DefaultLogix::addConditional(QString systemName, int /*order*/) {
    _conditionalSystemNames->append(systemName);
    return (true);
}

/**
 * Add a child Conditional to the parent Logix.
 *
 * @since 4.7.4
 * @param systemName The system name for the Conditional object.
 * @param conditional The Conditional object.
 * @return true if the Conditional was added, false otherwise.
 */
//@Override
/*public*/ bool DefaultLogix::addConditional(QString systemName, Conditional* conditional) {
//    Conditional* chkDuplicate = _conditionalMap.putIfAbsent(systemName, conditional);
 if(!_conditionalMap.contains(systemName))
 {
  _conditionalMap.insert(systemName, conditional);
  return true;
 }
 log->error(tr("Conditional '%1' has already been added to Logix '%2'").arg(systemName).arg(getSystemName()));  // NOI18N
 return (false);
}

/**
 * Get a Conditional belonging to this Logix.
 *
 * @since 4.7.4
 * @param systemName The name of the Conditional object.
 * @return the Conditional object or null if not found.
 */
//@Override
/*public*/ Conditional* DefaultLogix::getConditional(QString systemName) {
    return _conditionalMap.value(systemName);
}

/**
 * Set enabled status.  Enabled is a bound property
 *   All conditionals are set to UNKNOWN state and recalculated
 *		when the Logix is enabled, provided the Logix has been
 *		previously activated.
 */
/*public*/ void DefaultLogix::setEnabled(bool state) {

    bool old = mEnabled;
    mEnabled = state;
    if (old != state) {
        bool active = _isActivated;
        deActivateLogix();
        activateLogix();
        _isActivated = active;
        for (int i=_listeners->size()-1; i>=0; i--)
        {
            _listeners->at(i)->setEnabled(state);
        }
        firePropertyChange("Enabled", QVariant(old), QVariant(state));
    }
}

/**
 * Get enabled status
*/
/*public*/ bool DefaultLogix::getEnabled() {
    return mEnabled;
}

/**
 * Delete a Conditional and remove it from this Logix
 * <P>
 * Note: Since each Logix must have at least one Conditional to
 *	do anything, the user is warned in Logix Table Action when the
 *  last Conditional is deleted.
 * <P>
 * Returns true if Conditional was successfully deleted, otherwise
 *  returns false.
 * @param systemName The Conditional system name
 */
/*public*/ QStringList* DefaultLogix::deleteConditional(QString systemName) {
    if (_conditionalSystemNames->size()<=0) {
        return (NULL);
    }
    // check other Logix(es) for use of this conditional (systemName) for use as a
    // variable in one of their conditionals
    QStringListIterator iter1 (((LogixManager*)InstanceManager::getDefault("LogixManager"))->getSystemNameList());
    while (iter1.hasNext()) {
        QString sNameLogix = iter1.next();
        if (sNameLogix!=(getSystemName()) ) {
            Logix* x = (Logix*)((LogixManager*)InstanceManager::getDefault("LogixManager"))->getBySystemName(sNameLogix)->self();
            int numCond = x->getNumConditionals();
            for (int i=0; i<numCond; i++) {
                QString sNameCond = x->getConditionalByNumberOrder(i);
                Conditional* c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getBySystemName(sNameCond);
                QList <ConditionalVariable*>* varList = c->getCopyOfStateVariables();
                for (int k=0; k<varList->size(); k++)  {
                    ConditionalVariable* v = varList->at(k);
                    if ( (v->getType()==Conditional::TYPE_CONDITIONAL_TRUE) ||
                         (v->getType()==Conditional::TYPE_CONDITIONAL_FALSE) )
                    {
                        QString name = v->getName();
                        Conditional* c1 = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getConditional(name);
                        if (c1 == NULL) {
                            log->error("\""+name+"\" is a non-existent Conditional variable in Conditional \""
                                      +c->getUserName()+"\" in Logix \""+x->getUserName()+"\" ("+sNameLogix+")");
                        } else {
                            if ( systemName==(c1->getSystemName()) ) {
                                QStringList* result = new QStringList();
                                        *result << name << systemName << c->getUserName() <<
                                                        sNameCond << x->getUserName() << sNameLogix;
                                return result;
                            }
                        }
                    }
                }
            }
        }
    }
    // Remove Conditional from this logix
    int ix = _conditionalSystemNames->indexOf(systemName);
    if (ix < 0) {
        log->error("attempt to delete Conditional not in Logix: "+systemName);
        return NULL;
    }
    _conditionalSystemNames->removeAt(ix);
    // delete the Conditional object
    Conditional* c = ((ConditionalManager*)((ConditionalManager*)InstanceManager::getDefault("ConditionalManager")))->getBySystemName(systemName);
    if (c == NULL) {
        log->error("attempt to delete non-existant Conditional - "+systemName);
        return NULL;
    }
    ((ConditionalManager*)((ConditionalManager*)InstanceManager::getDefault("ConditionalManager")))->deleteConditional(c);
    return (NULL);
}

/**
 * Calculate all Conditionals, triggering action if the user specified
 *   conditions are met, and the Logix is enabled.
 */
/*public*/ void DefaultLogix::calculateConditionals()
{
 // are there Conditionals to calculate?
     // There are conditionals to calculate
 QString cName = "";
 Conditional* c = NULL;
 for (int i=0; i<_conditionalSystemNames->size(); i++)
 {
  cName = _conditionalSystemNames->at(i);
  c = getConditional(cName);
  if (c==NULL)
  {
   log->error("Invalid conditional system name when calculating Logix - "+cName);
  }
  else
  {
   // calculate without taking any action unless Logix is enabled
   c->calculate(mEnabled, NULL);
  }
 }
}

/**
 * Activate the Logix, starts Logix processing by connecting all
 *    inputs that are included the Conditionals in this Logix->
 * <P>
 * A Logix must be activated before it will calculate any of its
 *    Conditionals.
 */
/*public*/ void DefaultLogix::activateLogix() {
    // if the Logix is already busy, simply return
    if (_isActivated) return;
    // set the state of all Conditionals to UNKNOWN
    resetConditionals();
    // assemble a list of needed listeners
    assembleListenerList();
    // create and attach the needed property change listeners
    // start a minute Listener if needed
    for (int i=0; i<_listeners->size(); i++) {
        startListener(_listeners->at(i));
    }
    // mark this Logix as busy
    _isActivated = true;
    // calculate this Logix to set initial state of Conditionals
    calculateConditionals();
}

/*private*/ void DefaultLogix::resetConditionals() {
    ConditionalManager* cm = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"));
    for (int i=0; i<_conditionalSystemNames->size(); i++) {
        Conditional* conditional = ((DefaultConditionalManager*)cm)->getBySystemName(_conditionalSystemNames->at(i));
        if (conditional!=NULL) {
            try {
                ((DefaultConditional*)conditional)->setState(Conditional::UNKNOWN);
            } catch ( JmriException e) {
                  // ignore
            }
        }
    }
}

// Pattern to check for new style NX system name
//    static /*final*/ Pattern NXUUID = Pattern.compile(
//        "^IN:[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$",   // NOI18N
//        Pattern.CASE_INSENSITIVE);
/*static*/ QRegExp DefaultLogix::NXUUID = QRegExp("^IN:[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$");

/**
 * ConditionalVariables only have a single name field.  For user interface purposes
 * a gui name is used for the referenced conditional user name.  This is not used
 * for other object types.
 * <p>
 * In addition to setting the GUI name, any state variable references are changed to
 * conditional system names.  This converts the XML system/user name field to the system name
 * for conditional references.  It does not affect other objects such as sensors, turnouts, etc.
 * <p>
 * For Entry/Exit references, replace NX user names and old style NX UUID references
 * with the new style "IN:" + UUID reference.  If the referenced NX does not exist,
 * it will be removed from the the Variable or Action list. (4.11.4)
 * <p>
 * Called by {@link jmri.managers.DefaultLogixManager#activateAllLogixs}
 * @since 4.7.4
 */
//@Override
/*public*/ void DefaultLogix::setGuiNames() {
    if (_isGuiSet) {
        return;
    }
    if (getSystemName() == ("SYS")) {
        _isGuiSet = true;
        return;
    }
    QRegExpValidator validator(NXUUID, 0);
    int pos = 0;

    for (int i = 0; i < _conditionalSystemNames->size(); i++) {
        QString cName = _conditionalSystemNames->value(i);
        Conditional* conditional = getConditional(cName);
        if (conditional == nullptr) {
            // A Logix index entry exists without a corresponding conditional.  This
            // should never happen.
            log->error(tr("setGuiNames: Missing conditional for Logix index entry,  Logix name = '%1', Conditional index name = '%2'").arg(  // NOI18N
                getSystemName()).arg(cName));
            continue;
        }
        QList<ConditionalVariable*>* varList = conditional->getCopyOfStateVariables();
        bool isDirty = false;
        QList<ConditionalVariable*> badVariable = QList<ConditionalVariable*>();
        for (ConditionalVariable* var : *varList) {
            // Find any Conditional State Variables
            if (var->getType() == Conditional::TYPE_CONDITIONAL_TRUE || var->getType() == Conditional::TYPE_CONDITIONAL_FALSE) {
                // Get the referenced (target) conditonal -- The name can be either a system name or a user name
                Conditional* cRef = static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"))->getConditional(var->getName());
                if (cRef != nullptr) {
                    // re-arrange names as needed
                    var->setName(cRef->getSystemName());      // The state variable reference is now a conditional system name
                    QString uName = cRef->getUserName();
                    if (uName == "" || uName.isEmpty()) {
                        var->setGuiName(cRef->getSystemName());
                    } else {
                        var->setGuiName(uName);
                    }
                    // Add the conditional reference to the where used map
                    static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"))->addWhereUsed(var->getName(), cName);
                    isDirty = true;
                } else {
                    log->error(tr("setGuiNames: For conditional '%1' in logix '%2', the referenced conditional, '%3',  does not exist").arg(  // NOI18N
                         cName).arg(getSystemName()).arg(var->getName()));
                }
            }

            // Find any Entry/Exit State Variables
            if (var->getType() == Conditional::TYPE_ENTRYEXIT_ACTIVE
                    || var->getType() == Conditional::TYPE_ENTRYEXIT_INACTIVE) {
                //if (!NXUUID.matcher(var.getName()).find())
             pos = 0;
             QString s = var->getName();
             if(validator.validate(s, pos) != QValidator::Acceptable)
             {
                    // Either a user name or an old style system name (plain UUID)
                    DestinationPoints* dp = (DestinationPoints* )static_cast<EntryExitPairs*>(
                            InstanceManager::getDefault("EntryExitPairs"))->
                            getNamedBean(var->getName())->self();
                    if (dp != nullptr) {
                        // Replace name with current system name
                        var->setName(dp->getSystemName());
                        isDirty = true;
                    } else {
                        log->error(tr("setGuiNames: For conditional '%1' in logix '%2', the referenced Entry Exit Pair, '%3',  does not exist").arg(  // NOI18N
                             cName).arg(getSystemName()).arg(var->getName()));
                        badVariable.append(var);
                    }
                }
            }
        }
        if (badVariable.size() > 0) {
            isDirty = true;
            //badVariable.forEach((badVar) -> varList.remove(badVar));
            foreach(ConditionalVariable* var, badVariable)
             varList->removeOne(var);
        }
        if (isDirty) {
            conditional->setStateVariables(varList);
        }

        QList<ConditionalAction*>* actionList = conditional->getCopyOfActions();
        isDirty = false;
        QList<ConditionalAction*> badAction = QList<ConditionalAction*>();
        for (ConditionalAction* action : *actionList) {
            // Find any Entry/Exit Actions
            if (action->getType() == Conditional::ACTION_SET_NXPAIR_ENABLED
                    || action->getType() == Conditional::ACTION_SET_NXPAIR_DISABLED
                    || action->getType() == Conditional::ACTION_SET_NXPAIR_SEGMENT) {
                //if (!NXUUID.matcher(action.getDeviceName()).find())
             pos = 0;
             QString s = action->getDeviceName();
             if(validator.validate(s, pos) != QValidator::Acceptable)
                {
                    // Either a user name or an old style system name (plain UUID)
                    DestinationPoints* dp = (DestinationPoints*)static_cast<EntryExitPairs*>(
                       InstanceManager::getDefault("EntryExitPairs"))->
                            getNamedBean(action->getDeviceName())->self();
                    if (dp != nullptr) {
                        // Replace name with current system name
                        action->setDeviceName(dp->getSystemName());
                        isDirty = true;
                    } else {
                        log->error(tr("setGuiNames: For conditional '%1' in logix '%2', the referenced Entry Exit Pair, '%3',  does not exist").arg(  // NOI18N
                             cName).arg(getSystemName()).arg(action->getDeviceName()));
                        badAction.append(action);
                    }
                }
            }
        }
        if (badAction.size() > 0) {
            isDirty = true;
//                badAction.forEach((badAct) -> actionList.remove(badAct));
            foreach(ConditionalAction* var, badAction)
             actionList->removeOne(var);
        }
        if (isDirty) {
            conditional->setAction(actionList);
        }
    }
    _isGuiSet = true;
}

/**
 * Assembles a list of Listeners needed to activate this Logix
 */
/*private*/ void DefaultLogix::assembleListenerList() {
    // initialize
    for (int i=_listeners->size()-1; i>=0; i--)
    {
        removeListener(_listeners->at(i));
    }
    _listeners = new QList<JmriSimplePropertyListener*>();
    // cycle thru Conditionals to find objects to listen to
    ConditionalManager* cm = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"));
    for (int i=0; i<_conditionalSystemNames->size(); i++) {
        Conditional* conditional = NULL;
        conditional = ((DefaultConditionalManager*)cm)->getBySystemName(_conditionalSystemNames->at(i));
        if (conditional!=NULL) {
            QList<ConditionalVariable*>* variableList = ((DefaultConditional*)conditional)->getCopyOfStateVariables();
            for (int k = 0; k<variableList->size(); k++) {
                ConditionalVariable* variable = variableList->at(k);
                // check if listening for a change has been suppressed
                int varListenerType = 0;
                QString varName = variable->getName();
                NamedBeanHandle<NamedBean*>* namedBean = variable->getNamedBean();
                int varType = variable->getType();
                int signalAspect = -1;
                // Get Listener type from varible type
                switch(varType) {
                    case Conditional::TYPE_SENSOR_ACTIVE:
                    case Conditional::TYPE_SENSOR_INACTIVE:
                        varListenerType = Logix::LISTENER_TYPE_SENSOR;
                        break;
                    case Conditional::TYPE_TURNOUT_THROWN:
                    case Conditional::TYPE_TURNOUT_CLOSED:
                        varListenerType = Logix::LISTENER_TYPE_TURNOUT;
                        break;
                    case Conditional::TYPE_CONDITIONAL_TRUE:
                    case Conditional::TYPE_CONDITIONAL_FALSE:
                        varListenerType = Logix::LISTENER_TYPE_CONDITIONAL;
                        break;
                    case Conditional::TYPE_LIGHT_ON:
                    case Conditional::TYPE_LIGHT_OFF:
                        varListenerType = Logix::LISTENER_TYPE_LIGHT;
                        break;
                    case Conditional::TYPE_MEMORY_EQUALS:
                    case Conditional::TYPE_MEMORY_COMPARE:
                    case Conditional::TYPE_MEMORY_EQUALS_INSENSITIVE:
                    case Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE:
                        varListenerType = Logix::LISTENER_TYPE_MEMORY;
                        break;
                    case Conditional::TYPE_ROUTE_FREE:
                    case Conditional::TYPE_ROUTE_OCCUPIED:
                    case Conditional::TYPE_ROUTE_ALLOCATED:
                    case Conditional::TYPE_ROUTE_SET:
                    case Conditional::TYPE_TRAIN_RUNNING:
                        varListenerType = Logix::LISTENER_TYPE_WARRANT;
                        break;
                    case Conditional::TYPE_FAST_CLOCK_RANGE:
                        varListenerType = Logix::LISTENER_TYPE_FASTCLOCK;
                        varName = "clock";
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_RED:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        signalAspect = SignalHead::RED;
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        signalAspect = SignalHead::YELLOW;
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_GREEN:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        signalAspect = SignalHead::GREEN;
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_DARK:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        signalAspect = SignalHead::DARK;
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        signalAspect = SignalHead::FLASHRED;
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        signalAspect = SignalHead::FLASHYELLOW;
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        signalAspect = SignalHead::FLASHGREEN;
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_LIT:
                    case Conditional::TYPE_SIGNAL_HEAD_HELD:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALHEAD;
                        break;
                    case Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS:
                    case Conditional::TYPE_SIGNAL_MAST_LIT:
                    case Conditional::TYPE_SIGNAL_MAST_HELD:
                        varListenerType = Logix::LISTENER_TYPE_SIGNALMAST;
                        break;
                    case Conditional::TYPE_BLOCK_STATUS_EQUALS:
                        varListenerType = Logix::LISTENER_TYPE_OBLOCK;
                        break;
                    case Conditional::TYPE_ENTRYEXIT_ACTIVE:
                    case Conditional::TYPE_ENTRYEXIT_INACTIVE:
                        varListenerType = Logix::LISTENER_TYPE_ENTRYEXIT;
                        break;
                }
                int positionOfListener = getPositionOfListener(varListenerType, varType, varName);
                // add to list if new
                JmriSimplePropertyListener* listener = NULL;
                if (positionOfListener == -1) {
                    switch (varListenerType) {
                        case Logix::LISTENER_TYPE_SENSOR:
                            listener = new JmriTwoStatePropertyListener("KnownState", Logix::LISTENER_TYPE_SENSOR, namedBean, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_TURNOUT:
                            listener = new JmriTwoStatePropertyListener("KnownState", Logix::LISTENER_TYPE_TURNOUT,namedBean, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_CONDITIONAL:
                            listener = new JmriTwoStatePropertyListener("KnownState", Logix::LISTENER_TYPE_CONDITIONAL, varName, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_LIGHT:
                            listener = new JmriTwoStatePropertyListener("KnownState", Logix::LISTENER_TYPE_LIGHT, varName, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_MEMORY:
                            listener = new JmriTwoStatePropertyListener("value", Logix::LISTENER_TYPE_MEMORY, namedBean, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_WARRANT:
                            listener = new JmriSimplePropertyListener(NULL, Logix::LISTENER_TYPE_WARRANT,
                                                                      varName, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_FASTCLOCK:
                            listener = new JmriClockPropertyListener("minutes", Logix::LISTENER_TYPE_FASTCLOCK,
                                                                     varName, varType, conditional,
                                                                variable->getNum1(), variable->getNum2());
                            break;
                        case Logix::LISTENER_TYPE_SIGNALHEAD:
                            if (signalAspect <0) {
                                if (varType == Conditional::TYPE_SIGNAL_HEAD_LIT) {
                                    listener = new JmriTwoStatePropertyListener("Lit", Logix::LISTENER_TYPE_SIGNALHEAD,
                                                                        varName, varType, conditional);
                                } else { // varType == Conditional::TYPE_SIGNAL_HEAD_HELD
                                    listener = new JmriTwoStatePropertyListener("Held", Logix::LISTENER_TYPE_SIGNALHEAD,
                                                                        varName, varType, conditional);
                                }
                            } else {
                                listener = new JmriMultiStatePropertyListener("Appearance", Logix::LISTENER_TYPE_SIGNALHEAD,
                                                                    varName, varType, conditional, signalAspect);
                            }
                            break;
                        case Logix::LISTENER_TYPE_SIGNALMAST:
                            listener = new JmriTwoStatePropertyListener("Aspect", Logix::LISTENER_TYPE_SIGNALMAST,
                                                                varName, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_OBLOCK:
                            listener = new JmriTwoStatePropertyListener("state", Logix::LISTENER_TYPE_OBLOCK,
                                                                varName, varType, conditional);
                            break;
                        case Logix::LISTENER_TYPE_ENTRYEXIT:
                            listener = new JmriTwoStatePropertyListener("active", Logix::LISTENER_TYPE_ENTRYEXIT,
                                namedBean, varType, conditional);
                            break;
                        default:
                            if (LRouteTableAction::LOGIX_INITIALIZER !=(varName)) {
                                log->error("Unknown (new) Variable Listener type= "+QString::number(varListenerType)+", for varName= "
                                          +varName+", varType= "+QString::number(varType)+" in Conditional, "+
                                          _conditionalSystemNames->at(i));
                            }
                            continue;
                    }
                    _listeners->append(listener);
                    //log->debug("Add listener for "+varName);
                }
                else {
                    switch (varListenerType) {
                        case Logix::LISTENER_TYPE_SENSOR:
                        case Logix::LISTENER_TYPE_TURNOUT:
                        case Logix::LISTENER_TYPE_CONDITIONAL:
                        case Logix::LISTENER_TYPE_LIGHT:
                        case Logix::LISTENER_TYPE_MEMORY:
                        case Logix::LISTENER_TYPE_WARRANT:
                        case Logix::LISTENER_TYPE_SIGNALMAST:
                        case Logix::LISTENER_TYPE_OBLOCK:
                        case Logix::LISTENER_TYPE_ENTRYEXIT:
                            listener = _listeners->at(positionOfListener);
                            listener->addConditional(conditional);
                            break;

                        case Logix::LISTENER_TYPE_FASTCLOCK:
                    {
                            JmriClockPropertyListener* cpl =
                                    (JmriClockPropertyListener*)_listeners->at(positionOfListener);
                            cpl->setRange(variable->getNum1(), variable->getNum2());
                            cpl->addConditional(conditional);
                            break;
}
                        case Logix::LISTENER_TYPE_SIGNALHEAD:
                    {
                            if (signalAspect < 0) {
                                listener = _listeners->at(positionOfListener);
                                listener->addConditional(conditional);
                            } else {
                                JmriMultiStatePropertyListener* mpl =
                                    (JmriMultiStatePropertyListener*)_listeners->at(positionOfListener);
                                mpl->addConditional(conditional);
                                mpl->setState(signalAspect);
                            }
                            break;
                    }
                        default:
                            log->error("Unknown (old) Variable Listener type= "+QString::number(varListenerType)+", for varName= "
                                      +varName+", varType= "+QString::number(varType)+" in Conditional, "+
                                      _conditionalSystemNames->at(i));
                    }
                }
                // addition listeners needed for memory compare
                if (varType==Conditional::TYPE_MEMORY_COMPARE ||
                    varType==Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE) {
                    positionOfListener = getPositionOfListener(varListenerType, varType,
                                                                   variable->getDataString());
                    if (positionOfListener == -1) {
                        QString name = variable->getDataString();
                        Memory* my = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->provideMemory(name);
                        if (my == NULL) {
                            log->error("invalid memory name= \""+name+"\" in state variable");
                            break;
                        }
                        NamedBeanHandle<NamedBean*>* nb = (NamedBeanHandle<NamedBean*>*)((NamedBeanHandleManager*)InstanceManager::getDefault(
                                    "NamedBeanHandleManager"))->getNamedBeanHandle(name, my);

                        listener = new JmriTwoStatePropertyListener("value", Logix::LISTENER_TYPE_MEMORY,
                                                                  nb, varType,
                                                                  conditional);
                        _listeners->append(listener);
                    } else {
                        listener = _listeners->at(positionOfListener);
                        listener->addConditional(conditional);
                    }
                }
            }
        }
        else {
            log->error("invalid conditional system name in Logix \""+getSystemName()+
                      "\" assembleListenerList DELETING "+
                      _conditionalSystemNames->at(i)+ " from Conditional list." );
            _conditionalSystemNames->removeAt(i);

        }
    }
}

/*private*/ int DefaultLogix::getPositionOfListener(int varListenerType, int varType, QString varName)
{
 // check if already in list
 for (int j=0; (j<_listeners->size()); j++)
 {
  if (varListenerType==_listeners->at(j)->getType() )
  {
   if (varName==(_listeners->at(j)->getDevName()))
   {
    if (varListenerType == Logix::LISTENER_TYPE_SIGNALHEAD)
    {
     if (varType == Conditional::TYPE_SIGNAL_HEAD_LIT ||
                 varType == Conditional::TYPE_SIGNAL_HEAD_HELD )
     {
      if (varType == _listeners->at(j)->getVarType() )
      {
       return j;
      }
     } else if ("Appearance"==(_listeners->at(j)->getPropertyName()))
     {
      // the Appearance Listener can handle all aspects
      return j;
     }
    }
    else
    {
     return j;
    }
   }
  }
 }
 return -1;
}

/**
 * Assembles and returns a list of state variables that are used by conditionals
 *   of this Logix including the number of occurances of each variable that
 *   trigger a calculation, and the number of occurances where the triggering
 *   has been suppressed.
 * The main use of this method is to return information that can be used to test
 *   for inconsistency in suppressing triggering of a calculation among multiple
 *   occurances of the same state variable.
 * Caller provides an ArrayList of the variables to check and and empty Array list
 *   to return the counts for triggering or suppressing calculation.  The first
 *   index is a count that the correspondeing variable triggers calculation and
 *   second is a count that the correspondeing variable suppresses Calculation.
 * Note this method must not modify the supplied variable list in any way.
 *
public void getStateVariableList(ArrayList <ConditionalVariable> varList, ArrayList <int[]> triggerPair) {
    // initialize
    Conditional c = NULL;
    String testSystemName = "";
    String testUserName = "";
    String testVarName = "";
    // cycle thru Conditionals to find state variables
    ConditionalManager cm = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"));
    for (int i=0; i<_conditionalSystemNames.size(); i++) {
        c = cm.getBySystemName(_conditionalSystemNames.get(i));
        if (c!=NULL) {
            ArrayList variableList = c.getCopyOfStateVariables();
            for (int k = 0; k<variableList.size(); k++) {
                ConditionalVariable variable = (ConditionalVariable)variableList.get(k);
                testVarName = variable.getName();
                testSystemName = "";
                testUserName = "";
                // initialize this state variable
                switch (variable.getType()) {
                    case Conditional::TYPE_SENSOR_ACTIVE:
                    case Conditional::TYPE_SENSOR_INACTIVE:
                        Sensor s = InstanceManager::sensorManagerInstance().
                                            getSensor(testVarName);
                        if (s!=NULL) {
                            testSystemName = s.getSystemName();
                            testUserName = s.getUserName();
                        }
                        break;
                    case Conditional::TYPE_TURNOUT_THROWN:
                    case Conditional::TYPE_TURNOUT_CLOSED:
                        Turnout t = InstanceManager::turnoutManagerInstance().
                                            getTurnout(testVarName);
                        if (t!=NULL) {
                            testSystemName = t.getSystemName();
                            testUserName = t.getUserName();
                        }
                        break;
                    case Conditional::TYPE_CONDITIONAL_TRUE:
                    case Conditional::TYPE_CONDITIONAL_FALSE:
                        Conditional cx = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager")).
                                            getConditional(this,testVarName);
                        if (cx==NULL) {
                            cx = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager")).
                                            getBySystemName(testVarName);
                        }
                        if (cx!=NULL) {
                            testSystemName = cx->getSystemName();
                            testUserName = cx->getUserName();
                        }
                        break;
                    case Conditional::TYPE_LIGHT_ON:
                    case Conditional::TYPE_LIGHT_OFF:
                        Light lgt = InstanceManager::lightManagerInstance().
                                            getLight(testVarName);
                        if (lgt!=NULL) {
                            testSystemName = lgt.getSystemName();
                            testUserName = lgt.getUserName();
                        }
                        break;
                    case Conditional::TYPE_MEMORY_EQUALS:
                        Memory m = InstanceManager::memoryManagerInstance().
                                            getMemory(testVarName);
                        if (m!=NULL) {
                            testSystemName = m.getSystemName();
                            testUserName = m.getUserName();
                        }
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_RED:
                    case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
                    case Conditional::TYPE_SIGNAL_HEAD_GREEN:
                    case Conditional::TYPE_SIGNAL_HEAD_DARK:
                    case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
                    case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
                    case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
                        SignalHead h = InstanceManager::signalHeadManagerInstance().
                                            getSignalHead(testVarName);
                        if (h!=NULL) {
                            testSystemName = h.getSystemName();
                            testUserName = h.getUserName();
                        }
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_LIT:
                        SignalHead hx = InstanceManager::signalHeadManagerInstance().
                                            getSignalHead(testVarName);
                        if (hx!=NULL) {
                            testSystemName = hx->getSystemName();
                            testUserName = hx->getUserName();
                        }
                        break;
                    case Conditional::TYPE_SIGNAL_HEAD_HELD:
                        SignalHead hy = InstanceManager::signalHeadManagerInstance().
                                            getSignalHead(testVarName);
                        if (hy!=NULL) {
                            testSystemName = hy.getSystemName();
                            testUserName = hy.getUserName();
                        }
                        break;
                    default:
                        testSystemName = "";
                }
                // check if this state variable is already in the list to be returned
                boolean inList = false;
                int indexOfRepeat = -1;
                if (testSystemName!="") {
                    // getXXXXXX succeeded, process this state variable
                    for (int j=0; j<varList.size(); j++)  {
                        ConditionalVariable v = varList.get(j);
                        if ( v.getName()==(testSystemName) || v.getName()==(testUserName) ) {
                            inList = true;
                            indexOfRepeat = j;
                            break;
                        }
                    }
                    // add to list if new and if there is room
                    if ( inList ) {
                        int[] trigs = triggerPair.get(indexOfRepeat);
                        if ( variable.doCalculation() ) {
                            trigs[0]++;
                        }
                        else {
                            trigs[1]++;

                        }
                    }
                }
            }
        }
        else {
            log->error("invalid conditional system name in Logix getStateVariableList - "+
                                                        _conditionalSystemNames.get(i));

        }
    }
}       // getStateVariableList
*/
/**
 * Deactivate the Logix-> This method disconnects the Logix from
 *    all input objects and stops it from being triggered to calculate.
 * <P>
 * A Logix must be deactivated before it's Conditionals are
 *   changed.
 */
/*public*/ void DefaultLogix::deActivateLogix() {
    if (_isActivated) {
        // Logix is active, deactivate it and all listeners
        _isActivated = false;
        // remove listeners if there are any
        for (int i=_listeners->size()-1; i>=0; i--) {
            removeListener(_listeners->at(i));
        }
    }
}

/**
 * Creates a listener of the required type and starts it
 */
/*private*/ void DefaultLogix::startListener(JmriSimplePropertyListener* listener)
{
 QString msg = "(unknown type number "+QString::number(listener->getType())+")";
 /* If all are converted to NamedBeanHandles, do we have to go through this switch,
 the only reason for doing so would be the error message */
 NamedBean* nb;
 NamedBeanHandle<NamedBean*>* namedBeanHandle;
 switch (listener->getType())
 {
  case LISTENER_TYPE_FASTCLOCK:
  {
   Timebase* tb = (Timebase*)InstanceManager::getDefault("Timebase");
   tb->addMinuteChangeListener(listener);
   return;
  }
  default:
   namedBeanHandle = listener->getNamedBean();
   if (namedBeanHandle == NULL)
   {
    switch (listener->getType())
    {
     case LISTENER_TYPE_SENSOR:
         msg = "sensor";  // NOI18N
         break;
     case LISTENER_TYPE_TURNOUT:
         msg = "turnout";  // NOI18N
         break;
     case LISTENER_TYPE_LIGHT:
         msg = "light";  // NOI18N
         break;
     case LISTENER_TYPE_CONDITIONAL:
         msg = "conditional";  // NOI18N
         break;
     case LISTENER_TYPE_SIGNALHEAD:
         msg = "signalhead";  // NOI18N
         break;
     case LISTENER_TYPE_SIGNALMAST:
         msg = "signalmast";  // NOI18N
         break;
     case LISTENER_TYPE_MEMORY:
         msg = "memory";  // NOI18N
         break;
     case LISTENER_TYPE_WARRANT:
         msg = "warrant";  // NOI18N
         break;
     case LISTENER_TYPE_OBLOCK:
         msg = "oblock";  // NOI18N
         break;
     case LISTENER_TYPE_ENTRYEXIT:
         msg = "entry exit";  // NOI18N
         break;
     default:
         msg = "unknown";  // NOI18N
    }
    break;
   }
   nb = namedBeanHandle->getBean();
   nb->addPropertyChangeListener(listener, namedBeanHandle->getName(),
           "Logix " + getDisplayName());  // NOI18N
   return;
 }
 log->error(tr("Bad name for %1 '%2' when setting up Logix listener [ %3 ]").arg(
       msg).arg(listener->getDevName()).arg(this->getSystemName()));
}

/**
 * Removes a listener of the required type
 */
/*private*/ void DefaultLogix::removeListener(JmriSimplePropertyListener* listener)
{
 QString msg = "";
 NamedBean* nb;
 NamedBeanHandle<NamedBean*>* namedBeanHandle;
 try
 {
  switch (listener->getType())
  {
   case LISTENER_TYPE_FASTCLOCK:
   {
    Timebase* tb = (Timebase*)InstanceManager::getDefault("Timebase");
    tb->removeMinuteChangeListener(listener);
    return;
   }
   case LISTENER_TYPE_ENTRYEXIT:
   {
    NamedBean* ex = ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->
               getNamedBean(listener->getDevName());
    if (ex == NULL) {
        msg = "entryexit";  // NOI18N
        break;
    }
    ex->removePropertyChangeListener(listener);
    return;
   }
   default:
   namedBeanHandle = listener->getNamedBean();
   if (namedBeanHandle == NULL)
   {
    switch (listener->getType())
    {
     case LISTENER_TYPE_SENSOR:
         msg = "sensor";  // NOI18N
         break;
     case LISTENER_TYPE_TURNOUT:
         msg = "turnout";  // NOI18N
         break;
     case LISTENER_TYPE_LIGHT:
         msg = "light";  // NOI18N
         break;
     case LISTENER_TYPE_CONDITIONAL:
         msg = "conditional";  // NOI18N
         break;
     case LISTENER_TYPE_SIGNALHEAD:
         msg = "signalhead";  // NOI18N
         break;
     case LISTENER_TYPE_SIGNALMAST:
         msg = "signalmast";  // NOI18N
         break;
     case LISTENER_TYPE_MEMORY:
         msg = "memory";  // NOI18N
         break;
     case LISTENER_TYPE_WARRANT:
         msg = "warrant";  // NOI18N
         break;
     case LISTENER_TYPE_OBLOCK:
         msg = "oblock";  // NOI18N
         break;
     case LISTENER_TYPE_ENTRYEXIT:
         msg = "entry exit";  // NOI18N
         break;
     default:
         msg = "unknown";  // NOI18N
    }
    break;
   }
   nb = namedBeanHandle->getBean();
   nb->removePropertyChangeListener(listener);
   return;
  }
 } catch (Exception* ex) {
     log->error(tr("Bad name for listener on \"%1\": ").arg(listener->getDevName()), ex);  // NOI18N
 }
 log->error(tr("Bad name for ") + msg + " listener on \"" + listener->getDevName()  // NOI18N
         + "\" when removing");  // NOI18N
}

/**
 * Assembles a list of state variables that both trigger the Logix, and are
 *   changed by it.  Returns true if any such variables were found.  Returns false
 *   otherwise.
 * Can be called when Logix is enabled.
 *
public boolean checkLoopCondition() {
    loopGremlins = new ArrayList<String[]>();
    if (!_isActivated) {
        // Prepare a list of all variables used in conditionals
        java.util.HashSet <ConditionalVariable> variableList = new java.util.HashSet<ConditionalVariable>();
        ConditionalManager cm = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"));
        for (int i=0; i<_conditionalSystemNames.size(); i++) {
            Conditional c = NULL;
            c = cm.getBySystemName(_conditionalSystemNames.get(i));
            if (c!=NULL) {
                // Not necesary to modify methods, equals and hashcode. Redundacy checked in addGremlin
                variableList.addAll(c.getCopyOfStateVariables());
            }
        }
        java.util.HashSet <ConditionalVariable> variableList = new java.util.HashSet<ConditionalVariable>();
        ConditionalVariable v = NULL;
            // check conditional action items
        Conditional c = NULL;
        for (int i=0; i<_conditionalSystemNames.size(); i++) {
            // get next conditional
            c = cm.getBySystemName(_conditionalSystemNames.get(i));
            if (c!=NULL) {
                ArrayList <ConditionalAction> actionList = c.getCopyOfActions();
                for (int j = 0; j < actionList.size(); j++) {
                    ConditionalAction action = actionList.get(j);
                    String sName = "";
                    String uName = "";
                    switch (action.getType()) {
                        case Conditional::ACTION_NONE:
                            break;
                        case Conditional::ACTION_SET_TURNOUT:
                        case Conditional::ACTION_DELAYED_TURNOUT:
                        case Conditional::ACTION_RESET_DELAYED_TURNOUT:
                        case Conditional::ACTION_CANCEL_TURNOUT_TIMERS:
                            Turnout t = InstanceManager::turnoutManagerInstance().
                                        provideTurnout(action.getDeviceName());
                            if (t!=NULL) {
                                sName = t.getSystemName();
                                uName = t.getUserName();
                                // check for action on the same turnout
                                Iterator <ConditionalVariable>it= variableList.iterator();
                                while(it.hasNext()) {
                                    v = it.next();
                                    if (v.getType() == Conditional::TYPE_TURNOUT_CLOSED ||
                                        v.getType() == Conditional::TYPE_TURNOUT_THROWN) {
                                        if ( (v.getName()==(sName)) ||
                                                (v.getName()==(uName)) ) {
                                            // possible conflict found
                                            addGremlin("Turnout", sName, uName);
                                        }
                                    }
                                }
                            }
                            break;
                        case Conditional::ACTION_SET_SIGNAL_APPEARANCE:
                        case Conditional::ACTION_SET_SIGNAL_HELD:
                        case Conditional::ACTION_CLEAR_SIGNAL_HELD:
                        case Conditional::ACTION_SET_SIGNAL_DARK:
                        case Conditional::ACTION_SET_SIGNAL_LIT:
                            SignalHead h = InstanceManager::signalHeadManagerInstance().
                                            getSignalHead(action.getDeviceName());
                            if (h!=NULL) {
                                sName = h.getSystemName();
                                uName = h.getUserName();
                                // check for action on the same signal head
                                Iterator <ConditionalVariable>it= variableList.iterator();
                                while(it.hasNext()) {
                                    v = it.next();
                                    if (v.getType() >= Conditional::TYPE_SIGNAL_HEAD_RED ||
                                        v.getType() <= Conditional::TYPE_SIGNAL_HEAD_HELD) {
                                        if ( (v.getName()==(sName)) ||
                                                (v.getName()==(uName)) ) {
                                            // possible conflict found
                                            addGremlin("SignalHead", sName, uName);
                                        }
                                    }
                                }
                            }
                            break;
                        case Conditional::ACTION_SET_SENSOR:
                        case Conditional::ACTION_DELAYED_SENSOR:
                        case Conditional::ACTION_RESET_DELAYED_SENSOR:
                        case Conditional::ACTION_CANCEL_SENSOR_TIMERS:
                            Sensor s = InstanceManager::sensorManagerInstance().
                                        provideSensor(action.getDeviceName());
                            if (s!=NULL) {
                                sName = s.getSystemName();
                                uName = s.getUserName();
                                // check for action on the same sensor
                                Iterator <ConditionalVariable>it= variableList.iterator();
                                while(it.hasNext()) {
                                    v = it.next();
                                    if (v.getType() == Conditional::TYPE_SENSOR_ACTIVE ||
                                        v.getType() == Conditional::TYPE_SENSOR_INACTIVE) {

                                        if ( (v.getName()==(sName)) ||
                                                (v.getName()==(uName)) ) {
                                            // possible conflict found
                                            addGremlin("Sensor",sName, uName);
                                        }
                                    }
                                }
                            }
                            break;
                        case Conditional::ACTION_SET_LIGHT:
                        case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
                        case Conditional::ACTION_SET_LIGHT_INTENSITY:
                            Light lgt = InstanceManager::lightManagerInstance().
                                            getLight(action.getDeviceName());
                            if (lgt!=NULL) {
                                sName = lgt.getSystemName();
                                uName = lgt.getUserName();
                                // check for listener on the same light
                                Iterator <ConditionalVariable>it= variableList.iterator();
                                while(it.hasNext()) {
                                    v = it.next();
                                    if (v.getType() == Conditional::TYPE_LIGHT_ON ||
                                        v.getType() == Conditional::TYPE_LIGHT_OFF) {
                                        if ( (v.getName()==(sName)) ||
                                                (v.getName()==(uName)) ) {
                                            // possible conflict found
                                            addGremlin("Light", sName, uName);
                                        }
                                    }
                                }
                            }
                            break;
                        case Conditional::ACTION_SET_MEMORY:
                        case Conditional::ACTION_COPY_MEMORY:
                            Memory m = InstanceManager::memoryManagerInstance().
                                        provideMemory(action.getDeviceName());
                            if (m!=NULL) {
                                sName = m.getSystemName();
                                uName = m.getUserName();
                                // check for variable on the same memory
                                Iterator <ConditionalVariable>it= variableList.iterator();
                                while(it.hasNext()) {
                                    v = it.next();
                                    if (v.getType() == Conditional::TYPE_MEMORY_EQUALS) {
                                        if ( (v.getName()==(sName)) ||
                                                (v.getName()==(uName)) ) {
                                            // possible conflict found
                                            addGremlin("Memory", sName, uName);
                                        }
                                    }
                                }
                            }
                            break;
                        case Conditional::ACTION_SET_FAST_CLOCK_TIME:
                        case Conditional::ACTION_START_FAST_CLOCK:
                        case Conditional::ACTION_STOP_FAST_CLOCK:
                            Iterator <ConditionalVariable>it= variableList.iterator();
                            while(it.hasNext()) {
                                v = it.next();
                                if (v.getType() == Conditional::TYPE_FAST_CLOCK_RANGE) {
                                        addGremlin("FastClock", NULL, v.getName());
                                }
                            }
                            break;
                        default:
                    }
                }
            }
        }
    }
    return (loopGremlins.size()>0);
}

private void addGremlin(String type, String sName, String uName) {
    // check for redundancy
    String names = uName+ (sName == NULL ? "" : " ("+sName+")");
    for (int i=0; i<loopGremlins.size(); i++)
    {
        String[] str = loopGremlins.get(i);
        if (str[0]==(type) && str[1]==(names)) {
            return;
        }
    }
    String[] item = new String[2];
    item[0] = type;
    item[1] = names;
    loopGremlins.add(item);
}

ArrayList <String[]> loopGremlins = NULL;

/**
 * Returns a string listing state variables that might result in a loop.
 *    Returns an empty string if there are none, probably because
 *    "checkLoopCondition" was not invoked before the call, or returned false.
 *
 * public ArrayList <String[]> getLoopGremlins() {return(loopGremlins);}
 */

/**
 * Not needed for Logixs - included to complete implementation of the NamedBean interface.
 */
/*public*/ int DefaultLogix::getState() {
    log->warn("Unexpected call to getState in DefaultLogix->");
    return UNKNOWN;
}

/**
 * Not needed for Logixs - included to complete implementation of the NamedBean interface.
 */
/*public*/ void DefaultLogix::setState(int /*state*/) {
    log->warn("Unexpected call to setState in DefaultLogix->");
    return;
}
//@Override
/*public*/ void DefaultLogix::vetoableChange(PropertyChangeEvent* evt) /*throw  (PropertyVetoException)*/
{
 if ("CanDelete" == (evt->getPropertyName()))
 {   // NOI18N
  NamedBean* nb =  VPtr<NamedBean>::asPtr(evt->getOldValue());
  for (JmriSimplePropertyListener* listener : *_listeners)
  {
   if (nb->equals(listener->getBean()->self())) {
       PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());  // NOI18N
       throw new PropertyVetoException(tr("%1 is in use by Logix \"%2\" as a Trigger").arg(nb->getBeanType()).arg(getDisplayName()), e);   // NOI18N
   }
  }

  QString cName = "";
  Conditional* c = nullptr;
  for (int i = 0; i < _conditionalSystemNames->size(); i++)
  {
   cName = _conditionalSystemNames->at(i);
   c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getBySystemName(cName);
   if (c != nullptr)
   {
    for (ConditionalAction* ca : *c->getCopyOfActions())
    {
     if (nb->equals(ca->getBean()->self()))
     {
      PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());  // NOI18N
      throw new PropertyVetoException(tr("%1 is in use by Logix \"%2\" as a Trigger").arg(nb->getBeanType()).arg(getDisplayName()), e);   // NOI18N
     }
    }
    for (ConditionalVariable* v : *c->getCopyOfStateVariables())
    {
     if (nb->equals(v->getBean()->self()) || nb->equals(v->getNamedBeanData()->self()))
     {
      PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());  // NOI18N
      throw new PropertyVetoException(tr("%1 is in use by Logix \"%2\" as a Trigger").arg(nb->getBeanType()).arg(getDisplayName()), e);   // NOI18N
     }
    }
   }
  }
 }
}

//@Override
/*public*/ QList<NamedBeanUsageReport *> *DefaultLogix::getUsageReport(NamedBean* bean) {
    QList<NamedBeanUsageReport*>* report = new QList<NamedBeanUsageReport*>();
    if (bean != nullptr) {
        for (int i = 0; i < getNumConditionals(); i++) {
            DefaultConditional* cdl = (DefaultConditional*) getConditional(getConditionalByNumberOrder(i));
            //cdl.getStateVariableList().forEach((variable) ->
            for(ConditionalVariable* variable :  *cdl->getStateVariableList())
            {
                if (bean->equals(variable->getBean()->self())) {
                    report->append(new NamedBeanUsageReport("ConditionalVariable", cdl, variable->toString()));
                }
                if (bean->equals(variable->getNamedBeanData()->self())) {
                    report->append(new NamedBeanUsageReport("ConditionalVariableData", cdl, variable->toString()));
                }
            }//);
            //cdl.getActionList().forEach((action) ->
            for(ConditionalAction* action :cdl->getActionList())
            {
                if (bean->equals(action->getBean()->self())) {
                    bool triggerType = cdl->getTriggerOnChange();
                    report->append(new NamedBeanUsageReport("ConditionalAction", cdl, action->description(triggerType)));
                }
            }//);
        }
    }
    return report;
}
//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultLogix->class.getName());
//}

/* @(#)DefaultLogix->java */
