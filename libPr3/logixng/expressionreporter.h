#ifndef EXPRESSIONREPORTER_H
#define EXPRESSIONREPORTER_H

#include "abstractdigitalexpression.h"
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "reporter.h"
#include "memory.h"

class ExpressionReporter : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
 public:
  class ReporterOperation
  {
   public:
    enum RO {LessThan, LessThanOrEqual, Equal, GreaterThanOrEqual, GreaterThan, NotEqual, IsNull, IsNotNull,
            MatchRegex, NotMatchRegex};
    static QString toString(RO t)
    {
     switch(t)
     {
     case LessThan: return "";
     case LessThanOrEqual: return "is less than or equal";
     case Equal: return "is equal";
     case GreaterThanOrEqual: return "is greater than or equal";
     case GreaterThan: return "is greater than";
     case NotEqual: return "is not equal";
     case IsNull: return "is null";
     case IsNotNull: return "is not null";
     case MatchRegex: return "does match regular expression";
     case NotMatchRegex: return "does not match regular expression";
     }
    }
    static RO fromString(QString s)
    {
     if(s == "is less than") return LessThan;
     if(s == "is less than or equal") return LessThanOrEqual;
     if(s == "is equal") return Equal;
     if(s == "is greater than or equal") return GreaterThanOrEqual;
     if(s == "is greater than") return GreaterThan;
     if(s == "is not equal") return NotEqual;
     if(s == "is null") return IsNull;
     if(s == "is not null") return IsNotNull;
     if(s == "does match regular expression") return MatchRegex;
     if(s == "does not match regular expression") return NotMatchRegex;
     throw new IllegalArgumentException(tr("bad value ") + s);
    }
    static bool hasExtraValue(RO t)
    {
     if(t == IsNull || t == IsNotNull) return false;
     return true;
    }
    static QList<RO> values;
  };
  class ReporterValue
  {
   public:
    enum RV {CurrentReport, LastReport, State};
    static QString toString(RV t)
    {
     switch(t)
     {
      case CurrentReport: return "Current Report";
     case LastReport: return "Last Report";
     case State: return "State";
     }
    }
    static RV fromString(QString s)
    {
     if(s == "Current Report") return CurrentReport;
     if(s == "Last Report") return LastReport;
     if(s == "State") return State;
     throw new IllegalArgumentException(tr("bad value ") + s);
    }
    static QList<RV> values;// = {CurrentReport, LastReport, State};
  };

  class CompareTo //:QObject
  {
    //Q_OBJECT
   public:
    enum CT {Value, Memory, LocalVariable, RegEx};
    static QString toString(CT t){
     switch (t) {
     case Value: return tr("Value");
     case Memory: return tr("Memory");
     case LocalVariable: return tr("Local variable");
     case RegEx: return tr("Regular expression");
     }
    }
    static CT fromString(QString s)
    {
     if(s == "Value") return Value;
     if(s == "Memory") return Memory;
     if(s == "Local variable") return LocalVariable;
     if(s == "Regular expression") return RegEx;
      throw new IllegalArgumentException(tr("bad value ") + s);
    }
  };

  Q_INVOKABLE ExpressionReporter(QString sys, QString user, QObject* parent = nullptr);
  ~ExpressionReporter() {}
  ExpressionReporter(const ExpressionReporter&) : AbstractDigitalExpression("", "") {}
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  void setReporter(/*@Nonnull*/ QString reporterName) ;
  /*public*/  void setReporter(/*@Nonnull*/ NamedBeanHandle<Reporter*>* handle);
  /*public*/  void setReporter(/*@Nonnull*/ Reporter* reporter);
  /*public*/  void removeReporter();
  /*public*/  NamedBeanHandle<Reporter*>* getReporter();
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle);
  /*public*/  void setMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void removeMemory();
  /*public*/  NamedBeanHandle<Memory*>* getMemory();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setConstantValue(QString constantValue);
  /*public*/  QString getConstantValue();
  /*public*/  void setRegEx(QString regEx) ;
  /*public*/  QString getRegEx();
  /*public*/  void setListenToMemory(bool listenToMemory);
  /*public*/  bool getListenToMemory();
  /*public*/  void setReporterValue(ReporterValue::RV reporterValue);
  /*public*/  ReporterValue::RV getReporterValue();
  /*public*/  void setReporterOperation(ReporterOperation::RO reporterOperation);
  /*public*/  ReporterOperation::RO getReporterOperation();
  /*public*/  void setCompareTo(CompareTo::CT compareTo);
  /*public*/  CompareTo::CT getCompareTo();
  /*public*/  void setCaseInsensitive(bool caseInsensitive);
  /*public*/  bool getCaseInsensitive();
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) override;
  /*public*/  Category getCategory()override;
  /*public*/  bool evaluate()override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
  /*public*/  void disposeMe()override;
