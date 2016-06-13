#ifndef SDLVERSION_H
#define SDLVERSION_H
#include "sdfmacro.h"

class SdlVersion : public SdfMacro
{
 Q_OBJECT
public:
 //explicit SdlVersion(QObject *parent = 0);
 /*public*/ SdlVersion(int version, QObject *parent = 0);
 /*public*/ QString name() ;
 /*public*/ int length();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString() ;
 /*public*/ QString allInstructionString(QString indent);

signals:

public slots:
private:
 int version;


};

#endif // SDLVERSION_H
