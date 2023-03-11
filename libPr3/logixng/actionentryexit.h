#ifndef ACTIONENTRYEXIT_H
#define ACTIONENTRYEXIT_H

#include "abstractdigitalaction.h"
#include "namedbeanhandle.h"
#include "namedbeanaddressing.h"
#include "vetoablechangelistener.h"
#include "threadingutil.h"
#include "destinationpoints.h"
#include "entryexitpairs.h"
#include "instancemanager.h"


class DestinationPoints;
class ExpressionNode;
class ActionEntryExit : public AbstractDigitalAction, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener)
public:
    ActionEntryExit(QString sys, QString user, QObject *parent = nullptr);
    class Operation
    {
    public:
        enum TYPE {SetNXPairEnabled, SetNXPairDisabled, SetNXPairSegment};
        static QString toString(TYPE t)
        {
          switch(t)
          {
          case SetNXPairEnabled: return tr("Set NX Pair Enabled");
          case SetNXPairDisabled: return tr("Set NX Pair Disabled");
          case SetNXPairSegment: return tr("Set NX Pair Segment Active / Inactive");
          }
        }
        static TYPE valueOf(QString s)
        {
            if(s == tr("Set NX Pair Enabled")) return SetNXPairEnabled;
            if(s == tr("Set NX Pair Disabled")) return SetNXPairDisabled;
            if(s == tr("Set NX Pair Segment Active / Inactive")) return SetNXPairSegment;
            throw IllegalArgumentException("bad Operation");
        }
        static QList<TYPE> values() {return {SetNXPairEnabled, SetNXPairDisabled, SetNXPairSegment};}
    };
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/override;
    /*public*/ void setDestinationPoints(/*@Nonnull*/ QString entryExitName);
    /*public*/ void setDestinationPoints(/*@Nonnull*/ NamedBeanHandle<DestinationPoints*>* handle);
    /*public*/ void setDestinationPoints(/*@Nonnull*/ DestinationPoints* entryExit);
    /*public*/ void removeDestinationPoints() ;
    /*public*/ NamedBeanHandle<DestinationPoints*>* getDestinationPoints();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing)/* throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing();
    /*public*/ void setReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getLocalVariable();
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getFormula() ;
    /*public*/ void setOperationAddressing(NamedBeanAddressing::TYPE addressing)/* throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getOperationAddressing() ;
    /*public*/ void setOperationDirect(Operation::TYPE state);
    /*public*/ ActionEntryExit::Operation::TYPE getOperationDirect();
    /*public*/ void setOperationReference(/*@Nonnull*/ QString reference) ;
    /*public*/ QString getOperationReference();
    /*public*/ void setOperationLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getOperationLocalVariable();
    /*public*/ void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getLockFormula();
    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/ override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale) override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe() override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

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
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

public slots:
    /*public*/ void vetoableChange(PropertyChangeEvent* evt)/* throws java.beans.PropertyVetoException*/override;

private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<DestinationPoints*>* _destinationPointsHandle = nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;
    /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
    /*private*/ Operation::TYPE _operationDirect = Operation::SetNXPairEnabled;
    /*private*/ QString _operationReference = "";
    /*private*/ QString _operationLocalVariable = "";
    /*private*/ QString _operationFormula = "";
    /*private*/ ExpressionNode* _operationExpressionNode;
    /*private*/ void parseFormula() /*throws ParserException*/ ;
    /*private*/ QString getNewLock() /*throws JmriException*/;
    /*private*/ void parseLockFormula() /*throws ParserException*/;

};
#if 1
class AEE_ThreadingUtil : public ThreadActionWithJmriException
{
  Q_OBJECT
  ActionEntryExit::Operation::TYPE theOper;
  DestinationPoints* entryExit;
 public:
  AEE_ThreadingUtil(ActionEntryExit::Operation::TYPE theOper, DestinationPoints* entryExit) {
   this->theOper = theOper;
   this->entryExit = entryExit;
  }

    void run()
    {
                switch (theOper) {
                    case ActionEntryExit::Operation::SetNXPairEnabled:
                        entryExit->setEnabled(true);
                        break;
                    case ActionEntryExit::Operation::SetNXPairDisabled:
                        entryExit->setEnabled(false);
                        break;
                    case ActionEntryExit::Operation::SetNXPairSegment:
                        ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->
                                setSingleSegmentRoute(entryExit->getSystemName());
                        break;
                    default:
                        throw new IllegalArgumentException("invalid oper state: " + ActionEntryExit::Operation::toString(theOper));
            };
    }
};
#endif
#endif // ACTIONENTRYEXIT_H
