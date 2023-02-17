#include "defaultmaledigitalexpressionsocket.h"
#include "loggerfactory.h"
#include "digitalexpressionbean.h"
#include "conditionalng.h"
#include "abstractdigitalexpression.h"

/**
 * Every DigitalExpressionBean has an DefaultMaleDigitalExpressionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DefaultMaleDigitalExpressionSocket extends AbstractMaleSocket implements MaleDigitalExpressionSocket {



/*public*/ DefaultMaleDigitalExpressionSocket::DefaultMaleDigitalExpressionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
  /*@Nonnull*/ DigitalExpressionBean* expression, QObject *parent)
 :  AbstractMaleSocket(manager, expression, parent){
    //super(manager, expression);
 setObjectName("DefaultMaleDigitalExpressionSocket");
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::notifyChangedResult(bool oldResult, bool newResult) {
    ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->notifyChangedResult(oldResult, newResult);
}

/*private*/ void DefaultMaleDigitalExpressionSocket::checkChangedLastResult(bool savedLastResult) {
    if (savedLastResult != lastEvaluationResult) {
//            ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())
//                    ->notifyChangedResult(savedLastResult, lastEvaluationResult);
     Base* object  =AbstractMaleSocket::getObject();
     ((AbstractDigitalExpression*)object->bself())->notifyChangedResult(savedLastResult, lastEvaluationResult);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleDigitalExpressionSocket::evaluate() /*throws JmriException*/ {
    bool saveLastResult = lastEvaluationResult;
    if (! _enabled) {
        lastEvaluationResult = false;
        checkChangedLastResult(saveLastResult);
        return false;
    }

    if ((_debugConfig != nullptr)
            && ((DigitalExpressionDebugConfig*)_debugConfig)->_forceResult) {
        lastEvaluationResult = ((DigitalExpressionDebugConfig*)_debugConfig)->_result;
        checkChangedLastResult(saveLastResult);
        return lastEvaluationResult;
    }

    ConditionalNG* conditionalNG = AbstractMaleSocket::getConditionalNG();

    int currentStackPos = conditionalNG->getStack()->getCount();

    try {
        conditionalNG->getSymbolTable()->createSymbols(_localVariables);
        //lastEvaluationResult = ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->evaluate();
        Base* object  =AbstractMaleSocket::getObject();
        lastEvaluationResult = ((AbstractDigitalExpression*)object->bself())->evaluate();
    } catch (JmriException* e) {
        if (!e->getErrors().isEmpty()) {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during evaluate:"), e->getErrors(), e, log);
        } else {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during execute: %1").arg( e->getLocalizedMessage()), e, log);
        }
        lastEvaluationResult = false;
    } catch (RuntimeException* e) {
        handleError((AbstractMaleSocket*)this, tr("An exception has occurred during execute: %1").arg(e->getLocalizedMessage()), e, log);
        lastEvaluationResult = false;
    }

    conditionalNG->getStack()->setCount(currentStackPos);
    conditionalNG->getSymbolTable()->removeSymbols(_localVariables);

    checkChangedLastResult(saveLastResult);
    return lastEvaluationResult;
}

//@Override
/*public*/  bool DefaultMaleDigitalExpressionSocket::getLastResult() {
    return lastEvaluationResult;
}

//@Override
/*public*/  int DefaultMaleDigitalExpressionSocket::getState() {
    return ((AbstractNamedBean*)getObject()->bself())->getState();
}

//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::setState(int s) /*throws JmriException*/ {
    ((AbstractNamedBean*)getObject()->bself())->setState(s);
}

//@Override
/*public*/  QString DefaultMaleDigitalExpressionSocket::describeState(int state) {
    //return ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->describeState(state);
    return ((AbstractNamedBean*)getObject()->bself())->describeState(state);
}

//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::setProperty(QString key, QVariant value) {
    ((AbstractNamedBean*)getObject()->bself())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleDigitalExpressionSocket::getProperty(QString key) {
    return ((AbstractNamedBean*)getObject()->bself())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::removeProperty(QString key) {
   ((AbstractNamedBean*)getObject()->bself())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> DefaultMaleDigitalExpressionSocket::getPropertyKeys() {
    return ((AbstractNamedBean*)getObject()->bself())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleDigitalExpressionSocket::getBeanType(){
    return ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleDigitalExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    //return ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
 return ((AbstractBase*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::setDebugConfig(DebugConfig* config) {
    _debugConfig = config;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleDigitalExpressionSocket::getDebugConfig() {
    return _debugConfig;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleDigitalExpressionSocket::createDebugConfig() {
    return new DigitalExpressionDebugConfig();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::setEnabled(bool enable) {
    _enabled = enable;
    if (AbstractMaleSocket::isActive()) {
        AbstractMaleSocket::registerListeners();
    } else {
        AbstractMaleSocket::unregisterListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::setEnabledFlag(bool enable) {
    _enabled = enable;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleDigitalExpressionSocket::isEnabled() {
    return _enabled;
}

//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::disposeMe() {
    ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::registerListenersForThisClass() {
//        ((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
  ((AbstractMaleSocket*)getObject()->bself())->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleDigitalExpressionSocket::unregisterListenersForThisClass() {
    //((DigitalExpressionBean*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
 Base* base = getObject();
 ((AbstractBase*)getObject()->bself())->unregisterListeners();
}

//@Override
/*public*/  QString DefaultMaleDigitalExpressionSocket::getDisplayName() {
    return ((AbstractNamedBean*)getObject()->bself())->getDisplayName();
}

/*private*/ /*final*/ /*static*/ /*org.slf4j.*/Logger* DefaultMaleDigitalExpressionSocket::log = LoggerFactory::getLogger("DefaultMaleDigitalExpressionSocket");
