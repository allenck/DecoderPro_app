#include "stringactionmemoryswing.h"
#include "instancemanager.h"
#include "stringactionmemory.h"
#include "beanselectpanel.h"
#include "jlabel.h"
#include "namedbeanhandlemanager.h"
#include "abstractmemory.h"
#include "defaultstringactionmanager.h"

StringActionMemorySwing::StringActionMemorySwing(QObject *parent) : AbstractStringActionSwing(parent)
{
 setObjectName("StringActionMemorySwing");
}

/**
 * Configures an ActionMemory object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class StringActionMemorySwing extends AbstractStringActionSwing {



    //@Override
    /*protected*/ void StringActionMemorySwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        StringActionMemory* action = (StringActionMemory*)object->bself();

        panel = new JPanel();
        memoryBeanPanel = new BeanSelectPanel((AbstractManager*)(DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);

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
    /*public*/  bool StringActionMemorySwing:: validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* StringActionMemorySwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        StringActionMemory* action = new StringActionMemory(systemName, userName);
        if (!memoryBeanPanel->isEmpty()) {
            Memory* memory = (AbstractMemory*)memoryBeanPanel->getNamedBean()->self();
            if (memory != nullptr) {
                NamedBeanHandle<Memory*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(memory->getDisplayName(), memory);
                action->setMemory(handle);
            }
        }
        return ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringActionMemorySwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<StringActionMemory*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionMemory but is a: ")+object->bself()->metaObject()->className());
        }
        StringActionMemory* action = (StringActionMemory*)object->bself();
        Memory* memory = (AbstractMemory*)memoryBeanPanel->getNamedBean()->self();
        if (memory != nullptr) {
            NamedBeanHandle<Memory*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                            ->getNamedBeanHandle(memory->getDisplayName(), memory);
            action->setMemory(handle);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString StringActionMemorySwing::toString() {
        return tr("StringActionMemory");
    }

    //@Override
    /*public*/  void StringActionMemorySwing::dispose() {
        if (memoryBeanPanel != nullptr) {
            memoryBeanPanel->dispose();
        }
    }

