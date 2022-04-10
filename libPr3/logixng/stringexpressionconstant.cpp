#include "stringexpressionconstant.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultstringexpressionmanager.h"

/**
 * Constant value.
 * This can be useful for example by the ActionThrottle.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class StringExpressionConstant extends AbstractStringExpression {



/*public*/  StringExpressionConstant::StringExpressionConstant(QString sys, QString user, QObject* parent) : AbstractStringExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {

    //super(sys, user);
 setObjectName("StringExpressionConstant");
}

//@Override
/*public*/  Base* StringExpressionConstant::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
    StringExpressionManager* manager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    StringExpressionConstant* copy = new StringExpressionConstant(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    copy->setValue(_value);
    return manager->registerExpression(copy);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* StringExpressionConstant::getCategory() {
    return Category::ITEM;
}

/*public*/  void StringExpressionConstant::setValue(QString value) {
    assertListenersAreNotRegistered(log, "setValue");
    _value = value;
}

/*public*/  QString StringExpressionConstant::getValue() {
    return _value;
}

/** {@inheritDoc} */
//@Override
/*public*/  QString StringExpressionConstant::evaluate() {
    return _value;
}

//@Override
/*public*/  FemaleSocket* StringExpressionConstant::getChild(int index)
        /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int StringExpressionConstant::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString StringExpressionConstant::getShortDescription(QLocale locale) {
    return tr(/*locale, */"String constant");
}

//@Override
/*public*/  QString StringExpressionConstant::getLongDescription(QLocale locale) {
    if (_value == "") {
        return tr(/*locale, */"Get string constant null");
    } else {
        return tr(/*locale, */"Get string constant \"&1\"").arg(_value);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void StringExpressionConstant::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void StringExpressionConstant::registerListenersForThisClass() {
    // This class does not have any listeners registered, but we still don't
    // want a caller to change the value then listeners are registered.
    // So we set this property to warn the caller when the caller is using
    // the class in the wrong way.
    _listenersAreRegistered = true;
}

/** {@inheritDoc} */
//@Override
/*public*/  void StringExpressionConstant::unregisterListenersForThisClass() {
    _listenersAreRegistered = false;
}

/** {@inheritDoc} */
//@Override
/*public*/  void StringExpressionConstant::disposeMe() {
}


/*private*/ /*final*/ /*static*/ Logger* StringExpressionConstant::log = LoggerFactory::getLogger("StringExpressionConstant");
