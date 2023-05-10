#include "defaultmalestringactionsocket.h"
#include "loggerfactory.h"
#include "stringactionbean.h"
#include "conditionalng.h"
#include "abstractstringaction.h"

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
    QObject::setProperty("AdapterName", "jmri.jmrit.logixng.implementation.configurexml.DefaultMaleStringActionSocketXml");

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
        //((AbstractNamedBean*)getObject()->bself())->setValue(value);
        Base* object  =AbstractMaleSocket::getObject();
        ((AbstractStringAction*)object->bself())->setValue(value);
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
    return ((AbstractNamedBean*)getObject()->bself())->getDisplayName();
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::disposeMe() {
    ((AbstractNamedBean*)getObject()->bself())->NamedBean::dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringActionSocket::registerListenersForThisClass() {
 //((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
 ((AbstractBase*)getObject()->bself())->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleStringActionSocket::unregisterListenersForThisClass() {
    //((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
 ((AbstractBase*)getObject()->bself())->unregisterListeners();
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::setState(int s) /*throws JmriException*/ {
    ((AbstractNamedBean*)getObject()->bself())->setState(s);
}

//@Override
/*public*/  int DefaultMaleStringActionSocket::getState() {
    return ((AbstractNamedBean*)getObject()->bself())->getState();
}

//@Override
/*public*/  QString DefaultMaleStringActionSocket::describeState(int state) {
    return ((AbstractNamedBean*)getObject()->bself())->describeState(state);
}

//@Override
/*public*/  QString DefaultMaleStringActionSocket::getComment() {
    return ((AbstractNamedBean*)getObject()->bself())->getComment();
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::setComment(QString comment) {
    ((AbstractNamedBean*)getObject()->bself())->setComment(comment);
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::setProperty(QString key, QVariant value) {
    ((AbstractNamedBean*)getObject()->bself())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleStringActionSocket::getProperty(QString key) {
    return ((AbstractNamedBean*)getObject()->bself())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleStringActionSocket::removeProperty(QString key) {
    ((AbstractNamedBean*)getObject()->bself())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> DefaultMaleStringActionSocket::getPropertyKeys() {
    return ((AbstractNamedBean*)getObject()->bself())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleStringActionSocket::getBeanType() {
    return ((AbstractNamedBean*)getObject()->bself())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleStringActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    return ((AbstractBase*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
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
