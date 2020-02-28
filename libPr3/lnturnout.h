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
 LnTurnout(QString prefix, int number, LocoNetInterface *controller, QObject *parent = 0);
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
 /*public*/ virtual void dispose() override;
 /*public*/ bool canInvert()const override;
 /*public*/ void messageFromManager(LocoNetMessage* l);
 static const int METERINTERVAL;// = 100;  // msec wait before closed
 /*public*/ void setUseOffSwReqAsConfirmation(bool state);

signals:
    
public slots:
 /*public*/ void message(LocoNetMessage* l);
 void meterTimerTimeout();

private:
 LocoNetInterface* controller;
 static QVector<QString> modeNames;
 static QVector<int> modeValues;
 bool pending;
 // data members
 int _number;   // loconet turnout number
 static QTimer*  meterTimer;
 // data members
 /*private*/ void initFeedbackModes();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(LnTurnout.class);
 /*private*/ bool myAddress(int a1, int a2);
 //ln turnouts do support inversion
 //method which takes a turnout state as a parameter and adjusts it  as necessary
 //to reflect the turnout invert property
 /*private*/ int adjustStateForInversion(int rawState);
 LnTurnoutTimerTask* timerTask;
 /*private*/ void computeKnownStateOpSwAckReq(int sw2, int state);
 /*private*/ void setKnownStateFromOutputStateClosedReport();
 /*private*/ void setKnownStateFromOutputStateThrownReport() ;
 /*private*/ void setKnownStateFromOutputStateOddReport();
 /*private*/ void setKnownStateFromOutputStateReallyOddReport();
 /*private*/ void computeFromOutputStateReport(int sw2);
 /*private*/ void computeFeedbackFromSwitchReport(int sw2);
 /*private*/ void computeFeedbackFromSwitchOffReport();
 /*private*/ void computeFeedbackFromSwitchOnReport();
 /*private*/ void computeFromSwFeedbackState(int sw2);
 /*private*/ void computeFeedbackFromAuxInputReport(int sw2);
 /*private*/ void handleReceivedOpSwRep(LocoNetMessage* l);
 /*private*/ void handleReceivedOpSwAckReq(LocoNetMessage* l);
 bool _useOffSwReqAsConfirmation = false;
 /**
  * True when setFeedbackMode has specified the mode;
  * false when the mode is just left over from initialization.
  * This is intended to indicate (when true) that a configuration
  * file has set the value; message-created turnouts have it false.
  */
 bool feedbackDeliberatelySet = false; // package to allow access from LnTurnoutManager

protected:
 // Handle a request to change state by sending a LocoNet command
 /*protected*/ void forwardCommandChangeToLayout(/*final*/ int newstate) override;

 /*protected*/ void turnoutPushbuttonLockout(bool _pushButtonLockout) override;
 friend class LnTurnoutTimerTask;
 friend class LnTurnoutTest;
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
