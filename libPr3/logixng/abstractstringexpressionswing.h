#ifndef ABSTRACTSTRINGEXPRESSIONSWING_H
#define ABSTRACTSTRINGEXPRESSIONSWING_H

#include "abstractswingconfigurator.h"

class AbstractStringExpressionSwing : public AbstractSwingConfigurator
{
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

};

#endif // ABSTRACTSTRINGEXPRESSIONSWING_H
