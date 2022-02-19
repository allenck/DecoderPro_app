#ifndef ABSTRACTDIGITALEXPRESSIONSWING_H
#define ABSTRACTDIGITALEXPRESSIONSWING_H

#include "abstractswingconfigurator.h"
#include "threadingutil.h"

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

};

#endif // ABSTRACTDIGITALEXPRESSIONSWING_H
