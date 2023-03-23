#ifndef EXPRESSIONMEMORY_H
#define EXPRESSIONMEMORY_H

#include "abstractdigitalexpression.h"
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "memory.h"

class ExpressionMemory : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:/*public*/  /*enum*/class MemoryOperation {
//   LessThan(Bundle.getMessage("MemoryOperation_LessThan"), true),
//   LessThanOrEqual(Bundle.getMessage("MemoryOperation_LessThanOrEqual"), true),
//   Equal(Bundle.getMessage("MemoryOperation_Equal"), true),
//   GreaterThanOrEqual(Bundle.getMessage("MemoryOperation_GreaterThanOrEqual"), true),
//   GreaterThan(Bundle.getMessage("MemoryOperation_GreaterThan"), true),
//   NotEqual(Bundle.getMessage("MemoryOperation_NotEqual"), true),
//   IsNull(Bundle.getMessage(""), false),
//   IsNotNull(Bundle.getMessage("MemoryOperation_IsNotNull"), false),
//   MatchRegex(Bundle.getMessage("MemoryOperation_MatchRegEx"), true),
//   NotMatchRegex(Bundle.getMessage("MemoryOperation_NotMatchRegEx"), true);
   public:
 enum TYPE {LessThan, LessThanOrEqual, Equal, GreaterThanOrEqual, GreaterThan, NotEqual, IsNull, IsNotNull, MatchRegex, NotMatchRegex};

//   /*private*/ /*final*/ QString _text;
//   /*private*/ /*final*/ bool _extraValue;

//   /*private*/ MemoryOperation(QString text, bool extraValue) {
//       this->_text = text;
//       this->_extraValue = extraValue;
//   }
   /*public*/ static QList<TYPE> values()
   {
    return QList<TYPE>{LessThan, LessThanOrEqual, Equal, GreaterThanOrEqual, GreaterThan, NotEqual, IsNull, IsNotNull, MatchRegex, NotMatchRegex};
   }

   //@Override
   /*public*/ static QString toString(TYPE t) {
    switch (t)
    {
     case LessThan: return tr("is less than");
     case LessThanOrEqual: return tr("is less than or equal");
     case Equal: return tr("is equal");
     case GreaterThanOrEqual: return tr("is greater than or equal");
     case GreaterThan: return tr("is greater than");
     case NotEqual: return tr("is not equal");
     case IsNull: return tr("is null");
     case IsNotNull:return tr("is not null");
     case MatchRegex: return tr("does match regular expression");
     case NotMatchRegex:return tr("does not match regular expression");
    default:
     throw new IllegalArgumentException("Invalid type");
    }
   }

   /*public*/  bool static hasExtraValue(TYPE t) {
       if(t == IsNull || t == IsNotNull) return false;
       return true;
   }
   /*public*/ static TYPE valueOf(QString s)
   {
    if(s== tr("is less than")) return LessThan;
    if(s== tr("is less than or equal")) return LessThanOrEqual;
    if(s== tr("is equal")) return Equal;
    if(s== tr("is greater than or equal")) return GreaterThanOrEqual;
    if(s== tr("is greater than")) return GreaterThan;
    if(s== tr("is not equal")) return NotEqual;
    if(s== tr("is null")) return IsNull;
    if(s== tr("is not null")) return IsNotNull;
    if(s== tr("does match regular expression")) return MatchRegex;
    if(s== tr("does not match regular expression")) return MatchRegex;
    throw new IllegalArgumentException();
   }
};


/*public*/  /*enum*/class  CompareTo {
//   Value(Bundle.getMessage("Memory_CompareTo_Value")),
//   Memory(Bundle.getMessage("Memory_CompareTo_Memory")),
//   LocalVariable(Bundle.getMessage("Memory_CompareTo_LocalVariable")),
//   RegEx(Bundle.getMessage("Memory_CompareTo_RegularExpression"));
   public:
    enum TYPE {Value, Memory, LocalVariable, RegEx};

   /*private*/ /*final*/ QString _text;

   /*private*/ CompareTo(QString text) {
       this->_text = text;
   }

   //@Override
   /*public*/ static QString toString(TYPE t) {
       switch(t)
       {
       case Value: return tr("Value");
       case Memory: return tr("Memory");
       case LocalVariable: return tr("Local variable");
       case RegEx: return tr("Regular expression");
      }
       throw new IllegalArgumentException("invalid compare type");
   }
    /*public*/ static TYPE valueOf(QString s)
    {
     if(s == tr("Value")) return Value;
     if(s == tr("Memory")) return Memory;
     if(s == tr("Local variable")) return LocalVariable;
     if(s == tr("Regular expression")) return RegEx;
     throw new IllegalArgumentException();
    }

};

  explicit ExpressionMemory(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle);
  /*public*/  void setMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeMemory() ;
  /*public*/  NamedBeanHandle<Memory*>* getMemory();
  /*public*/  void setOtherMemory(/*@Nonnull*/ QString memoryName) ;
  /*public*/  void setOtherMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) ;
  /*public*/  void setOtherMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeOtherMemory() ;
  /*public*/  NamedBeanHandle<Memory*>* getOtherMemory() ;
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setConstantValue(QString constantValue);
  /*public*/  QString getConstantValue();
  /*public*/  void setRegEx(QString regEx);
  /*public*/  QString getRegEx() ;
  /*public*/  void setListenToOtherMemory(bool listenToOtherMemory);
  /*public*/  bool getListenToOtherMemory();
  /*public*/  void setMemoryOperation(MemoryOperation::TYPE memoryOperation);
  /*public*/  MemoryOperation::TYPE getMemoryOperation();
  /*public*/  void setCompareTo(CompareTo::TYPE compareTo);
  /*public*/  CompareTo::TYPE getCompareTo();
  /*public*/  void setCaseInsensitive(bool caseInsensitive);
  /*public*/  bool getCaseInsensitive();
  /*public*/  Category getCategory() override;
  /*public*/  bool evaluate() override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
    /*public*/ QString getClass() const override
    {
        return "jmri.jmrit.logixng.expressions.ExpressionMemory";
    }

  QObject* bself() override{return (QObject*)this;}
  QObject* self() override{return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}

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
  /*public*/ QList<QString> getListenerRefs() override {
      return AbstractNamedBean::getListenerRefs();
  }
  /*public*/ int getNumPropertyChangeListeners() override {
      return  AbstractNamedBean::getNumPropertyChangeListeners();
  }
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
  void addPropertyChangeListener(PropertyChangeListener* l) override {
      AbstractNamedBean::addPropertyChangeListener(l);
  }

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;

 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle = nullptr;
  /*private*/ MemoryOperation::TYPE _memoryOperation = MemoryOperation::Equal;
  /*private*/ CompareTo::TYPE _compareTo = CompareTo::Value;
  /*private*/ bool _caseInsensitive = false;
  /*private*/ QString _constantValue = "";
  /*private*/ NamedBeanHandle<Memory*>* _otherMemoryHandle=nullptr;
  /*private*/ QString _localVariable = "";
  /*private*/ QString _regEx = "";
  /*private*/ bool _listenToOtherMemory = true;
//    /*private*/ boolean _listenToOtherMemory = false;
  /*private*/ void addRemoveVetoListener();
  /*private*/ QString getString(QVariant o);
  /*private*/ bool compare(QString value1, QString value2, bool caseInsensitive);
  /*private*/ bool matchRegex(QString memoryValue, QString regex);

};

#endif // EXPRESSIONMEMORY_H
