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
#include "abstractanalogexpressionswing.h"
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
#include "falsexml.h"
#include "expressionsensorxml.h"
#include "orxml.h"
#include "andxml.h"
#include "logixngmoduletableaction.h"
#include "logixngtableaction.h"
#include "logixngtabletableaction.h"

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

   qRegisterMetaType<DefaultMaleAnalogActionSocketXml>("DefaultMaleAnalogActionSocketXml");
   qRegisterMetaType<DefaultMaleAnalogExpressionSocketXml>("DefaultMaleAnalogExpressionSocketXml");
   qRegisterMetaType<DefaultMaleDigitalBooleanActionSocketXml>("DefaultMaleDigitalBooleanActionSocketXml");
   qRegisterMetaType<DefaultMaleDigitalExpressionSocketXml>("DefaultMaleDigitalExpressionSocketXml");
   qRegisterMetaType<DefaultMaleStringActionSocketXml>("DefaultMaleStringActionSocketXml");
   qRegisterMetaType<DefaultMaleStringExpressionSocketXml>("DefaultMaleStringExpressionSocketXml");
   qRegisterMetaType<ExpressionSensorXml>("ExpressionSensorXml");

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

   // AbstractDigitalActionSwing
   qRegisterMetaType<TableForEachSwing>("TableForEachSwing");
   qRegisterMetaType<ForSwing>("ForSwing");
   qRegisterMetaType<IfThenElseSwing>("IfThenElseSwing");
   qRegisterMetaType<ActionPositionableSwing>("ActionPositionableSwing");
   qRegisterMetaType<DigitalManySwing>("DigitalManySwing");

   // AbstractStringExpressionSwing
   qRegisterMetaType<StringFormulaSwing>("StringFormulaSwing");

   LogixNG_Metatypes::ng_done = true;
}
