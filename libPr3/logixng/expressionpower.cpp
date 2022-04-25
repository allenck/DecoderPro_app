#include "expressionpower.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultpowermanager.h"
#include "defaultconditionalng.h"

/**
 * This expression sets the state of a power.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ExpressionPower extends AbstractDigitalExpression
//        implements PropertyChangeListener {


    /*public*/  ExpressionPower::ExpressionPower(QString sys, QString user, QObject *parent)
     : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ExpressionPower");
    }

    //@Override
    /*public*/  Base* ExpressionPower::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionPower* copy = new ExpressionPower(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->set_Is_IsNot(_is_IsNot);
        copy->setBeanState(_powerState);
        return manager->registerExpression(copy);
    }

    /*public*/  void ExpressionPower::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/  Is_IsNot_Enum::VAL ExpressionPower::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/  void ExpressionPower::setBeanState(PowerState::STATE state) {
        _powerState = state;
    }

    /*public*/  ExpressionPower::PowerState::STATE ExpressionPower::getBeanState() {
        return _powerState;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ExpressionPower::getCategory() {
        return Category::ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionPower::evaluate() /*throws JmriException*/ {

        PowerState::STATE checkPowerState = _powerState;

        PowerState::STATE currentPowerState =
                PowerState::get(((AbstractPowerManager*)InstanceManager::getDefault("PowerManager"))
                        ->getPower());

        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return currentPowerState == checkPowerState;
        } else {
            return currentPowerState != checkPowerState;
        }
    }

    //@Override
    /*public*/  FemaleSocket* ExpressionPower::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ExpressionPower::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ExpressionPower:: getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Power_Short");
    }

    //@Override
    /*public*/  QString ExpressionPower::getLongDescription(QLocale locale) {
        return tr("Power %1} %2").arg(Is_IsNot_Enum::toString(_is_IsNot), PowerState::toString(_powerState));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionPower::registerListenersForThisClass() {
        if (!_listenersAreRegistered) {
            ((AbstractPowerManager*)InstanceManager::getDefault("PowerManager"))
                    ->SwingPropertyChangeSupport::addPropertyChangeListener(PowerManager::POWER, this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionPower::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            ((AbstractPowerManager*)InstanceManager::getDefault("PowerManager"))
                    ->SwingPropertyChangeSupport::removePropertyChangeListener(PowerManager::POWER, this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionPower::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionPower::disposeMe() {
    }



