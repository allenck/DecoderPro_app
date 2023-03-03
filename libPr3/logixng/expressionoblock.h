#ifndef EXPRESSIONOBLOCK_H
#define EXPRESSIONOBLOCK_H

#include "abstractdigitalexpression.h"
#include "namedbeanaddressing.h"
#include "is_isnot_enum.h"
#include "namedbeanhandle.h"
#include "expressionnode.h"
#include "oblock.h"
#include "vetoablechangelistener.h"


class ExpressionOBlock : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener PropertyChangeListener)
public:
    ExpressionOBlock(QString sys, QString user, QObject *parent = nullptr);
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/override;
    /*public*/ void setOBlock(/*@Nonnull*/ QString oblockName) ;
    /*public*/ void setOBlock(/*@Nonnull*/ NamedBeanHandle<OBlock*>* handle) ;
    /*public*/ void setOBlock(/*@Nonnull*/ OBlock* oblock);
    /*public*/ void removeOBlock() ;
    /*public*/ NamedBeanHandle<OBlock*>* getOBlock();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
    /*public*/ NamedBeanAddressing::TYPE getAddressing() ;
    /*public*/ void setReference(/*@Nonnull*/ QString reference) ;
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getLocalVariable() ;
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getFormula();
    /*public*/ void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
    /*public*/ Is_IsNot_Enum::VAL get_Is_IsNot();
    /*public*/ void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
    /*public*/ NamedBeanAddressing::TYPE getStateAddressing() ;
    /*public*/ void setBeanState(OBlock::OBlockStatus::STATES state);
    /*public*/ OBlock::OBlockStatus::STATES getBeanState() ;
    /*public*/ void setStateReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getStateReference() ;
    /*public*/ void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getStateLocalVariable();
    /*public*/ void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getStateFormula() ;
    /*public*/ Category getCategory()override;
    /*public*/ bool evaluate() /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
    /*public*/ int getChildCount() override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup() override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe() override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

    QObject* bself() override {return this;}
    QObject* pself() override {return this;}


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

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt)override;
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

private:
     static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<OBlock*>* _oblockHandle;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;
    /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
    /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
    /*private*/ OBlock::OBlockStatus::STATES _oblockState = OBlock::OBlockStatus::Unoccupied;
    /*private*/ QString _stateReference = "";
    /*private*/ QString _stateLocalVariable = "";
    /*private*/ QString _stateFormula = "";
    /*private*/ ExpressionNode* _stateExpressionNode;
    /*private*/ QString getNewState() /*throws JmriException*/;
    /*private*/ void parseStateFormula() /*throws ParserException*/;
    /*private*/ void parseFormula()/* throws ParserException */;

};

#endif // EXPRESSIONOBLOCK_H
