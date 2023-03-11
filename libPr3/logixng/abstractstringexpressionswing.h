#ifndef ABSTRACTSTRINGEXPRESSIONSWING_H
#define ABSTRACTSTRINGEXPRESSIONSWING_H

#include "abstractswingconfigurator.h"
#include "threadingutil.h"
#include "conditionalng.h"
#include "symboltable.h"
#include "stringexpression.h"
#include "joptionpane.h"
#include "jmriexception.h"
#include "abstractnamedbean.h"


class AbstractStringExpressionSwing : public AbstractSwingConfigurator
{
  Q_OBJECT
 public:
  explicit AbstractStringExpressionSwing(QObject *parent = nullptr);
  /*public*/  QString getExecuteEvaluateMenuText() override;
  /*public*/  void executeEvaluate(/*@Nonnull*/ Base* object)override;
  /*public*/  BaseManager/*<? extends NamedBean>*/* getManager()override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/override;
  /*public*/  QString getExampleSystemName()override;
  /*public*/  QString getAutoSystemName()override;

 private:
  /*private*/ static Logger* log;

  protected:
  /*protected*/ JPanel* panel;
  /*protected*/ /*abstract*/ virtual void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)=0;

  friend class ASES_run;
};

class ASES_JOption : public ThreadAction
{
  Q_OBJECT
  QString result;
 public:
  ASES_JOption(QString result) { this->result = result;}
  void run()
  {
   JOptionPane::showMessageDialog(nullptr,
           tr("The result of the expression is: %1").arg(result),
           tr("The expression has been evaluated"),
           JOptionPane::PLAIN_MESSAGE);
  }
};

class ASES_run : public ThreadAction
{
  Q_OBJECT
  ConditionalNG* conditionalNG;
  SymbolTable* symbolTable;
  AbstractStringExpressionSwing* ases;
  Base* object;
 public:
  ASES_run(Base* object, ConditionalNG* conditionalNG, SymbolTable* symbolTable, AbstractStringExpressionSwing* ases) {
   this-> object = object;
   this->conditionalNG = conditionalNG;
   this->symbolTable = symbolTable;
   this->ases = ases;
  }

  void run()
  {
   SymbolTable* oldSymbolTable = conditionalNG->getSymbolTable();

  try {
      conditionalNG->setSymbolTable(symbolTable);
      QString result = ((StringExpression*)object->bself())->evaluate();
//      ThreadingUtil.runOnGUIEventually(() -> {
//          JOptionPane::showMessageDialog(null,
//                  Bundle.getMessage("ExecuteEvaluate_EvaluationCompleted", result),
//                  Bundle.getMessage("ExecuteEvaluate_Title"),
//                  JOptionPane.PLAIN_MESSAGE);
//      });
      ThreadingUtil::runOnGUIEventually(new ASES_JOption(result));
  }
   catch (JmriException* /*| RuntimeException*/ e) {
      ases->log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
              conditionalNG->NamedBean::getSystemName(), e->getMessage()), e);
  }

  conditionalNG->setSymbolTable(oldSymbolTable);
  }

};

#endif // ABSTRACTSTRINGEXPRESSIONSWING_H
