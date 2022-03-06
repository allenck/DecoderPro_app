#include "stringactionmemory.h"
#include "instancemanager.h"
#include "loggerfactory.h"

/**
 * Sets a Memory.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class StringActionMemory extends AbstractStringAction
//        implements VetoableChangeListener {


    /*public*/  StringActionMemory::StringActionMemory(QString sys, QString user, QObject *parent) : AbstractStringAction(sys, user, parent) {
        //super(sys, user);
    }
#if 0
    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) {
        StringActionManager manager = InstanceManager.getDefault(StringActionManager.class);
        String sysName = systemNames.get(getSystemName());
        String userName = userNames.get(getSystemName());
        if (sysName == null) sysName = manager.getAutoSystemName();
        StringActionMemory copy = new StringActionMemory(sysName, userName);
        copy.setComment(getComment());
        if (_memoryHandle != null) copy.setMemory(_memoryHandle);
        return manager.registerAction(copy);
    }

    /*public*/  void setMemory(/*@Nonnull*/ String memoryName) {
        assertListenersAreNotRegistered(log, "setMemory");
        Memory* memory = InstanceManager.getDefault(MemoryManager.class).getMemory(memoryName);
        if (memory != null) {
            setMemory(memory);
        } else {
            removeMemory();
            log.error("memory \"{}\" is not found", memoryName);
        }
    }

    /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory> handle) {
        assertListenersAreNotRegistered(log, "setMemory");
        _memoryHandle = handle;
        InstanceManager.memoryManagerInstance().addVetoableChangeListener(this);
    }

    /*public*/  void setMemory(/*@Nonnull*/ Memory memory) {
        assertListenersAreNotRegistered(log, "setMemory");
        setMemory(InstanceManager.getDefault(NamedBeanHandleManager.class)
                .getNamedBeanHandle(memory.getDisplayName(), memory));
    }

    /*public*/  void removeMemory() {
        assertListenersAreNotRegistered(log, "setMemory");
        if (_memoryHandle != null) {
            InstanceManager.memoryManagerInstance().removeVetoableChangeListener(this);
            _memoryHandle = null;
        }
    }

    /*public*/  NamedBeanHandle<Memory> getMemory() {
        return _memoryHandle;
    }
#endif
    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemory::setValue(QString value) {
        if (_memoryHandle != nullptr) {
            _memoryHandle->getBean()->setValue(value);
        }
    }
#if 0
    //@Override
    /*public*/  void vetoableChange(PropertyChangeEvent evt) throws PropertyVetoException {
        if ("CanDelete".equals(evt.getPropertyName())) { // No I18N
            if (evt.getOldValue() instanceof Memory) {
                if (evt.getOldValue().equals(getMemory().getBean())) {
                    PropertyChangeEvent e = new PropertyChangeEvent(this, "DoNotDelete", null, null);
                    throw new PropertyVetoException(Bundle.getMessage("StringMemory_MemoryInUseMemoryActionVeto", getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete".equals(evt.getPropertyName())) { // No I18N
            if (evt.getOldValue() instanceof Memory) {
                if (evt.getOldValue().equals(getMemory().getBean())) {
                    removeMemory();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleSocket getChild(int index) throws IllegalArgumentException, UnsupportedOperationException {
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int getChildCount() {
        return 0;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category getCategory() {
        return Category.ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  String getShortDescription(Locale locale) {
        return Bundle.getMessage(locale, "StringActionMemory_Short");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  String getLongDescription(Locale locale) {
        if (_memoryHandle != null) {
            return Bundle.getMessage(locale, "StringActionMemory_Long", _memoryHandle.getBean().getDisplayName());
        } else {
            return Bundle.getMessage(locale, "StringActionMemory_Long", "none");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void disposeMe() {
    }

    /** {@inheritDoc} */
    //@Override
    /*/*public*/ */  void getUsageDetail(int level, NamedBean bean, List<NamedBeanUsageReport> report, NamedBean cdl) {
        log.debug("getUsageReport :: StringActionMemory: bean = {}, report = {}", cdl, report);
        if (getMemory() != null && bean.equals(getMemory().getBean())) {
            report.add(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription()));
        }
    }
#endif
    /*private*/ /*final*/ /*static*/ Logger* StringActionMemory::log = LoggerFactory::getLogger("StringActionMemory");
