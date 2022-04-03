#include "defaultmaledigitalactionsocket.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "runtimeexception.h"
#include "conditionalng.h"
#include "digitalactionbean.h"
#include "abstractdigitalaction.h"

/**
 * Every DigitalActionBean has an DefaultMaleDigitalActionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DefaultMaleDigitalActionSocket
//        extends AbstractMaleSocket implements MaleDigitalActionSocket {



/*public*/  DefaultMaleDigitalActionSocket::DefaultMaleDigitalActionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
                       /*@Nonnull*/ DigitalActionBean* action, QObject* parent) : AbstractMaleSocket(manager, (Base*)action, parent){
    //super(manager, action);
 setObjectName("DefaultMaleDigitalActionSocket");
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalActionSocket::execute() /*throws JmriException*/ {
    if (! _enabled) {
        return;
    }

    if ((_debugConfig != nullptr)
            && ((DigitalActionDebugConfig*)_debugConfig)->_dontExecute) {
        return;
    }

    ConditionalNG* conditionalNG = AbstractMaleSocket::getConditionalNG();

    int currentStackPos = conditionalNG->getStack()->getCount();

    try {
        conditionalNG->getSymbolTable()->createSymbols(_localVariables);
        Base* object  =AbstractMaleSocket::getObject();
        //((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->execute();
        ((AbstractDigitalAction*)object->bself())->execute();
    } catch (JmriException* e) {
        if (!e->getErrors().isEmpty()) {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during execute:"), e->getErrors(), e, log);
        } else {
            handleError((AbstractMaleSocket*)this, tr("An exception has occurred during execute: %1").arg(e->getLocalizedMessage()), e, log);
        }
    } catch (RuntimeException* e) {
        handleError((AbstractMaleSocket*)this, tr("An exception has occurred during execute: %1").arg( e->getLocalizedMessage()), e, log);
    }

    conditionalNG->getStack()->setCount(currentStackPos);
    conditionalNG->getSymbolTable()->removeSymbols(_localVariables);
}

//@Override
/*public*/  void DefaultMaleDigitalActionSocket::disposeMe() {
    ((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::dispose();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleDigitalActionSocket::registerListenersForThisClass() {
    //((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
 Base* ams = getObject();
 QObject* obj = (QObject*)ams->bself();
 ((AbstractDigitalAction*)obj)->registerListeners();
}

/**
 * Register listeners if this object needs that.
 */
//@Override
/*public*/  void DefaultMaleDigitalActionSocket::unregisterListenersForThisClass() {
    //((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
AbstractMaleSocket::getObject()->unregisterListeners();
}

//@Override
/*public*/  void DefaultMaleDigitalActionSocket::setState(int s) /*throws JmriException*/ {
    //((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->setState(s);
 ((AbstractBase*)getObject()->bself())->setState(s);
}

//@Override
/*public*/  int DefaultMaleDigitalActionSocket::getState() {
    //return ((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->getState();
 return ((AbstractBase*)getObject()->bself())->getState();
}

//@Override
/*public*/  QString DefaultMaleDigitalActionSocket::describeState(int state) {
    return ((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->describeState(state);
}

//@Override
/*public*/  QString DefaultMaleDigitalActionSocket::getComment() {
    return ((AbstractNamedBean*)getObject()->bself())->getComment();
}

//@Override
/*public*/  void DefaultMaleDigitalActionSocket::setComment(QString comment) {
    ((AbstractNamedBean*)getObject()->bself())->setComment(comment);
}

//@Override
/*public*/  void DefaultMaleDigitalActionSocket::setProperty(QString key, QVariant value) {
    ((AbstractNamedBean*)getObject()->bself())->setProperty(key, value);
}

//@Override
/*public*/  QVariant DefaultMaleDigitalActionSocket::getProperty(QString key) {
    return ((AbstractNamedBean*)getObject()->bself())->getProperty(key);
}

//@Override
/*public*/  void DefaultMaleDigitalActionSocket::removeProperty(QString key) {
    ((AbstractNamedBean*)getObject()->bself())->removeProperty(key);
}

//@Override
/*public*/  QSet<QString> DefaultMaleDigitalActionSocket::getPropertyKeys() {
    return ((AbstractNamedBean*)getObject()->bself())->getPropertyKeys();
}

//@Override
/*public*/  QString DefaultMaleDigitalActionSocket::getBeanType() {
    return ((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->getBeanType();
}

//@Override
/*public*/  int DefaultMaleDigitalActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
    //return ((DigitalActionBean*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    return ((AbstractBase*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalActionSocket::setDebugConfig(DebugConfig* config) {
    _debugConfig = config;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleDigitalActionSocket::getDebugConfig() {
    return _debugConfig;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket::DebugConfig* DefaultMaleDigitalActionSocket::createDebugConfig() {
    return new DigitalActionDebugConfig();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalActionSocket::setEnabled(bool enable) {
    _enabled = enable;
    if (AbstractMaleSocket::isActive()) {
        AbstractMaleSocket::registerListeners();
    } else {
        AbstractMaleSocket::unregisterListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultMaleDigitalActionSocket::setEnabledFlag(bool enable) {
    _enabled = enable;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DefaultMaleDigitalActionSocket::isEnabled() {
    return _enabled;
}

/*private*/ /*final*/ /*static*/ Logger* DefaultMaleDigitalActionSocket::log = LoggerFactory::getLogger("DefaultMaleDigitalActionSocket");
