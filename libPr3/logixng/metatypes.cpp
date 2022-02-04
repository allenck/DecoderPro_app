#include "metatypes.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixngmanagerxml.h"


Metatypes::Metatypes(QObject *parent) : QObject(parent)
{
   qRegisterMetaType<DefaultLogixNGManager>("DefaultLogixNGManager");
   qRegisterMetaType<DefaultLogixNGManagerXml>("DefaultLogixNGManagerXml");

   Metatypes::done = true;
}
