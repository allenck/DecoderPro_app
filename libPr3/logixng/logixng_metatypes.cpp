#include "logixng_metatypes.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixngmanagerxml.h"
#include "defaultanalogactionmanagerxml.h"
#include "defaultnamedtablemanagerxml.h"
#include "defaultstringexpressionmanagerxml.h"
#include "defaultdigitalbooleanactionmanagerxml.h"
#include "defaultdigitalexpressionmanagerxml.h"
#include "analogformulaswing.h"
#include "analogexpressionanalogioswing.h"
#include "analogexpressionconstantswing.h"
#include "analogexpressionmemoryswing.h"
#include "timesincemidnightswing.h"
#include "analogmanyswing.h"
#include "analogactionmemoryswing.h"
#include "digitalbooleanmanyswing.h"
#include "digitalbooleanonchangeswing.h"
#include "expressionsensorswing.h"
#include "antecedentswing.h"
#include "trueswing.h"
#include "orswing.h"
#include "digitalformulaswing.h"
#include "falseswing.h"
#include "tableforeachswing.h"
#include  "functionmanager.h"
#include "tableforeachxml.h"
#include "analogmanyxml.h"
#include "analogactionlightintensityswing.h"
#include "forswing.h"
#include "ifthenelseswing.h"
#include "actionpositionableswing.h"
#include "digitalmanyswing.h"
#include "defaultmaleanalogactionsocketxml.h"
#include "defaultmaleanalogexpressionsocketxml.h"
#include "defaultmaledigitalbooleanactionsocketxml.h"
#include "defaultmaledigitalexpressionsocketxml.h"
#include "defaultmalestringactionsocketxml.h"
#include "defaultmalestringexpressionsocketxml.h"
#include "stringformulaswing.h"
#include "andswing.h"
#include "notswing.h"
#include "expressionsensorxml.h"
#include "orxml.h"
#include "andxml.h"
#include "logixngmoduletableaction.h"
#include "logixngtableaction.h"
#include "logixngtabletableaction.h"
#include "defaultconditionalngmanagerxml.h"
#include "analogactionmemoryxml.h"
#include "defaultstringactionmanagerxml.h"
#include "stringexpressionconstantxml.h"
#include "stringexpressionmemoryxml.h"
#include "stringformulaxml.h"
#include "expressionlightxml.h"
#include "actionsensorxml.h"
#include "actionsensorswing.h"
#include "ifthenelsexml.h"
#include "digitalformulaxml.h"
#include "holdswing.h"
#include "actionblockswing.h"
#include "actionblockxml.h"
#include "actionclockswing.h"
#include "actionclockxml.h"
#include "actionlistenonbeansswing.h"
#include "actionlistenonbeansxml.h"
#include "actionlocalvariablexml.h"
#include "actionlocalvariableswing.h"
#include "defaultcsvnamedtablexml.h"
#include "antecedentxml.h"
#include "defaultmodulemanagerxml.h"
#include "notxml.h"
#include "actionsignalheadswing.h"
#include "analogexpressionconstantxml.h"
#include "analogexpressionanalogioxml.h"
#include "analogformulaxml.h"
#include "analogexpressionmemoryxml.h"
#include "actionsignalheadxml.h"
#include "analogactionlightintensityxml.h"
#include "digitalbooleanmanyxml.h"
#include "actionpositionablexml.h"
#include "stringactionmemoryxml.h"
#include "stringactionmemoryswing.h"
#include "stringmanyxml.h"
#include "stringmanyswing.h"
#include "clipboardmanyxml.h"
#include "lastresultofdigitalexpressionswing.h"
#include "lastresultofdigitalexpressionxml.h"
#include "expressionsignalheadxml.h"
#include "expressionsignalheadswing.h"
#include "expressionlocalvariablexml.h"
#include "expressionlocalvariableswing.h"
#include "expressionmemoryxml.h"
#include "expressionmemoryswing.h"
#include "actionpowerswing.h"
#include "actionpowerxml.h"
#include "expressionpowerswing.h"
#include "expressionpowerxml.h"
#include "forxml.h"
#include "digitalmanyxml.h"
#include "actionlightxml.h"
#include "actionlightswing.h"
#include "expressionreferenceswing.h"
#include "expressionreferencexml.h"
#include "defaultdigitalactionmanagerxml.h"
#include "actions/logdata.h"
#include "actions/logdataswing.h"
#include "actions/logdataxml.h"
#include "expressions/ex_logdata.h"
#include "expressions/ex_logdataswing.h"
#include "expressions/ex_logdataxml.h"
#include "defaultanalogexpressionmanagerxml.h"
#include "expressionreporterswing.h"
#include "expressionreporterxml.h"
#include "sequenceswing.h"
#include "expressions/ex_digitalcallmoduleswing.h"
#include "actions/digitalcallmoduleswing.h"
#include "expressionentryexitxml.h"
#include "expressionentryexitswing.h"
#include "triggeronceswing.h"
#include "triggeroncexml.h"
#include "defaultmaledigitalactionsocketxml.h"
#include "digitalbooleanonchangexml.h"
#include "executedelayedswing.h"
#include "executedelayedxml.h"
#include "sequencexml.h"
#include "logixxml.h"
#include "logixswing.h"
#include "actionmemoryswing.h"
#include "actionmemoryxml.h"
#include "actionsignalmastswing.h"
#include "actionsignalmastxml.h"
#include "expressionsignalmastswing.h"
#include "expressionsignalmastxml.h"
#include "expressionlightswing.h"
#include "expressionblockswing.h"
#include "expressionblockxml.h"
#include "expressionconditionalswing.h"
#include "expressionconditionalxml.h"
#include "actionturnoutlockswing.h"
#include "actionturnoutlockxml.h"

