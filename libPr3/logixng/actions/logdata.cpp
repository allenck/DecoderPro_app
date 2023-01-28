#include "logdata.h"
#include "loggerfactory.h"
#include "../defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "../abstractbase.h"
#include "../conditionalng.h"
#include "../defaultmemorymanager.h"
#include "../referenceutil.h"
#include "scriptoutput.h"
#include "jtextarea.h"

/**
 * This action logs some data.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
namespace Actions
{
 ///*public*/  class LogData extends AbstractDigitalAction
 //        implements PropertyChangeListener, VetoableChangeListener {

     /*public*/  LogData::LogData(QString sys, QString user, QObject* parent)
             /*throws BadUserNameException, BadSystemNameException*/
      : AbstractDigitalAction(sys, user, parent){
         //super(sys, user);
     }

     //@Override
     /*public*/  Base* LogData::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws ParserException*/ {
         DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
         QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
         QString userName = userNames->value(AbstractNamedBean::getSystemName());
         if (sysName == nullptr) sysName = manager->getAutoSystemName();
         LogData* copy = new LogData(sysName, userName);
         copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
         copy->setLogToLog(_logToLog);
         copy->setLogToScriptOutput(_logToScriptOutput);
         copy->setFormat(_format);
         copy->setFormatType(_formatType);
         for (Data data : *_dataList) {
             copy->getDataList()->append(Data(data));
         }
         return manager->registerAction(copy);
     }

     /*public*/  void LogData::setLogToLog(bool logToLog) {
         _logToLog = logToLog;
     }

     /*public*/  bool LogData::getLogToLog() {
         return _logToLog;
     }

     /*public*/  void LogData::setLogToScriptOutput(bool logToScriptOutput) {
         _logToScriptOutput = logToScriptOutput;
     }

     /*public*/  bool LogData::getLogToScriptOutput() {
         return _logToScriptOutput;
     }

     /*public*/  void LogData::setFormatType(FormatType::FORMATTYPE formatType) {
         _formatType = formatType;
     }

     /*public*/  LogData::FormatType::FORMATTYPE LogData::getFormatType() {
         return _formatType;
     }

     /*public*/  void LogData::setFormat(QString format) {
         _format = format;
     }

     /*public*/  QString LogData::getFormat() {
         return _format;
     }

     /*public*/  QList<LogData::Data>* LogData::getDataList() {
         return _dataList;
     }

     //@Override
     /*public*/  void LogData::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
 /*
         if ("CanDelete".equals(evt.getPropertyName())) { // No I18N
             if (evt.getOldValue() instanceof Memory) {
                 if (evt.getOldValue().equals(getMemory().getBean())) {
                     throw new PropertyVetoException(getDisplayName(), evt);
                 }
             }
         } else if ("DoDelete".equals(evt.getPropertyName())) { // No I18N
             if (evt.getOldValue() instanceof Memory) {
                 if (evt.getOldValue().equals(getMemory().getBean())) {
                     setMemory((Memory)null);
                 }
             }
         }
 */
     }

     /** {@inheritDoc} */
     //@Override
     /*public*/  Category LogData::getCategory() {
         return Category::OTHER;
     }

     /*private*/ QList<QVariant> LogData::getDataValues() /*throws JmriException*/ {
         QList<QVariant> values = QList<QVariant>();
         for (Data _data : *_dataList) {
             switch (_data._dataType) {
                 case DataType::LocalVariable:
                     values.append(getConditionalNG()->getSymbolTable()->getValue(_data._data));
                     break;

                 case DataType::Memory:
                 {
                     MemoryManager* memoryManager = (DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager");
#if 0
                     Memory* memory = memoryManager->getMemory(_data._data);
                     if (memory.isNull()) throw new IllegalArgumentException("Memory '" + _data._data + "' not found");
                     values.append(memory->getValue());
#endif
                     break;
                 }
                 case DataType::Reference:
                     values.append(ReferenceUtil::getReference(
                             getConditionalNG()->getSymbolTable(), _data._data));
                     break;

                 case DataType::Formula:
                     if (_data._expressionNode != nullptr) {
                         values.append(_data._expressionNode->calculate(getConditionalNG()->getSymbolTable()));
                     }

                     break;

                 default:
                     throw new IllegalArgumentException("_formatType has invalid value: "+FormatType::toString(_formatType));
             }
         }
         return values;
     }

     /** {@inheritDoc} */
     //@Override
     /*public*/  void LogData::execute() /*throws JmriException*/ {

         QString str;

         switch (_formatType) {
             case FormatType::FORMATTYPE::OnlyText:
                 str = _format;
                 break;

             case FormatType::FORMATTYPE::CommaSeparatedList:
             {
                 QString sb;// = new StringBuilder();
                 for (QVariant value : getDataValues()) {
                     if (sb.length() > 0) sb.append(", ");
                     sb.append(value != "" ? value.toString() : "null");
                 }
                 str = sb/*.toString()*/;
                 break;
             }
             case FormatType::FORMATTYPE::StringFormat:
#if 0
                 str = String.format(_format, getDataValues().toArray());
#endif
                 break;

             default:
                 throw new IllegalArgumentException("_formatType has invalid value: "+FormatType::toString(_formatType));
         }

         if (_logToLog) log->warn(str);
         if (_logToScriptOutput) ScriptOutput::getDefault()->getOutputArea()->append(str+"\n");

     }

     //@Override
     /*public*/  FemaleSocket* LogData::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
         throw new UnsupportedOperationException("Not supported.");
     }

     //@Override
     /*public*/  int LogData::getChildCount() {
         return 0;
     }

     //@Override
     /*public*/  QString LogData::getShortDescription(QLocale locale) {
         //return Bundle.getMessage(locale, "LogData_Short");
      return "Log data";
     }

     //@Override
     /*public*/  QString LogData::getLongDescription(QLocale locale) {
         //return Bundle.getMessage(locale, "LogData_Long");
         return "Log data";
     }

     /** {@inheritDoc} */
     //@Override
     /*public*/  void LogData::setup() {
         // Do nothing
     }

     /** {@inheritDoc} */
     //@Override
     /*public*/  void LogData::registerListenersForThisClass() {
         // Do nothing
     }

     /** {@inheritDoc} */
     //@Override
     /*public*/  void LogData::unregisterListenersForThisClass() {
         // Do nothing
     }

     /** {@inheritDoc} */
     //@Override
     /*public*/  void LogData::propertyChange(PropertyChangeEvent* evt) {
         getConditionalNG()->execute();
     }

     /** {@inheritDoc} */
     //@Override
     /*public*/  void LogData::disposeMe() {
     }


     /** {@inheritDoc} */
     //@Override
     /*public*/  void LogData::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
 /*
         log.debug("getUsageReport :: LogData: bean = {}, report = {}", cdl, report);
         for (NamedBeanReference namedBeanReference : _namedBeanReferences.values()) {
             if (namedBeanReference._handle != null) {
                 if (bean.equals(namedBeanReference._handle.getBean())) {
                     report.add(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription()));
                 }
             }
         }
 */
     }

