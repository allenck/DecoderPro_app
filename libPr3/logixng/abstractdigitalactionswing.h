#ifndef ABSTRACTDIGITALACTIONSWING_H
#define ABSTRACTDIGITALACTIONSWING_H

#include "abstractswingconfigurator.h"
#include "joptionpane.h"
#include "threadingutil.h"
#include "defaultconditionalng.h"
#include "digitalaction.h"
#include "runtimeexception.h"

class AbstractDigitalActionSwing : public AbstractSwingConfigurator
{
 public:
  AbstractDigitalActionSwing(QObject* parent = nullptr) : AbstractSwingConfigurator(parent) {}
  /*public*/ QString getExecuteEvaluateMenuText()override;
  /*public*/ void executeEvaluate(/*@Nonnull*/ Base* object)override;
  /*public*/ BaseManager/*<? extends NamedBean>*/* getManager()override ;
  /*public*/ JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel)override /*throws IllegalArgumentException*/;
  /*public*/ JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override /*throws IllegalArgumentException*/;
  /*public*/ QString getExampleSystemName()override;
  /*public*/ QString getAutoSystemName()override;


  QObject* sself() override {return this;}
 private:
  static Logger* log;
 protected:
  /*protected*/ JPanel* panel;
  /*protected*/ /*abstract*/ virtual void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)=0;

};
class ThreadAction3 : public ThreadAction
{
  Q_OBJECT
 public:
  ThreadAction3() {}
  void run (){
   JOptionPane::showMessageDialog(nullptr,
           tr("The action has completed"),
           tr("The action has been executed"),
           JOptionPane::PLAIN_MESSAGE);
  }
};

class ADSRun1 : public ThreadAction
{
  Q_OBJECT
  ConditionalNG* conditionalNG;
  SymbolTable* symbolTable;
  Base* object;
  Logger* log;
 public:
  ADSRun1(ConditionalNG* conditionalNG, SymbolTable* symbolTable, Base* object, Logger* log) {
   this->conditionalNG = conditionalNG;
   this->symbolTable = symbolTable;
   this->object = object;
   this->log = log;
  }

  void run()
  {
  //conditionalNG->getCurrentThread()->runOnLogixNGEventually([=]()  {
      SymbolTable* oldSymbolTable = conditionalNG->getSymbolTable();

      try {
          conditionalNG->setSymbolTable(symbolTable);
          ((DigitalAction*)object->bself())->execute();
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
  }
};

#endif // ABSTRACTDIGITALACTIONSWING_H
