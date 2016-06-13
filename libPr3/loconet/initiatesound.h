#ifndef INITIATESOUND_H
#define INITIATESOUND_H
#include "sdfmacro.h"
#include "sdfconstants.h"

class InitiateSound : public SdfMacro
{
 Q_OBJECT
public:
 //explicit InitiateSound(QObject *parent = 0);
 /*public*/ InitiateSound(int byte1, int byte2, QObject *parent = 0);
 /*public*/ QString name();
 /*public*/ int getTrigger() ;
 /*public*/ void setTrigger(int t);
 /*public*/ int getPrempt() ;
 /*public*/ void setPrempt(int prempt);
 /*public*/ int length();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString() ;
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);
signals:

public slots:
private:
 int prempt;
 int trigger;
 int byte1, byte2;
 QString premptVal();
 QString triggerVal();

};

#endif // INITIATESOUND_H
