#include "stringexpressionmemory.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultstringexpressionmanager.h"
#include "typeconversionutil.h"
#include "namedbeanusagereport.h"
#include "conditionalng.h"
#include "vptr.h"
#include "defaultmemorymanager.h"

/**
 * Reads a Memory.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/   class StringExpressionMemory extends AbstractStringExpression
//        implements PropertyChangeListener, VetoableChangeListener {


/*public*/   StringExpressionMemory::StringExpressionMemory(QString sys, QString user, QObject *parent)
        /*throws BadUserNameException, BadSystemNameException*/
  : AbstractStringExpression(sys, user, parent)
{

    //super(sys, user);
}

//@Override
/*public*/   Base* StringExpressionMemory::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
    StringExpressionManager* manager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    StringExpressionMemory* copy = new StringExpressionMemory(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

//@Override
/*public*/   void StringExpressionMemory::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Memory>::asPtr(evt->getOldValue() )) {
            if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Memory is in use by Memory expression \"%1\"").arg(getDisplayName()), e); // NOI18N
            }
        }
    } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Memory>::asPtr(evt->getOldValue())) {
            if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                removeMemory();
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/   Category* StringExpressionMemory::getCategory() {
    return Category::ITEM;
}

/*public*/   void StringExpressionMemory::setMemory(/*@Nonnull*/QString memoryName) {
    assertListenersAreNotRegistered(log, "setMemory");
    Memory* memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName);
    if (memory != nullptr) {
        setMemory(memory);
    } else {
        removeMemory();
        log->error(tr("memory \"%1\" is not found").arg(memoryName));
    }
}

/*public*/   void StringExpressionMemory::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
 if(!handle) throw new NullPointerException("hanle is null!");
    assertListenersAreNotRegistered(log, "setMemory");
    _memoryHandle = handle;
    InstanceManager::memoryManagerInstance()->addVetoableChangeListener(this);
}

/*public*/   void StringExpressionMemory::setMemory(/*@Nonnull*/ Memory* memory) {
 if(!memory) throw new NullPointerException("hanle is null!");

    assertListenersAreNotRegistered(log, "setMemory");
    setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(memory->getDisplayName(), memory));
}

/*public*/   void StringExpressionMemory::removeMemory() {
    assertListenersAreNotRegistered(log, "setMemory");
    if (_memoryHandle != nullptr) {
        InstanceManager::memoryManagerInstance()->removeVetoableChangeListener(this);
        _memoryHandle = nullptr;
    }
}

/*public*/   NamedBeanHandle<Memory*>* StringExpressionMemory::getMemory() {
    return _memoryHandle;
}

/** {@inheritDoc} */
//@Override
/*public*/   QString StringExpressionMemory::evaluate() {
    if (_memoryHandle != nullptr) {
        return TypeConversionUtil::convertToString(_memoryHandle->getBean()->getValue(), false);
    } else {
        return "";
    }
}

//@Override
/*public*/   FemaleSocket* StringExpressionMemory::getChild(int index)
        /*throws IllegalArgumentException, UnsupportedOperationException */{
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/   int StringExpressionMemory::getChildCount() {
    return 0;
}

//@Override
/*public*/   QString StringExpressionMemory::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "StringExpressionMemory");
}

//@Override
/*public*/   QString StringExpressionMemory::getLongDescription(QLocale locale) {
    if (_memoryHandle != nullptr) {
        return tr(/*locale, */"Get memory %1 as string value").arg(_memoryHandle->getBean()->getDisplayName());
    } else {
        return tr(/*locale,*/ "Get memory %1 as string value").arg("none");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/   void StringExpressionMemory::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/   void StringExpressionMemory::registerListenersForThisClass() {
    if ((! _listenersAreRegistered) && (_memoryHandle != nullptr)) {
        _memoryHandle->getBean()->addPropertyChangeListener("value", this);
        _listenersAreRegistered = true;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/   void StringExpressionMemory::unregisterListenersForThisClass() {
    if (_listenersAreRegistered) {
        _memoryHandle->getBean()->removePropertyChangeListener("value", this);
        _listenersAreRegistered = false;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/   void StringExpressionMemory::propertyChange(PropertyChangeEvent* evt) {
    if (getTriggerOnChange()) {
        getConditionalNG()->execute();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/   void StringExpressionMemory::disposeMe() {
}
/** {@inheritDoc} */
//@Override
/*public*/   void StringExpressionMemory::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: StringExpressionMemory: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageBean->getDisplayName()));
    if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* StringExpressionMemory::log = LoggerFactory::getLogger("StringExpressionMemory");
