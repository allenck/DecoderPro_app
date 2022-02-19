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
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleStringExpressionSocket::getTriggerOnChange() {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->getTriggerOnChange();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->setTriggerOnChange(triggerOnChange);
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

    ConditionalNG* currentConditionalNG = AbstractMaleSocket::getConditionalNG();

    int currentStackPos = currentConditionalNG->getStack()->getCount();

    QString result = "";
    try {
        currentConditionalNG->getSymbolTable()->createSymbols(_localVariables);
        result = ((StringExpressionBean*)AbstractMaleSocket::getObject())->evaluate();
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
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->getState();
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::getDisplayName() {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->getDisplayName();
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::disposeMe() {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->NamedBean::dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::registerListenersForThisClass() {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringExpressionSocket::unregisterListenersForThisClass() {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->unregisterListeners();
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setState(int s) /*throws JmriException*/ {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->setState(s);
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::describeState(int /*state*/) {
    return tr("Unknown");
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::getComment() {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->NamedBean::getComment();
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setComment(QString comment) {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->NamedBean::setComment(comment);
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::setProperty(QString key, QVariant value) {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleStringExpressionSocket::getProperty(QString key) {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleStringExpressionSocket::removeProperty(QString key) {
    ((StringExpressionBean*)AbstractMaleSocket::getObject())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> DefaultMaleStringExpressionSocket::getPropertyKeys() {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleStringExpressionSocket::getBeanType() {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleStringExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    return ((StringExpressionBean*)AbstractMaleSocket::getObject())->compareSystemNameSuffix(suffix1, suffix2, n2);
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
