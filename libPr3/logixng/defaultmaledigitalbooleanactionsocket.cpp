#include "defaultmaledigitalbooleanactionsocket.h"
#include "loggerfactory.h"
#include "digitalbooleanactionbean.h"
#include "conditionalng.h"
#include "symboltable.h"
#include "digitalbooleanactionbean.h"
#include "abstractdigitalbooleanaction.h"

/**
 * Every DigitalBooleanActionBean has an DefaultMaleDigitalBooleanActionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DefaultMaleDigitalBooleanActionSocket
//        extends AbstractMaleSocket implements MaleDigitalBooleanActionSocket {



    /*public*/  DefaultMaleDigitalBooleanActionSocket::DefaultMaleDigitalBooleanActionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
      /*@Nonnull*/ DigitalBooleanActionBean* action, QObject* parent) : AbstractMaleSocket(manager, (Base*)action, parent) {
        //super(manager, action);
     setObjectName("DefaultMaleDigitalBooleanActionSocket");
        QObject::setProperty("AdapterName", "jmri.jmrit.logixng.implementation.configurexml.DefaultMaleDigitalBooleanActionSocketXml");

    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ {
        if (! _enabled) {
            return;
        }

        if ((_debugConfig != nullptr)
                && ((DigitalBooleanActionDebugConfig*)_debugConfig)->_dontExecute) {
            return;
        }

        ConditionalNG* conditionalNG = AbstractMaleSocket::getConditionalNG();

        int currentStackPos = conditionalNG->getStack()->getCount();

        try {
            conditionalNG->getSymbolTable()->createSymbols(_localVariables);
            //((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->execute(hasChangedToTrue, hasChangedToFalse);
          Base* object  =AbstractMaleSocket::getObject();
          ((AbstractDigitalBooleanAction*)object->bself())->execute(hasChangedToTrue, hasChangedToFalse);
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
    /*public*/  QString DefaultMaleDigitalBooleanActionSocket::getDisplayName() {
        //return ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->getDisplayName();
     return ((AbstractNamedBean*)getObject()->bself())->getDisplayName();
    }

    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::disposeMe() {
        ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::dispose();
    }

    /**
     * Register listeners if this object needs that.
     */
    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::registerListenersForThisClass() {
        ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
    }

    /**
     * Register listeners if this object needs that.
     */
    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::unregisterListenersForThisClass() {
        ((AbstractDigitalBooleanAction*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
    }

    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::setState(int s) /*throws JmriException */{
        //((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->setState(s);
     ((AbstractNamedBean*)getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DefaultMaleDigitalBooleanActionSocket::getState() {
        //return ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->getState();
        return ((AbstractNamedBean*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DefaultMaleDigitalBooleanActionSocket::describeState(int state) {
        return ((AbstractNamedBean*)getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  QString DefaultMaleDigitalBooleanActionSocket::getComment() {
        //return ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::getComment();
        return ((AbstractNamedBean*)getObject()->bself())->getComment();
    }

    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::setComment(QString comment) {
        //((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::setComment(comment);
     ((AbstractNamedBean*)getObject()->bself())->setComment(comment);
    }

    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::setProperty(QString key, QVariant value) {
        ((AbstractNamedBean*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DefaultMaleDigitalBooleanActionSocket::getProperty(QString key) {
        return ((AbstractNamedBean*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::removeProperty(QString key) {
//        ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->removeProperty(key);
        ((AbstractNamedBean*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DefaultMaleDigitalBooleanActionSocket::getPropertyKeys() {
        return ((AbstractNamedBean*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DefaultMaleDigitalBooleanActionSocket::getBeanType() {
        return ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DefaultMaleDigitalBooleanActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
//        return ((DigitalBooleanActionBean*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
        return ((AbstractBase*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::setDebugConfig(DebugConfig* config) {
        _debugConfig = config;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket::DebugConfig* DefaultMaleDigitalBooleanActionSocket::getDebugConfig() {
        return _debugConfig;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket::DebugConfig* DefaultMaleDigitalBooleanActionSocket::createDebugConfig() {
        return new DigitalBooleanActionDebugConfig();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::setEnabled(bool enable) {
        _enabled = enable;
        if (AbstractMaleSocket::isActive()) {
            AbstractMaleSocket::registerListeners();
        } else {
            AbstractMaleSocket::unregisterListeners();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocket::setEnabledFlag(bool enable) {
        _enabled = enable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultMaleDigitalBooleanActionSocket::isEnabled() {
        return _enabled;
    }

/*private*/ /*final*/ /*static*/ Logger* DefaultMaleDigitalBooleanActionSocket::log = LoggerFactory::getLogger("DefaultMaleDigitalBooleanActionSocket");