/*static*/ bool LogixNG_Metatypes::ng_done = false;

LogixNG_Metatypes::LogixNG_Metatypes(QObject *parent) : QObject(parent)
{
   qRegisterMetaType<DefaultLogixNGManager>("DefaultLogixNGManager");
   qRegisterMetaType<DefaultLogixNGManagerXml>("DefaultLogixNGManagerXml");
   qRegisterMetaType<DefaultAnalogActionManagerXml>("DefaultAnalogActionManagerXml");
   qRegisterMetaType<DefaultNamedTableManagerXml>("DefaultNamedTableManagerXml");
   qRegisterMetaType<DefaultStringExpressionManagerXml>("DefaultStringExpressionManagerXml");
   qRegisterMetaType<DefaultDigitalBooleanActionManagerXml>("DefaultDigitalBooleanActionManagerXml");
   qRegisterMetaType<DefaultDigitalExpressionManagerXml>("DefaultDigitalExpressionManagerXml");
   qRegisterMetaType<FunctionManager>("FunctionManager");
   qRegisterMetaType<TableForEachXml>("TableForEachXml");
   qRegisterMetaType<AnalogManyXml>("AnalogManyXml");
   qRegisterMetaType<OrXml>("OrXml");
   qRegisterMetaType<AndXml>("AndXml");
   qRegisterMetaType<LogixNGModuleTableAction>("LogixNGModuleTableAction");
   qRegisterMetaType<LogixNGTableAction>("LogixNGTableAction");
   qRegisterMetaType<LogixNGTableTableAction>("LogixNGTableTableAction");
   qRegisterMetaType<DefaultConditionalNGManagerXml>("DefaultConditionalNGManagerXml");
   qRegisterMetaType<AnalogActionMemoryXml>("AnalogActionMemoryXml");
   qRegisterMetaType<DefaultMaleAnalogActionSocketXml>("DefaultMaleAnalogActionSocketXml");
   qRegisterMetaType<DefaultMaleAnalogExpressionSocketXml>("DefaultMaleAnalogExpressionSocketXml");
   qRegisterMetaType<DefaultMaleDigitalBooleanActionSocketXml>("DefaultMaleDigitalBooleanActionSocketXml");
   qRegisterMetaType<DefaultMaleDigitalExpressionSocketXml>("DefaultMaleDigitalExpressionSocketXml");
   qRegisterMetaType<DefaultMaleStringActionSocketXml>("DefaultMaleStringActionSocketXml");
   qRegisterMetaType<DefaultMaleStringExpressionSocketXml>("DefaultMaleStringExpressionSocketXml");
   qRegisterMetaType<ExpressionSensorXml>("ExpressionSensorXml");
   qRegisterMetaType<DefaultStringActionManagerXml>("DefaultStringActionManagerXml");
   qRegisterMetaType<StringExpressionConstantXml>("StringExpressionConstantXml");
   qRegisterMetaType<StringExpressionMemoryXml>("StringExpressionMemoryXml");
   qRegisterMetaType<StringFormulaXml>("StringFormulaXml");
   qRegisterMetaType<ExpressionLightXml>("ExpressionLightXml");
   qRegisterMetaType<ActionSensorXml>("ActionSensorXml");
   qRegisterMetaType<IfThenElseXml>("IfThenElseXml");
   qRegisterMetaType<DigitalFormulaXml>("DigitalFormulaXml");
   qRegisterMetaType<ActionBlockXml>("ActionBlockXml");
   qRegisterMetaType<ActionClockXml>("qRegisterMetaType<Action");
   qRegisterMetaType<ActionListenOnBeansXml>("ActionListenOnBeansXml");
   qRegisterMetaType<ActionLocalVariableXml>("ActionLocalVariableXml");
   qRegisterMetaType<DefaultCsvNamedTableXml>("DefaultCsvNamedTableXml");
   qRegisterMetaType<AntecedentXml>("AntecedentXml");
   qRegisterMetaType<DefaultModuleManagerXml>("DefaultModuleManagerXml");
   qRegisterMetaType<NotXml>("NotXml");
   qRegisterMetaType<AnalogExpressionConstantXml*>("AnalogExpressionConstantXml");
   qRegisterMetaType<AnalogExpressionAnalogIOXml>("AnalogExpressionAnalogIOXml");
   qRegisterMetaType<AnalogFormulaXml>("AnalogFormulaXml");
   qRegisterMetaType<AnalogExpressionMemoryXml>("AnalogExpressionMemoryXml");
   qRegisterMetaType<ActionSignalHeadXml>("ActionSignalHeadXml");
   qRegisterMetaType<AnalogActionLightIntensityXml>("AnalogActionLightIntensityXml");
   qRegisterMetaType<DigitalBooleanManyXml>("DigitalBooleanManyXml");
   qRegisterMetaType<ActionPositionableXml>("ActionPositionableXml");
   qRegisterMetaType<StringActionMemoryXml>("StringActionMemoryXml");
   qRegisterMetaType<StringManyXml>("StringManyXml");
   qRegisterMetaType<ClipboardManyXml>("ClipboardManyXml");
   qRegisterMetaType<LastResultOfDigitalExpressionXml>("LastResultOfDigitalExpressionXml");
   qRegisterMetaType<ExpressionSignalHeadXml>("ExpressionSignalHeadXml");
   qRegisterMetaType<ExpressionLocalVariableXml>("ExpressionLocalVariableXml");
   qRegisterMetaType<ExpressionMemoryXml>("ExpressionMemoryXml");
   qRegisterMetaType<ActionPowerXml>("ActionPowerXml");
   qRegisterMetaType<ExpressionPowerXml>("ExpressionPowerXml");
   qRegisterMetaType<ForXml>("ForXml");
   qRegisterMetaType<DigitalManyXml>("DigitalManyXml");
   qRegisterMetaType<ActionLightXml>("ActionLightXml");
   qRegisterMetaType<ExpressionReferenceXml>("ExpressionReferenceXml");
   qRegisterMetaType<DefaultDigitalActionManagerXml>("DefaultDigitalActionManagerXml");

   // AbstractAnalogExpressionSwing
   qRegisterMetaType<AnalogFormulaSwing>("AnalogFormulaSwing");
   qRegisterMetaType<AnalogExpressionAnalogIOSwing>("AnalogExpressionAnalogIOSwing");
   qRegisterMetaType<AnalogExpressionConstantSwing>("AnalogExpressionConstantSwing");
   qRegisterMetaType<AnalogExpressionMemorySwing>("AnalogExpressionMemorySwing");
   qRegisterMetaType<TimeSinceMidnightSwing>("TimeSinceMidnightSwing");

   // AbstractAnalogActionSwing
   qRegisterMetaType<AnalogManySwing>("AnalogManySwing");
   qRegisterMetaType<AnalogActionMemorySwing>("AnalogActionMemorySwing");
   qRegisterMetaType<AnalogActionLightIntensitySwing>("AnalogActionLightIntensitySwing");
   qRegisterMetaType<StringActionMemorySwing>("StringActionMemorySwing");
   qRegisterMetaType<StringManySwing>("StringManySwing");

   // AbstractBooleanActionSwing classes
   qRegisterMetaType<DigitalBooleanManySwing>("DigitalBooleanManySwing");
   qRegisterMetaType<DigitalBooleanOnChangeSwing>("DigitalBooleanOnChangeSwing");

   // AbstractDigitalExpressionSwing
   qRegisterMetaType<AndSwing>("AndSwing");
   qRegisterMetaType<AntecedentSwing>("AntecedentSwing");
   qRegisterMetaType<DigitalFormulaSwing>("DigitalFormulaSwing");
   qRegisterMetaType<ExpressionSensorSwing>("ExpressionSensorSwing");
   qRegisterMetaType<FalseSwing>("FalseSwing");
   qRegisterMetaType<NotSwing>("NotSwing");
   qRegisterMetaType<OrSwing>("OrSwing");
   qRegisterMetaType<TrueSwing>("TrueSwing");
   qRegisterMetaType<HoldSwing>("HoldSwing");
   qRegisterMetaType<LastResultOfDigitalExpressionSwing>("LastResultOfDigitalExpressionSwing");
   qRegisterMetaType<ExpressionSignalHeadSwing>("ExpressionSignalHeadSwing");
   qRegisterMetaType<ExpressionMemorySwing>("ExpressionMemorySwing");
   qRegisterMetaType<ExpressionLocalVariableSwing>("ExpressionLocalVariableSwing");
   qRegisterMetaType<ExpressionPowerSwing>("ExpressionPowerSwing");
   qRegisterMetaType<ForSwing>("ForSwing");
   qRegisterMetaType<ExpressionReferenceSwing>("ExpressionReferenceSwing");
   qRegisterMetaType<ExpressionEntryExitSwing>("ExpressionEntryExitSwing");
   qRegisterMetaType<TriggerOnceSwing>("TriggerOnceSwing");
   qRegisterMetaType<TriggerOnceXml>("TriggerOnceXml");
   qRegisterMetaType<DigitalBooleanOnChangeXml>("DigitalBooleanOnChangeXml");

   // AbstractDigitalActionSwing
   qRegisterMetaType<TableForEachSwing>("TableForEachSwing");
   qRegisterMetaType<IfThenElseSwing>("IfThenElseSwing");
   qRegisterMetaType<ActionPositionableSwing>("ActionPositionableSwing");
   qRegisterMetaType<DigitalManySwing>("DigitalManySwing");
   qRegisterMetaType<ActionSensorSwing>("ActionSensorSwing");
   qRegisterMetaType<ActionBlockSwing>("ActionBlockSwing");
   qRegisterMetaType<ActionClockSwing>("ActionClockSwing");
   qRegisterMetaType<ActionListenOnBeansSwing>("ActionListenOnBeansSwing");
   qRegisterMetaType<ActionLocalVariableSwing>("ActionLocalVariableSwing");
   qRegisterMetaType<ActionSignalHeadSwing>("ActionSignalHeadSwing");
   qRegisterMetaType<ActionPowerSwing>("ActionPowerSwing");
   qRegisterMetaType<ActionLightSwing>("ActionLightSwing");
   qRegisterMetaType<Actions::LogData>("Actions::LogData");
   qRegisterMetaType<DefaultAnalogExpressionManagerXml>("DefaultAnalogExpressionManagerXml");
   qRegisterMetaType<Actions::DigitalCallModuleSwing>("Actions::DigitalCallModuleSwing");
   qRegisterMetaType<DefaultMaleDigitalActionSocketXml>("DefaultMaleDigitalActionSocketXml");
   qRegisterMetaType<ExecuteDelayedSwing>("ExecuteDelayedSwing");
   qRegisterMetaType<ExecuteDelayedXml>("ExecuteDelayedXml");
   qRegisterMetaType<SequenceXml>("SequenceXml");
   qRegisterMetaType<LogixXml>("LogixXml");
   qRegisterMetaType<LogixSwing>("LogixSwing");
   qRegisterMetaType<ActionMemorySwing>("ActionMemorySwing");
   qRegisterMetaType<ActionMemoryXml>("ActionMemoryXml");
   qRegisterMetaType<ActionSignalMastSwing>("ActionSignalMastSwing");
   qRegisterMetaType<ActionSignalMastXml>("ActionSignalMastXml");
   qRegisterMetaType<Actions::LogDataSwing>("Actions::LogDataSwing");
   qRegisterMetaType<Actions::LogDataXml>("Actions::LogDataXml");
   qRegisterMetaType<ActionTurnoutLockSwing>("ActionTurnoutLockSwing");
   qRegisterMetaType<ActionTurnoutLockXml>("ActionTurnoutLockXml");


   // AbstractStringExpressionSwing
   qRegisterMetaType<StringFormulaSwing>("StringFormulaSwing");
   qRegisterMetaType<SequenceSwing>("SequenceSwing");
   qRegisterMetaType<Expressions::DigitalCallModuleSwing>("Expressions::DigitalCallModuleSwing");
   qRegisterMetaType<Expressions::LogData>("Expressions::LogData");
   qRegisterMetaType<Expressions::LogDataSwing>("Expressions::LogDataSwing");
   qRegisterMetaType<Expressions::LogDataXml>("Expressions::LogDataXml");
   qRegisterMetaType<ExpressionReporterXml>("ExpressionReporterXml");
   qRegisterMetaType<ExpressionReporterSwing>("ExpressionReporterSwing");
   qRegisterMetaType<ExpressionEntryExitXml>("ExpressionEntryExitXml");
   qRegisterMetaType<ExpressionSignalMastSwing>("ExpressionSignalMastSwing");
   qRegisterMetaType<ExpressionSignalMastXml>("ExpressionSignalMastXml");
   qRegisterMetaType<ExpressionLightSwing>("ExpressionLightSwing");
   qRegisterMetaType<ExpressionBlockSwing>("ExpressionBlockSwing");
   qRegisterMetaType<ExpressionBlockXml>("ExpressionBlockXml");
   qRegisterMetaType<ExpressionConditionalSwing>("ExpressionConditionalSwing");
   qRegisterMetaType<ExpressionConditionalXml>("ExpressionConditionalXml");


   LogixNG_Metatypes::ng_done = true;
}
