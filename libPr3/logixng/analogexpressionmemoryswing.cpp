#include "analogexpressionmemoryswing.h"
#include "analogexpressionmemory.h"
#include "instancemanager.h"
#include "memorymanager.h"
#include "jlabel.h"
#include "namedbeanhandlemanager.h"
#include "defaultanalogexpressionmanager.h"

/**
 * Configures an AnalogExpressionMemory object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class AnalogExpressionMemorySwing extends AbstractAnalogExpressionSwing {



    //@Override
    /*protected*/ void AnalogExpressionMemorySwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        AnalogExpressionMemory* action = nullptr;
        if(object)
         action = (AnalogExpressionMemory*)object->bself();

        panel = new JPanel(new FlowLayout());
        memoryBeanPanel = new BeanSelectPanel((MemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);

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
    /*public*/  bool AnalogExpressionMemorySwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* AnalogExpressionMemorySwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        AnalogExpressionMemory* action = new AnalogExpressionMemory(systemName, userName);
        if (!memoryBeanPanel->isEmpty()) {
            Memory* memory = (Memory*)memoryBeanPanel->getNamedBean()->self();
            if (memory != nullptr) {
                NamedBeanHandle<Memory*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(memory->getDisplayName(), memory);
                action->setMemory(handle);
            }
        }
        return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionMemorySwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<AnalogExpressionMemory*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an AnalogExpressionMemory but is a: ")+object->bself()->metaObject()->className());
        }
        AnalogExpressionMemory* action = (AnalogExpressionMemory*)object->bself();
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
    /*public*/  QString AnalogExpressionMemorySwing::toString() {
        return tr("Memory as analog value");
    }

    //@Override
    /*public*/  void AnalogExpressionMemorySwing::dispose() {
        if (memoryBeanPanel != nullptr) {
            memoryBeanPanel->dispose();
        }
    }


//    /*private*/ /*final*/ static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(AnalogExpressionMemorySwing.class);
