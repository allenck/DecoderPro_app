#ifndef EXPRESSIONWARRANT_H
#define EXPRESSIONWARRANT_H

#include "abstractdigitalexpression.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "is_isnot_enum.h"
#include "vetoablechangelistener.h"

class ExpressionNode;
class Warrant;
class ExpressionWarrant : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
public:
    class WarrantState
    {
      public:
        enum TYPE {RouteFree, RouteOccupied, RouteAllocated, RouteSet, TrainRunning};

        static QString toString(TYPE t)
        {
            switch (t) {
            case RouteFree: return tr("Route Free");
            case RouteOccupied: return tr("Route Occupied");
            case RouteAllocated: return tr("Route Allocated");
            case RouteSet: return tr("Route Set");
            case TrainRunning: return tr("Train Running");
            }
        }
        static TYPE valueOf(QString s)
        {
         if(s == tr("Route Free")) return RouteFree;
         if(s == tr("Route Occupied")) return RouteOccupied;;
         if(s == tr("Route Allocated")) return RouteAllocated;
         if(s == tr("Route Set")) return RouteSet;
         if(s == tr("Train Running")) return TrainRunning;
            throw new IllegalArgumentException(s);
        }
        static QList<TYPE> values() {return {RouteFree, RouteOccupied, RouteAllocated, RouteSet, TrainRunning};}
    };
     ExpressionWarrant(QString sys, QString user, QObject *parent = nullptr);
     /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ override;
     /*public*/ void setWarrant(/*@Nonnull*/ QString warrantName) ;
     /*public*/ void setWarrant(/*@Nonnull*/ NamedBeanHandle<Warrant*>* handle);
     /*public*/ void setWarrant(/*@Nonnull*/ Warrant* warrant) ;
     /*public*/ void removeWarrant();
     /*public*/ NamedBeanHandle<Warrant*>* getWarrant();
     /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
     /*public*/ NamedBeanAddressing::TYPE getAddressing();
     /*public*/ void setReference(/*@Nonnull*/ QString reference);
     /*public*/ QString getReference() ;
     /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
     /*public*/ QString getLocalVariable();
     /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
     /*public*/ QString getFormula();
     /*private*/ void parseFormula() /*throws ParserException*/;
     /*public*/ void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
     /*public*/ Is_IsNot_Enum::VAL get_Is_IsNot();
     /*public*/ void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
     /*public*/ NamedBeanAddressing::TYPE getStateAddressing();
     /*public*/ void setBeanState(WarrantState::TYPE state);
     /*public*/ WarrantState::TYPE getBeanState();
     /*public*/ void setStateReference(/*@Nonnull*/ QString reference) ;
     /*public*/ QString getStateReference();
     /*public*/ void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
     /*public*/ QString getStateLocalVariable();
     /*public*/ void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
     /*public*/ QString getStateFormula() ;
     /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;
     /*public*/ Category getCategory()  override;
     /*public*/ bool evaluate() /*throws JmriException*/ override;
     /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/  override;
     /*public*/ int getChildCount() override;
     /*public*/ QString getShortDescription(QLocale locale)  override;
     /*public*/ QString getLongDescription(QLocale locale) override;
     /*public*/ void setup()  override;
     /*public*/ void registerListenersForThisClass() override;
     /*public*/ void unregisterListenersForThisClass() override;
     /*public*/ void propertyChange(PropertyChangeEvent* evt) override;
     /*public*/ void disposeMe() override;
     /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) override;
     /*public*/ QString getClass() const override
     {
         return "jmri.jmrit.logixng.expressions.ExpressionWarrant";
     }

     QObject* bself() override {return this;}
     QObject* pself() override {return this;}
     QObject* self() override {return this;}


     /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener)override{
      AbstractNamedBean::addPropertyChangeListener(listener);
     }
         /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
          AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
         }
         /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                           QString name, QString listenerRef) override {
          AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
         }
         /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
     //    /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
         /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
         /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
         /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
         /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
          return AbstractNamedBean::getPropertyChangeListenersByReference(name);
         }

private:
     static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<Warrant*>* _warrantHandle = nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;
    /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
    /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
    /*private*/ WarrantState::TYPE _warrantState = WarrantState::RouteAllocated;
    /*private*/ QString _stateReference = "";
    /*private*/ QString _stateLocalVariable = "";
    /*private*/ QString _stateFormula = "";
    /*private*/ ExpressionNode* _stateExpressionNode;
     /*private*/ void parseStateFormula() /*throws ParserException*/ ;
     /*private*/ QString getNewState() /*throws JmriException*/;

};

#endif // EXPRESSIONWARRANT_H
