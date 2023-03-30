#ifndef LASTRESULTOFDIGITALEXPRESSION_H
#define LASTRESULTOFDIGITALEXPRESSION_H

#include "abstractdigitalexpression.h"
#include "namedbeanhandle.h"
#include "vetoablechangelistener.h"

class LastResultOfDigitalExpression : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  explicit LastResultOfDigitalExpression(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/  void setDigitalExpression(/*@Nonnull*/ QString digitalExpressionName) ;
  /*public*/  void setDigitalExpression(/*@Nonnull*/ NamedBeanHandle<DigitalExpressionBean*>* handle) ;
  /*public*/  void setDigitalExpression(/*@Nonnull*/ DigitalExpressionBean* digitalExpression);
  /*public*/  void removeDigitalExpression() ;
  /*public*/  NamedBeanHandle<DigitalExpressionBean*>* getDigitalExpression();
  /*public*/  Category getCategory()override;
  /*public*/  bool evaluate() override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;
    /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.expressions.LastResultOfDigitalExpression";}


  QObject* self() override {return this;}
  QObject* bself() override {return this;}
  QObject* pself() override {return this;}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;

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

 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<DigitalExpressionBean*>* _digitalExpressionHandle = nullptr;

};

#endif // LASTRESULTOFDIGITALEXPRESSION_H
