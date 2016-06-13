#ifndef LOADMODIFIER_H
#define LOADMODIFIER_H
#include "sdfmacro.h"

class LoadModifier : public SdfMacro
{
 Q_OBJECT
public:
 //explicit LoadModifier(QObject *parent = 0);
 /*public*/ LoadModifier(int byte0, int arg1, int arg2, int arg3, QObject *parent = 0);
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
 int byte0;
 int modType;
 int arg1, arg2, arg3;
 QString modTypeVal();
 QString argVal();


};

#endif // LOADMODIFIER_H
