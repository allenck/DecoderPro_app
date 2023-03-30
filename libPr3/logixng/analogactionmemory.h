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
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
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
  /*public*/  Category getCategory()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
    /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.actions.AnalogActionMemory";}

  QObject* bself() override {return (QObject*)this;}
  QObject* self() override {return this;}


  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  ///*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }

  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle = nullptr;

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
