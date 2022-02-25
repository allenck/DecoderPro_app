#include "metatypes.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixngmanagerxml.h"
#include "defaultanalogactionmanagerxml.h"
#include "defaultnamedtablemanagerxml.h"
#include "defaultstringexpressionmanagerxml.h"
#include "defaultdigitalbooleanactionmanagerxml.h"
#include "defaultdigitalexpressionmanagerxml.h"

Metatypes::Metatypes(QObject *parent) : QObject(parent)
{
   qRegisterMetaType<DefaultLogixNGManager>("DefaultLogixNGManager");
   qRegisterMetaType<DefaultLogixNGManagerXml>("DefaultLogixNGManagerXml");
   qRegisterMetaType<DefaultAnalogActionManagerXml>("DefaultAnalogActionManagerXml");
   qRegisterMetaType<DefaultNamedTableManagerXml>("DefaultNamedTableManagerXml");
   qRegisterMetaType<DefaultStringExpressionManagerXml>("DefaultStringExpressionManagerXml");
   qRegisterMetaType<DefaultDigitalBooleanActionManagerXml>("DefaultDigitalBooleanActionManagerXml");
   qRegisterMetaType<DefaultDigitalExpressionManagerXml>("DefaultDigitalExpressionManagerXml");

   Metatypes::done = true;
}
