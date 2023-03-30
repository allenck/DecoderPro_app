#ifndef ACTIONREPORTER_H
#define ACTIONREPORTER_H

#include "abstractdigitalaction.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "vetoablechangelistener.h"

class Memory;
class Reporter;
class ExpressionNode;
class ActionReporter : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  ActionReporter(QString sys, QString user, QObject* parent = nullptr);
  class ReporterValue{
   public:
    enum VAL {CopyCurrentReport, CopyLastReport, CopyState};
    static QList<VAL> values() {return {CopyCurrentReport, CopyLastReport, CopyState};}
    static QString toString(VAL v)
    {
     switch (v) {
     case CopyCurrentReport: return tr("Current Report");
     case CopyLastReport: return tr("Last Report");
     case CopyState: return tr("State");
     }
     return "";
    }
    static VAL valueOf(QString s)
    {
     if(s == tr("Current Report")) return CopyCurrentReport;
     if(s == tr("Last Report")) return CopyLastReport;
     if(s == tr("State")) return CopyState;

     throw new IllegalArgumentException();
    }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ override;
  /*public*/  void setReporter(/*@Nonnull*/ QString reporterName) ;
  /*public*/  void setReporter(/*@Nonnull*/ Reporter* reporter) ;
  /*public*/  void setReporter(/*@Nonnull*/ NamedBeanHandle<Reporter*>* handle);
  /*public*/  void removeReporter();
  /*public*/  NamedBeanHandle<Reporter*>* getReporter() ;
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula() ;
  /*public*/  void setReporterValue(ReporterValue::VAL value);
  /*public*/  ReporterValue::VAL getReporterValue();
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName);
  /*public*/  void setMemory(/*@Nonnull*/ Memory* memory);
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle);
  /*public*/  void removeMemory();
  /*public*/  NamedBeanHandle<Memory*>* getMemory();
  /*public*/  void setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getDataAddressing();
  /*public*/  void setDataReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getDataReference();
  /*public*/  void setDataLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getDataLocalVariable();
  /*public*/  void setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getDataFormula();
  /*public*/  Category getCategory()  override;
  Reporter* getSourceReporter() /*throws JmriException*/ ;
  QVariant getReporterData(Reporter* reporter) /*throws JmriException*/ ;
  void updateDestination(QVariant data) /*throws JmriException*/;
  /*public*/  void execute() /*throws JmriException*/ override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */ override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe() override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) override;
  /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.tools.debugger.ActionReporter";}

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
//    /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}
 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Reporter*>* _reporterHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;

  /*private*/ ReporterValue::VAL _reporterValue = ReporterValue::CopyCurrentReport;

  /*private*/ NamedBeanAddressing::TYPE _dataAddressing = NamedBeanAddressing::Direct;
  /*private*/ QString _dataReference = "";
  /*private*/ QString _dataLocalVariable = "";
  /*private*/ QString _dataFormula = "";
  /*private*/ ExpressionNode* _dataExpressionNode;

  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle = nullptr;
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*private*/ void parseDataFormula() /*throws ParserException*/;

};

#endif // ACTIONREPORTER_H
