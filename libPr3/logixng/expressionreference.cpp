#include "expressionreference.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "vptr.h"
#include "defaultconditionalng.h"
#include "referenceutil.h"
#include "defaultnamedtablemanager.h"
#include "proxysensormanager.h"
#include "defaultsignalmastmanager.h"
#include "abstractsignalheadmanager.h"
#include "proxylightmanager.h"
#include "defaultaudiomanager.h"
#include "defaultmemorymanager.h"

/**
 * Evaluates what a reference points to.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ExpressionReference extends AbstractDigitalExpression
//        implements PropertyChangeListener {
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  ExpressionReference::ExpressionReference(QString sys, QString user, QObject *parent) : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException */{
        //super(sys, user);
        setObjectName("ExpressionReference");
    }

    //@Override
    /*public*/  Base* ExpressionReference::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException */{
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionReference* copy = new ExpressionReference(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setReference(_reference);
        copy->set_Is_IsNot(_is_IsNot);
        copy->setPointsTo(_pointsTo);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/  void ExpressionReference::setReference(QString reference) {
        assertListenersAreNotRegistered(log, "setReference");
        _reference = reference;
    }

    /*public*/  QString ExpressionReference::getReference() {
        return _reference;
    }

    /*public*/  void ExpressionReference::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/  Is_IsNot_Enum::VAL ExpressionReference::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/  void ExpressionReference::setPointsTo(ExpressionReference::PointsTo::TYPE pointsTo) {
        _pointsTo = pointsTo;
    }

    /*public*/  ExpressionReference::PointsTo::TYPE ExpressionReference::getPointsTo() {
        return _pointsTo;
    }
/*
    //@Override
    public  void vetoableChange(PropertyChangeEvent* evt) throws java.beans.PropertyVetoException {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (evt->getOldValue().canConvert<QString>()) {
                if (evt->getOldValue().toString() == (getReference().getBean())) {
                    throw new PropertyVetoException(getDisplayName(), evt);
                }
            }
        } else if ("DoDelete".equals(evt->getPropertyName())) { // No I18N
            if (evt->getOldValue() instanceof String) {
                if (evt->getOldValue().equals(getReference().getBean())) {
                    setReference((Turnout)null);
                }
            }
        }
    }
*/
    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ExpressionReference::getCategory() {
        return Category::ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionReference::evaluate() {
        if (_reference == nullptr) return false;

        bool result;
        QString ref = ReferenceUtil::getReference(
                getConditionalNG()->getSymbolTable(), _reference);
        NamedBean* t;

        switch (_pointsTo) {
            case ExpressionReference::PointsTo::Nothing:
                result = "" == (ref);
                break;

            case ExpressionReference::PointsTo::LogixNGTable:
                t = ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->getNamedBean(ref);
                result = (t != nullptr);
                break;

            case ExpressionReference::PointsTo::Audio:
                t = ((DefaultAudioManager*)InstanceManager::getDefault("AudioManager"))->getNamedBean(ref);
                result = (t != nullptr);
                break;

            case ExpressionReference::PointsTo::Light:
                t = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->AbstractProxyManager::getNamedBean(ref);
                result = (t != nullptr);
                break;

            case ExpressionReference::PointsTo::Memory:
                t = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getNamedBean(ref);
                result = (t != nullptr);
                break;

            case ExpressionReference::PointsTo::Sensor:
                t = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->AbstractProxyManager::getNamedBean(ref);
                result = (t != nullptr);
                break;

            case ExpressionReference::PointsTo::SignalHead:
                t = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::getNamedBean(ref);
                result = (t != nullptr);
                break;

            case ExpressionReference::PointsTo::SignalMast:
                t = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getNamedBean(ref);
                result = (t != nullptr);
                break;

            case ExpressionReference::PointsTo::Turnout:
                t = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->AbstractProxyManager::getNamedBean(ref);
                result = (t != nullptr);
                break;

            default:
                throw new UnsupportedOperationException("_pointsTo has unknown value: "+ExpressionReference::PointsTo::toString(_pointsTo));
        }

        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return result;
        } else {
            return !result;
        }
    }

    //@Override
    /*public*/  FemaleSocket* ExpressionReference::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ExpressionReference::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ExpressionReference::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Reference");
    }

    //@Override
    /*public*/  QString ExpressionReference::getLongDescription(QLocale locale) {
        QString reference;
        if (_reference != "") {
            reference = _reference;
        } else {
            reference = tr(/*locale,*/ "ReferenceNotSelected");
        }

        return tr(
//                locale,
                "Reference %1 %2 %3").arg(
                reference.isEmpty() ? "''" : reference,
                Is_IsNot_Enum::toString(_is_IsNot),
                ExpressionReference::PointsTo::toString(_pointsTo));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReference::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReference::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_reference != nullptr)) {
//            _reference.getBean().addPropertyChangeListener("KnownState", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReference::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
//            _reference.getBean().removePropertyChangeListener("KnownState", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReference::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReference::disposeMe() {
    }






    /*private*/ /*final*/ /*static*/ Logger* ExpressionReference::log = LoggerFactory::getLogger("ExpressionReference");
