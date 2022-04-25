#include "actionpower.h"
#include "defaultdigitalactionmanager.h"

/**
 * This action turns power on or off.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ActionPower extends AbstractDigitalAction {


    /*public*/  ActionPower::ActionPower(QString sys, QString user, QObject *parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ActionPower");
    }

    //@Override
    /*public*/  Base* ActionPower::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionPower* copy = new ActionPower(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setBeanState(_powerState);
        return manager->registerAction(copy);
    }

    /*public*/  void ActionPower::setBeanState(PowerState::STATE state) {
        _powerState = state;
    }

    /*public*/  ActionPower::PowerState::STATE ActionPower::getBeanState() {
        return _powerState;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ActionPower::getCategory() {
        return Category::ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPower::execute() /*throws JmriException*/ {
        AtomicReference<JmriException*>* exception = new AtomicReference<JmriException*>();
//        ThreadingUtil::runOnLayoutWithJmriException(() -> {
//            try {
//                InstanceManager.getDefault(PowerManager.class).setPower(_powerState.getID());
//            } catch (JmriException e) {
//                exception.set(e);
//            }
//        });
        ThreadingUtil::runOnLayoutWithJmriException(new ActionPower_run(_powerState, exception));
        if (exception->get() != nullptr) throw exception->get();
    }

    //@Override
    /*public*/  FemaleSocket* ActionPower::getChild(int index)/* throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionPower::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionPower::getShortDescription(QLocale locale) {
        return tr(/*locale, */"Power");
    }

    //@Override
    /*public*/  QString ActionPower::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Set power %1").arg(PowerState::toString(_powerState));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPower::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPower::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPower::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPower::disposeMe() {
    }



