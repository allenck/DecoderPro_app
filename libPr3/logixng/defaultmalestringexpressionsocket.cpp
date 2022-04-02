#include "defaultmalestringexpressionsocket.h"
#include "loggerfactory.h"
#include "conditionalng.h"
#include "jmriexception.h"

/**
 * Every StringExpressionBean has an DefaultMaleStringExpressionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class DefaultMaleStringExpressionSocket extends AbstractMaleSocket
//        implements MaleStringExpressionSocket {



/*public*/  DefaultMaleStringExpressionSocket::DefaultMaleStringExpressionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
  /*@Nonnull*/ StringExpressionBean* stringExpression, QObject* parent) : AbstractMaleSocket(manager, stringExpression, parent){
    //super(manager, stringExpression);
 setObjectName("DefaultMaleStringExpressionSocket");
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleStringExpressionSocket::getTriggerOnChange() {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->getTriggerOnChange();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
    ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->setTriggerOnChange(triggerOnChange);
}

/** {@inheritDoc} */
//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::evaluate() /*throws JmriException*/ {
    if (! _enabled) {
        return "";
    }

    if ((_debugConfig != nullptr)
            && ((StringExpressionDebugConfig*)_debugConfig)->_forceResult) {
        return ((StringExpressionDebugConfig*)_debugConfig)->_result;
    }

    ConditionalNG* currentConditionalNG = getConditionalNG();

    int currentStackPos = currentConditionalNG->getStack()->getCount();

    QString result = "";
    try {
        currentConditionalNG->getSymbolTable()->createSymbols(_localVariables);
        result = ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->evaluate();
    } catch (JmriException* e) {
        if (!e->getErrors().isEmpty()) {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during evaluate:"), e->getErrors(), e, log);
        } else {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during evaluate: %1").arg(e->getLocalizedMessage()), e, log);
        }
    } catch (RuntimeException* e) {
        handleError((AbstractMaleSocket*)this, tr("An exception has occurred during evaluate: %1").arg(e->getLocalizedMessage()), e, log);
    }

    currentConditionalNG->getStack()->setCount(currentStackPos);
    currentConditionalNG->getSymbolTable()->removeSymbols(_localVariables);

    return result;
}

//@Override
/*public*/  int DefaultMaleStringExpressionSocket::getState() {
    //return ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->getState();
 return ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->getState();
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::getDisplayName() {
    return ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->getDisplayName();
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::disposeMe() {
    ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::registerListenersForThisClass() {
    ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::unregisterListenersForThisClass() {
    ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setState(int s) /*throws JmriException*/ {
    //((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->setState(s);
  ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->setState(s);
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::describeState(int /*state*/) {
    return tr("Unknown");
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::getComment() {
    //return ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::getComment();
  return ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->getComment();
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setComment(QString comment) {
    //((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::setComment(comment);
 ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->setComment(comment);
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setProperty(QString key, QVariant value) {
    //((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->setProperty(key, value);
 ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleStringExpressionSocket::getProperty(QString key) {
    //return ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->getProperty(key);
 return ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::removeProperty(QString key) {
    //((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->removeProperty(key);
 ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> DefaultMaleStringExpressionSocket::getPropertyKeys() {
    //return ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->getPropertyKeys();
    return ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::getBeanType() {
    //return ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->getBeanType();
 ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleStringExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    //return ((StringExpressionBean*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
 return ((AbstractBase*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setDebugConfig(DebugConfig* config) {
    _debugConfig = config;
}

/** {@inheritDoc} */
//@Override
/*public*/  Debugable::DebugConfig* DefaultMaleStringExpressionSocket::getDebugConfig() {
    return _debugConfig;
}

/** {@inheritDoc} */
//@Override
/*public*/  Debugable::DebugConfig* DefaultMaleStringExpressionSocket::createDebugConfig() {
    return new StringExpressionDebugConfig();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setEnabled(bool enable) {
    _enabled = enable;
    if (AbstractMaleSocket::isActive()) {
        AbstractMaleSocket::registerListeners();
    } else {
        AbstractMaleSocket::unregisterListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setEnabledFlag(bool enable) {
    _enabled = enable;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleStringExpressionSocket::isEnabled() {
    return _enabled;
}



///*public*/  static class StringExpressionDebugConfig implements MaleSocket.DebugConfig {

//    // If true, the socket is returning the value of "result" instead of
//    // executing the expression.
//    /*public*/  boolean _forceResult = false;

//    // The result if the result is forced.
//    /*public*/  String _result = "";

//    //@Override
//    /*public*/  DebugConfig getCopy() {
//        StringExpressionDebugConfig config = new StringExpressionDebugConfig();
//        config._forceResult = _forceResult;
//        config._result = _result;
//        return config;
//    }

//}


/*private*/ /*final*/ /*static*/ Logger* DefaultMaleStringExpressionSocket::log = LoggerFactory::getLogger("DefaultMaleStringExpressionSocket");
