#ifndef CHANNELSTART_H
#define CHANNELSTART_H
#include "sdfmacro.h"

class ChannelStart : public SdfMacro
{
 Q_OBJECT
public:
 //explicit ChannelStart(QObject *parent = 0);
 /*public*/ ChannelStart(int number,QObject *parent = 0);
 /*public*/ QString name();
 /*public*/ int length();
 static /*public*/ SdfMacro* match(SdfBuffer* buff);
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/ QString toString() ;
 /*public*/ QString oneInstructionString();
 /*public*/ QString allInstructionString(QString indent);

signals:

public slots:
  private:
  int number;

};

#endif // CHANNELSTART_H
