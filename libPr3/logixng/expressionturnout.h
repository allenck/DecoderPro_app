#ifndef EXPRESSIONTURNOUT_H
#define EXPRESSIONTURNOUT_H

#include "abstractdigitalexpression.h"
#include "propertychangelistener.h"
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "turnout.h"
#include "expressionnode.h"
#include "is_isnot_enum.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"

class TurnoutState;
class ExpressionTurnout : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  /*public*/  /*enum*/class TurnoutState {
//      Closed(Turnout.CLOSED, InstanceManager::getDefault(TurnoutManager.class).getClosedText()),
//      Thrown(Turnout.THROWN, InstanceManager::getDefault(TurnoutManager.class).getThrownText()),
//      Other(-1, Bundle.getMessage("TurnoutOtherStatus"));
   public:
    enum VAL {Closed, Thrown, Other};

      /*private*/ /*final*/ int _id;
      /*private*/ /*final*/ QString _text;

      /*private*/ TurnoutState(int id, QString text) {
          this->_id = id;
          this->_text = text;
      }

      static /*public*/  TurnoutState::VAL get(int id) {
          switch (id) {
              case Turnout::CLOSED:
                  return Closed;

              case Turnout::THROWN:
                  return Thrown;

              default:
                  return Other;
          }
      }

      /*public*/  int getID() {
          return _id;
      }

      //@Override
      /*public*/static  QString toString(VAL v) {
       switch (v) {
       case Closed: return ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getClosedText();
       case Thrown: ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getThrownText();
       default: return tr("Other");
       }
      }

      /*public*/ static  VAL valueOf(QString s)
      {
       if(s == ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getClosedText()) return Closed;
       if(s == ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getThrownText()) return Thrown;
       if(s== tr("Other")) return Other;
       throw new IllegalArgumentException(tr("invaid TurnoutState %1").arg(s));
      }
      static QList<VAL> values()
      {
      return {Closed, Thrown, Other};
      }
  };

  explicit ExpressionTurnout(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setTurnout(/*@Nonnull*/ QString turnoutName);
  /*public*/  void setTurnout(/*@Nonnull*/ NamedBeanHandle<Turnout*>* handle) ;
  /*public*/  void setTurnout(/*@Nonnull*/ Turnout* turnout);
  /*public*/  void removeTurnout();
  /*public*/  NamedBeanHandle<Turnout*>* getTurnout();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable) ;
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
  /*public*/  QString getFormula() ;
  /*public*/  void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
  /*public*/  Is_IsNot_Enum::VAL get_Is_IsNot();
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing();
  /*public*/  void setBeanState(TurnoutState::VAL state);
  /*public*/  TurnoutState::VAL getBeanState();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getStateReference();
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getStateLocalVariable();
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getStateFormula();
  /*public*/  Category getCategory()override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
    /*public*/ QString getClass() const override
    {
        return "jmri.jmrit.logixng.expressions.ExpressionTurnout";
    }

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException */override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
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
  /*private*/ NamedBeanHandle<Turnout*>* _turnoutHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ TurnoutState::VAL _turnoutState = TurnoutState::Thrown;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*private*/ void parseStateFormula() /*throws ParserException*/;
  /*private*/ QString getNewState() /*throws JmriException*/ ;

};

#endif // EXPRESSIONTURNOUT_H
