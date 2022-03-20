#ifndef ANALOGACTIONMEMORY_H
#define ANALOGACTIONMEMORY_H

#include "abstractanalogaction.h"
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "memory.h"
#include "threadingutil.h"

class AnalogActionMemory : public AbstractAnalogAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit AnalogActionMemory(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames)override;
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) ;
  /*public*/  void setMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeMemory() ;
  /*public*/  NamedBeanHandle<Memory*>* getMemory() ;
  /*public*/  void setValue(double value) /*throws JmriException*/override;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/override;
  /*public*/  FemaleSocket* getChild(int index)
          /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  Category* getCategory()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;

  QObject* bself() override {return (QObject*)this;}

  QString getSystemName()  const override{return mSystemName;}
 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle;

};

class AAMRun : public ThreadActionWithJmriException
{
  Q_OBJECT
  NamedBeanHandle<Memory*>* _memoryHandle;
  double value;
 public:
  AAMRun(NamedBeanHandle<Memory*>* _memoryHandle, double value) {
   this->_memoryHandle = _memoryHandle;
  this->value = value;
  }
 public slots:
  void run();
};
#endif // ANALOGACTIONMEMORY_H
