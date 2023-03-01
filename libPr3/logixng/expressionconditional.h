#ifndef EXPRESSIONCONDITIONAL_H
#define EXPRESSIONCONDITIONAL_H

#include "abstractdigitalexpression.h"
#include "logixng/expressionnode.h"
#include "logixng/namedbeanaddressing.h"
#include "logixng/is_isnot_enum.h"
#include "namedbeanhandle.h"
#include <QMap>
#include "vetoablechangelistener.h"

class Conditional;
class ExpressionConditional : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
public:
    ExpressionConditional(QString sys, QString user,QObject *parent = nullptr);
    class ConditionalState
    {
    public:
        enum VAL {False, True, Other};


        static QString toString(VAL v)
        {
            switch (v)
            {
            case False: return tr("false");
            case True: return tr("true");
            case Other: return tr("other");
            }
        }
        static VAL valueOf(QString s)
        {
            if(s == "false") return False;
            if(s== "True") return True;
            return Other;
        }

        static QList<VAL> values()
        {
            return {False, True, Other};
        }
    };
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/override;
    /*public*/ void setConditional(/*@Nonnull*/ QString conditionalName);
    /*public*/ void setConditional(/*@Nonnull*/ NamedBeanHandle<Conditional*>* handle);
    /*public*/ void setConditional(/*@Nonnull*/ Conditional* conditional);
    /*public*/ void removeConditional();
    /*public*/ NamedBeanHandle<Conditional*>* getConditional() ;
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing() ;
    /*public*/ void setReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable) ;
    /*public*/ QString getLocalVariable();
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula();
    /*private*/ void parseFormula() /*throws ParserException*/;
    /*public*/ void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) ;
    /*public*/ Is_IsNot_Enum::VAL get_Is_IsNot() ;
    /*public*/ void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getStateAddressing();
    /*public*/ void setConditionalState(ConditionalState::VAL state);
    /*public*/ ConditionalState::VAL getConditionalState() ;
    /*public*/ void setStateReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getStateReference();
    /*public*/ void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getStateLocalVariable();
    /*public*/ void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getStateFormula();
    /*private*/ void parseStateFormula() /*throws ParserException*/ ;
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;
    /** {@inheritDoc} */
    //@Override
    /*public*/ Category getCategory() override;
    /*public*/ bool evaluate() /*throws JmriException*/ override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale) override;
    /*public*/ QString getLongDescription(QLocale locale) override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void propertyChange(PropertyChangeEvent* evt)override;
    /*public*/ void disposeMe()override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

    QObject* bself() override{return this;}
    QObject* pself() override{return this;}


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


private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<Conditional*>* _conditionalHandle;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;
    /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
    /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
    /*private*/ ConditionalState::VAL _conditionalState = ConditionalState::False;
    /*private*/ QString _stateReference = "";
    /*private*/ QString _stateLocalVariable = "";
    /*private*/ QString _stateFormula = "";
    /*private*/ ExpressionNode* _stateExpressionNode;
    /*private*/ QString getNewState() /*throws JmriException*/;
};

#endif // EXPRESSIONCONDITIONAL_H
