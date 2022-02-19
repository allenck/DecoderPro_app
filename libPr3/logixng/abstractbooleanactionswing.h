#ifndef ABSTRACTBOOLEANACTIONSWING_H
#define ABSTRACTBOOLEANACTIONSWING_H

#include "abstractswingconfigurator.h"

class AbstractBooleanActionSwing : public AbstractSwingConfigurator
{
  Q_OBJECT
 public:
  explicit AbstractBooleanActionSwing(QObject *parent = nullptr) : AbstractSwingConfigurator(parent) {}
  /*public*/  QString getExecuteEvaluateMenuText()override;
  /*public*/  void executeEvaluate(/*@Nonnull*/ Base* object)override;
  /*public*/  BaseManager/*<? extends NamedBean>*/* getManager()override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ override;
  /*public*/  JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ override;
  /*public*/  QString getExampleSystemName()override;
  /*public*/  QString getAutoSystemName()override;

 protected:
  /*protected*/ /*abstract*/virtual void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)=0;

  /*protected*/ JPanel* panel;
};

#endif // ABSTRACTBOOLEANACTIONSWING_H
