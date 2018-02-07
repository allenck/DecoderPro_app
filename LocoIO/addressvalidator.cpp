#include "addressvalidator.h"

 AddressValidator::AddressValidator(QObject* parent) : QRegExpValidator(parent) {}
 AddressValidator::AddressValidator(QRegExp& rx, QObject *parent) : QRegExpValidator(rx,  parent)
 {
//  if(rx.pattern().contains("a-f"))
//   iBase = 16;
//  else
//   iBase = 10;

 }
 void AddressValidator::setRelaxed(bool b) {bRelax = b;}
 /*virtual*/ QValidator::State	AddressValidator::validate ( QString & input, int & pos ) const
 {
   fixup(input);
   return QRegExpValidator::validate(input, pos);
 }
 /*virtual*/ void AddressValidator::fixup(QString &input) const
 {
  int addr=0;
  int subAddr = 0;
  bool bOk;
  int iBase;

  if(regExp().pattern().contains("a-f"))
   iBase = 16;
  else
   iBase = 10;

  if(!input.contains("/"))
   input.append("/1");
  QStringList sl = input.split("/");
  addr = sl.at(0).toInt(&bOk,iBase);
  if(!bOk)
   addr = 0x51;
  if(addr == 0x80)
   addr = 0x51;
  if(addr == 0)
   addr = 1;
  if(!bRelax)
  {
  if(addr > 127)
   addr = 127;
  }
  subAddr = sl.at(1).toInt(&bOk, iBase);
  if(!bRelax)
  {
   if(subAddr == 0)
    subAddr = 1;
  }
  if(subAddr>126)
   subAddr = 126;
  input = QString("%1/%2").arg(addr,0,iBase).arg(subAddr,0,iBase);
 }
