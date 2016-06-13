#ifndef DELAYSOUND_H
#define DELAYSOUND_H
#include "sdfmacro.h"

class DelaySound : public SdfMacro
{
 Q_OBJECT
public:
 //explicit DelaySound(QObject *parent = 0);
 /*public*/ DelaySound(int byte1, int byte2 , QObject *parent = 0);
 /*public*/ QString name();
 /*public*/ int length();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);
signals:

public slots:
private:
 int mode;
 int value;
 int glbl;
 int byte1, byte2;

};

#endif // DELAYSOUND_H
