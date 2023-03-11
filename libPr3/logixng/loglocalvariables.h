#ifndef LOGLOCALVARIABLES_H
#define LOGLOCALVARIABLES_H

#include "abstractdigitalaction.h"

class LogLocalVariables : public AbstractDigitalAction
{
    Q_OBJECT
public:
    explicit LogLocalVariables(QString sys, QString user, QObject *parent = nullptr);
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) override;
    /*public*/ Category getCategory()override;
    /*public*/ void execute()override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass() override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;

    QObject* bself() override{return this;}

    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

    /*public*/ void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef) override{
        AbstractNamedBean::addPropertyChangeListener(listener, name, listenerRef);
    }
    /*public*/ void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                              QString name, QString listenerRef) override{
        AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/ void updateListenerRef(/*@Nonnull*/ PropertyChangeListener* l, QString newName) override{
        AbstractNamedBean::updateListenerRef(l,newName);
    }
    /*public*/ int getNumPropertyChangeListeners() override{
        return AbstractNamedBean::getNumPropertyChangeListeners();
    }
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name) override
    {
       return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }
    /*public*/ virtual QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l)override{
        return AbstractNamedBean::getListenerRef(l);
    }
    /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override{
        return AbstractNamedBean::vetoableChange(evt);
    }

private:
    static Logger* log;
};

#endif // LOGLOCALVARIABLES_H
