#include "analogexpressionconstant.h"
#include "loggerfactory.h"
#include "category.h"
#include "loggerfactory.h"
#include "analogexpressionmanager.h"
#include "instancemanager.h"

/**
 * Constant value.
 * This can be useful for example by the ActionThrottle.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
// /*public*/  class AnalogExpressionConstant extends AbstractAnalogExpression {


    /*public*/  AnalogExpressionConstant::AnalogExpressionConstant(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractAnalogExpression(sys, user, parent){

        //super(sys, user);
    }

    //@Override
    /*public*/  Base* AnalogExpressionConstant::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
        AnalogExpressionManager* manager = (AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        AnalogExpressionConstant* copy = new AnalogExpressionConstant(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setValue(_value);
        return manager->registerExpression(copy);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* AnalogExpressionConstant::getCategory() {
        return Category::ITEM;
    }

    /*public*/  void AnalogExpressionConstant::setValue(double value) {
        assertListenersAreNotRegistered(log, "setValue");
        _value = value;
    }

    /*public*/  double AnalogExpressionConstant::getValue() {
        return _value;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  double AnalogExpressionConstant::evaluate() {
        return _value;
    }

    //@Override
    /*public*/  FemaleSocket* AnalogExpressionConstant::getChild(int index)
            /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int AnalogExpressionConstant::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString AnalogExpressionConstant::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Analog constant");
    }

    //@Override
    /*public*/  QString AnalogExpressionConstant::getLongDescription(QLocale locale) {
//        NumberFormat numberFormat = NumberFormat.getInstance(locale);
        return tr(/*locale,*/ "Get analog constant %1").arg(/*numberFormat.format*/(_value));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionConstant::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionConstant::registerListenersForThisClass() {
        // This class does not have any listeners registered, but we still don't
        // want a caller to change the value then listeners are registered.
        // So we set this property to warn the caller when the caller is using
        // the class in the wrong way.
        _listenersAreRegistered = true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionConstant::unregisterListenersForThisClass() {
        _listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionConstant::disposeMe() {
    }


    /*private*/ /*final*/ /*static*/ Logger* AnalogExpressionConstant::log = LoggerFactory::getLogger("AnalogExpressionConstant");
