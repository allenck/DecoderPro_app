#ifndef FOURBYTEMACRO_H
#define FOURBYTEMACRO_H
#include "sdfmacro.h"

class FourByteMacro : public SdfMacro
{
 Q_OBJECT
public:
 //explicit FourByteMacro(QObject *parent = 0);
 /*public*/ FourByteMacro(int byte1, int byte2, int byte3, int byte4, QObject *parent = 0);
 /*public*/ QString name();
 /*public*/ int length() ;
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);
signals:

public slots:

private:
 QVector<char>* bytes;
};

#endif // FOURBYTEMACRO_H
