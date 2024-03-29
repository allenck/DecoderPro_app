#ifndef FOR_H
#define FOR_H

#include "abstractdigitalaction.h"
#include <QWidget>
#include "femalesocketlistener.h"

class FemaleDigitalActionSocket;
class FemaleDigitalExpressionSocket;
class For : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  explicit For(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleDigitalActionSocket* getInitActionSocket();
  /*public*/  QString getInitActionSocketSystemName();
  /*public*/  void setInitActionSocketSystemName(QString systemName);
  /*public*/  FemaleDigitalExpressionSocket* getWhileExpressionSocket();
  /*public*/  QString getWhileExpressionSocketSystemName();
  /*public*/  void setWhileExpressionSocketSystemName(QString systemName);
  /*public*/  FemaleDigitalActionSocket* getAfterEachActionSocket();
  /*public*/  QString getAfterEachExpressionSocketSystemName();
  /*public*/  void setAfterEachActionSocketSystemName(QString systemName);
  /*public*/  FemaleDigitalActionSocket* getDoActionSocket();
  /*public*/  QString getDoExpressionSocketSystemName();
  /*public*/  void setDoActionSocketSystemName(QString systemName);
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  QString getClass() const override {return "jmri.jmrit.logixng.actions.For";}

  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
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
  /*private*/ QString _initActionSocketSystemName;
  /*private*/ QString _whileExpressionSocketSystemName;
  /*private*/ QString _afterEachActionSocketSystemName;
  /*private*/ QString _doActionSocketSystemName;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _initActionSocket;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _whileExpressionSocket;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _afterEachActionSocket;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _doActionSocket;

};

#endif // FOR_H
