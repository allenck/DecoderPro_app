#include "abstractstringactionswing.h"
#include "instancemanager.h"
#include "runtimeexception.h"
#include "stringactionmanager.h"

/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  abstract class AbstractStringActionSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractStringActionSwing::getExecuteEvaluateMenuText() {
        return tr("Execute");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractStringActionSwing::executeEvaluate(/*@Nonnull*/ Base* object) {
        throw new RuntimeException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractStringActionSwing::getManager() {
        return (StringActionManager*)InstanceManager::getDefault("StringActionManager");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractStringActionSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException */{
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractStringActionSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

//    protected abstract void createPanel(@CheckForNull Base object, /*@Nonnull*/ JPanel* buttonPanel);

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractStringActionSwing::getExampleSystemName() {
        return ((StringActionManager*)InstanceManager::getDefault("StringActionManager"))->getSystemNamePrefix() + "SA10";
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractStringActionSwing::getAutoSystemName() {
        return ((StringActionManager*)InstanceManager::getDefault("StringActionManager"))->getAutoSystemName();
    }
