#include "defaultmodulemanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "femalesocket.h"
#include "logixng_manager.h"
#include "loggingutil.h"
#include "threadingutil.h"
#include "defaultmodule.h"
#include "vptr.h"


/**
 * Class providing the basic logic of the LogixNG_Manager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultModuleManager extends AbstractManager<Module>
//        implements ModuleManager {


    /*public*/  DefaultModuleManager::DefaultModuleManager(QObject *parent) : AbstractManager(parent) {
        // The LogixNGPreferences class may load plugins so we must ensure
        // it's loaded here.
        InstanceManager::getDefault("LogixNGPreferences");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int DefaultModuleManager::getXMLOrder() const {
        return LOGIXNGS;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QChar DefaultModuleManager::typeLetter() const {
        return 'Q';
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Manager::NameValidity DefaultModuleManager::validSystemNameFormat(QString systemName) {
        return LogixNG_Manager::ng_validSystemNameFormat(
                ModuleManager::getSubSystemNamePrefix(), systemName);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Module* DefaultModuleManager::createModule(QString systemName, QString userName,
            FemaleSocketManager::SocketType* socketType)
            /*throws IllegalArgumentException*/ {

        // Check that Module does not already exist
        Module* x;
        if (userName != "" && userName!=("")) {
            x = getByUserName(userName);
            if (x != nullptr) {
                return nullptr;
            }
        }
        x = (Module*)getBySystemName(systemName);
        if (x != nullptr) {
            return nullptr;
        }
        // Check if system name is valid
        if (this->validSystemNameFormat(systemName) != NameValidity::VALID) {
            throw new IllegalArgumentException("SystemName " + systemName + " is not in the correct format");
        }
        // Module does not exist, create a new Module
        x = (Module*)new DefaultModule(systemName, userName, socketType);
        // save in the maps
        AbstractManager::Register(x);

        // Keep track of the last created auto system name
        updateAutoNumber(systemName);

        return x;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Module*/NamedBean* DefaultModuleManager::createModule(QString userName, FemaleSocketManager::SocketType* socketType) /*throws IllegalArgumentException*/ {
        return createModule(AbstractManager::getAutoSystemName(), userName, socketType);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Module* DefaultModuleManager::getModule(QString name) {
        Module* x = getByUserName(name);
        if (x != nullptr) {
            return x;
        }
        return (Module*)getBySystemName(name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Module* DefaultModuleManager::getByUserName(QString name) {
//        return (Module*)_tuser->value(name)->self();
     if(_tsys->value(name))
      return (Module*)_tuser->value(name)->self();
     return nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Module* DefaultModuleManager::getBySystemName(QString name) {
        //return (Module*)_tsys->value(name)->self();
     if(_tsys->value(name))
      return (Module*)_tsys->value(name)->self();
     return nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultModuleManager::getBeanTypeHandled(bool plural)const {
        return tr(plural ? "LogixNGModules" : "LogixNGModule");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultModuleManager::resolveAllTrees(QList<QString>* errors) {
        bool result = true;
        for (NamedBean* nb : _tsys->values()) {
         Module* logixNG_Module = (Module*)nb->self();
            result = result && logixNG_Module->setParentForAllChildren(errors);
        }
        return result;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultModuleManager::setupAllModules() {
        for (NamedBean* nb : _tsys->values()) {
         Module* logixNG = (Module*)nb->self();
            logixNG->setup();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultModuleManager::deleteModule(Module* x) {
        // delete the Module
        AbstractManager::deregister(x);
        x->NamedBean::dispose();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultModuleManager::printTree(
            Base::PrintTreeSettings* settings,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int* lineNumber) {

        printTree(settings, QLocale/*.getDefault*/(), writer, indent, lineNumber);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultModuleManager::printTree(
            Base::PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int* lineNumber) {

        for (NamedBean* nb : AbstractManager::getNamedBeanSet()) {
         Module* module = (Module*)nb->self();
            module->printTree(settings, locale, writer, indent, QString(), lineNumber);
            writer->println();
        }
        InstanceManager::getDefault("ModuleManager");
    }

    /*static*/ /*volatile*/ DefaultModuleManager*DefaultModuleManager:: _instance = nullptr;

    //@InvokeOnGuiThread  // this method is not thread safe
    /*static*/ /*public*/  DefaultModuleManager* DefaultModuleManager::instance() {
        if (!ThreadingUtil::isGUIThread()) {
            LoggingUtil::warnOnce(log, "instance() called on wrong thread");
        }

        if (_instance == nullptr) {
            _instance = new DefaultModuleManager();
        }
        return (_instance);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<Module>*/QString DefaultModuleManager::getNamedBeanClass()const {
        return "Module";
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
    /*public*/  void DefaultModuleManager::fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException*/ {
        PropertyChangeEvent* evt = new PropertyChangeEvent(this, p, old, QVariant());
        for (VetoableChangeListener* vc : VetoableChangeSupport::getVetoableChangeListeners()) {
            vc->vetoableChange(evt);
        }
    }

    /** {@inheritDoc} */
    //@Override
//    @OverridingMethodsMustInvokeSuper
    /*public*/  /*final*/ void DefaultModuleManager::deleteBean(/*@Nonnull*/ /*Module**/NamedBean* module, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/ {
        for (int i=0; i < ((Module*)module->self())->getChildCount(); i++) {
            FemaleSocket* child = ((Module*)module->self())->getChild(i);
            if (child->isConnected()) {
                MaleSocket* maleSocket = child->getConnectedSocket();
                maleSocket->getManager()->deleteBean(maleSocket, property);
            }
        }

        // throws PropertyVetoException if vetoed
        fireVetoableChange(property, VPtr<Module>::asQVariant(((Module*)module->self())));
        if (property == ("DoDelete")) { // NOI18N
            AbstractManager::deregister(module);
            module->NamedBean::dispose();
        }
    }


    /*private*/ /*final*/ /*static*/ /*org.slf4j.*/Logger* DefaultModuleManager::log = LoggerFactory::getLogger("DefaultModuleManager");
