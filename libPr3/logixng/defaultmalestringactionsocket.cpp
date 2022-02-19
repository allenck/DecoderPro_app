#include "defaultmalestringactionsocket.h"
#include "loggerfactory.h"
#include "stringactionbean.h"
#include "conditionalng.h"

/**
 * Every StringActionBean has an DefaultMaleStringActionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class DefaultMaleStringActionSocket extends AbstractMaleSocket implements MaleStringActionSocket {

//    /*private*/ /*final*/ StringActionBean ((StringActionBean)getObject()->bself());


/*public*/  DefaultMaleStringActionSocket::DefaultMaleStringActionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
 /*@Nonnull*/ StringActionBean* stringAction, QObject* parent) : AbstractMaleSocket(manager, stringAction, parent)
{
    //super(manager, stringAction);
}

/** {@inheritDoc} */
//@Override
/**
 * Set a string value.
 */
/*public*/  void DefaultMaleStringActionSocket::setValue(QString value) /*throws JmriException*/ {
    if (! _enabled) {
        return;
    }

    if ((_debugConfig != nullptr)
            && ((StringActionDebugConfig*)_debugConfig)->_dontExecute) {
        return;
    }

    ConditionalNG* conditionalNG = AbstractMaleSocket::getConditionalNG();

    int currentStackPos = conditionalNG->getStack()->getCount();

    try {
        conditionalNG->getSymbolTable()->createSymbols(_localVariables);
        ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->setValue(value);
    } catch (JmriException* e) {
        if (!e->getErrors().isEmpty()) {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during execute:"), e->getErrors(), e, log);
        } else {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during setValue: %1").arg(e->getLocalizedMessage()), e, log);
        }
    } catch (RuntimeException* e) {
        handleError((AbstractMaleSocket*)this, tr("An exception has occurred during setValue: %1").arg(e->getLocalizedMessage()), e, log);
    }

    conditionalNG->getStack()->setCount(currentStackPos);
    conditionalNG->getSymbolTable()->removeSymbols(_localVariables);
}

//@Override
/*public*/  QString DefaultMaleStringActionSocket::getDisplayName() {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->getDisplayName();
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::disposeMe() {
    ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringActionSocket::registerListenersForThisClass() {
    ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringActionSocket::unregisterListenersForThisClass() {
    ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::setState(int s) /*throws JmriException*/ {
    ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->setState(s);
}

//@Override
/*public*/  int DefaultMaleStringActionSocket::getState() {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->getState();
}

//@Override
/*public*/  QString DefaultMaleStringActionSocket::describeState(int state) {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->describeState(state);
}

//@Override
/*public*/  QString DefaultMaleStringActionSocket::getComment() {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::getComment();
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::setComment(QString comment) {
    ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::setComment(comment);
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::setProperty(QString key, QVariant value) {
    ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleStringActionSocket::getProperty(QString key) {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::removeProperty(QString key) {
    ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> DefaultMaleStringActionSocket::getPropertyKeys() {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleStringActionSocket::getBeanType() {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleStringActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    return ((StringActionBean*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringActionSocket::setDebugConfig(DebugConfig* config) {
    _debugConfig = config;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleStringActionSocket::getDebugConfig() {
    return _debugConfig;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleStringActionSocket::createDebugConfig() {
    return new StringActionDebugConfig();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringActionSocket::setEnabled(bool enable) {
    _enabled = enable;
    if (AbstractMaleSocket::isActive()) {
        AbstractMaleSocket::registerListeners();
    } else {
        AbstractMaleSocket::unregisterListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleStringActionSocket::setEnabledFlag(bool enable) {
    _enabled = enable;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleStringActionSocket::isEnabled() {
    return _enabled;
}




/*private*/ /*final*/ /*static*/ Logger* DefaultMaleStringActionSocket::log = LoggerFactory::getLogger("DefaultMaleStringActionSocket");
