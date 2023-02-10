#ifndef ACTIONSIGNALHEAD_H
#define ACTIONSIGNALHEAD_H

#include "abstractdigitalaction.h"
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "signalhead.h"
#include "expressionnode.h"
#include "atomicreference.h"
#include "threadingutil.h"
#include "jmriexception.h"
#include "defaultconditionalng.h"

class ActionSignalHead : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  ActionSignalHead(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  /*enum*/class OperationType {
//      Appearance(Bundle.getMessage("SignalHeadOperationType_Appearance")),
//      Lit(Bundle.getMessage("SignalHeadOperationType_Lit")),
//      NotLit(Bundle.getMessage("SignalHeadOperationType_NotLit")),
//      Held(Bundle.getMessage("SignalHeadOperationType_Held")),
//      NotHeld(Bundle.getMessage("SignalHeadOperationType_NotHeld"));
   public:
   enum TYPE {Appearance, Lit, NotLit, Held, NotHeld};
   /*public*/ static QList<TYPE> values()
   {
    return QList<TYPE>{Appearance, Lit, NotLit, Held, NotHeld};
   }

//      /*private*/ /*final*/ String _text;

//      /*private*/ OperationType(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/ static  QString toString(TYPE t) {
          switch(t)
          {
           case Appearance: return tr("appearance");
           case Lit: return tr("lit");
           case NotLit: return tr("not lit");
           case Held: return tr("held");
           case NotHeld: return tr("not held");
          }
          throw new IllegalAccessException();
      }

      /*public*/ static TYPE valueOf(QString s)
      {
       if(s== tr("appearance")) return Appearance;
       if(s== tr("lit")) return Lit;
       if(s== tr("not lit")) return NotLit;
       if(s== tr("held")) return Held;
       if(s== tr("not held")) return NotHeld;
       throw new IllegalArgumentException();
      }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  void setSignalHead(/*@Nonnull*/ QString signalHeadName);
  /*public*/  void setSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle);
  /*public*/  void setSignalHead(/*@Nonnull*/ SignalHead *signalHead);
  /*public*/  void removeSignalHead() ;
  /*public*/  NamedBeanHandle<SignalHead*>* getSignalHead();
  /*public*/  void setExampleSignalHead(/*@Nonnull*/ QString signalHeadName);
  /*public*/  void setExampleSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle);
  /*public*/  void setExampleSignalHead(/*@Nonnull*/ SignalHead* signalHead) ;
  /*public*/  void removeExampleSignalHead();
  /*public*/  NamedBeanHandle<SignalHead*>* getExampleSignalHead();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula();
  /*public*/  void setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getOperationAddressing();
  /*public*/  void setOperationType(OperationType::TYPE operationType);
  /*public*/  OperationType::TYPE getOperationType();
  /*public*/  void setOperationReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getOperationReference() ;
  /*public*/  void setOperationLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getOperationLocalVariable();
  /*public*/  void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getOperationFormula() ;
  /*public*/  void setAppearanceAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAppearanceAddressing() ;
  /*public*/  void setAppearance(int appearance) ;
  /*public*/  int getAppearance();
  /*public*/  void setAppearanceReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getAppearanceReference();
  /*public*/  void setAppearanceLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getAppearanceLocalVariable();
  /*public*/  void setAppearanceFormula(/*@Nonnull*/ QString formula)/* throws ParserException*/;
  /*public*/  QString getAppearanceFormula();
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
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
  /*private*/ NamedBeanHandle<SignalHead*>* _signalHeadHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;

  /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
  /*private*/ OperationType::TYPE _operationType = OperationType::Appearance;
  /*private*/ QString _operationReference = "";
  /*private*/ QString _operationLocalVariable = "";
  /*private*/ QString _operationFormula = "";
  /*private*/ ExpressionNode* _operationExpressionNode;

  /*private*/ NamedBeanAddressing::TYPE _appearanceAddressing = NamedBeanAddressing::Direct;
  /*private*/ int _signalHeadAppearance = SignalHead::DARK;
  /*private*/ QString _appearanceReference = "";
  /*private*/ QString _appearanceLocalVariable = "";
  /*private*/ QString _appearanceFormula = "";
  /*private*/ ExpressionNode* _appearanceExpressionNode;

  /*private*/ NamedBeanHandle<SignalHead*>* _exampleSignalHeadHandle = nullptr;

  /*private*/ void parseFormula() /*throws ParserException*/;
  /*private*/ void parseOperationFormula() /*throws ParserException*/ ;
  /*private*/ void parseAppearanceFormula() /*throws ParserException*/;
  /*private*/ int getAppearanceFromName(QString name);
  /*private*/ int getNewAppearance(ConditionalNG* conditionalNG) /*throws JmriException*/;
  /*private*/ OperationType::TYPE getOperation() /*throws JmriException*/;
//  OperationType::TYPE operation = getOperation();
  /*final*/ ConditionalNG* conditionalNG = getConditionalNG();
  friend class ActionSignalHead_Run;
};

class ActionSignalHead_Run : public ThreadActionWithJmriException
{
  Q_OBJECT
  AtomicReference<JmriException*>* ref;
  ActionSignalHead::OperationType::TYPE operation;
  ConditionalNG* conditionalNG;
  SignalHead* signalHead;
  ActionSignalHead* act;
 public:
  ActionSignalHead_Run(AtomicReference<JmriException*>* ref,
                       ActionSignalHead::OperationType::TYPE operation,
                       ConditionalNG* conditionalNG,
                       SignalHead* signalHead,
                       ActionSignalHead* act)
  {
   this->ref = ref;
   this->operation = operation;
   this->conditionalNG = conditionalNG;
   this->signalHead = signalHead;
   this->act = act;
  }
  void run()
  {
   try {
    switch (operation) {
       case ActionSignalHead::OperationType::Appearance:
       {
           int newAppearance = act->getNewAppearance(conditionalNG);
           if (newAppearance != -1) {
               signalHead->setAppearance(newAppearance);
           }
           break;
       }
       case ActionSignalHead::OperationType::Lit:
           signalHead->setLit(true);
           break;
       case ActionSignalHead::OperationType::NotLit:
           signalHead->setLit(false);
           break;
       case ActionSignalHead::OperationType::Held:
           signalHead->setHeld(true);
           break;
       case ActionSignalHead::OperationType::NotHeld:
           signalHead->setHeld(false);
           break;
//            case PermissiveSmlDisabled:
//                signalHead->setPermissiveSmlDisabled(true);
//                break;
//            case PermissiveSmlNotDisabled:
//                signalHead->setPermissiveSmlDisabled(false);
//                break;
       default:
           throw new JmriException("Unknown enum: "+ActionSignalHead::OperationType::toString(act->_operationType));
      }
   } catch (JmriException* e) {
       ref->set(e);
   }
  }
};

#endif // ACTIONSIGNALHEAD_H
