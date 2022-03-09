#include "analogexpressionanalogioswing.h"
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"
#include "analogexpressionanalogio.h"
#include "defaultanalogexpressionmanager.h"
#include "beanselectpanel.h"
#include "proxyanalogiomanager.h"
#include "jlabel.h"

/**
 * Configures an AnalogExpressionAnalogIO object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class AnalogExpressionAnalogIOSwing extends AbstractAnalogExpressionSwing {



    //@Override
    /*protected*/ void AnalogExpressionAnalogIOSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        AnalogExpressionAnalogIO* action = nullptr;
        if(object)
         action= (AnalogExpressionAnalogIO*)object->bself();

        panel = new JPanel(new FlowLayout());
        analogIOBeanPanel = new BeanSelectPanel((Manager*)InstanceManager::getDefault("AnalogIOManager"), nullptr);

        if (action != nullptr) {
            if (action->getAnalogIO() != nullptr) {
                analogIOBeanPanel->setDefaultNamedBean(action->getAnalogIO()->getBean());
            }
        }

        panel->layout()->addWidget(new JLabel(tr("AnalogIO")));
        panel->layout()->addWidget(analogIOBeanPanel);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool AnalogExpressionAnalogIOSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* AnalogExpressionAnalogIOSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        AnalogExpressionAnalogIO* action = new AnalogExpressionAnalogIO(systemName, userName);
        if (!analogIOBeanPanel->isEmpty()) {
            AnalogIO* analogIO = (AnalogIO*)analogIOBeanPanel->getNamedBean()->self();
            if (analogIO != nullptr) {
                NamedBeanHandle<AnalogIO*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(analogIO->getDisplayName(), analogIO);
                action->setAnalogIO(handle);
            }
        }
        return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIOSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<AnalogExpressionAnalogIO*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an AnalogExpressionAnalogIO but is a: ")+object->bself()->metaObject()->className());
        }
        AnalogExpressionAnalogIO* action = (AnalogExpressionAnalogIO*)object->bself();
        AnalogIO* analogIO = (AnalogIO*)analogIOBeanPanel->getNamedBean()->self();
        if (analogIO != nullptr) {
            NamedBeanHandle<AnalogIO*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                            ->getNamedBeanHandle(analogIO->getDisplayName(), analogIO);
            action->setAnalogIO(handle);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AnalogExpressionAnalogIOSwing::toString() {
        return tr("AnalogIO");
    }

    //@Override
    /*public*/  void AnalogExpressionAnalogIOSwing::dispose() {
        if (analogIOBeanPanel != nullptr) {
            analogIOBeanPanel->dispose();
        }
    }
