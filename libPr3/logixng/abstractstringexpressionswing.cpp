#include "abstractstringexpressionswing.h"
#include "instancemanager.h"
#include "runtimeexception.h"
#include "loggerfactory.h"
#include "stringexpressionmanager.h"
#include "defaultsymboltable.h"
#include "logixng_thread.h"

AbstractStringExpressionSwing::AbstractStringExpressionSwing(QObject *parent) : AbstractSwingConfigurator(parent)
{

}

/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  abstract class AbstractStringExpressionSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractStringExpressionSwing::getExecuteEvaluateMenuText() {
        return tr("Evaluate");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractStringExpressionSwing::executeEvaluate(/*@Nonnull*/ Base* object) {
        ConditionalNG* conditionalNG = object->getConditionalNG();
        if (conditionalNG == nullptr) throw new RuntimeException("Not supported yet");

        SymbolTable* symbolTable = new DefaultSymbolTable();
        getAllSymbols(object, symbolTable);
#if 0
        conditionalNG->getCurrentThread().runOnLogixNGEventually(() -> {
            SymbolTable oldSymbolTable = conditionalNG.getSymbolTable();

            try {
                conditionalNG.setSymbolTable(symbolTable);
                String result = ((StringExpression)object).evaluate();
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
#endif
        conditionalNG->getCurrentThread()->runOnLogixNGEventually(new ASES_run(object, conditionalNG, symbolTable,this));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractStringExpressionSwing::getManager() {
        return (StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractStringExpressionSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  JPanel* AbstractStringExpressionSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

    //protected abstract void createPanel(@CheckForNull Base object, @Nonnull JPanel buttonPanel);

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractStringExpressionSwing::getExampleSystemName() {
        return ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getSystemNamePrefix() + "SE10";
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractStringExpressionSwing::getAutoSystemName() {
        return ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getAutoSystemName();
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractStringExpressionSwing::log = LoggerFactory::getLogger("AbstractStringExpressionSwing");
