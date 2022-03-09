#include "abstractanalogactionswing.h"
#include "instancemanager.h"
#include "defaultanalogactionmanager.h"

/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  abstract class AbstractAnalogActionSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractAnalogActionSwing::getExecuteEvaluateMenuText() {
        return tr("Execute");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractAnalogActionSwing::executeEvaluate(/*@Nonnull*/ Base* object) {
        throw new RuntimeException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractAnalogActionSwing::getManager() {
        return (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractAnalogActionSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractAnalogActionSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

//    /*protected*/ abstract void createPanel(@CheckForNull Base object, /*@Nonnull*/ JPanel* buttonPanel);

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractAnalogActionSwing::getExampleSystemName() {
        return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->getSystemNamePrefix() + "AA10";
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractAnalogActionSwing::getAutoSystemName() {
        return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->AbstractManager::getAutoSystemName();
    }
