#ifndef ACTIONSIGNALMAST_H
#define ACTIONSIGNALMAST_H

#include "abstractdigitalaction.h"
#include "vetoablechangelistener.h"
#include "logixng/expressionnode.h"
#include "logixng/namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "signalmast.h"
#include "threadingutil.h"
#include "jmriexception.h"
#include <QAtomicPointer>

class ActionSignalMast : public AbstractDigitalAction, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener)

public:
    class OperationType
    {
    public:
    //    Aspect(Bundle.getMessage("SignalMastOperationType_Aspect")),
    //    Lit(Bundle.getMessage("SignalMastOperationType_Lit")),
    //    NotLit(Bundle.getMessage("SignalMastOperationType_NotLit")),
    //    Held(Bundle.getMessage("SignalMastOperationType_Held")),
    //    NotHeld(Bundle.getMessage("SignalMastOperationType_NotHeld")),
    //    PermissiveSmlDisabled(Bundle.getMessage("SignalMastOperationType_PermissiveSmlDisabled")),
    //    PermissiveSmlNotDisabled(Bundle.getMessage("SignalMastOperationType_PermissiveSmlNotDisabled"));
        enum TYPE {None, Aspect, Lit, NotLit, Held, NotHeld, PermissiveSmlDisabled, PermissiveSmlNotDisabled};

        static QString toString(TYPE t)
        {
            switch(t)
            {
             case None: return "None";
             case Aspect: return tr("Aspect");
            case Lit: return tr("Lit");
            case NotLit: return tr("not lit");
            case Held: return tr("Held");
            case NotHeld: return tr("not held");
            case PermissiveSmlDisabled: return tr("permissive sml disabled");
            case PermissiveSmlNotDisabled: return tr("permissive sml not disabled");
            }
            return "";
        }
        /*public*/ static TYPE valueOf(QString s)
        {
            if(s=="Aspect") return Aspect;
            if(s=="Lit") return Lit;
            if(s=="not lit") return NotLit;
            if(s=="Held") return Held;
            if(s=="not held") return NotHeld;
            if(s=="permissive sml disabled") return PermissiveSmlDisabled;
            if(s=="permissive sml not disabled") return PermissiveSmlNotDisabled;
            throw new IllegalArgumentException("invalid operation");
        }
        /*public*/ static QList<TYPE> values()
        {
            return {None, Aspect, Lit, NotLit, Held, NotHeld, PermissiveSmlDisabled, PermissiveSmlNotDisabled};
        }
    };
    explicit ActionSignalMast(QObject *parent = nullptr);
    /*public*/ ActionSignalMast(QString sys, QString user, QObject* parent= nullptr)
            /*throws BadUserNameException, BadSystemNameException*/;
    /*public*/ Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
    /*public*/ void setSignalMast(/*@Nonnull*/ QString signalMastName);
    /*public*/ void setSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle);
    /*public*/ void setSignalMast(/*@Nonnull*/ SignalMast* signalMast);
    /*public*/ void removeSignalMast();
    /*public*/ NamedBeanHandle<SignalMast*>* getSignalMast();
    /*public*/ void setExampleSignalMast(/*@Nonnull*/ QString signalMastName);
    /*public*/ void setExampleSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle);
    /*public*/ void setExampleSignalMast(/*@Nonnull*/ SignalMast* signalMast);
    /*public*/ void removeExampleSignalMast();
    /*public*/ NamedBeanHandle<SignalMast*>* getExampleSignalMast();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing();
    /*public*/ void setReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable) ;
    /*public*/ QString getLocalVariable();
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula();
    /*public*/ void setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
    /*public*/ NamedBeanAddressing::TYPE getOperationAddressing() ;
    /*public*/ void setOperationType(OperationType::TYPE operationType);
    /*public*/ OperationType::TYPE getOperationType();
    /*public*/ void setOperationReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getOperationReference();
    /*public*/ void setOperationLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getOperationLocalVariable();
    /*public*/ void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getOperationFormula();
    /*public*/ void setAspectAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
    /*public*/ NamedBeanAddressing::TYPE getAspectAddressing() ;
    /*public*/ void setAspect(QString aspect);
    /*public*/ QString getAspect();
    /*public*/ void setAspectReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getAspectReference();
    /*public*/ void setAspectLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getAspectLocalVariable();
    /*public*/ void setAspectFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getAspectFormula();
    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/ override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup() override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

    QObject* bself() override {return this;}

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

