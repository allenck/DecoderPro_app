#ifndef ENABLELOGIX_H
#define ENABLELOGIX_H

#include "abstractdigitalaction.h"
#include "logix.h"
#include "namedbeanhandle.h"
#include "namedbeanaddressing.h"
#include "vetoablechangelistener.h"
#include "threadingutil.h"

class ExpressionNode;
class Logix;
class EnableLogix : public AbstractDigitalAction, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener)
public:
    EnableLogix(QString sys, QString user, QObject *parent = nullptr);
    class Operation{
    public:
        enum TYPE {Enable, Disable};
        static QString toString(TYPE t)
        {
           if(t==Enable) return tr("Enable");
           return tr("Disable");
        }
        static TYPE valueOf(QString s)
        {
            if(s==tr("Enable")) return Enable;
            return Disable;
        }
        static QList<TYPE> values()
        {
            return {Enable, Disable};
        }
    };
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/override;
    /*public*/ void setLogix(/*@Nonnull*/ QString logixName);
    /*public*/ void setLogix(/*@Nonnull*/ NamedBeanHandle<Logix*>* handle);
    /*public*/ void setLogix(/*@Nonnull*/ Logix* logix);
    /*public*/ void removeLogix();
    /*public*/ NamedBeanHandle<Logix*>* getLogix();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing();
    /*public*/ void setReference(/*@Nonnull*/ QString reference) ;
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getLocalVariable();
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getFormula();
    /*public*/ void setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getOperationAddressing();
    /*public*/ void setOperationDirect(Operation::TYPE state);
    /*public*/ Operation::TYPE getOperationDirect() ;
    /*public*/ void setOperationReference(/*@Nonnull*/ QString reference);
    /*public*/ void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getOperationReference() ;
    /*public*/ void setOperationLocalVariable(/*@Nonnull*/ QString localVariable) ;
    /*public*/ QString getOperationLocalVariable();;
    /*public*/ QString getLockFormula() ;
    /*public*/ Category getCategory() override;
    /*public*/ void execute() /*throws JmriException*/ override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale) override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;

    QObject* bself() override {return this;}

    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
     AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                      QString name, QString listenerRef) override {
     AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener) override
    {
        AbstractNamedBean::addPropertyChangeListener(propertyName, listener);
    }
    /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
    ///*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
    /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
    /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
    /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
     return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }
    virtual void addPropertyChangeListener(PropertyChangeListener* l) override{
        AbstractNamedBean::addPropertyChangeListener(l);
    }

public slots:
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<Logix*>* _logixHandle;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;
    /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
    /*private*/ Operation::TYPE _operationDirect = Operation::Disable;
    /*private*/ QString _operationReference = "";
    /*private*/ QString _operationLocalVariable = "";
    /*private*/ QString _operationFormula = "";
    /*private*/ ExpressionNode* _operationExpressionNode;
    /*private*/ void parseFormula() /*throws ParserException*/ ;
    /*private*/ void parseLockFormula() /*throws ParserException*/;
    /*private*/ QString getNewLock() /*throws JmriException*/ ;

};
class EL_ThreadingUtil : ThreadingUtil
{
   public:
    static void runOnLayoutWithJmriException(Logix* logix, EnableLogix::Operation::TYPE theLock)
    {
        logix->setEnabled(theLock == EnableLogix::Operation::Enable);
    }
};

#endif // ENABLELOGIX_H
