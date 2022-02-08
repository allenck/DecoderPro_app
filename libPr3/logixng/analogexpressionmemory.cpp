#include "analogexpressionmemory.h"
#include "loggerfactory.h"
#include "analogexpressionmanager.h"
#include "instancemanager.h"
#include "vptr.h"
#include "memorymanager.h"
#include "typeconversionutil.h"
#include "conditionalng.h"

/**
 * Reads a Memory.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class AnalogExpressionMemory extends AbstractAnalogExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  AnalogExpressionMemory::AnalogExpressionMemory(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException */: AbstractAnalogExpression(sys, user, parent){

        //super(sys, user);
    }

    //@Override
    /*public*/  Base* AnalogExpressionMemory::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException */{
        AnalogExpressionManager* manager = (AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString sysName = systemNames.value(AbstractNamedBean::getSystemName());
        QString userName = userNames.value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        AnalogExpressionMemory* copy = new AnalogExpressionMemory(sysName, userName);
        copy->AbstractBase::setComment(AbstractBase::getComment());
        if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionMemory::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        if ("CanDelete" ==(evt->getPropertyName())) { // No I18N
            if (VPtr<Memory>::asPtr(evt->getOldValue() )) {
                if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Memory is in use by Memory expression \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
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
    /*public*/  Category* AnalogExpressionMemory::getCategory() {
        return Category::ITEM;
    }

    /*public*/  void AnalogExpressionMemory::setMemory(/*@Nonnull*/ QString memoryName) {
        assertListenersAreNotRegistered(log, "setMemory");
        Memory* memory = ((MemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName);
        if (memory != nullptr) {
            setMemory(memory);
        } else {
            removeMemory();
            log->error(tr("memory \"%1\" is not found").arg(memoryName));
        }
    }

    /*public*/  void AnalogExpressionMemory::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
        assertListenersAreNotRegistered(log, "setMemory");
        _memoryHandle = handle;
        InstanceManager::memoryManagerInstance()->addVetoableChangeListener(this);
    }

    /*public*/  void AnalogExpressionMemory::setMemory(/*@Nonnull*/ Memory* memory) {
        assertListenersAreNotRegistered(log, "setMemory");
        setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(memory->getDisplayName(), memory));
    }

    /*public*/  void AnalogExpressionMemory::removeMemory() {
        assertListenersAreNotRegistered(log, "setMemory");
        if (_memoryHandle != nullptr) {
            InstanceManager::memoryManagerInstance()->removeVetoableChangeListener(this);
            _memoryHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Memory*>* AnalogExpressionMemory::getMemory() {
        return _memoryHandle;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  double AnalogExpressionMemory::evaluate() {
        if (_memoryHandle != nullptr) {
            return TypeConversionUtil::convertToDouble(_memoryHandle->getBean()->getValue(), false);
        } else {
            return 0.0;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleSocket* AnalogExpressionMemory::getChild(int index)
            /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int AnalogExpressionMemory::getChildCount() {
        return 0;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AnalogExpressionMemory::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Memory as analog value");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AnalogExpressionMemory::getLongDescription(QLocale locale) {
        if (_memoryHandle != nullptr) {
            return tr(/*locale,*/ "Get memory %1 as analog value").arg(_memoryHandle->getBean()->getDisplayName());
        } else {
            return tr(/*locale,*/ "Get memory %1 as analog value").arg("none");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionMemory::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionMemory::registerListenersForThisClass() {
        if ((! _listenersAreRegistered) && (_memoryHandle != nullptr)) {
            _memoryHandle->getBean()->addPropertyChangeListener("value", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionMemory::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _memoryHandle->getBean()->removePropertyChangeListener("value", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionMemory::propertyChange(PropertyChangeEvent* evt) {
        if (getTriggerOnChange()) {
            AbstractBase::getConditionalNG()->execute();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void disposeMe() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionMemory::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: AnalogExpressionMemory: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report.size()));
        if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
            report.append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription()));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* AnalogExpressionMemory::log = LoggerFactory::getLogger("AnalogExpressionMemory");
