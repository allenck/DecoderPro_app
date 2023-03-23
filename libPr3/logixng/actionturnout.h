#ifndef ACTIONTURNOUT_H
#define ACTIONTURNOUT_H

#include "abstractdigitalaction.h"
#include "turnout.h"
#include "namedbeanhandle.h"
#include "namedbeanaddressing.h"
#include "expressionnode.h"
#include "instancemanager.h"
#include "threadingutil.h"

class ActionTurnout : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit ActionTurnout(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  class TurnoutState {
//      Closed(Turnout.CLOSED, InstanceManager.getDefault(TurnoutManager.class).getClosedText()),
//      Thrown(Turnout.THROWN, InstanceManager.getDefault(TurnoutManager.class).getThrownText()),
//      Toggle(TOGGLE_ID, Bundle.getMessage("TurnoutToggleStatus"));
   public:
   enum STATE {Closed, Thrown, Toggle};

//      /*private*/ /*final*/ int _id;
//      /*private*/ /*final*/ String _text;

//      /*private*/ TurnoutState(int id, String text) {
//          this._id = id;
//          this._text = text;
//      }

      static /*public*/  TurnoutState::STATE get(int id) {
          switch (id) {
              case Turnout::CLOSED:
                  return Closed;

              case Turnout::THROWN:
                  return Thrown;

//              case TOGGLE_ID:
//                  return Toggle;

              default:
                  throw new IllegalArgumentException("invalid turnout state");
          }
      }

//      /*public*/ static int getID( TYPE _id) {
//          return _id;
//      }

      //@Override
      /*public*/  static QString toString(STATE _id) {
           switch(_id)
           {
            case Closed:
             ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getClosedText();
           case Thrown:
            ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getThrownText();
           case Toggle:
            return tr("Toggle");

           }
      };

      static STATE valueOf(QString s)
      {
       if(s == tr("Closed")) return Closed;
       if(s == tr("Thrown")) return Thrown;
       if(s == tr("Toggle")) return Toggle;
       throw new IllegalArgumentException("invalid turnout state");
      }
      static QList<STATE> values() {return {Closed, Thrown, Toggle};};
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setTurnout(/*@Nonnull*/ QString turnoutName);
  /*public*/  void setTurnout(/*@Nonnull*/ NamedBeanHandle<Turnout*>* handle);
  /*public*/  void setTurnout(/*@Nonnull*/ Turnout* turnout);
  /*public*/  void removeTurnout() ;
  /*public*/  NamedBeanHandle<Turnout*>* getTurnout();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing() ;
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula();
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing();
  /*public*/  void setBeanState(TurnoutState::STATE state) ;
  /*public*/  TurnoutState::STATE getBeanState();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getStateReference();
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getStateLocalVariable() ;
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getStateFormula();
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
    /*public*/  QString getClass() const override
    {
     return "jmri.jmrit.logixng.actions.ActionTurnout";
    }

    QObject* self() override {return this;}
    QObject* bself() override {return this;}


  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  ///*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Turnout*>* _turnoutHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode = nullptr;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ TurnoutState::STATE _turnoutState = TurnoutState::Thrown;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode=nullptr;
  // This constant is only used internally in TurnoutState but must be outside
  // the enum.
  /*private*/ static /*final*/ int TOGGLE_ID;// = -1;
  /*private*/ void parseStateFormula() /*throws ParserException*/;
  /*private*/ QString getNewState() /*throws JmriException*/;

};

class ToggleTurnout : public ThreadActionWithJmriException
{
  Q_OBJECT
  Turnout* turnout;
  ActionTurnout::TurnoutState::STATE state;
 public:
  ToggleTurnout(Turnout* turnout, ActionTurnout::TurnoutState::STATE state) {
   this->turnout = turnout;
   this->state = state;
  }
  void run()
  {
   if (state == ActionTurnout::TurnoutState::Toggle) {
       if (turnout->getKnownState() == Turnout::CLOSED) {
           turnout->setCommandedState(Turnout::THROWN);
       } else {
           turnout->setCommandedState(Turnout::CLOSED);
       }
   } else {
       turnout->setCommandedState(state);
   }

  }
};

#endif // ACTIONTURNOUT_H
