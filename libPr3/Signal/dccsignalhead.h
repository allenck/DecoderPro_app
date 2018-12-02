#ifndef DCCSIGNALHEAD_H
#define DCCSIGNALHEAD_H
#include "abstractsignalhead.h"

class CommandStation;
class DccSignalHead : public AbstractSignalHead
{
public:
 //DccSignalHead();
 /*public*/ DccSignalHead(QString sys, QString user, QObject* parent = nullptr);
 /*public*/ DccSignalHead(QString sys, QObject* parent = nullptr);
 /*public*/ void setAppearance(int newAppearance);
 /*public*/ void setLit(bool newLit);
 /*public*/ void setHeld(bool newHeld);
 /*public*/ void useAddressOffSet(bool boo);
 /*public*/ bool useAddressOffSet();
 /*public*/ int getOutputForAppearance(int appearance);
 /*public*/ void setOutputForAppearance(int appearance, int number);
 /*public*/ static int getDefaultNumberForApperance(int i);


private:
 static Logger* log;
 int dccSignalDecoderAddress;
 void configureHead(QString sys);
 CommandStation* c;
 bool _useAddressOffSet = false;
 bool isTurnoutUsed(Turnout* t);

protected:
 /*protected*/ void updateOutput();
 /*protected*/ QMap<int, int> appearanceToOutput;// = new HashMap<Integer, Integer>();

};

#endif // DCCSIGNALHEAD_H
