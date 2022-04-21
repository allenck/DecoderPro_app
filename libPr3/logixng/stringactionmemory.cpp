#include "stringactionmemory.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultstringactionmanager.h"
#include "defaultmemorymanager.h"
#include "namedbeanhandlemanager.h"
#include "vptr.h"

/**
 * Sets a Memory.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class StringActionMemory extends AbstractStringAction
//        implements VetoableChangeListener {


    /*public*/  StringActionMemory::StringActionMemory(QString sys, QString user, QObject *parent) : AbstractStringAction(sys, user, parent) {
        //super(sys, user);
     setObjectName("StringActionMemory");
    }

    //@Override
    /*public*/  Base* StringActionMemory::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
        StringActionManager* manager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        StringActionMemory* copy = new StringActionMemory(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
        return manager->registerAction(copy);
    }

    /*public*/  void StringActionMemory::setMemory(/*@Nonnull*/ QString memoryName) {
        assertListenersAreNotRegistered(log, "setMemory");
        Memory* memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName);
        if (memory != nullptr) {
            setMemory(memory);
        } else {
            removeMemory();
            log->error(tr("memory \"%1\" is not found").arg(memoryName));
        }
    }

    /*public*/  void StringActionMemory::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
        assertListenersAreNotRegistered(log, "setMemory");
        _memoryHandle = handle;
        InstanceManager::memoryManagerInstance()->addVetoableChangeListener(this);
    }

    /*public*/  void StringActionMemory::setMemory(/*@Nonnull*/ Memory* memory) {
        assertListenersAreNotRegistered(log, "setMemory");
        setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(memory->getDisplayName(), memory));
    }

    /*public*/  void StringActionMemory::removeMemory() {
        assertListenersAreNotRegistered(log, "setMemory");
        if (_memoryHandle != nullptr) {
            InstanceManager::memoryManagerInstance()->removeVetoableChangeListener(this);
            _memoryHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Memory*>* StringActionMemory::getMemory() {
        return _memoryHandle;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemory::setValue(QString value) {
        if (_memoryHandle != nullptr) {
            _memoryHandle->getBean()->setValue(value);
        }
    }

    //@Override
    /*public*/  void StringActionMemory::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        if ("CanDelete"==(evt->getPropertyName())) { // No I18N
            if (VPtr<Memory>::asPtr(evt->getOldValue())) {
                if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Memory is in use by Memory action \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Memory>::asPtr(evt->getOldValue()) ) {
                if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                    removeMemory();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleSocket* StringActionMemory::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int StringActionMemory::getChildCount() {
        return 0;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* StringActionMemory::getCategory() {
        return Category::ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString StringActionMemory::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "StringActionMemory");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString StringActionMemory::getLongDescription(QLocale locale) {
        if (_memoryHandle != nullptr) {
            return tr(/*locale,*/ "Set memory %1").arg(_memoryHandle->getBean()->getDisplayName());
        } else {
            return tr(/*locale,*/ "Set memory %1").arg("none");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemory::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemory::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemory::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemory::disposeMe() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemory::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: StringActionMemory: bean = %1, report = %2").arg(cdl->getSystemName()).arg(report->size()));
        if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* StringActionMemory::log = LoggerFactory::getLogger("StringActionMemory");
