#ifndef TWOBYTEMACRO_H
#define TWOBYTEMACRO_H
#include "sdfmacro.h"

class TwoByteMacro : public SdfMacro
{
 Q_OBJECT
public:
 //TwoByteMacro(Q);
 /*public*/ TwoByteMacro(int byte1, int byte2, QObject* parent = 0);
 /*public*/ QString name() ;
 /*public*/ int length() ;
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString() ;
 /*public*/ QString allInstructionString(QString indent) ;
private:
 QVector<char>* bytes;
};

#endif // TWOBYTEMACRO_H