#if 0
     /*public*/  enum FormatType {
         OnlyText(Bundle.getMessage("LogData_FormatType_TextOnly"), true, false),
         CommaSeparatedList(Bundle.getMessage("LogData_FormatType_CommaSeparatedList"), false, true),
         StringFormat(Bundle.getMessage("LogData_FormatType_StringFormat"), true, true);

         /*private*/ final String _text;
         /*private*/ final bool _useFormat;
         /*private*/ final bool _useData;

         /*private*/ FormatType(String text, bool useFormat, bool useData) {
             this._text = text;
             this._useFormat = useFormat;
             this._useData = useData;
         }

         //@Override
         /*public*/  String toString() {
             return _text;
         }

         /*public*/  bool getUseFormat() {
             return _useFormat;
         }

         /*public*/  bool getUseData() {
             return _useData;
         }

     }


     /*public*/  enum DataType {
         LocalVariable(Bundle.getMessage("LogData_Operation_LocalVariable")),
         Memory(Bundle.getMessage("LogData_Operation_Memory")),
         Reference(Bundle.getMessage("LogData_Operation_Reference")),
         Formula(Bundle.getMessage("LogData_Operation_Formula"));

         /*private*/ final String _text;

         /*private*/ DataType(String text) {
             this._text = text;
         }

         //@Override
         /*public*/  String toString() {
             return _text;
         }

     }


     /*public*/  static class Data {

         /*private*/ DataType _dataType = DataType.LocalVariable;
         /*private*/ String _data = "";
         /*private*/ ExpressionNode _expressionNode;

         /*public*/  Data(Data data) throws ParserException {
             _dataType = data._dataType;
             _data = data._data;
             calculateFormula();
         }

         /*public*/  Data(DataType dataType, String data) throws ParserException {
             _dataType = dataType;
             _data = data;
             calculateFormula();
         }

         /*private*/ void calculateFormula() throws ParserException {
             if (_dataType == DataType.Formula) {
                 Map<String, Variable> variables = new HashMap<>();
                 RecursiveDescentParser parser = new RecursiveDescentParser(variables);
                 _expressionNode = parser.parseExpression(_data);
             } else {
                 _expressionNode = null;
             }
         }

         /*public*/  void setDataType(DataType dataType) { _dataType = dataType; }
         /*public*/  DataType getDataType() { return _dataType; }

         /*public*/  void setData(String data) { _data = data; }
         /*public*/  String getData() { return _data; }

     }
#endif

     /*private*/ /*final*/ /*static*/ Logger*  LogData::log = LoggerFactory::getLogger("LogData");
}
