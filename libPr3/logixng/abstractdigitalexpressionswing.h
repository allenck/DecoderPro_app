#ifndef ABSTRACTDIGITALEXPRESSIONSWING_H
#define ABSTRACTDIGITALEXPRESSIONSWING_H

#include "abstractswingconfigurator.h"
#include "threadingutil.h"
#include "joptionpane.h"
#include "defaultconditionalng.h"
#include "symboltable.h"
#include "digitalexpression.h"

class AbstractDigitalExpressionSwing : public AbstractSwingConfigurator
{
  Q_OBJECT
 public:
  explicit AbstractDigitalExpressionSwing(QObject *parent = nullptr) : AbstractSwingConfigurator(parent) {}
  /*public*/  QString getExecuteEvaluateMenuText()override;
  /*public*/  void executeEvaluate(/*@Nonnull*/ Base* object)override;
  /*public*/  BaseManager/*<? extends NamedBean>*/* getManager()override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ override;
  /*public*/  QString getExampleSystemName()override;
  /*public*/  QString getAutoSystemName()override;

 private:
  static Logger* log;

 protected:
  /*protected*/ /*abstract*/virtual void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)=0;
  /*protected*/ JPanel* panel;
  friend class AbstractDigitalExpressionSwing_run1;
};
class AbstractDigitalExpressionSwing_run2 : public ThreadAction
{
  Q_OBJECT
  bool result;
 public:
  AbstractDigitalExpressionSwing_run2(bool result) {this->result = result;}
  void run()
  {
   JOptionPane::showMessageDialog(nullptr,
    tr("The result of the expression is: %1").arg(result?"true":"false"),
    tr("The expression has been evaluated"),
    JOptionPane::PLAIN_MESSAGE);
  }

};

class AbstractDigitalExpressionSwing_run1 : public ThreadAction
{
  Q_OBJECT
 public:
  Base* object;
  AbstractDigitalExpressionSwing* ades;
  ConditionalNG* conditionalNG;
  SymbolTable* symbolTable;
  AbstractDigitalExpressionSwing_run1(Base* object, SymbolTable* symbolTable, ConditionalNG* conditionalNG, AbstractDigitalExpressionSwing* ades)
  {
   this->object = object;
   this->symbolTable = symbolTable;
   this->conditionalNG = conditionalNG;
   this->ades = ades;
  }
  void run()
  {
   SymbolTable* oldSymbolTable = conditionalNG->getSymbolTable();

   try {
       conditionalNG->setSymbolTable(symbolTable);
       bool result = ((DigitalExpression*)object->bself())->evaluate();
//       jmri.util.ThreadingUtil.runOnGUIEventually(() -> {
//           JOptionPane.showMessageDialog(null,
//                   Bundle.getMessage("ExecuteEvaluate_EvaluationCompleted", result),
//                   Bundle.getMessage("ExecuteEvaluate_Title"),
//                   JOptionPane.PLAIN_MESSAGE);
//       });
       ThreadingUtil::runOnGUIEventually(new AbstractDigitalExpressionSwing_run2(result));
   } catch (JmriException* /*| RuntimeException*/ e) {
       ades->log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
               conditionalNG->NamedBean::getSystemName(), e->getMessage()), e);
   }

   conditionalNG->setSymbolTable(oldSymbolTable);
  }
};

#endif // ABSTRACTDIGITALEXPRESSIONSWING_H
