#ifndef EXPRESSIONENTRYEXIT_H
#define EXPRESSIONENTRYEXIT_H

#include "abstractdigitalexpression.h"
#include "namedbeanaddressing.h"
#include "destinationpoints.h"
#include "namedbeanhandle.h"
#include "expressionnode.h"
#include "is_isnot_enum.h"

class EntryExitState;
class ExpressionEntryExit : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
 public:
  ExpressionEntryExit(QObject* parent = nullptr) : AbstractDigitalExpression("", "") {}
  Q_INVOKABLE ExpressionEntryExit(QString sys, QString user, QObject* parent = nullptr);
  ~ExpressionEntryExit() {}
  ExpressionEntryExit(const ExpressionEntryExit&) : AbstractDigitalExpression("", "") {}
  class EntryExitState
  {
   public:
    enum STATE {Inactive, Active, Other};
    static QString toString(STATE state)
    {
     switch(state)
     {
     case Inactive: return tr("Inactive");
     case Active: return tr("Active");
     case Other: return tr("Other");
     }
    }
    static STATE fromString(QString s)
    {
     if(s == tr("Inactive")) return Inactive;
     if(s == tr("Active")) return Active;
     return Other;
    }
    static QList<STATE> values(){
    return  {Inactive, Active, Other};
    }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ override;
  /*public*/  void setDestinationPoints(/*@Nonnull*/ QString entryExitName);
  /*public*/  void setDestinationPoints(/*@Nonnull*/ NamedBeanHandle<DestinationPoints*>* handle);
  /*public*/  void setDestinationPoints(/*@Nonnull*/ DestinationPoints* destinationPoints);
  /*public*/  void removeDestinationPoints();
  /*public*/  NamedBeanHandle<DestinationPoints*>* getEntryExit();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable() ;
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula() ;
  /*public*/  void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
  /*public*/  Is_IsNot_Enum::VAL get_Is_IsNot();
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing() ;
  /*public*/  void setBeanState(EntryExitState::STATE state);
  /*public*/  EntryExitState::STATE getBeanState();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getStateReference();
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable) ;
  /*public*/  QString getStateLocalVariable();
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getStateFormula();
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;
  /*public*/  Category getCategory() override;
  /*public*/  bool evaluate() /*throws JmriException*/  override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/  override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt) override;
  /*public*/  void disposeMe() override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) override;
  /*public*/ QString getClass() const override
  {
      return "jmri.jmrit.logixng.expressions.ExpressionEntryExit";
  }

  QObject* self() override {return this;}
  QObject* bself() override {return this;}
  QObject* pself() override {return this;}
  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  ///*public*/ virtual void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ virtual QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ virtual QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ virtual int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ virtual QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<DestinationPoints*>* _entryDestinationPoints = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ EntryExitState::STATE _entryExitState = EntryExitState::Active;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*private*/ void parseStateFormula() ;
  /*private*/ QString getNewState() /*throws JmriException*/ ;

};
Q_DECLARE_METATYPE(ExpressionEntryExit)
#endif // EXPRESSIONENTRYEXIT_H
