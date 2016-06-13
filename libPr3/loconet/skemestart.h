#ifndef SKEMESTART_H
#define SKEMESTART_H
#include "sdfmacro.h"

class SkemeStart : public SdfMacro
{
 Q_OBJECT
public:
 //explicit SkemeStart(QObject *parent = 0);
 /*public*/ SkemeStart(int byte1, int byte2, int byte3, int byte4, QObject *parent = 0);
 /*public*/ int getNumber();
 /*public*/ void setNumber(int num);
 /*public*/ QString name() ;
 /*public*/ int length();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString();
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);

signals:

public slots:
  private:
  int byte1, byte2, byte3, byte4;

  int number;
  int _length;


};

#endif // SKEMESTART_H
