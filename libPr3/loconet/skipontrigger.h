#ifndef SKIPONTRIGGER_H
#define SKIPONTRIGGER_H
#include "sdfmacro.h"

class SkipOnTrigger : public SdfMacro
{
 Q_OBJECT
public:
 //explicit SkipOnTrigger(QObject *parent = 0);
 /*public*/ SkipOnTrigger(int byte1, int byte2, QObject* parent = 0);
 /*public*/ QString name();
 /*public*/ int length();
 QString logicVal() ;
 QString triggerVal();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer) ;
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString() ;
 /*public*/ QString allInstructionString(QString indent);

signals:

public slots:
  private:
  int byte1, byte2;

  int logic;
  int trigger;


};

#endif // SKIPONTRIGGER_H
