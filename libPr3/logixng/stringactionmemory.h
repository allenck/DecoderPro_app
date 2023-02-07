#ifndef STRINGACTIONMEMORY_H
#define STRINGACTIONMEMORY_H

#include "abstractstringaction.h"
#include <QObject>
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "namedbeanhandlemanager.h"
#include "memory.h"

class StringActionMemory : public AbstractStringAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit StringActionMemory(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) ;
  /*public*/  void setMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeMemory() ;
  /*public*/  NamedBeanHandle<Memory*>* getMemory();
  /*public*/  void setValue(QString value)override;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  Category getCategory()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;


  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
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

 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle = nullptr;

};

#endif // STRINGACTIONMEMORY_H
