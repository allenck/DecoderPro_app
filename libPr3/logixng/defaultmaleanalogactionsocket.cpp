#include "defaultmaleanalogactionsocket.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "mathutil.h"
#include "analogactionbean.h"
#include "conditionalng.h"
#include "abstractanalogaction.h"

/**
 * Every AnalogActionBean has an DefaultMaleAnalogActionSocket as its parent.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DefaultMaleAnalogActionSocket extends AbstractMaleSocket implements MaleAnalogActionSocket {



    /*public*/  DefaultMaleAnalogActionSocket::DefaultMaleAnalogActionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
        /*@Nonnull*/ AnalogActionBean* action, QObject* parent) : AbstractMaleSocket(manager, (AbstractBase*)action->self(), parent) {
        //super(manager, action);
     setObjectName("DefaultMaleAnalogActionSocket");
    }

    /**
     * Set the value of the AnalogActionBean.
     */
    /*private*/ void DefaultMaleAnalogActionSocket::internalSetValue(double value) /*throws JmriException*/ {
        if (/*Double.isNaN*/(value!=value)) {
            throw new IllegalArgumentException("The value is NaN");
        }
        if (value == /*Double.NEGATIVE_INFINITY*/-INFINITY) {
            throw new IllegalArgumentException("The value is negative infinity");
        }
        if (value == /*Double.POSITIVE_INFINITY*/INFINITY) {
            throw new IllegalArgumentException("The value is positive infinity");
        }
        Base* object  =AbstractMaleSocket::getObject();
        //((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->setValue(value);
        ((AbstractAnalogAction*)object->bself())->setValue(value);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::setValue(double value) /*throws JmriException*/ {
        if (! _enabled) {
            return;
        }

        if ((_debugConfig != nullptr)
                && ((AnalogActionDebugConfig*)_debugConfig)->_dontExecute) {
            return;
        }

        ConditionalNG* conditionalNG = getConditionalNG();

        int currentStackPos = conditionalNG->getStack()->getCount();

        try {
            conditionalNG->getSymbolTable()->createSymbols(_localVariables);
            internalSetValue(value);
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
    /*public*/  QString DefaultMaleAnalogActionSocket::getDisplayName() {
        return ((AbstractNamedBean*)getObject()->bself())->getDisplayName();
    }

    /**
     * Register listeners if this object needs that.
     */
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::registerListenersForThisClass() {
        ((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->registerListeners();
    }

    /**
     * Register listeners if this object needs that.
     */
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::unregisterListenersForThisClass() {
        //((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->unregisterListeners();
    ((AbstractBase*)getObject()->bself())->unregisterListeners();
    }

    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::setState(int s) /*throws JmriException*/ {
        //((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->setState(s);
     ((AbstractBase*)getObject()->bself())->setState(s);

    }

    //@Override
    /*public*/  int DefaultMaleAnalogActionSocket::getState() {
        //return ((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->getState();
     return ((AbstractBase*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DefaultMaleAnalogActionSocket::describeState(int state) {
        return ((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  QString DefaultMaleAnalogActionSocket::getComment() {
        return ((AbstractNamedBean*)getObject()->bself())->getComment();
    }

    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::setComment(QString comment) {
        //((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->NamedBean::setComment(comment);
     ((AbstractNamedBean*)getObject()->bself())->setComment(comment);
    }

    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::setProperty(QString key, QVariant value) {
        //((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->setProperty(key, value);
     ((AbstractNamedBean*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DefaultMaleAnalogActionSocket::getProperty(QString key) {
        //return ((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->getProperty(key);
      return ((AbstractNamedBean*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::removeProperty(QString key) {
        ((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->removeProperty(key);
     ((AbstractNamedBean*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DefaultMaleAnalogActionSocket::getPropertyKeys() {
        //return ((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->getPropertyKeys();
     return ((AbstractNamedBean*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DefaultMaleAnalogActionSocket::getBeanType() {
        return ((AnalogActionBean*)AbstractMaleSocket::getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DefaultMaleAnalogActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        //return ((AnalogActionBean*)AbstractMaleSocket::geObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
     return ((AbstractBase*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::setDebugConfig(DebugConfig* config) {
        _debugConfig = config;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket::DebugConfig* DefaultMaleAnalogActionSocket::getDebugConfig() {
        return _debugConfig;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket::DebugConfig* DefaultMaleAnalogActionSocket::createDebugConfig() {
        return new AnalogActionDebugConfig();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::setEnabled(bool enable) {
        _enabled = enable;
        if (AbstractMaleSocket::isActive()) {
            AbstractMaleSocket::registerListeners();
        } else {
            AbstractMaleSocket::unregisterListeners();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::setEnabledFlag(bool enable) {
        _enabled = enable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultMaleAnalogActionSocket::isEnabled() {
        return _enabled;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocket::disposeMe() {
    }




    /*private*/ /*final*/ /*static*/ Logger* DefaultMaleAnalogActionSocket::log = LoggerFactory::getLogger("DefaultMaleAnalogActionSocket");
