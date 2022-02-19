#ifndef ABSTRACTSTRINGACTIONSWING_H
#define ABSTRACTSTRINGACTIONSWING_H

#include "abstractswingconfigurator.h"

class AbstractStringActionSwing : public AbstractSwingConfigurator
{
 public:
  explicit AbstractStringActionSwing(QObject *parent = nullptr) : AbstractSwingConfigurator(parent) {}
  /*public*/  QString getExecuteEvaluateMenuText()override;
  /*public*/  void executeEvaluate(/*@Nonnull*/ Base* object)override;
  /*public*/  BaseManager/*<? extends NamedBean>*/* getManager()override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/override;
  /*public*/  QString getExampleSystemName()override;
  /*public*/  QString getAutoSystemName()override;

 protected:
  /*protected*/ JPanel* panel;
  /*protected*/ /*abstract*/virtual void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)=0;

};

#endif // ABSTRACTSTRINGACTIONSWING_H
