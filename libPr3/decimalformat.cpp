#include "decimalformat.h"

DecimalFormat::DecimalFormat(QString tmplt) //, QObject *parent) : QObject(parent)
{
 this->tmplt = tmplt;
}

QString DecimalFormat::format(int num)
{
 QString s = QString("%1").arg(num);
 if(s.length() >= tmplt.length()) return s;
 return tmplt.mid(0,tmplt.length()-s.length())+s;
}
QString DecimalFormat::format(double num)
{
 QString s = QString("%1").arg(num);
// if(s.length() >= tmplt.length()) return s;
// return tmplt.mid(0,tmplt.length()-s.length())+s;
 return s;
}
