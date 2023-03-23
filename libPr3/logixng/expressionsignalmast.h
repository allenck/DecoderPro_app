#ifndef EXPRESSIONSIGNALMAST_H
#define EXPRESSIONSIGNALMAST_H

#include "abstractdigitalexpression.h"
#include "logixng/expressionnode.h"
#include "signalmast.h"
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"

class ExpressionSignalMast : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
public:
    class QueryType
    {
    public:
    //    Aspect(Bundle.getMessage("SignalMastOperationType_Aspect")),
    //    Lit(Bundle.getMessage("SignalMastOperationType_Lit")),
    //    NotLit(Bundle.getMessage("SignalMastOperationType_NotLit")),
    //    Held(Bundle.getMessage("SignalMastOperationType_Held")),
    //    NotHeld(Bundle.getMessage("SignalMastOperationType_NotHeld")),
    //    PermissiveSmlDisabled(Bundle.getMessage("SignalMastOperationType_PermissiveSmlDisabled")),
    //    PermissiveSmlNotDisabled(Bundle.getMessage("SignalMastOperationType_PermissiveSmlNotDisabled"));
        enum TYPE {None, Aspect, NotAspect, Lit, NotLit, Held, NotHeld, IsPermissiveSmlDisabled, IsPermissiveSmlNotDisabled};

        static QString toString(TYPE t)
        {
            switch(t)
            {
             case None: return "None";
             case Aspect: return tr("has aspect");
            case NotAspect: return tr("has not aspect");
            case Lit: return tr("is lit");
            case NotLit: return tr("is not lit");
            case Held: return tr("is held");
            case NotHeld: return tr("is not held");
            case IsPermissiveSmlDisabled: return tr("is permissive sml disabled");
            case IsPermissiveSmlNotDisabled: return tr("is permissive sml not disabled");
            }
            return "";
        }
        /*public*/ static TYPE valueOf(QString s)
        {
            if(s=="has aspect") return Aspect;
            if(s=="has not aspect") return Aspect;
            if(s=="is lit") return Lit;
            if(s=="not lit") return NotLit;
            if(s=="is held") return Held;
            if(s=="is not held") return NotHeld;
            if(s=="is permissive sml disabled") return IsPermissiveSmlDisabled;
            if(s=="is permissive sml not disabled") return IsPermissiveSmlNotDisabled;
            throw new IllegalArgumentException("invalid operation");
        }
        /*public*/ static QList<TYPE> values()
        {
            return {None, Aspect, NotAspect, Lit, NotLit, Held, NotHeld, IsPermissiveSmlDisabled, IsPermissiveSmlNotDisabled};
        }
    };
    //explicit ExpressionSignalMast(QObject *parent = nullptr);
    /*public*/ ExpressionSignalMast(QString sys, QString user, QObject *parent = nullptr);
    /*public*/ Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ override;
    /*public*/ void setSignalMast(/*@Nonnull*/ QString signalMastName);
    /*public*/ void setSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle);
    /*public*/ void setSignalMast(/*@Nonnull*/ SignalMast* signalMast) ;
    /*public*/ void removeSignalMast();
    /*public*/ NamedBeanHandle<SignalMast*>* getSignalMast();
    /*public*/ void setExampleSignalMast(/*@Nonnull*/ QString signalMastName);
    /*public*/ void setExampleSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle) ;
    /*public*/ void setExampleSignalMast(/*@Nonnull*/ SignalMast* signalMast);
    /*public*/ void removeExampleSignalMast();
    /*public*/ NamedBeanHandle<SignalMast*>* getExampleSignalMast();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing() ;
    /*public*/ void setReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getLocalVariable() ;
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula() ;
    /*public*/ void setQueryAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getQueryAddressing();
    /*public*/ void setQueryType(QueryType::TYPE queryType);
    /*public*/ QueryType::TYPE getQueryType();
    /*public*/ void setQueryReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getQueryReference();
    /*public*/ void setQueryLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getQueryLocalVariable();
    /*public*/ void setQueryFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getQueryFormula() ;
    /*public*/ void setAspectAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
    /*public*/ NamedBeanAddressing::TYPE getAspectAddressing() ;
    /*public*/ void setAspect(QString aspect) ;
    /*public*/ QString getAspect() ;
    /*public*/ void setAspectReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getAspectReference();
    /*public*/ void setAspectLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getAspectLocalVariable() ;
    /*public*/ void setAspectFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getAspectFormula();
    /*public*/ Category getCategory() override;
    /*public*/ bool evaluate() /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
    /*public*/ QString getClass() const override
    {
        return "jmri.jmrit.logixng.expressions.ExpressionSignalMast";
    }

    QObject* bself() override {return this;}
    QObject* pself() override {return this;}
    QObject* self() override {return this;}


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
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt) override;
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<SignalMast*>* _signalMastHandle=nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;

    /*private*/ NamedBeanAddressing::TYPE _queryAddressing = NamedBeanAddressing::Direct;
    /*private*/ QueryType::TYPE _queryType = QueryType::Aspect;
    /*private*/ QString _queryReference = "";
    /*private*/ QString _queryLocalVariable = "";
    /*private*/ QString _queryFormula = "";
    /*private*/ ExpressionNode* _queryExpressionNode;

    /*private*/ NamedBeanAddressing::TYPE _aspectAddressing = NamedBeanAddressing::Direct;
    /*private*/ QString _signalMastAspect = "";
    /*private*/ QString _aspectReference = "";
    /*private*/ QString _aspectLocalVariable = "";
    /*private*/ QString _aspectFormula = "";
    /*private*/ ExpressionNode* _aspectExpressionNode;

    /*private*/ NamedBeanHandle<SignalMast*>* _exampleSignalMastHandle;
    /*private*/ void parseFormula() /*throws ParserException*/;
    /*private*/ void parseQueryFormula() /*throws ParserException*/;
    /*private*/ void parseAspectFormula() /*throws ParserException*/;
    /*private*/ QString getNewAspect() /*throws JmriException*/;
    /*private*/ QueryType::TYPE getQuery() /*throws JmriException*/ ;

};

#endif // EXPRESSIONSIGNALMAST_H
