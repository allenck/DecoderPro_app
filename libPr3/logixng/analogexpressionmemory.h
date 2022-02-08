#ifndef ANALOGEXPRESSIONMEMORY_H
#define ANALOGEXPRESSIONMEMORY_H

#include "abstractanalogexpression.h"
#include "namedbeanhandle.h"
#include  "vetoablechangelistener.h"

class Memory;
class AnalogExpressionMemory : public AbstractAnalogExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  explicit AnalogExpressionMemory(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException */override;
  /*public*/  Category* getCategory()override;
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName) ;
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) ;
  /*public*/  void setMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeMemory() ;
  /*public*/  NamedBeanHandle<Memory*>* getMemory();
  /*public*/  double evaluate()override;
  /*public*/  FemaleSocket* getChild(int index)
          /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;

  QObject* self() override {return (QObject*)this;}
  QString getUserName()const override {return AbstractBase::getUserName();}
 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;

 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle;

};

#endif // ANALOGEXPRESSIONMEMORY_H
