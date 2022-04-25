#ifndef EXPRESSIONLOCALVARIABLE_H
#define EXPRESSIONLOCALVARIABLE_H

#include "abstractdigitalexpression.h"
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "memory.h"

class CompareTo;
class VariableOperation;
class ExpressionLocalVariable : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  /*public*/  /*enum*/class VariableOperation {
//      LessThan(Bundle.getMessage("LocalVariableOperation_LessThan"), true),
//      LessThanOrEqual(Bundle.getMessage("LocalVariableOperation_LessThanOrEqual"), true),
//      Equal(Bundle.getMessage("LocalVariableOperation_Equal"), true),
//      GreaterThanOrEqual(Bundle.getMessage("LocalVariableOperation_GreaterThanOrEqual"), true),
//      GreaterThan(Bundle.getMessage("LocalVariableOperation_GreaterThan"), true),
//      NotEqual(Bundle.getMessage("LocalVariableOperation_NotEqual"), true),
//      IsNull(Bundle.getMessage("LocalVariableOperation_IsNull"), false),
//      IsNotNull(Bundle.getMessage("LocalVariableOperation_IsNotNull"), false),
//      MatchRegex(Bundle.getMessage("LocalVariableOperation_MatchRegEx"), true),
//      NotMatchRegex(Bundle.getMessage("LocalVariableOperation_NotMatchRegEx"), true);

//      /*private*/ final String _text;
//      /*private*/ final boolean _extraValue;

//      /*private*/ VariableOperation(String text, boolean extraValue) {
//          this._text = text;
//          this._extraValue = extraValue;
//      }

   public:
    enum TYPE {LessThan, LessThanOrEqual, Equal, GreaterThanOrEqual, GreaterThan, NotEqual,
              IsNull,  IsNotNull, MatchRegex, NotMatchRegex};
    /*public*/ static QList<TYPE> values()
    {
     return QList<TYPE>{LessThan, LessThanOrEqual, Equal, GreaterThanOrEqual, GreaterThan, NotEqual,
       IsNull,  IsNotNull, MatchRegex, NotMatchRegex};
    }
      //@Override
      /*public*/ static  QString toString(TYPE t) {
          switch(t)
          {
          case LessThan: return tr("is less than");
          case LessThanOrEqual:  return tr("is less than or equal");
          case Equal: return tr("is equal");
          case GreaterThanOrEqual:  return tr("is greater than or equal");
          case GreaterThan:  return tr("is greater than");
          case NotEqual:  return tr("is not equal");
          case IsNull:  return tr("is null");
          case  IsNotNull:  return tr("is not null");
          case MatchRegex:  return tr("does match regular expression");
          case NotMatchRegex: return tr("does not match regular expression");
          }
          throw new IllegalArgumentException();
      }

    /*public*/ static  TYPE valueOf(QString s)
    {
     if(s == tr("is less than")) return LessThan;
     if(s == tr("is less than or equal")) return LessThanOrEqual;
     if(s == tr("is equal")) return Equal;
     if(s == tr("is greater than or equal")) return GreaterThanOrEqual;
     if(s == tr("is greater than")) return GreaterThan;
     if(s == tr("s not equal")) return NotEqual;
     if(s == tr("is not null")) return IsNotNull;
     if(s == tr("does match regular expression")) return MatchRegex;
     if(s == tr("does not match regular expression")) return NotMatchRegex;
     throw new IllegalArgumentException();
    }
      /*public*/ static bool hasExtraValue(TYPE t) {
          if(t==IsNull) return false;
          return true;
      }

  };


  /*public*/  /*enum*/ class CompareTo {
//      Value(Bundle.getMessage("LocalVariable_CompareTo_Value")),
//      Memory(Bundle.getMessage("LocalVariable_CompareTo_Memory")),
//      LocalVariable(Bundle.getMessage("LocalVariable_CompareTo_LocalVariable")),
//      RegEx(Bundle.getMessage("LocalVariable_CompareTo_RegularExpression"));

//      /*private*/ final String _text;

//      /*private*/ CompareTo(String text) {
//          this._text = text;
//      }
public:
    enum TYPE {Value, Memory, LocalVariable, RegEx};
      //@Override
      /*public*/static QString toString(TYPE t) {
         switch (t)
         {
         case Value:  return tr("Value");
         case Memory:  return tr("Memory");
         case LocalVariable:  return tr("Local Variable");
         case RegEx: return tr("Regular expression");
         }
         throw new IllegalArgumentException();
      }
    /*public*/ static  TYPE valueOf(QString s)
    {
     if(s == tr("Value")) return Value;
     if(s == tr("Memory")) return Memory;
     if(s == tr("Local Variable")) return LocalVariable;
     if(s == tr("Regular expression")) return RegEx;
     throw new IllegalArgumentException();
    }

  };

  ExpressionLocalVariable(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  void setLocalVariable(QString variableName);
  /*public*/  QString getLocalVariable();
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle);
  /*public*/  void setMemory(/*CheckForNull*/ Memory* memory);
  /*public*/  void removeMemory();
  /*public*/  NamedBeanHandle<Memory*>* getMemory() ;
  /*public*/  void setOtherLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getOtherLocalVariable();
  /*public*/  void setConstantValue(QString constantValue);
  /*public*/  QString getConstantValue();
  /*public*/  void setRegEx(QString regEx);
  /*public*/  QString getRegEx();
  /*public*/  void setListenToMemory(bool listenToMemory);
  /*public*/  bool getListenToMemory();
  /*public*/  void setVariableOperation(VariableOperation::TYPE variableOperation) ;
  /*public*/  VariableOperation::TYPE getVariableOperation();
  /*public*/  void setCompareTo(CompareTo::TYPE compareTo);
  /*public*/  CompareTo::TYPE getCompareTo() ;
  /*public*/  void setCaseInsensitive(bool caseInsensitive);
  /*public*/  bool getCaseInsensitive();
  /*public*/  Category* getCategory()override;
  /*public*/  bool evaluate()override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

  QObject* bself() override{return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

 private:
  static Logger* log;
  /*private*/ QString _localVariable;
  /*private*/ VariableOperation::TYPE _variableOperation = VariableOperation::Equal;
  /*private*/ CompareTo::TYPE _compareTo = CompareTo::Value;
  /*private*/ bool _caseInsensitive = false;
  /*private*/ QString _constantValue = "";
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle;
  /*private*/ QString _otherLocalVariable = "";
  /*private*/ QString _regEx = "";
  /*private*/ bool _listenToMemory = true;
//    /*private*/ boolean _listenToMemory = false;
  /*private*/ QString getString(QVariant o) ;
  /*private*/ bool compare(QString value1, QString value2, bool caseInsensitive);
  /*private*/ bool matchRegex(QString memoryValue, QString regex);

};

#endif // EXPRESSIONLOCALVARIABLE_H
