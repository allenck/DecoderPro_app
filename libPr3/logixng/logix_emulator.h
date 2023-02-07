#ifndef LOGIX_EMULATOR_H
#define LOGIX_EMULATOR_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"

class FemaleDigitalBooleanActionSocket;
class FemaleDigitalExpressionSocket;
class Logix_Emulator : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  Logix_Emulator(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ override;
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  void setExecuteOnChange(bool b);
  /*public*/  bool isExecuteOnChange();
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount() override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket) override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleDigitalExpressionSocket* getExpressionSocket();
  /*public*/  QString getExpressionSocketSystemName();
  /*public*/  void setExpressionSocketSystemName(QString systemName);
  /*public*/  FemaleDigitalBooleanActionSocket* getActionSocket();
  /*public*/  QString getActionSocketSystemName();
  /*public*/  void setActionSocketSystemName(QString systemName);
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
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

 private:
  static Logger* log;
  /*private*/ bool _executeOnChange = true;
  /*private*/ bool _lastExpressionResult = false;
  /*private*/ QString _expressionSocketSystemName;
  /*private*/ QString _actionSocketSystemName;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _expressionSocket;
  /*private*/ /*final*/ FemaleDigitalBooleanActionSocket* _actionSocket;

};

#endif // LOGIX_EMULATOR_H
