#ifndef ACTIONCLEARSLOTS_H
#define ACTIONCLEARSLOTS_H

#include "abstractdigitalaction.h"

class LocoNetSystemConnectionMemo;
class ActionClearSlots : public AbstractDigitalAction
{
    Q_OBJECT
public:
     ActionClearSlots(QString sys, QString user, LocoNetSystemConnectionMemo* memo, QObject *parent = nullptr);
     /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ override;
     /*public*/ Category getCategory()override;
     /*public*/ void setMemo(LocoNetSystemConnectionMemo* memo) ;
     /*public*/ LocoNetSystemConnectionMemo* getMemo();
     /*public*/ void execute() override;
     /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
     /*public*/ int getChildCount()override;
     /*public*/ QString getShortDescription(QLocale locale)override;
     /*public*/ QString getLongDescription(QLocale locale)override;
     /*public*/ void setup()override;
     /*public*/ void registerListenersForThisClass()override;
     /*public*/ void unregisterListenersForThisClass() override;
     /*public*/ void disposeMe()override;
     /*public*/  QString getClass() const override
     {
      return "jmri.jmrit.logixng.actions.ActionClearSlots";
     }

     QObject* bself() override {return this;}

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
     /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/{
         AbstractNamedBean::vetoableChange(evt);
     }
     void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

   private:
    /*private*/ static /*final*/const  int NUM_LOCO_SLOTS_TO_CLEAR = 119;
    static Logger* log;
    /*private*/ LocoNetSystemConnectionMemo* _memo;

};

#endif // ACTIONCLEARSLOTS_H
