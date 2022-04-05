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
   qRegisterMetaType<AntecedentSwing>("AntecedentSwing");
   qRegisterMetaType<DigitalFormulaSwing>("DigitalFormulaSwing");
   qRegisterMetaType<ExpressionSensorSwing>("ExpressionSensorSwing");
   qRegisterMetaType<FalseSwing>("FalseSwing");
   qRegisterMetaType<OrSwing>("OrSwing");
   qRegisterMetaType<TrueSwing>("TrueSwing");

   // AbstractDigitalActionSwing
   qRegisterMetaType<TableForEachSwing>("TableForEachSwing");
   qRegisterMetaType<ForSwing>("ForSwing");
   qRegisterMetaType<IfThenElseSwing>("IfThenElseSwing");
   qRegisterMetaType<ActionPositionableSwing>("ActionPositionableSwing");
   qRegisterMetaType<DigitalManySwing>("DigitalManySwing");

   LogixNG_Metatypes::ng_done = true;
}
