#include "abstractdigitalexpressionswing.h"
#include "loggerfactory.h"
#include"instancemanager.h"
#include "runtimeexception.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultsymboltable.h"
#include "logixng_thread.h"

/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  abstract class AbstractDigitalExpressionSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractDigitalExpressionSwing::getExecuteEvaluateMenuText() {
        return tr("Execute");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractDigitalExpressionSwing::executeEvaluate(/*@Nonnull*/ Base* object) {
        ConditionalNG* conditionalNG = object->getConditionalNG();
        if (conditionalNG == nullptr) throw new RuntimeException("Not supported yet");

        SymbolTable* symbolTable = new DefaultSymbolTable();
        getAllSymbols(object, symbolTable);
#if 0 // TODO:
        conditionalNG->getCurrentThread().runOnLogixNGEventually(() -> {
            SymbolTable oldSymbolTable = conditionalNG.getSymbolTable();

            try {
                conditionalNG.setSymbolTable(symbolTable);
                boolean result = ((DigitalExpression)object).evaluate();
                jmri.util.ThreadingUtil.runOnGUIEventually(() -> {
                    JOptionPane.showMessageDialog(null,
                            Bundle.getMessage("ExecuteEvaluate_EvaluationCompleted", result),
                            Bundle.getMessage("ExecuteEvaluate_Title"),
                            JOptionPane.PLAIN_MESSAGE);
                });
            } catch (JmriException | RuntimeException e) {
                log.warn("ConditionalNG {} got an exception during execute: {}",
                        conditionalNG.getSystemName(), e, e);
            }

            conditionalNG.setSymbolTable(oldSymbolTable);
        });
#else
        conditionalNG->getCurrentThread()->runOnLogixNGEventually(new AbstractDigitalExpressionSwing_run1(object, symbolTable, conditionalNG,this));
#endif
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractDigitalExpressionSwing::getManager() {
        return (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractDigitalExpressionSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException */{
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractDigitalExpressionSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractDigitalExpressionSwing::getExampleSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getSystemNamePrefix() + "DE10";
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractDigitalExpressionSwing::getAutoSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->AbstractManager::getAutoSystemName();
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractDigitalExpressionSwing::log =LoggerFactory::getLogger("AbstractDigitalExpressionSwing");
