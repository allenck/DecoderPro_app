#ifndef ENDSOUND_H
#define ENDSOUND_H
#include "sdfmacro.h"

class EndSound : public SdfMacro
{
 Q_OBJECT
public:
 //explicit EndSound(QObject *parent = 0);
 /*public*/ EndSound(int byte1, int byte2, QObject *parent = 0);
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
 int byte1, byte2;

};

#endif // ENDSOUND_H
