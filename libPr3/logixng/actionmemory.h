#ifndef ACTIONMEMORY_H
#define ACTIONMEMORY_H

#include "abstractdigitalaction.h"
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "memory.h"
#include "expressionnode.h"
#include "threadingutil.h"
#include "atomicreference.h"

class JmriException;
class MemoryOperation;
class ActionMemory : public AbstractDigitalAction, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  Q_INVOKABLE explicit ActionMemory(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  /*enum*/class  MemoryOperation {
//      SetToNull(Bundle.getMessage("ActionMemory_MemoryOperation_SetToNull")),
//      SetToString(Bundle.getMessage("ActionMemory_MemoryOperation_SetToString")),
//      CopyVariableToMemory(Bundle.getMessage("Variable")),
//      CopyMemoryToMemory(Bundle.getMessage("ActionMemory_MemoryOperation_CopyMemoryToMemory")),
//      CopyTableCellToMemory(Bundle.getMessage("ActionMemory_MemoryOperation_CopyTableCellToMemory")),
//      CalculateFormula(Bundle.getMessage("ActionMemory_MemoryOperation_CalculateFormula"));
  public:
    enum TYPE {SetToNull, SetToString, CopyVariableToMemory, CopyMemoryToMemory, CopyTableCellToMemory, CalculateFormula};
//      /*private*/ /*final*/ String _text;

//      /*private*/ MemoryOperation(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/static  QString toString(TYPE t) {
     switch (t) {
     case SetToNull: return tr("Null");
     case SetToString: return tr("Constant");
     case CopyVariableToMemory: return tr("Variable");
     case CopyMemoryToMemory: return tr("Memory");
     case CopyTableCellToMemory: return  tr("Table");
     case CalculateFormula: return tr("Formula");
     }
   }

    /*public*/static  TYPE valueOf(QString s) {
     if(s=="Null") return SetToNull;
     if(s=="Constant") return SetToString;
     if(s=="Variable") return CopyVariableToMemory;
     if(s=="Memory") return CopyMemoryToMemory;
     if(s=="Table") return CopyTableCellToMemory;
     if(s=="Formula") return CalculateFormula;
     throw new IllegalArgumentException();
   }


  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle);
  /*public*/  void setMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeMemory();
  /*public*/  NamedBeanHandle<Memory*>* getMemory();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable() ;
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula() ;
  /*public*/  void setMemoryOperation(MemoryOperation::TYPE state) /*throws ParserException*/;
  /*public*/  MemoryOperation::TYPE getMemoryOperation();
  /*public*/  void setOtherConstantValue(QString constantValue);
  /*public*/  QString getConstantValue();
  /*public*/  void setOtherMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setOtherMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle);
  /*public*/  void setOtherMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeOtherMemory() ;
  /*public*/  NamedBeanHandle<Memory*>* getOtherMemory() ;
  /*public*/  void setListenToMemory(bool listenToMemory);
  /*public*/  bool getListenToMemory();
  /*public*/  void setOtherTableCell(/*@Nonnull*/ QString tableCell) ;
  /*public*/  QString getOtherTableCell();
  /*public*/  static QString convertTableReference(QString string, bool toReference);
  /*public*/  void setOtherLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getOtherLocalVariable();
  /*public*/  void setOtherFormula(QString formula) /*throws ParserException */;
  /*public*/  QString getOtherFormula();
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

  QObject* pself() override{return this;}
  QObject* bself() override{return this;}
  QObject* self() override{return this;}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;
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
 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle =nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode = nullptr;
  /*private*/ NamedBeanHandle<Memory*>* _otherMemoryHandle = nullptr;
  /*private*/ MemoryOperation::TYPE _memoryOperation = MemoryOperation::SetToString;
  /*private*/ QString _otherConstantValue = "";
  /*private*/ QString _otherTableCell = "";
  /*private*/ QString _otherLocalVariable = "";
  /*private*/ QString _otherFormula = "";
  /*private*/ ExpressionNode* _otherExpressionNode = nullptr;
  /*private*/ bool _listenToMemory = true;
  //    /*private*/ boolean _listenToMemory = false;
  /*private*/ void parseOtherFormula() /*throws ParserException */;
  /*private*/ void addRemoveVetoListener();
  /*private*/ void parseFormula() /*throws ParserException*/;

  friend class ActionMemory_Run;
};
class ActionMemory_Run : public ThreadActionWithJmriException{
  Q_OBJECT
  ActionMemory* actionMemory;
  Memory* memory;
  ConditionalNG* conditionalNG;
  //std::atomic<JmriException*>* ref;
  AtomicReference<JmriException*>* ref;
 public:
  ActionMemory_Run(AtomicReference<JmriException*>* ref, ConditionalNG* conditionalNG, Memory* memory, ActionMemory* actionMemory) {
   this->ref = ref;
   this->conditionalNG = conditionalNG;
   this->memory = memory;
   this->actionMemory = actionMemory;}
  void run();
};

#endif // ACTIONMEMORY_H
