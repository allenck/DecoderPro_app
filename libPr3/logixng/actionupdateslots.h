#ifndef ACTIONUPDATESLOTS_H
#define ACTIONUPDATESLOTS_H

#include "abstractdigitalaction.h"

class LocoNetSystemConnectionMemo;
class ActionUpdateSlots : public AbstractDigitalAction
{
    Q_OBJECT
public:
    ActionUpdateSlots() {}
    Q_INVOKABLE ActionUpdateSlots(QString sys, QString user, LocoNetSystemConnectionMemo* memo, QObject *parent = nullptr);
    ~ActionUpdateSlots() {}
    ActionUpdateSlots(const ActionUpdateSlots&) : AbstractDigitalAction() {}
    /*public*/ Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ override;
    /*public*/ Category getCategory()override;
    /*public*/ void setMemo(LocoNetSystemConnectionMemo* memo);
    /*public*/ LocoNetSystemConnectionMemo* getMemo();
    /*public*/ void execute() override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale) override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass() override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;

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

private:

    static Logger* log;
    /*private*/ LocoNetSystemConnectionMemo* _memo;

};
Q_DECLARE_METATYPE(ActionUpdateSlots)
#endif // ACTIONUPDATESLOTS_H
