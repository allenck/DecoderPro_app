#include "actionatomicboolean.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "atomicboolean.h"

/**
 * This action sets the value of an AtomicBoolean. It is mostly used for tests.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class ActionAtomicBoolean extends AbstractDigitalAction {


    /*public*/  ActionAtomicBoolean::ActionAtomicBoolean(AtomicBoolean* atomicBoolean,
                                                         bool newValue, QObject* parent)
     : AbstractDigitalAction(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->AbstractManager::getAutoSystemName(), nullptr, parent)
            /*throws BadUserNameException*/ {
        //super(InstanceManager::getDefault("DigitalActionManager")).getAutoSystemName(), null);
        _atomicBoolean = atomicBoolean;
        _newValue = newValue;
    }

    /*public*/  ActionAtomicBoolean::ActionAtomicBoolean(QString sys, QString user, QObject* parent)
     : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
        _atomicBoolean = new AtomicBoolean();
    }

    /*public*/  ActionAtomicBoolean::ActionAtomicBoolean(QString sys, QString user, AtomicBoolean* atomicBoolean, bool newValue, QObject* parent)
     : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
        _atomicBoolean = atomicBoolean;
        _newValue = newValue;
    }

    //@Override
    /*public*/  Base* ActionAtomicBoolean::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        DigitalActionBean* copy = new ActionAtomicBoolean(sysName, userName, new AtomicBoolean, _newValue);
// TODO:        copy->NamedBean::setComment(NamedBean::getComment());
        return manager->registerAction(copy);
    }

    /*public*/  void ActionAtomicBoolean::setAtomicBoolean(AtomicBoolean* atomicBoolean) {
        _atomicBoolean = atomicBoolean;
    }

    /*public*/  AtomicBoolean* ActionAtomicBoolean::getAtomicBoolean() {
        return _atomicBoolean;
    }

    /*public*/  void ActionAtomicBoolean::setNewValue(bool newValue) {
        _newValue = newValue;
    }

    /*public*/  bool ActionAtomicBoolean::getNewValue() {
        return _newValue;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ActionAtomicBoolean::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionAtomicBoolean::execute() {
        _atomicBoolean->set(_newValue);
    }

    //@Override
    /*public*/  FemaleSocket* ActionAtomicBoolean::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionAtomicBoolean::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionAtomicBoolean::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Atomic boolean");
    }

    //@Override
    /*public*/  QString ActionAtomicBoolean::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Set the atomic boolean to %1").arg(_newValue);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionAtomicBoolean::setup() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionAtomicBoolean::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionAtomicBoolean::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionAtomicBoolean::disposeMe() {
    }