#if 0
  /*public*/  enum ReporterValue {
      CurrentReport(Bundle.getMessage("Reporter_Value_CurrentReport")),
      LastReport(Bundle.getMessage("Reporter_Value_LastReport")),
      State(Bundle.getMessage("Reporter_Value_State"));

      /*private*/ final String _text;

      /*private*/ ReporterValue(String text) {
          this._text = text;
      }

      //@Override
      /*public*/  String toString() {
          return _text;
      }
  }


  /*public*/  enum ReporterOperation {
      LessThan(Bundle.getMessage("ReporterOperation_LessThan"), true),
      LessThanOrEqual(Bundle.getMessage("ReporterOperation_LessThanOrEqual"), true),
      Equal(Bundle.getMessage("ReporterOperation_Equal"), true),
      GreaterThanOrEqual(Bundle.getMessage("ReporterOperation_GreaterThanOrEqual"), true),
      GreaterThan(Bundle.getMessage("ReporterOperation_GreaterThan"), true),
      NotEqual(Bundle.getMessage("ReporterOperation_NotEqual"), true),
      IsNull(Bundle.getMessage("ReporterOperation_IsNull"), false),
      IsNotNull(Bundle.getMessage("ReporterOperation_IsNotNull"), false),
      MatchRegex(Bundle.getMessage("ReporterOperation_MatchRegEx"), true),
      NotMatchRegex(Bundle.getMessage("ReporterOperation_NotMatchRegEx"), true);

      /*private*/ final String _text;
      /*private*/ final boolean _extraValue;

      /*private*/ ReporterOperation(String text, boolean extraValue) {
          this._text = text;
          this._extraValue = extraValue;
      }

      //@Override
      /*public*/  String toString() {
          return _text;
      }

      /*public*/  boolean hasExtraValue() {
          return _extraValue;
      }

  }


  /*public*/  enum CompareTo {
      Value(Bundle.getMessage("Reporter_CompareTo_Value")),
      Memory(Bundle.getMessage("Reporter_CompareTo_Memory")),
      LocalVariable(Bundle.getMessage("Reporter_CompareTo_LocalVariable")),
      RegEx(Bundle.getMessage("Reporter_CompareTo_RegularExpression"));

      /*private*/ final String _text;

      /*private*/ CompareTo(String text) {
          this._text = text;
      }

      //@Override
      /*public*/  String toString() {
          return _text;
      }

  }
#endif
  /** {@inheritDoc} */
  //@Override
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
  /*public*/ QString getClass() const override
  {
      return "jmri.jmrit.logixng.expressions.ExpressionReporter";
  }


  QObject* self() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

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
  /*private*/ NamedBeanHandle<Reporter*>* _reporterHandle;

  /*private*/ ReporterValue::RV _reporterValue = ReporterValue::CurrentReport;
  /*private*/ ReporterOperation::RO _reporterOperation = ReporterOperation::Equal;
  /*private*/ CompareTo::CT _compareTo = CompareTo::Value;

  /*private*/ bool _caseInsensitive = false;
  /*private*/ QString _constantValue = "";
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle;
  /*private*/ QString _localVariable = "";
  /*private*/ QString _regEx = "";
  /*private*/ bool _listenToMemory = true;
//    /*private*/ boolean _listenToMemory = false;
  /*private*/ QString getString(QVariant o);
  /*private*/ bool compare(QString value1, QString value2, bool caseInsensitive);
  /*private*/ bool matchRegex(QString reporterValue, QString regex);

};
//Q_DECLARE_METATYPE(ExpressionReporter)
#endif // EXPRESSIONREPORTER_H
