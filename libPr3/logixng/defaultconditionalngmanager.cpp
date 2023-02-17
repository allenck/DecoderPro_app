#include "defaultconditionalngmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "logixng_manager.h"
#include "logixng_thread.h"
#include "loggingutil.h"
#include "defaultconditionalng.h"
#include "defaultlogixng.h"
#include "vptr.h"
#include "defaultlogixngmanager.h"

/**
 * Class providing the basic logic of the ConditionalNG_Manager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 * @author Dave Sand          Copyright (C) 2021
 */
///*public*/  class DefaultConditionalNGManager extends AbstractManager<ConditionalNG>
//        implements ConditionalNG_Manager {


    /*public*/  DefaultConditionalNGManager::DefaultConditionalNGManager(QObject* parent) : AbstractManager(parent) {
        // LogixNGPreferences class may load plugins so we must ensure
        // it's loaded here.
        InstanceManager::getDefault("LogixNGPreferences");
        registerSelf();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int  DefaultConditionalNGManager::getXMLOrder() const {
        return LOGIXNG_CONDITIONALNGS;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QChar  DefaultConditionalNGManager::typeLetter() const {
        return 'Q';
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Manager::NameValidity  DefaultConditionalNGManager::validSystemNameFormat(QString systemName) {
        return LogixNG_Manager::ng_validSystemNameFormat(
                ConditionalNG_Manager::getSubSystemNamePrefix(), systemName);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  DefaultConditionalNG*  DefaultConditionalNGManager::createConditionalNG(LogixNG* logixNG, QString systemName, QString userName)
            /*throws IllegalArgumentException*/ {

        return createConditionalNG(logixNG, systemName, userName, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  DefaultConditionalNG*  DefaultConditionalNGManager::createConditionalNG(
            LogixNG* logixNG, QString systemName, QString userName, int threadID)
            /*throws IllegalArgumentException*/ {

        // Check that ConditionalNG does not already exist
        DefaultConditionalNG* x;
        if (userName != "" && !userName.isEmpty()) {
            x = getByUserName(logixNG, userName);
            if (x != nullptr) {
                log->error(tr("username '%1' already exists, conditionalNG is '%2'").arg(userName, x->AbstractNamedBean::getDisplayName()));
                return nullptr;
            }
        }

        x = (DefaultConditionalNG*)getBySystemName(systemName);
        if (x != nullptr) {
            log->error(tr("systemname '%1' already exists, conditionalNG is '%2'").arg(systemName, x->AbstractNamedBean::getDisplayName()));
            return nullptr;
        }

        // Check if system name is valid
        if (this->validSystemNameFormat(systemName) != NameValidity::VALID) {
            throw new IllegalArgumentException("SystemName '" + systemName + "' is not in the correct format");
        }

        // ConditionalNG does not exist, create a new ConditionalNG
        x = new DefaultConditionalNG(systemName, userName, threadID);

        // Add the conditional to the LogixNG map
        logixNG->addConditionalNG(x);

        // Keep track of the last created auto system name
        updateAutoNumber(systemName);

        return x;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  ConditionalNG*  DefaultConditionalNGManager::createConditionalNG(LogixNG* logixNG, QString userName) /*throws IllegalArgumentException*/ {
        return createConditionalNG(logixNG, AbstractManager::getAutoSystemName(), userName);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  ConditionalNG*  DefaultConditionalNGManager::createConditionalNG(LogixNG* logixNG, QString userName, int threadID) /*throws IllegalArgumentException*/ {
        return createConditionalNG(logixNG, AbstractManager::getAutoSystemName(), userName, threadID);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  ConditionalNG*  DefaultConditionalNGManager::getConditionalNG(LogixNG* logixNG, QString name) {
        if (logixNG != nullptr) {
            ConditionalNG* x = getByUserName(logixNG, name);
            if (x != nullptr) {
                return x;
            }
        }
        return getBySystemName(name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  LogixNG*  DefaultConditionalNGManager::getParentLogixNG(QString systemName) const {
        if (systemName == "" || systemName.isEmpty()) {
            return nullptr;
        }

        for (NamedBean* nb : ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->AbstractManager::getNamedBeanSet()) {
         DefaultLogixNG* logixNG = (DefaultLogixNG*)nb->self();
            for (int i = 0; i < logixNG->getNumConditionalNGs(); i++) {
                if (systemName == (logixNG->getConditionalNG_SystemName(i))) {
                    return logixNG;
                }
            }
        }
        return nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  DefaultConditionalNG*  DefaultConditionalNGManager::getByUserName(LogixNG* logixNG, QString name) {
        if (logixNG != nullptr && name != "null" && !name.isEmpty()) {
            for (int i = 0; i < logixNG->getNumConditionalNGs(); i++) {
                DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)logixNG->getConditionalNG(i);
                if (conditionalNG != nullptr) {
                    if (name == (conditionalNG->AbstractNamedBean::getUserName())) {
                        return conditionalNG;
                    }
                }
            }
        }
        return nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  ConditionalNG *DefaultConditionalNGManager::getBySystemName(QString name) const{
     if(name.isEmpty()) throw new NullPointerException("name is null!");
        LogixNG* logixNG = getParentLogixNG(name);
        if (logixNG != nullptr) {
            for (int i = 0; i < logixNG->getNumConditionalNGs(); i++) {
                if (name ==(logixNG->getConditionalNG_SystemName(i))) {
                    return logixNG->getConditionalNG(i);
                }
            }
        }
        return nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString  DefaultConditionalNGManager::getBeanTypeHandled(bool plural) const {
        return tr(plural ? "ConditionalNGs" : "ConditionalNG");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void  DefaultConditionalNGManager::deleteConditionalNG(ConditionalNG* x) {
        // delete the ConditionalNG
        AbstractManager::deregister(x);
        x->Base::dispose();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void  DefaultConditionalNGManager::setLoadDisabled(bool s) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void  DefaultConditionalNGManager::setRunOnGUIDelayed(bool value) {
     foreach(NamedBean* nb,
        ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->AbstractManager::getNamedBeanSet()) {
      LogixNG* logixNG = (LogixNG*)nb->self();
            for (int i = 0; i < logixNG->getNumConditionalNGs(); i++) {
                if (logixNG->getConditionalNG(i) != nullptr) {
                    logixNG->getConditionalNG(i)->setRunDelayed(false);
                }
            }
        }//);
    }

    /*static*/ /*volatile*/ DefaultConditionalNGManager* DefaultConditionalNGManager::_instance = nullptr;

    //@InvokeOnGuiThread  // this method is not thread safe
    /*static*/ /*public*/  DefaultConditionalNGManager*  DefaultConditionalNGManager::instance() {
        if (!ThreadingUtil::isGUIThread()) {
            LoggingUtil::warnOnce(log, "instance() called on wrong thread");
        }

        if (_instance == nullptr) {
            _instance = new DefaultConditionalNGManager();
        }
        return (_instance);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<ConditionalNG>*/QString  DefaultConditionalNGManager::getNamedBeanClass() const {
        return "ConditionalNG";
    }

    /**
     * Inform all registered listeners of a vetoable change.If the propertyName
     * is "CanDelete" ALL listeners with an interest in the bean will throw an
     * exception, which is recorded returned back to the invoking method, so
     * that it can be presented back to the user.However if a listener decides
     * that the bean can not be deleted then it should throw an exception with
     * a property name of "DoNotDelete", this is thrown back up to the user and
     * the delete process should be aborted.
     *
     * @param p   The programmatic name of the property that is to be changed.
     *            "CanDelete" will inquire with all listeners if the item can
     *            be deleted. "DoDelete" tells the listener to delete the item.
     * @param old The old value of the property.
     * @throws java.beans.PropertyVetoException If the recipients wishes the
     *                                          delete to be aborted (see above)
     */
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void  DefaultConditionalNGManager::fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException*/ {
        PropertyChangeEvent* evt = new PropertyChangeEvent(this, p, old, QVariant());
        for (VetoableChangeListener* vc : *vetoableChangeSupport->getVetoableChangeListeners()) {
            vc->vetoableChange(evt);
        }
    }

    /** {@inheritDoc} */
    //@Override
//    @OverridingMethodsMustInvokeSuper
    /*public*/  /*final*/ void  DefaultConditionalNGManager::deleteBean(/*@Nonnull*/ /*ConditionalNG*/NamedBean* nb, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/ {
     ConditionalNG* conditionalNG = (DefaultConditionalNG*)nb->self();
     for (int i=0; i < conditionalNG->getChildCount(); i++) {
            FemaleSocket* child = conditionalNG->getChild(i);
            if (child->isConnected()) {
                MaleSocket* maleSocket = child->getConnectedSocket();
                maleSocket->getManager()->deleteBean(maleSocket, property);
            }
        }

        // throws PropertyVetoException if vetoed
        fireVetoableChange(property, VPtr<ConditionalNG>::asQVariant(conditionalNG));
        if (property == ("DoDelete")) { // NOI18N
            if (conditionalNG->getLogixNG() != nullptr) {
                conditionalNG->getLogixNG()->deleteConditionalNG(conditionalNG);
            }
            conditionalNG->Base::dispose();
        }
    }


    /*private*/ /*final*/ /*static*/ Logger* DefaultConditionalNGManager::log = LoggerFactory::getLogger("DefaultConditionalNGManager");
