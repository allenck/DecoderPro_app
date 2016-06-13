#ifndef BRANCHTO_H
#define BRANCHTO_H
#include "sdfmacro.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT BranchTo : public SdfMacro
{
 Q_OBJECT
public:
 //explicit BranchTo(QObject *parent = 0);
 /*public*/ BranchTo(int byte1, int byte2,QObject *parent = 0) ;
 /*public*/ QString name();
 /*public*/ int length();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer) ;
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);

signals:

public slots:
private:
 int byte1, byte2;

 int addr;
 int skemebase;

};

#endif // BRANCHTO_H
