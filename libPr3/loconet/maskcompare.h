#ifndef MASKCOMPARE_H
#define MASKCOMPARE_H
#include "sdfmacro.h"

class MaskCompare : public SdfMacro
{
 Q_OBJECT
public:
 //explicit MaskCompare(QObject *parent = 0);
 /*public*/ MaskCompare(int byte1, int byte2, int byte3, int byte4, QObject *parent = 0);
 /*public*/ QString name() ;
 /*public*/ int length();
 QString srcVal() ;
 QString immedVal();
 QString argVal();
 QString targVal() ;
 QString maskVal();
 QString skipVal() ;
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);

signals:

public slots:
private:
 int src;
 int immed;
 int targ;
 int mask;
 int skip;

 QVector<char> bytes;// = new byte[4];


};

#endif // MASKCOMPARE_H
