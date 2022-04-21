#include "defaultmaleanalogexpressionsocket.h"
#include "loggerfactory.h"
#include <cmath>
#include "conditionalng.h"
#include "abstractanalogexpression.h"

/**
 * Every AnalogExpressionBean has an DefaultMaleAnalogExpressionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class DefaultMaleAnalogExpressionSocket extends AbstractMaleSocket implements MaleAnalogExpressionSocket {



/*public*/  DefaultMaleAnalogExpressionSocket::DefaultMaleAnalogExpressionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
   /*@Nonnull*/ AnalogExpressionBean* expression, QObject *parent) : AbstractMaleSocket(manager, expression, parent) {
    //super(manager, expression);
 setObjectName("DefaultMaleAnalogExpressionSocket");
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleAnalogExpressionSocket::getTriggerOnChange() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->getTriggerOnChange();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->setTriggerOnChange(triggerOnChange);
}

/**
 * Get the value of the AnalogExpressionBean.
 */
/*private*/ double DefaultMaleAnalogExpressionSocket::internalEvaluate() /*throws JmriException*/ {
    //double result = ((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->evaluate();
    Base* object  =AbstractMaleSocket::getObject();
    double result = ((AbstractAnalogExpression*)object->bself())->evaluate();

    if (/*Double.isNaN*/std::isnan(result)) {
        throw new IllegalArgumentException("The result is NaN");
    }
    if (result == /*Double.NEGATIVE_INFINITY*/-INFINITY) {
        throw new IllegalArgumentException("The result is negative infinity");
    }
    if (result == /*Double.POSITIVE_INFINITY*/INFINITY) {
        throw new IllegalArgumentException("The result is positive infinity");
    }
    return result;
}

/** {@inheritDoc} */
//@Override
/*public*/  double DefaultMaleAnalogExpressionSocket::evaluate() /*throws JmriException*/ {
    if (! _enabled) {
        return 0.0;
    }

    if ((_debugConfig != nullptr)
            && ((AnalogExpressionDebugConfig*)_debugConfig)->_forceResult) {
        return ((AnalogExpressionDebugConfig*)_debugConfig)->_result;
    }

    ConditionalNG* conditionalNG = getConditionalNG();

    int currentStackPos = conditionalNG->getStack()->getCount();

    double result = 0.0;
    try {
        conditionalNG->getSymbolTable()->createSymbols(_localVariables);
        result = internalEvaluate();
    } catch (JmriException* e) {
        if (!e->getErrors().isEmpty()) {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during evaluate:"), e->getErrors(), e, log);
        } else {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during evaluate: %1").arg(e->getLocalizedMessage()), e, log);
        }
    } catch (RuntimeException* e) {
        handleError((AbstractMaleSocket*)this, tr("An exception has occurred during evaluate: %1").arg(e->getLocalizedMessage()), e, log);
    }

    conditionalNG->getStack()->setCount(currentStackPos);
    conditionalNG->getSymbolTable()->removeSymbols(_localVariables);

    return result;
}

//@Override
/*public*/  int DefaultMaleAnalogExpressionSocket::getState() {
    return ((AbstractBase*)getObject()->bself())->getState();
}

//@Override
/*public*/  QString DefaultMaleAnalogExpressionSocket::getDisplayName() {
    return ((AbstractNamedBean*)getObject()->bself())->getDisplayName();
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::disposeMe() {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::registerListenersForThisClass() {
    //((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
 AbstractMaleSocket::getObject()->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::unregisterListenersForThisClass() {
    //((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
AbstractMaleSocket::getObject()->unregisterListeners();}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setState(int s) /*throws JmriException*/ {
    ((AbstractBase*)getObject()->bself())->setState(s);
}

//@Override
/*public*/  QString DefaultMaleAnalogExpressionSocket::describeState(int state) {
    return tr("Unknown");
}

//@Override
/*public*/  QString DefaultMaleAnalogExpressionSocket::getComment() {
    return ((AbstractNamedBean*)getObject()->bself())->getComment();
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setComment(QString comment) {
    return ((AbstractNamedBean*)getObject()->bself())->setComment(comment);
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setProperty(QString key, QVariant value) {
    return ((AbstractNamedBean*)getObject()->bself())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleAnalogExpressionSocket::getProperty(QString key) {
    //return ((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->getProperty(key);
 return ((AbstractNamedBean*)getObject()->bself())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::removeProperty(QString key) {
    return ((AbstractNamedBean*)getObject()->bself())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> DefaultMaleAnalogExpressionSocket::getPropertyKeys() {
    return ((AbstractNamedBean*)getObject()->bself())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleAnalogExpressionSocket::getBeanType() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleAnalogExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    //return ((AnalogExpressionBean*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
 return ((AbstractBase*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setDebugConfig(DebugConfig* config) {
    _debugConfig = config;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleAnalogExpressionSocket::getDebugConfig() {
    return _debugConfig;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleAnalogExpressionSocket::createDebugConfig() {
    return new AnalogExpressionDebugConfig();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setEnabled(bool enable) {
    _enabled = enable;
    if (AbstractMaleSocket::isActive()) {
        AbstractMaleSocket::registerListeners();
    } else {
        AbstractMaleSocket::unregisterListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setEnabledFlag(bool enable) {
    _enabled = enable;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleAnalogExpressionSocket::isEnabled() {
    return _enabled;
}

/*private*/ /*final*/ /*static*/ Logger* DefaultMaleAnalogExpressionSocket::log = LoggerFactory::getLogger("DefaultMaleAnalogExpressionSocket");
