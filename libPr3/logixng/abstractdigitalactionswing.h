#ifndef ABSTRACTDIGITALACTIONSWING_H
#define ABSTRACTDIGITALACTIONSWING_H

#include "abstractswingconfigurator.h"
#include "joptionpane.h"
#include "threadingutil.h"

class AbstractDigitalActionSwing : public AbstractSwingConfigurator
{
 public:
  AbstractDigitalActionSwing();
  /*public*/ QString getExecuteEvaluateMenuText()override;
  /*public*/ void executeEvaluate(/*@Nonnull*/ Base* object)override;
  /*public*/ BaseManager/*<? extends NamedBean>*/* getManager()override ;
  /*public*/ JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel)override /*throws IllegalArgumentException*/;
  /*public*/ JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override /*throws IllegalArgumentException*/;
  /*public*/ QString getExampleSystemName()override;
  /*public*/ QString getAutoSystemName()override;

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

#endif // ABSTRACTDIGITALACTIONSWING_H
