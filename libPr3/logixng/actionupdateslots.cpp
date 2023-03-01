#include "actionupdateslots.h"
#include "loconetsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "slotmanager.h"
#include "categoryloconet.h"

/**
 * Request an update of the LocoNet slots
 *
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/ class ActionUpdateSlots extends AbstractDigitalAction {


/*public*/ ActionUpdateSlots::ActionUpdateSlots(QString sys, QString user, LocoNetSystemConnectionMemo* memo, QObject* parent)
: AbstractDigitalAction(sys, user, parent){
    //super(sys, user);
    _memo = memo;
}

//@Override
/*public*/ Base* ActionUpdateSlots::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    ActionUpdateSlots* copy = new ActionUpdateSlots(sysName, userName, _memo);
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/ Category ActionUpdateSlots::getCategory() {
    return CategoryLocoNet::LOCONET;
}

/*public*/ void ActionUpdateSlots::setMemo(LocoNetSystemConnectionMemo* memo) {
    assertListenersAreNotRegistered(log, "setMemo");
    _memo = memo;
}

/*public*/ LocoNetSystemConnectionMemo* ActionUpdateSlots::getMemo() {
    return _memo;
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionUpdateSlots::execute() {
    if (_memo != nullptr) _memo->getSlotManager()->update();
}

//@Override
/*public*/ FemaleSocket* ActionUpdateSlots::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/ int ActionUpdateSlots::getChildCount() {
    return 0;
}

//@Override
/*public*/ QString ActionUpdateSlots::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "ActionUpdateSlots");
}

//@Override
/*public*/ QString ActionUpdateSlots::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "ActionUpdateSlots_Long").arg(
              _memo != nullptr ? _memo->getUserName() : tr("connection not set"));
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionUpdateSlots::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionUpdateSlots::registerListenersForThisClass() {
    if (!_listenersAreRegistered) {
        _listenersAreRegistered = true;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionUpdateSlots::unregisterListenersForThisClass() {
    _listenersAreRegistered = false;
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionUpdateSlots::disposeMe() {
}


/*private*/ /*final*/ /*static*/ Logger* ActionUpdateSlots::log = LoggerFactory::getLogger("ActionUpdateSlots");
