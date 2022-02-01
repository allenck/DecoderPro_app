#include "abstractdigitalactionswing.h"
#include "loggerfactory.h"
#include "defaultsymboltable.h"
#include "logixng_thread.h"
#include "digitalaction.h"
#include "threadingutil.h"
#include "joptionpane.h"
#include "instancemanager.h"
#include "digitalactionmanager.h"
#include "runtimeexception.h"

/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2021
 */
 // /*public*/ abstract class AbstractDigitalActionSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
     //QOverride
     /*public*/ QString AbstractDigitalActionSwing::getExecuteEvaluateMenuText() {
        return tr("Evaluate");
    }

    /** {@inheritDoc} */
     //QOverride
     /*public*/ void AbstractDigitalActionSwing::executeEvaluate(/*@Nonnull*/ Base* object) {
        ConditionalNG* conditionalNG = object->getConditionalNG();
        if (conditionalNG == nullptr) throw new RuntimeException("Not supported yet");

        SymbolTable* symbolTable = new DefaultSymbolTable();
        getAllSymbols(object, symbolTable);
#if 0 // TODO:
        conditionalNG->getCurrentThread()->runOnLogixNGEventually([=]()  {
            SymbolTable* oldSymbolTable = conditionalNG->getSymbolTable();

            try {
                conditionalNG->setSymbolTable(symbolTable);
                ((DigitalAction*)object)->execute();
//                ThreadingUtil::runOnGUIEventually([=]()  {
//                    JOptionPane::showMessageDialog(nullptr,
//                            tr("The action has completed"),
//                            tr("The action has been executed"),
//                            JOptionPane::PLAIN_MESSAGE);
//                });
                ThreadingUtil::runOnGUIEventually(new ThreadAction3);
            } catch (JmriException* e) {
    //                LoggingUtil.warnOnce(log, "ConditionalNG {} got an exception during execute: {}",
    //                        conditionalNG.getSystemName(), e, e);
                log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
                        conditionalNG->NamedBean::getSystemName(), e->getMessage()), e);
            }
         catch (RuntimeException* e) {
//                LoggingUtil.warnOnce(log, "ConditionalNG {} got an exception during execute: {}",
//                        conditionalNG.getSystemName(), e, e);
             log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
                     conditionalNG->NamedBean::getSystemName(), e->getMessage()), e);
        }
            conditionalNG->setSymbolTable(oldSymbolTable);
        });
#endif
    }

    /** {@inheritDoc} */
     //QOverride
     /*public*/ BaseManager/*<? extends NamedBean>*/* AbstractDigitalActionSwing::getManager() {
        return (DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    }

    /** {@inheritDoc} */
     //QOverride
     /*public*/ JPanel* AbstractDigitalActionSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
     //QOverride
     /*public*/ JPanel* AbstractDigitalActionSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

    ///*protected*/ abstract void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);

    /** {@inheritDoc} */
     //QOverride
     /*public*/ QString AbstractDigitalActionSwing::getExampleSystemName() {
        return ((DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getSystemNamePrefix() + "DA10";
    }

    /** {@inheritDoc} */
     //QOverride
     /*public*/ QString AbstractDigitalActionSwing::getAutoSystemName() {
        return ((DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getAutoSystemName();
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractDigitalActionSwing::log = LoggerFactory::getLogger("AbstractDigitalActionSwing");
