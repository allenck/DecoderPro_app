#ifndef EXPRESSIONS_LOGDATA_H
#define EXPRESSIONS_LOGDATA_H

#include "../abstractdigitalexpression.h"
#include "propertychangelistener.h"
#include "vetoablechangelistener.h"
#include "../expressionnode.h"
#include "../variable.h"
#include "../recursivedescentparser.h"
#include "../../memory.h"

namespace Expressions {

 class Data;
 class LogData : public AbstractDigitalExpression, public PropertyChangeListener, VetoableChangeListener
 {
   Q_OBJECT
   Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
  public:
   class FormatType
   {
    public:
    enum FORMATTYPE {OnlyText, CommaSeparatedList, StringFormat};
    static QString toString(FORMATTYPE type)
    {
     switch (type) {
      case OnlyText:
      return tr("Only text");
     case CommaSeparatedList:
      return tr("Comma separated list");
     case StringFormat:
      return tr("String. format");
     }
    }
    static FORMATTYPE fromString(QString s)
    {
      if(s == "Only text")
      return OnlyText;
      if(s == "Comma separated list")
       return CommaSeparatedList;
      if(s == "String. format")
       return StringFormat;
      throw new IllegalArgumentException(QString("Invalid value " + s));
    }
    static QList<FORMATTYPE> values() {return {OnlyText, CommaSeparatedList, StringFormat};};
   };
   class DataType
   {
    public:
     enum DATATYPE {LocalVariable, Memory, Reference, Formula};
     static QString toString(DATATYPE t)
     {
      switch (t)
      {
       case LocalVariable:
        return tr("Local variable");
      case Memory:
       return tr("Memory");
      case Reference:
       return tr("Reference");
      case Formula:
       return "Formula";
      }
     }
     static DATATYPE fromString(QString s)
     {
      if(s == tr("Local variable"))
       return LocalVariable;
      if(s == tr("Memory"))
       return Memory;
      if(s == tr("Reference"))
       return Reference;
      if(s == "Formula")
       return Formula;
      throw new IllegalArgumentException(QString("Invalid value " + s));
     }
   };
   /*public*/  /*static*/ class Data {

       /*private*/ DataType::DATATYPE _dataType = DataType::LocalVariable;
       /*private*/ QString _data = "";
       /*private*/ ExpressionNode* _expressionNode;
   public:
       /*public*/  Data(const Data& data) /*throws ParserException */{
           _dataType = data._dataType;
           _data = data._data;
           calculateFormula();
       }

       /*public*/  Data(DataType::DATATYPE dataType, QString data) /*throws ParserException*/ {
           _dataType = dataType;
           _data = data;
           calculateFormula();
       }

       /*private*/ void calculateFormula() /*throws ParserException*/ {
           if (_dataType == DataType::Formula) {
               QMap<QString, Variable*> variables = QMap<QString, Variable*>();
               RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
               _expressionNode = parser->parseExpression(_data);
           } else {
               _expressionNode = nullptr;
           }
       }

       /*public*/  void setDataType(DataType::DATATYPE dataType) { _dataType = dataType; }
       /*public*/  DataType::DATATYPE getDataType() const { return _dataType; }

       /*public*/  void setData(QString data) { _data = data; }
       /*public*/  QString getData() const { return _data; }
    friend class LogData;
   };
   Q_INVOKABLE LogData() : AbstractDigitalExpression("", ""){}
   Q_INVOKABLE LogData(QString sys, QString user, QObject* parent =0);
   ~LogData() {}
   LogData(const LogData&) : AbstractDigitalExpression("", "") {}
   /*public*/  Base* getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws ParserException*/override;
   /*public*/  void setResult(bool result);
   /*public*/  bool getResult();
   /*public*/  void setLogToLog(bool logToLog);
   /*public*/  bool getLogToLog();
   /*public*/  void setLogToScriptOutput(bool logToScriptOutput);
   /*public*/  bool getLogToScriptOutput();
   /*public*/  void setFormatType(FormatType::FORMATTYPE formatType);
   /*public*/  FormatType::FORMATTYPE getFormatType() ;
   /*public*/  void setFormat(QString format);
   /*public*/  QString getFormat();
   /*public*/  QList<Data> getDataList();
   /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;
   /*public*/  Category getCategory()override;
   /*public*/  bool evaluate() /*throws JmriException*/override;
   /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
   /*public*/  int getChildCount() override;
   /*public*/  QString getShortDescription(QLocale locale)override;
   /*public*/  QString getLongDescription(QLocale locale)override;
   /*public*/  void setup()override;
   /*public*/  void registerListenersForThisClass()override;
   /*public*/  void unregisterListenersForThisClass()override;
   /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
   /*public*/  void disposeMe()override;
   /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) override;

   QObject* bself() override {return this;}
   QObject* pself() override {return this;}

   /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
    AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
   }
   /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                     QString name, QString listenerRef) override {
    AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
   }
   /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
   // /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
   /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
   /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
   /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
   /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
    return AbstractNamedBean::getPropertyChangeListenersByReference(name);
   }
   void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

//   /*public*/  enum FormatType {
//       OnlyText(Bundle.getMessage("LogData_FormatType_TextOnly"), true, false),
//       CommaSeparatedList(Bundle.getMessage("LogData_FormatType_CommaSeparatedList"), false, true),
//       StringFormat(Bundle.getMessage("LogData_FormatType_StringFormat"), true, true);

//       /*private*/ final String _text;
//       /*private*/ final bool _useFormat;
//       /*private*/ final bool _useData;

//       /*private*/ FormatType(String text, bool useFormat, bool useData) {
//           this._text = text;
//           this._useFormat = useFormat;
//           this._useData = useData;
//       }

//       //@Override
//       /*public*/  String toString() {
//           return _text;
//       }

//       /*public*/  bool getUseFormat() {
//           return _useFormat;
//       }

//       /*public*/  bool getUseData() {
//           return _useData;
//       }

//   }
//   class


//   /*public*/  enum DataType {
//       LocalVariable(Bundle.getMessage("LogData_Operation_LocalVariable")),
//       Memory(Bundle.getMessage("LogData_Operation_Memory")),
//       Reference(Bundle.getMessage("LogData_Operation_Reference")),
//       Formula(Bundle.getMessage("LogData_Operation_Formula"));

//       /*private*/ final String _text;

//       /*private*/ DataType(String text) {
//           this._text = text;
//       }

//   /*public*/  QString toString()override;

  private:
   static Logger* log;
   /*private*/ bool _result = false;
   /*private*/ bool _logToLog = true;
   /*private*/ bool _logToScriptOutput = false;
   /*private*/ FormatType::FORMATTYPE _formatType = FormatType::FORMATTYPE::OnlyText;
   /*private*/ QString _format = "";
   /*private*/ /*final*/ QList<LogData::Data> _dataList = QList<LogData::Data>();
   /*private*/ QList<QVariant> getDataValues()  /*throws JmriException*/;
 };
}
Q_DECLARE_METATYPE(Expressions::LogData)
#endif // EXPRESSIONS_LOGDATA_H
