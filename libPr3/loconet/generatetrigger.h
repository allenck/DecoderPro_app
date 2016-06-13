#ifndef GENERATETRIGGER_H
#define GENERATETRIGGER_H
#include "sdfmacro.h"

class GenerateTrigger : public SdfMacro
{
 Q_OBJECT
public:
 //explicit GenerateTrigger(QObject *parent = 0);
 /*public*/ GenerateTrigger(int trigger,QObject *parent = 0) ;
 /*public*/ QString name();
 /*public*/ int length();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString() ;
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);
signals:

public slots:
private:
 int trigger;
 QString triggerVal();

};

#endif // GENERATETRIGGER_H
