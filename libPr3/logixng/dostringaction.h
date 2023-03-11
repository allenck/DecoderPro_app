#ifndef DOSTRINGACTION_H
#define DOSTRINGACTION_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"

class FemaleStringExpressionSocket;
class FemaleStringActionSocket;

class DoStringAction : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  explicit DoStringAction(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/override;
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  void connected(FemaleSocket* socket) override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleStringActionSocket* getStringActionSocket();
  /*public*/  QString getStringActionSocketSystemName() ;
  /*public*/  void setStringActionSocketSystemName(QString systemName) ;
  /*public*/  FemaleStringExpressionSocket* getStringExpressionSocket();
  /*public*/  QString getStringExpressionSocketSystemName();
  /*public*/  void setStringExpressionSocketSystemName(QString systemName);
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 private:
  static Logger* log;
  /*private*/ QString _stringExpressionSocketSystemName;
  /*private*/ QString _stringActionSocketSystemName;
  /*private*/ /*final*/ FemaleStringExpressionSocket* _stringExpressionSocket;
  /*private*/ /*final*/ FemaleStringActionSocket* _stringActionSocket;

};

#endif // DOSTRINGACTION_H
