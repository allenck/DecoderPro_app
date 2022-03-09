#include "analogactionmemoryswing.h"
#include "analogactionmemory.h"
#include "beanselectpanel.h"
#include "defaultmemorymanager.h"
#include "instancemanager.h"
#include "jlabel.h"
#include "defaultanalogactionmanager.h"
#include "namedbeanhandlemanager.h"

/**
 * Configures an ActionMemory object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class AnalogActionMemorySwing extends AbstractAnalogActionSwing {



    //@Override
/*protected*/ void AnalogActionMemorySwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    AnalogActionMemory* action = (AnalogActionMemory*)object->bself();

    panel = new JPanel(new FlowLayout);
    memoryBeanPanel = new BeanSelectPanel((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);

    if (action != nullptr) {
        if (action->getMemory() != nullptr) {
            memoryBeanPanel->setDefaultNamedBean(action->getMemory()->getBean());
        }
    }

    panel->layout()->addWidget(new JLabel(tr("Memory")));
    panel->layout()->addWidget(memoryBeanPanel);
}

/** {@inheritDoc} */
//@Override
/*public*/  bool AnalogActionMemorySwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* AnalogActionMemorySwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
    AnalogActionMemory* action = new AnalogActionMemory(systemName, userName);
    Memory* memory = (Memory*)memoryBeanPanel->getNamedBean()->self();
    if (memory != nullptr) {
        NamedBeanHandle<Memory*>* handle
                = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                        ->getNamedBeanHandle(memory->getDisplayName(), memory);
        action->setMemory(handle);
    } else {
        action->removeMemory();
    }
    return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->registerAction(action);
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionMemorySwing::updateObject(/*@Nonnull*/ Base* object) {
    if (! (qobject_cast<AnalogActionMemory*>(object->bself()))) {
        throw new IllegalArgumentException(QString("object must be an ActionMemory but is a: ")+object->bself()->metaObject()->className());
    }
    AnalogActionMemory* action = (AnalogActionMemory*)object->bself();
    Memory* memory = (Memory*)memoryBeanPanel->getNamedBean()->self();
    if (memory != nullptr) {
        NamedBeanHandle<Memory*>* handle
                = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                        ->getNamedBeanHandle(memory->getDisplayName(), memory);
        action->setMemory(handle);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AnalogActionMemorySwing::toString() {
    return tr("Memory");
}

//@Override
/*public*/  void AnalogActionMemorySwing::dispose() {
    if (memoryBeanPanel != nullptr) {
        memoryBeanPanel->dispose();
    }
}
