#include "abstractanalogexpressionswing.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "defaultsymboltable.h"
#include "logixng_thread.h"
#include "joptionpane.h"
#include "analogexpression.h"
#include "jmriexception.h"
#include "instancemanager.h"
#include "defaultanalogexpressionmanager.h"
/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  /*abstract*/ class AbstractAnalogExpressionSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractAnalogExpressionSwing::getExecuteEvaluateMenuText() {
        return tr("Evaluate");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractAnalogExpressionSwing::executeEvaluate(/*@Nonnull*/ Base* object) {
        ConditionalNG* conditionalNG = object->getConditionalNG();
        if (conditionalNG == nullptr) throw new RuntimeException("Not supported yet");

        SymbolTable* symbolTable = new DefaultSymbolTable();
        getAllSymbols(object, symbolTable);

//        conditionalNG->getCurrentThread()->runOnLogixNGEventually(new  AbstractAnalogExpressionSwingTA1(object, conditionalNG, symbolTable, log));
    }

        void AbstractAnalogExpressionSwingTA1::run()
        {
            SymbolTable* oldSymbolTable = conditionalNG->getSymbolTable();

            try {
                conditionalNG->setSymbolTable(symbolTable);
                double result = ((AnalogExpression*)object->bself())->evaluate();
//                ThreadingUtil::runOnGUIEventually([]()  {
//                    JOptionPane::showMessageDialog(nullptr,
//                            tr("The result of the expression is: %1").arg(result),
//                            tr("The expression has been evaluated"),
//                            JOptionPane::PLAIN_MESSAGE);
//                });
                ThreadingUtil::runOnGUIEventually(new AbstractAnalogExpressionSwingRun1(result));
            } catch (JmriException* e) {
                log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
                        conditionalNG->NamedBean::getSystemName(), e->toString()), e);
            } catch ( RuntimeException* e) {
             log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
                     conditionalNG->NamedBean::getSystemName(), e->toString()), e);
            }

            conditionalNG->setSymbolTable(oldSymbolTable);
        }//);
    //}

    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractAnalogExpressionSwing::getManager() {
        return (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractAnalogExpressionSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException */{
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractAnalogExpressionSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

//    /*protected*/ /*abstract*/ void createPanel(@CheckForNull Base object, @Nonnull JPanel buttonPanel);

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractAnalogExpressionSwing::getExampleSystemName() {
        return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->getSystemNamePrefix() + "AE10";
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractAnalogExpressionSwing::getAutoSystemName() {
        return  ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->DefaultAnalogExpressionManager::getAutoSystemName();
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractAnalogExpressionSwing::log = LoggerFactory::getLogger("AbstractAnalogExpressionSwing");
