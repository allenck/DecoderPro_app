#ifndef LNTURNOUT_H
#define LNTURNOUT_H
#include "abstractturnout.h"
#include "loconetinterface.h"
#include "lntrafficcontroller.h"
#include "lnpacketizer.h"
#include <QTimer>
#include "timertask.h"

class LnTurnoutTimerTask;
class LIBPR3SHARED_EXPORT LnTurnout : public AbstractTurnout
{
 Q_OBJECT
public:
 //explicit LnTurnout(QObject *parent = 0);
 LnTurnout(QString prefix, int number, LnTrafficController* controller, QObject *parent = 0);
 /*public*/ int getNumber();
 /**
  * Send a single OPC_SW_REQ message
  * for this turnout, with the CLOSED/THROWN
  * ON/OFF state.
  *<p>
  * Inversion is to already have been handled.
  */
 void sendOpcSwReqMessage(int state, bool on);
 /**
  * Set the turnout OFF, e.g. after a timeout
  */
 void sendSetOffMessage(int state);
 // implementing classes will typically have a function/listener to get
 // updates from the layout, which will then call
 //		public void firePropertyChange(String propertyName,
 //					      	Object oldValue,
 //						Object newValue)
 // _once_ if anything has changed state (or set the commanded state directly)
 //    /*public*/ void message(LocoNetMessage* l);
 /*public*/ virtual void dispose();
 /*public*/ bool canInvert();

signals:
    
public slots:
 /*public*/ void message(LocoNetMessage* l);
 void meterTimerTimeout();

private:
 LnTrafficController* controller;
 static QStringList modeNames;
 static QList<int> modeValues;
 bool pending;
 // data members
 int _number;   // loconet turnout number
 static const int METERINTERVAL = 100;  // msec wait before closed
 static QTimer*  meterTimer;
 // data members
 /*private*/ void initFeedbackModes();
 Logger log;
 /*private*/ bool myAddress(int a1, int a2);
 //ln turnouts do support inversion
 //method which takes a turnout state as a parameter and adjusts it  as necessary
 //to reflect the turnout invert property
 /*private*/ int adjustStateForInversion(int rawState);
 LnTurnoutTimerTask* timerTask;

protected:
 // Handle a request to change state by sending a LocoNet command
 /*protected*/ virtual void forwardCommandChangeToLayout(/*final*/ int newstate);

 /*protected*/ virtual void turnoutPushbuttonLockout(bool _pushButtonLockout);
 friend class LnTurnoutTimerTask;
};
class LnTurnoutTimerTask : public TimerTask
{
 Q_OBJECT
 LnTurnout* turnout;
 int state;
public:
 LnTurnoutTimerTask(int state, LnTurnout* turnout);
 /*public*/ void run();

};

#endif // LNTURNOUT_H
