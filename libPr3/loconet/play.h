#ifndef PLAY_H
#define PLAY_H
#include "sdfmacro.h"

class Play : public SdfMacro
{
 Q_OBJECT
public:
 //explicit Play(QObject *parent = 0);
 /*public*/ Play(int byte1, int byte2, QObject *parent = 0);
 /*public*/  QString name();
 /*public*/  QString handleVal();
 /*public*/ void setHandle(int val);
 /*public*/  QString brkVal() ;
 /*public*/ void setBrk( QString name);
 /*public*/ void setBrk(int n);
 /*public*/  QString wavebrkFlagsVal() ;
 /*public*/ int getWaveBrkFlags();
 /*public*/ void setWaveBrkFlags( QString name) ;
 /*public*/ void setWaveBrkFlags(int n);
 /*public*/ int length();
static  /*public*/ SdfMacro* match(SdfBuffer* buff) ;
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 /*public*/  QString toString();
 /*public*/  QString oneInstructionString();
 /*public*/  QString allInstructionString( QString indent);
signals:

public slots:
private:
int handle;
int brk;  // "break" is a reserved word
int wavebrkFlags;

int byte1, byte2;

};

#endif // PLAY_H
