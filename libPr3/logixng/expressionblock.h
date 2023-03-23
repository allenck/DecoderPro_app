#ifndef EXPRESSIONBLOCK_H
#define EXPRESSIONBLOCK_H

#include "abstractdigitalexpression.h"
#include "block.h"
#include "logixng/namedbeanaddressing.h"
#include "is_isnot_enum.h"
#include "vetoablechangelistener.h"
#include "propertychangelistener.h"

class ExpressionNode;
class ExpressionBlock : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
public:
    /*public*/ ExpressionBlock(QString sys, QString user,QObject *parent=nullptr);

    class BlockState
    {
     public:
        enum VAL {None=0, Occupied=2, NotOccupied=4, Other=-1, Allocated=-2, ValueMatches=-3};
        static QString toString(VAL v)
        {
            switch (v) {
            case Occupied: return tr("Occupied");
            case NotOccupied: return tr("not Occupied");
            case Other: return tr("Other");
            case Allocated: return tr("Allocated");
            case ValueMatches: return tr("equal to");
            default:
                return "None";
            }
        }
        static VAL valueOf(QString s)
        {
            if(s ==tr("Occupied"))return Occupied;
            if(s ==tr("not Occupied"))return NotOccupied;
            if(s ==tr("Other"))return Other;
            if(s ==tr("Allocated"))return Allocated;
            if(s ==tr("equal to"))return ValueMatches;
            throw new IllegalArgumentException("invalid block state");
        }
        static QList<VAL> values()
        {
            return {None, Occupied, NotOccupied, Other, Allocated, ValueMatches};
        }
    };
    /*public*/ Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
    /*public*/ void setBlock(/*@Nonnull*/ QString blockName);
    /*public*/ void setBlock(/*@Nonnull*/ Block* block);
    /*public*/ void setBlock(/*@Nonnull*/ NamedBeanHandle<Block*>* handle);
    /*public*/ void removeBlock();
    /*public*/ NamedBeanHandle<Block*>* getBlock();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing();
    /*public*/ void setReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getLocalVariable();
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula();
    /*private*/ void parseFormula() /*throws ParserException*/;
    /*public*/ void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
    /*public*/ Is_IsNot_Enum::VAL get_Is_IsNot();
    /*public*/ void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getStateAddressing();
    /*public*/ void setBeanState(BlockState::VAL state);
    /*public*/ BlockState::VAL getBeanState();
    /*public*/ void setStateReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getStateReference();
    /*public*/ void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getStateLocalVariable();
    /*public*/ void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getStateFormula();
    /*private*/ void parseStateFormula() /*throws ParserException*/;
    /*public*/ void setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getDataAddressing();
    /*public*/ void setDataReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getDataReference();
    /*public*/ void setDataLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getDataLocalVariable();
    /*public*/ void setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getDataFormula();
    /*public*/ void setBlockValue(/*@Nonnull*/ QString value);
    /*public*/ QString getBlockValue();
    /*public*/ Category getCategory()override;
    /*public*/ bool isBlockAllocated(Block* block) ;
    /*public*/ bool evaluate() /*throws JmriException*/ override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale) override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass() override;
    /*public*/ void unregisterListenersForThisClass()  override;
    /*public*/ void disposeMe()override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
    /*public*/ QString getClass() const override
    {
        return "jmri.jmrit.logixng.expressions.ExpressionBlock";
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
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;
    /*public*/ void propertyChange(PropertyChangeEvent* evt)override;

private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<Block*>* _blockHandle = nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;

    /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;

    /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
    /*private*/ BlockState::VAL _blockState = BlockState::Occupied;
    /*private*/ QString _stateReference = "";
    /*private*/ QString _stateLocalVariable = "";
    /*private*/ QString _stateFormula = "";
    /*private*/ ExpressionNode* _stateExpressionNode;

    /*private*/ NamedBeanAddressing::TYPE _dataAddressing = NamedBeanAddressing::Direct;
    /*private*/ QString _dataReference = "";
    /*private*/ QString _dataLocalVariable = "";
    /*private*/ QString _dataFormula = "";
    /*private*/ ExpressionNode* _dataExpressionNode;

    /*private*/ QString _blockValue = "";
    /*private*/ void parseDataFormula() /*throws ParserException*/;
    /*private*/ QString getNewState() /*throws JmriException*/ ;
    /*private*/ QString getNewData() /*throws JmriException*/;

};

#endif // EXPRESSIONBLOCK_H
