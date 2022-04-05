#include "abstractbooleanactionswing.h"
#include "runtimeexception.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "instancemanager.h"

/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  abstract class AbstractBooleanActionSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractBooleanActionSwing::getExecuteEvaluateMenuText() {
        return tr("Execute");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractBooleanActionSwing::executeEvaluate(/*@Nonnull*/ Base* object) {
        throw new RuntimeException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractBooleanActionSwing::getManager() {
        return (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractBooleanActionSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractBooleanActionSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

//    /*protected*/ abstract void createPanel(@CheckForNull Base object, @Nonnull JPanel* buttonPanel);

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractBooleanActionSwing::getExampleSystemName() {
        return ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->getSystemNamePrefix() + "DB10";
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractBooleanActionSwing::getAutoSystemName() {
        return ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->AbstractManager::getAutoSystemName();
    }
