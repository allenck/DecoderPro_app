#ifndef SHUTDOWNCOMPUTER_H
#define SHUTDOWNCOMPUTER_H

#include "abstractdigitalaction.h"
#include "defaultshutdownmanager.h"
#include "threadingutil.h"
#include "runtimeexception.h"
#include "instancemanager.h"

class ShutdownComputer : public AbstractDigitalAction
{
    Q_OBJECT
public:
    ShutdownComputer(QString sys, QString user, QObject *parent = nullptr);
    class Operation{
    public:
        enum TYPE {ShutdownComputer, RebootComputer, ShutdownJMRI, RebootJMRI};
        static QString toString(TYPE t)
        {
            switch (t)
            {
                case ShutdownComputer: return tr("Shut down the computer");
                case RebootComputer: return tr("Reboot the computer");
                case ShutdownJMRI: return tr("Shut down JMRI");
                case RebootJMRI: return tr("Reboot JMRI");
                    throw new IllegalArgumentException();
            }
        }
        static QList<TYPE> values() {return {ShutdownComputer, RebootComputer, ShutdownJMRI, RebootJMRI};}
        static TYPE valueOf(QString s)
        {
            if(s == tr("Shut down the computer")) return ShutdownComputer;
            if(s == tr("Reboot the computer")) return RebootComputer;
            if(s == tr("Shut down JMRI")) return ShutdownJMRI;
            if(s == tr("Reboot JMRI")) return RebootJMRI;
            throw new IllegalArgumentException();
        }
    };

    /*public*/ Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames);
    /*public*/ void setOperation(Operation::TYPE operation);
    /*public*/ Operation::TYPE getOperation();
    /*public*/ Category getCategory() override;
    /*public*/ void execute() override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass() override;
    /*public*/ void disposeMe()override;

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
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

private:
    static Logger* log;
    /*private*/ Operation::TYPE _operation = Operation::ShutdownJMRI;

};
class SD_ThreadingUtil : public ThreadingUtil
{
    Q_OBJECT
    ShutdownComputer::Operation::TYPE _operation;
public:
    SD_ThreadingUtil(ShutdownComputer::Operation::TYPE _operation) {this->_operation = _operation;}
    void runOnGui(){
        switch (_operation) {
            case ShutdownComputer::Operation::ShutdownComputer:
 //           ((DefaultShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->shutdownOS();
                break;

            case ShutdownComputer::Operation::RebootComputer:
//            ((DefaultShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->restartOS();
                break;

            case ShutdownComputer::Operation::ShutdownJMRI:
            ((DefaultShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->shutdown();
                break;

            case ShutdownComputer::Operation::RebootJMRI:
            ((DefaultShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->restart();
                break;

            default:
                throw new RuntimeException("_operation has invalid value: "+ShutdownComputer::Operation::toString(_operation));
        }
    };

};

#endif // SHUTDOWNCOMPUTER_H
