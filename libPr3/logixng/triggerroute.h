#ifndef TRIGGERROUTE_H
#define TRIGGERROUTE_H

#include "abstractdigitalaction.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "vetoablechangelistener.h"

class Route;
class ExpressionNode;
class TriggerRoute : public AbstractDigitalAction, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener)
public:
    TriggerRoute(QString sys, QString user,QObject *parent = nullptr);
    class Operation
    {
    public:
        enum TYPE {TriggerRoute};
        static QString toString(TYPE) {return tr("Trigger route");}
        static QList<TYPE> values() {return {TriggerRoute};}
        static TYPE valueOf(QString s) {if(s==tr("Trigger route"))return TriggerRoute; throw new IllegalArgumentException();}
    };
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/override;
    /*public*/ void setRoute(/*@Nonnull*/ QString routeName);
    /*public*/ void setRoute(/*@Nonnull*/ NamedBeanHandle<Route*>* handle) ;
    /*public*/ void setRoute(/*@Nonnull*/ Route* route);
    /*public*/ void removeRoute() ;
    /*public*/ NamedBeanHandle<Route*>* getRoute() ;
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing();
    /*public*/ void setReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable) ;
    /*public*/ QString getLocalVariable() ;
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula();
    /*public*/ void setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getOperationAddressing() ;
    /*public*/ void setOperationDirect(TriggerRoute::Operation::TYPE state);
    /*public*/ TriggerRoute::Operation::TYPE getOperationDirect();
    /*public*/ void setOperationReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getOperationReference();
    /*public*/ void setOperationLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getOperationLocalVariable() ;
    /*public*/ void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getLockFormula();
    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup() override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe() override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
    /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.tools.debugger.TriggerRoute";}

    QObject* bself() override {return this;}

    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
     AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                      QString name, QString listenerRef) override {
     AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
    /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
    /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
    /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
     return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

public slots:
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;


private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<Route*>* _routeHandle = nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;
    /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
    /*private*/ Operation::TYPE _operationDirect = Operation::TriggerRoute;
    /*private*/ QString _operationReference = "";
    /*private*/ QString _operationLocalVariable = "";
    /*private*/ QString _operationFormula = "";
    /*private*/ ExpressionNode* _operationExpressionNode;
    /*private*/ void parseFormula() /*throws ParserException*/;
    /*private*/ void parseLockFormula() /*throws ParserException*/ ;
    /*private*/ QString getNewLock() /*throws JmriException*/;

};

#endif // TRIGGERROUTE_H
