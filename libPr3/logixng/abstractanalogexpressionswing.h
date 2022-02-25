#ifndef ABSTRACTANALOGEXPRESSIONSWING_H
#define ABSTRACTANALOGEXPRESSIONSWING_H

#include "abstractswingconfigurator.h"
#include "threadingutil.h"
#include "joptionpane.h"

class AbstractAnalogExpressionSwing : public AbstractSwingConfigurator
{
  Q_OBJECT

 public:
  explicit AbstractAnalogExpressionSwing(QObject *parent = nullptr) : AbstractSwingConfigurator(parent) {};
  /*public*/  QString getExecuteEvaluateMenuText()override;
  /*public*/  void executeEvaluate(/*@Nonnull*/ Base* object)override;
  void run();
  /*public*/  BaseManager/*<? extends NamedBean>*/* getManager()override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException */override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/override;
  /*public*/  QString getExampleSystemName()override;
  /*public*/  QString getAutoSystemName()override;

 private:
  static Logger* log;

 protected:
  /*protected*/ JPanel* panel;
  /*protected*/ /*abstract*/virtual void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)=0;

};

class AbstractAnalogExpressionSwingTA1 : public ThreadAction
{
  Q_OBJECT
  ConditionalNG* conditionalNG;
  SymbolTable* symbolTable;
  Base* object;
  Logger* log;
 public:
  AbstractAnalogExpressionSwingTA1(Base* object, ConditionalNG* conditionalNG, SymbolTable* symbolTable, Logger* log) {
   this->object = object;
   this->conditionalNG = conditionalNG;
   this->symbolTable = symbolTable;
   this->log = log;
  }
  void run();
};

class AbstractAnalogExpressionSwingRun1 : public ThreadAction
{
  Q_OBJECT
   double result;
 public:
   AbstractAnalogExpressionSwingRun1(double result) {this->result = result;}
  void run()
  {
   JOptionPane::showMessageDialog(nullptr,
           tr("The result of the expression is: %1").arg(result),
           tr("The expression has been evaluated"),
           JOptionPane::PLAIN_MESSAGE);

  }
};

#endif // ABSTRACTANALOGEXPRESSIONSWING_H
