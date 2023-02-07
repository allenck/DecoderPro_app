#ifndef ACTIONTURNOUTLOCK_H
#define ACTIONTURNOUTLOCK_H

#include "abstractdigitalaction.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "turnout.h"
#include "expressionnode.h"
#include "vetoablechangelistener.h"
#include "threadingutil.h"

class ActionTurnoutLock : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit ActionTurnoutLock(QString sys, QString user, QObject *parent = nullptr);

  /*public*/ /*enum*/class TurnoutLock {
//      Lock(Bundle.getMessage("TurnoutLock_Lock")),
//      Unlock(Bundle.getMessage("TurnoutLock_Unlock")),
//      Toggle(Bundle.getMessage("TurnoutLock_Toggle"));
   public:
    enum ACT {Lock, Unlock, Toggle};

//      private final String _text;

//      private TurnoutLock(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/static QString toString(ACT v) {
       switch (v) {
       case Lock: return tr("Lock");
       case Unlock: return tr("Unlock");
       case Toggle: return tr("Toggle");
       }
       throw new IllegalArgumentException();
      }
    static ACT valueOf(QString s)
    {
     if(s == tr("Lock")) return Lock;
     if(s == tr("Unlock")) return Unlock;
     if(s == tr("Toggle")) return Toggle;
     throw new IllegalArgumentException();
    }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setTurnout(/*@Nonnull*/ QString turnoutName);
  /*public*/  void setTurnout(/*@Nonnull*/ NamedBeanHandle<Turnout*>* handle);
  /*public*/  void setTurnout(/*@Nonnull*/ Turnout* turnout);
  /*public*/  void removeTurnout();
  /*public*/  NamedBeanHandle<Turnout*>* getTurnout() ;
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference() ;
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula() ;
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*public*/  void setLockAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getLockAddressing();
  /*public*/  void setTurnoutLock(TurnoutLock::ACT state);
  /*public*/  TurnoutLock::ACT getTurnoutLock();
  /*public*/  void setLockReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getLockReference();
  /*public*/  void setLockLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLockLocalVariable();
  /*public*/  void setLockFormula(/*Nonnull*/ QString formula) /*throws ParserException*/ ;
  /*public*/  QString getLockFormula();
  /*public*/  Category getCategory() override;
  /*public*/  void execute() /*throws JmriException*/  override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()  override;
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale)  override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe() override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

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
 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Turnout*>* _turnoutHandle;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ NamedBeanAddressing::TYPE _lockAddressing = NamedBeanAddressing::Direct;
  /*private*/ TurnoutLock::ACT _turnoutLock = TurnoutLock::Unlock;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;
  /*private*/ void parseLockFormula() /*throws ParserException*/ ;
  /*private*/ QString getNewLock() /*throws JmriException*/;

  friend class ATLRun;
};

class ATLRun : public ThreadActionWithJmriException
{
  Q_OBJECT
  ActionTurnoutLock::TurnoutLock::ACT theLock;
  Turnout* turnout;
 public:
  ATLRun(ActionTurnoutLock::TurnoutLock::ACT theLock , Turnout* turnout) {this->theLock = theLock; this->turnout = turnout;}
  void run(){
   if (theLock == ActionTurnoutLock::TurnoutLock::Lock) {
       turnout->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
   } else if (theLock == ActionTurnoutLock::TurnoutLock::Unlock) {
       turnout->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, false);
   }
  }
};

#endif // ACTIONTURNOUTLOCK_H
