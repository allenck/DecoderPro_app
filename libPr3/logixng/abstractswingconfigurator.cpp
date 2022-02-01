#include "abstractswingconfigurator.h"
#include "joptionpane.h"
#include "runtimeexception.h"
#include "abstractmalesocket.h"

/**
 * Abstract class for SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  abstract class AbstractSwingConfigurator implements SwingConfiguratorInterface {

    /*private*/ void AbstractSwingConfigurator::getSymbols(/*@Nonnull*/ Base* object, SymbolTable* symbolTable) /*throws JmriException*/ {
        if (object->getParent() != nullptr) getSymbols(object->getParent(), symbolTable);

        if (qobject_cast<AbstractMaleSocket*>(object->self())) {
            symbolTable->createSymbols(symbolTable, ((AbstractMaleSocket*)object->self())->getLocalVariables());
        }
    }

    /*public*/  void AbstractSwingConfigurator::getAllSymbols(/*@Nonnull*/ Base* object, SymbolTable* symbolTable) {
        try {
            getSymbols(object->getParent(), symbolTable);
        } catch (JmriException* e) {
            JOptionPane::showMessageDialog(nullptr,
                    e->getLocalizedMessage(),
                    "Error",
                    JOptionPane::ERROR_MESSAGE);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractSwingConfigurator::getExecuteEvaluateMenuText() {
        throw new RuntimeException(QString("Not supported. Class: ") + this->metaObject()->className());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractSwingConfigurator::executeEvaluate(/*@Nonnull*/ Base* object) {
        throw new RuntimeException("Not supported");
    }
