#ifndef JMRICLIENTTURNOUT_H
#define JMRICLIENTTURNOUT_H
#include "abstractturnout.h"

class JMRIClientMessage;
class JMRIClientReply;
class JMRIClientSystemConnectionMemo;
class JMRIClientTrafficController;
class JMRIClientTurnout : public AbstractTurnout
{
public:
 JMRIClientTurnout(int number, JMRIClientSystemConnectionMemo* memo, QObject* paent = nullptr);
 /*public*/ int getNumber();
 /*public*/ bool canInvert();
 /*public*/ void requestUpdateFromLayout();
 /*public*/ void reply(JMRIClientReply* m);
 /*public*/ void message(JMRIClientMessage* m);

private:
 static Logger* log;
 // data members
 /*private*/ int _number;   // turnout number
 /*private*/ JMRIClientTrafficController* tc = nullptr;
 /*private*/ QString prefix;// = null;
 /*private*/ QString transmitName ;//= null;
 static QVector<QString> modeNames;// = null;
 static QVector<int> modeValues;// = null;
 /*synchronized*/ static /*private*/ void setModeInformation(QVector<QString> feedbackNames, QVector<int> feedbackModes);
 static QVector<int> getModeValues();
 static QVector<QString> getModeNames();

protected:
 /*protected*/ void forwardCommandChangeToLayout(int s);
 /*protected*/ void turnoutPushbuttonLockout(bool _pushButtonLockout);
 /*protected*/ void sendMessage(bool closed);

};

#endif // JMRICLIENTTURNOUT_H
