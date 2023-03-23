#ifndef ACT_LOGIX_H
#define ACT_LOGIX_H

#include "../abstractdigitalaction.h"
#include "../femalesocketlistener.h"

class FemaleDigitalExpressionSocket;
class FemaleDigitalBooleanActionSocket;

namespace Actions
{
 class Logix : public AbstractDigitalAction, public FemaleSocketListener
 {
   Q_OBJECT
   Q_INTERFACES(FemaleSocketListener)
  public:
   Logix(QString sys, QString user, QObject* parent = nullptr);
   /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/override;
   /*public*/  Category getCategory()override;
   /*public*/  void execute() /*throws JmriException*/ override;
   /*public*/  void setExecuteOnChange(bool b);
   /*public*/  bool isExecuteOnChange();
   /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
   /*public*/  int getChildCount()override;
   /*public*/  void connected(FemaleSocket* socket)override;
   /*public*/  void disconnected(FemaleSocket* socket)override;
   /*public*/  QString getShortDescription(QLocale locale)override;
   /*public*/  QString getLongDescription(QLocale locale)override;
   /*public*/  FemaleDigitalExpressionSocket* getExpressionSocket();
   /*public*/  QString getExpressionSocketSystemName();
   /*public*/  void setExpressionSocketSystemName(QString systemName);
   /*public*/  FemaleDigitalBooleanActionSocket* getActionSocket();
   /*public*/  QString getActionSocketSystemName();
   /*public*/  void setActionSocketSystemName(QString systemName) ;
   /*public*/  void setup()override;
   /*public*/  void registerListenersForThisClass()override;
   /*public*/  void unregisterListenersForThisClass()override;
   /*public*/  void disposeMe()override;
   /*public*/  QString getClass() const override
   {
    return "jmri.jmrit.logixng.actions.Logix";
   }

   QObject* bself() override {return this;}

   /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef) override{
    AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);}
   /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                              QString name, QString listenerRef) override {
    AbstractNamedBean::addPropertyChangeListener(propertyName,listener, name,listenerRef);}
   /*public*/  void updateListenerRef(/*@Nonnull*/ PropertyChangeListener* l, QString newName) override
               {AbstractNamedBean::updateListenerRef(l, newName);}
   /*public*/  void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/ override {
    AbstractNamedBean::vetoableChange(evt);}
   /*public*/  QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override{return AbstractNamedBean::getListenerRef(l);}
   /*public*/  int getNumPropertyChangeListeners() override{return AbstractNamedBean::getNumPropertyChangeListeners();}
   /*public*/  QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name) override{
    return AbstractNamedBean::getPropertyChangeListenersByReference(name);
   }
   void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

  private:
   static Logger* log;
   /*private*/ bool _executeOnChange = true;
   /*private*/ bool _lastExpressionResult = false;
   /*private*/ QString _expressionSocketSystemName;
   /*private*/ QString _actionSocketSystemName;
   /*private*/ /*final*/ FemaleDigitalExpressionSocket* _expressionSocket;
   /*private*/ /*final*/ FemaleDigitalBooleanActionSocket* _actionSocket;

 };
}
#endif // ACT_LOGIX_H