private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<SignalMast*>* _signalMastHandle = nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode = nullptr;

    /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
    /*private*/ OperationType::TYPE _operationType = OperationType::Aspect;
    /*private*/ QString _operationReference = "";
    /*private*/ QString _operationLocalVariable = "";
    /*private*/ QString _operationFormula = "";
    /*private*/ ExpressionNode* _operationExpressionNode;

    /*private*/ NamedBeanAddressing::TYPE _aspectAddressing = NamedBeanAddressing::Direct;
    /*private*/ QString _signalMastAspect = "";
    /*private*/ QString _aspectReference = "";
    /*private*/ QString _aspectLocalVariable = "";
    /*private*/ QString _aspectFormula = "";
    /*private*/ ExpressionNode* _aspectExpressionNode;

    /*private*/ NamedBeanHandle<SignalMast*>* _exampleSignalMastHandle = nullptr;
    /*private*/ void parseFormula() /*throws ParserException*/ ;
    /*private*/ void parseOperationFormula() /*throws ParserException*/;
    /*private*/ void parseAspectFormula() /*throws ParserException*/ ;
    /*private*/ QString getNewAspect(ConditionalNG* conditionalNG) /*throws JmriException*/ ;
    /*private*/ OperationType::TYPE getOperation() /*throws JmriException*/;

    friend class ASM_ThreadingUtil;
};

class ASM_ThreadingUtil : public ThreadActionWithJmriException
{
  Q_OBJECT
  ActionSignalMast* _asm;
  QAtomicPointer<JmriException> ref;
  ActionSignalMast::OperationType::TYPE operation;
  ConditionalNG* conditionalNG;
  SignalMast* signalMast;

 public:
  ASM_ThreadingUtil(SignalMast* signalMast, ConditionalNG* conditionalNG, QAtomicPointer<JmriException> ref,
                    ActionSignalMast::OperationType::TYPE operation, ActionSignalMast* _asm)
  {
   this->signalMast = signalMast;
   this->conditionalNG = conditionalNG;
   this->_asm = _asm;
   this->operation = operation;
   this->ref = ref;
  }
  void run()
  {
   try {
       switch (operation) {
       case ActionSignalMast::OperationType::Aspect:
       {
               QString newAspect = _asm->getNewAspect(conditionalNG);
               if (!newAspect.isEmpty()) {
                   signalMast->setAspect(newAspect);
               }
               break;
       }
           case ActionSignalMast::OperationType::Lit:
               signalMast->setLit(true);
               break;
           case ActionSignalMast::OperationType::NotLit:
               signalMast->setLit(false);
               break;
           case ActionSignalMast::OperationType::Held:
               signalMast->setHeld(true);
               break;
           case ActionSignalMast::OperationType::NotHeld:
               signalMast->setHeld(false);
               break;
           case ActionSignalMast::OperationType::PermissiveSmlDisabled:
               signalMast->setPermissiveSmlDisabled(true);
               break;
           case ActionSignalMast::OperationType::PermissiveSmlNotDisabled:
               signalMast->setPermissiveSmlDisabled(false);
               break;
           default:
               throw new JmriException("Unknown enum: "+ActionSignalMast::OperationType::toString(_asm->_operationType));
       }
   } catch (JmriException* e) {
       ref.storeRelease(e);
   }
  }
};

#endif // ACTIONSIGNALMAST_H
