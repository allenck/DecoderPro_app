#include "defaultmaleanalogexpressionsocket.h"
#include "loggerfactory.h"
#include <cmath>
#include "conditionalng.h"

/**
 * Every AnalogExpressionBean has an DefaultMaleAnalogExpressionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class DefaultMaleAnalogExpressionSocket extends AbstractMaleSocket implements MaleAnalogExpressionSocket {



/*public*/  DefaultMaleAnalogExpressionSocket::DefaultMaleAnalogExpressionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
   /*@Nonnull*/ AnalogExpressionBean* expression, QObject *parent) : AbstractMaleSocket(manager, expression, parent) {
    //super(manager, expression);
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleAnalogExpressionSocket::getTriggerOnChange() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->getTriggerOnChange();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->setTriggerOnChange(triggerOnChange);
}

/**
 * Get the value of the AnalogExpressionBean.
 */
/*private*/ double DefaultMaleAnalogExpressionSocket::internalEvaluate() /*throws JmriException*/ {
    double result = ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->evaluate();

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

    ConditionalNG* conditionalNG = AbstractMaleSocket::getConditionalNG();

    int currentStackPos = conditionalNG->getStack()->getCount();

    double result = 0.0;
    try {
        conditionalNG->getSymbolTable()->createSymbols(_localVariables);
        result = internalEvaluate();
    } catch (JmriException* e) {
        if (e->getErrors() != nullptr) {
            handleError(this, tr("An exception has occurred during evaluate:"), e.getErrors(), e, log);
        } else {
            handleError(this, tr("An exception has occurred during evaluate: %1").arg(e->getLocalizedMessage()), e, log);
        }
    } catch (RuntimeException* e) {
        handleError(this, tr("An exception has occurred during evaluate: %1", e->getLocalizedMessage()), e, log);
    }

    conditionalNG->getStack()->setCount(currentStackPos);
    conditionalNG->getSymbolTable()->removeSymbols(_localVariables);

    return result;
}

//@Override
/*public*/  int DefaultMaleAnalogExpressionSocket::getState() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->getState();
}

//@Override
/*public*/  QString DefaultMaleAnalogExpressionSocket::getDisplayName() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->getDisplayName();
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::disposeMe() {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void registerListenersForThisClass() {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::unregisterListenersForThisClass() {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->unregisterListeners();
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setState(int s) /*throws JmriException*/ {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->setState(s);
}

//@Override
/*public*/  QString DefaultMaleAnalogExpressionSocket::describeState(int state) {
    return tr("Unknown");
}

//@Override
/*public*/  QString AbstractMaleSocket::getComment() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->NamedBean::getComment();
}

//@Override
/*public*/  void AbstractMaleSocket::setComment(QString comment) {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->NamedBean::setComment(comment);
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setProperty(QString key, QVariant value) {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleAnalogExpressionSocket::getProperty(QString key) {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::removeProperty(QString key) {
    ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> AbstractMaleSocket::getPropertyKeys() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleAnalogExpressionSocket::getBeanType() {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleAnalogExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    return ((AnalogExpressionBean*)AbstractMaleSocket::getObject())->compareSystemNameSuffix(suffix1, suffix2, n2);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setDebugConfig(DebugConfig* config) {
    _debugConfig = config;
}

/** {@inheritDoc} */
//@Override
/*public*/  DebugConfig* DefaultMaleAnalogExpressionSocket::getDebugConfig() {
    return _debugConfig;
}

/** {@inheritDoc} */
//@Override
/*public*/  DebugConfig* DefaultMaleAnalogExpressionSocket::createDebugConfig() {
    return new AnalogExpressionDebugConfig();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleAnalogExpressionSocket::setEnabled(bool enable) {
    _enabled = enable;
    if (isActive()) {
        registerListeners();
    } else {
        unregisterListeners();
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
