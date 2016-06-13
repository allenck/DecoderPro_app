#ifndef ABSTRACTBOARDPROGPANEL_H
#define ABSTRACTBOARDPROGPANEL_H
#include "lnpanel.h"
#include "logger.h"
#include "libPr3_global.h"

class JToggleButton;
class JTextField;
class QLabel;
class QVBoxLayout;
class LocoNetMessage;
class LIBPR3SHARED_EXPORT AbstractBoardProgPanel : public LnPanel
{
 Q_OBJECT
public:
 /*public*/ JToggleButton* readAllButton;// = null;
 /*public*/ JToggleButton* writeAllButton;// = null;
 /*public*/ JTextField* addrField;// = new JTextField(4);

 /*public*/ bool read;// = false;
 /*public*/ int state;// = 0;
 /* The responseTimer provides a timeout mechanism for OpSw read and write
  * requests.
  */
 /*public*/ QTimer* responseTimer;// = NULL;

 /* The pacing timer is used to reduce the speed of this tool's requests to
  * LocoNet.
  */
 /*public*/ QTimer* pacingTimer;// = NULL;

 /* The bool field onlyOneOperation is intended to allow accesses to
  * a single OpSw value at a time.  This is un-tested functionality.
  */
 /*public*/ bool onlyOneOperation;// = false;
 /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
 /*public*/ void initComponents() ;
 /*public*/ void setBoardIdValue(int boardId);
 /*public*/ int getBoardIdValue();
 /*public*/ void readAll();
 /*public*/ void dispose();
 /*public*/ void writeAll();
 /*public*/ void writeOne(int opswIndex);
 /*public*/ void doTheNextThing();

signals:

public slots:
 void On_readAllButton_selected();
 void On_writeAllButton_selected();
 /*public*/ void message(LocoNetMessage* m);
private slots:
 void On_ResponseTimer_timeout();
 /*private*/ void On_pacingTimer_timeout();

private:
 QWidget* contents;// = new QWidget();
 void common(int boardNum, bool readOnInit);
 Logger* log;
 QVBoxLayout* thisLayout;
 QLabel* status;// = new QLabel();
 bool awaitingReply;// = false;
 int replyTryCount;// = 0;
 int address;// = 0;
 /* typeWord provides the encoded device type number, and is used within the
  * LocoNet OpSw Read and Write request messages.  Different Digitrax boards
  *  respond to different encoded device type values, as shown here:
  *      PM4/PM42                0x70
  *      BDL16/BDL162/BDL168     0x71
  *      SE8C                    0x72
  *      DS64                    0x73
  */
 int typeWord;

 bool readOnInit;
 /*private*/ /*final*/ static int HALF_A_SECOND;// = 500;
 /*private*/ /*final*/ static int FIFTIETH_OF_A_SECOND;// = 20; // 20 milliseconds = 1/50th of a second
 /*private*/ /*final*/ void delayedNextRequest();
 /*private*/ /*final*/ void nextRequest();
 bool setAddress(int maxValid) /*throws Exception*/;
 QVBoxLayout* contentsLayout;
 /*private*/ void initializeResponseTimer();
 /*private*/ void initializePacingTimer();
 // maximum number of additional retries after board does not respond to
 // first attempt to access a given OpSw
 /*private*/ /*final*/ int MAX_OPSW_ACCESS_RETRIES;// = 2;

protected:
 /**
  * True is "closed", false is "thrown". This matches how we do the check
  * boxes also, where we use the terminology for the "closed" option. Note
  * that opsw[0] is not a legal OpSwitch.
  */
 /*protected*/ QVector<bool> opsw;// = new bool[65];
 explicit AbstractBoardProgPanel(QWidget *parent = 0);
 /*protected*/ AbstractBoardProgPanel(int boardNum, QWidget *parent);
 /*protected*/ AbstractBoardProgPanel(bool readOnInit, QWidget *parent = 0);
 /*protected*/ AbstractBoardProgPanel(int boardNum, bool readOnInit, QWidget *parent = 0);
 /*protected*/ QWidget* provideAddressing(QString type);
 /*protected*/ QWidget* provideStatusLine();
 /*protected*/ void setStatus(QString msg);
 /*protected*/ void appendLine(QWidget* c);
 /*protected*/ void setTypeWord(int type);
 /**
  * Copy from the GUI to the opsw array.
  * <p>
  * Used before a write operation is started.
  */
 /*abstract*/ virtual  /*protected*/ void copyToOpsw();

 /**
  * Update the GUI based on the contents of opsw[].
  * <p>
  * This method is executed after completion of a read operation sequence.
  */
 /*abstract*/ virtual /*protected*/ void updateDisplay();

 /**
  * Specify which OpSws (and which sequence) need to be read/written
  */
 /*abstract*/ virtual /*protected*/ int nextState(int state);

};

#endif // ABSTRACTBOARDPROGPANEL_H
