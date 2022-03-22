#ifndef ABSTRACTSWINGCONFIGURATOR_H
#define ABSTRACTSWINGCONFIGURATOR_H

#include <QObject>
#include "swingconfiguratorinterface.h"
#include "base.h"
#include "symboltable.h"

class AbstractSwingConfigurator : public QObject, public SwingConfiguratorInterface
{
  Q_OBJECT
  Q_INTERFACES(SwingConfiguratorInterface)
 public:
  explicit AbstractSwingConfigurator(QObject *parent = nullptr) : QObject(parent){}
  /*public*/  void getAllSymbols(/*@Nonnull*/ Base* object, SymbolTable* symbolTable);
  /*public*/  QString getExecuteEvaluateMenuText() override;
  /*public*/  void executeEvaluate(/*@Nonnull*/ Base* object)override;

 signals:

 private:
  /*private*/ void getSymbols(/*@Nonnull*/ Base* object, SymbolTable* symbolTable) /*throws JmriException*/;

};

#endif // ABSTRACTSWINGCONFIGURATOR_H
