#include "analogactionmemory.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultanalogactionmanager.h"
#include "abstractmemorymanager.h"
#include "threadingutil.h"
#include "vptr.h"

/**
 * Sets a Memory.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class AnalogActionMemory extends AbstractAnalogAction
//        implements VetoableChangeListener {


/*public*/  AnalogActionMemory::AnalogActionMemory(QString sys, QString user, QObject *parent)
 : AbstractAnalogAction(sys, user, parent) {
    //super(sys, user);
 setObjectName("AnalogActionMemory");
}

//@Override
/*public*/  Base* AnalogActionMemory::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
    AnalogActionManager* manager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    AnalogActionMemory* copy = new AnalogActionMemory(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
    return manager->registerAction(copy);
}

/*public*/  void AnalogActionMemory::setMemory(/*@Nonnull*/ QString memoryName) {
 if(memoryName.isEmpty())
  throw new NullPointerException("required memory name is null");

    assertListenersAreNotRegistered(log, "setMemory");
    Memory* memory = ((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName);
    if (memory != nullptr) {
        setMemory(memory);
    } else {
        removeMemory();
        log->error(tr("memory \"%1\" is not found").arg(memoryName));
    }
}

/*public*/  void AnalogActionMemory::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
 if(!handle)
  throw new NullPointerException("required handle is null");
    assertListenersAreNotRegistered(log, "setMemory");
    _memoryHandle = handle;
    InstanceManager::memoryManagerInstance()->addVetoableChangeListener(this);
}

/*public*/  void AnalogActionMemory::setMemory(/*@Nonnull*/ Memory* memory) {
 if(!memory)
  throw new NullPointerException("required memory is null");
    assertListenersAreNotRegistered(log, "setMemory");
    setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(memory->getDisplayName(), memory));
}

/*public*/  void AnalogActionMemory::removeMemory() {
    assertListenersAreNotRegistered(log, "setMemory");
    if (_memoryHandle != nullptr) {
        InstanceManager::memoryManagerInstance()->removeVetoableChangeListener(this);
        _memoryHandle = nullptr;
    }
}

/*public*/  NamedBeanHandle<Memory*>* AnalogActionMemory::getMemory() {
    return _memoryHandle;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionMemory::setValue(double value) /*throws JmriException*/ {
    if (_memoryHandle != nullptr) {
#if 0
        ThreadingUtil::runOnLayoutWithJmriException(() -> {
            _memoryHandle.getBean().setValue(value);
        });
#else
     ThreadingUtil::runOnLayoutWithJmriException(new AAMRun(_memoryHandle,value));
#endif
    }
}

void AAMRun::run()
{
 _memoryHandle->getBean()->setValue(value);
}

//@Override
/*public*/  void AnalogActionMemory::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Memory>::asPtr(evt->getOldValue())) {
            if (VPtr<Memory>::asPtr( evt->getOldValue()) == (getMemory()->getBean())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Memory is in use by Memory action \"%1\"").arg(getDisplayName()), e); // NOI18N
            }
        }
    } else if ("DoDelete" == ( evt->getPropertyName())) { // No I18N
        if ( VPtr<Memory>::asPtr(evt->getOldValue())) {
            if ( VPtr<Memory>::asPtr(evt->getOldValue()) == (getMemory()->getBean())) {
                removeMemory();
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  FemaleSocket* AnalogActionMemory::getChild(int index)
        /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    throw new UnsupportedOperationException("Not supported.");
}

/** {@inheritDoc} */
//@Override
/*public*/  int AnalogActionMemory::getChildCount() {
    return 0;
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* AnalogActionMemory::getCategory() {
    return Category::ITEM;
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AnalogActionMemory::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "AnalogActionMemory");
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AnalogActionMemory::getLongDescription(QLocale locale) {
    if (_memoryHandle != nullptr) {
        return tr(/*locale, */"Set memory %1").arg(_memoryHandle->getBean()->getDisplayName());
    } else {
        return tr(/*locale,*/ "Set memory %1").arg("none");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionMemory::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionMemory::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionMemory::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionMemory::disposeMe() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionMemory::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
//    log->debug(tr("getUsageReport :: AnalogActionMemory: bean = %1, report = %2").arg(cdl, report.));
    if (getMemory() != nullptr && bean == (getMemory()->getBean())) {
        report.append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* AnalogActionMemory::log = LoggerFactory::getLogger("AnalogActionMemory");

