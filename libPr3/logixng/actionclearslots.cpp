#include "actionclearslots.h"
#include "loconetsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "logixng/actionupdateslots.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "categoryloconet.h"
#include "instancemanager.h"
#include "slotmanager.h"

/**
 * Sets all engine slots to status common
 *
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/ class ActionClearSlots extends AbstractDigitalAction {


    /*public*/ ActionClearSlots::ActionClearSlots(QString sys, QString user, LocoNetSystemConnectionMemo* memo, QObject *parent)
    : AbstractDigitalAction(sys, user, parent){
        //super(sys, user);
        _memo = memo;
    }

    //@Override
    /*public*/ Base* ActionClearSlots::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionUpdateSlots* copy = new ActionUpdateSlots(sysName, userName, _memo);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ActionClearSlots::getCategory() {
        return CategoryLocoNet::LOCONET;
    }

    /*public*/ void ActionClearSlots::setMemo(LocoNetSystemConnectionMemo* memo) {
        assertListenersAreNotRegistered(log, "setMemo");
        _memo = memo;
    }

    /*public*/ LocoNetSystemConnectionMemo* ActionClearSlots::getMemo() {
        return _memo;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionClearSlots::execute() {
        for (int i=1; i <= NUM_LOCO_SLOTS_TO_CLEAR; i++) {
            LocoNetSlot* slot = _memo->getSlotManager()->slot(i);
            if ((slot->slotStatus() & LnConstants::LOCOSTAT_MASK) != LnConstants::LOCO_FREE) {
//                _memo.getLnTrafficController().sendLocoNetMessage(slot.writeStatus(LnConstants.LOCO_FREE));
                _memo->getLnTrafficController()->sendLocoNetMessage(slot->releaseSlot());
            }
        }
    }

    //@Override
    /*public*/ FemaleSocket* ActionClearSlots::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ActionClearSlots::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ActionClearSlots::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionClearSlots_Short");
    }

    //@Override
    /*public*/ QString ActionClearSlots::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Clear loconet slots for connection %1").arg(
                  _memo != nullptr ? _memo->getUserName() : tr("connection not set"));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionClearSlots::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionClearSlots::registerListenersForThisClass() {
        if (!_listenersAreRegistered) {
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionClearSlots::unregisterListenersForThisClass() {
        _listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionClearSlots::disposeMe() {
    }


    /*private*/ /*final*/ /*static*/ Logger* ActionClearSlots::log = LoggerFactory::getLogger("ActionClearSlots");
