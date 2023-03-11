#ifndef ACTIONLISTENONBEANS_H
#define ACTIONLISTENONBEANS_H

#include "abstractdigitalaction.h"
#include "vetoablechangelistener.h"
#include "namedbeantype.h"
#include "namedbeanhandlemanager.h"

class NamedBeanReference;
class ActionListenOnBeans : public AbstractDigitalAction, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener )
 public:
  Q_INVOKABLE ActionListenOnBeans(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/  /*static*/ class NamedBeanReference {

      /*private*/ QString _name;
      /*private*/ NamedBeanType::TYPE _type;
      /*private*/ NamedBeanHandle<NamedBean*>* _handle;
public:
      /*public*/  NamedBeanReference(QString name, NamedBeanType::TYPE type) {
          _name = name;
          _type = type;

          NamedBean* bean = NamedBeanType::getManager(_type)->getNamedBean(name);//_type.getManager().getNamedBean(name);
          if (bean != nullptr) {
              _handle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(_name, bean);
          }
      }

      /*public*/  QString getName() {
          return _name;
      }

      /*public*/  void setName(QString name) {
          _name = name;
      }

      /*public*/  NamedBeanType::TYPE getType() {
          return _type;
      }

      /*public*/  void setType(NamedBeanType::TYPE type) {
//          if (type == null) {
//              log.warn("type is null");
//              type = NamedBeanType.Turnout;
//          }
          _type = type;
      }

      /*public*/  NamedBeanHandle<NamedBean*>* getHandle() {
          return _handle;
      }

      /*public*/  void updateHandle() {
          if (!_name.isEmpty()) {
              NamedBean* bean = NamedBeanType::getManager(_type)->getNamedBean(_name);
              if (bean != nullptr) {
                  _handle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(_name, bean);
              } else {
                  log->warn(QString("Cannot find named bean ") + _name + " in manager for " + (NamedBeanType::getManager(_type)->getBeanTypeHandled()));
                  _handle = nullptr;
              }
          } else {
              _handle = nullptr;
          }
      }
    friend class ActionListenOnBeans;
  };
  /*public*/  void addReference(QString beanAndType);
  /*public*/  void addReference(NamedBeanReference* reference);
  /*public*/  void removeReference(NamedBeanReference* reference);
  /*public*/  QList<NamedBeanReference*> getReferences();
  /*public*/  void clearReferences() ;
  /*public*/  Category getCategory()override;
  /*public*/  void execute()override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;


  QObject* pself() override{return(QObject*)this;}

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
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, NamedBeanReference*> _namedBeanReferences = /*new DuplicateKeyMap*/QMap<QString, NamedBeanReference*>();

};

#endif // ACTIONLISTENONBEANS_H
