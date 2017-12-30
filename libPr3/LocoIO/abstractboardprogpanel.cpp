#include "abstractboardprogpanel.h"
#include <QLabel>
#include "jtogglebutton.h"
#include "jtextfield.h"
#include "loconetsystemconnectionmemo.h"
#include "flowlayout.h"
#include <QScrollArea>
#include <QMessageBox>

AbstractBoardProgPanel::AbstractBoardProgPanel(QWidget *parent) :
  LnPanel(parent)
{
 common(1, false);
}
/**
 * Display and modify an Digitrax board configuration.
 * <P>
 * Supports boards which can be read and write using LocoNet opcode
 * OPC_MULTI_SENSE, such as PM4x, DS64, SE8c, BDL16x.
 * <P>
 * The read and write require a sequence of operations, which we handle with a
 * state variable.
 * <p>
 * Each read or write OpSw access requires a response from the addressed board.
 * If a response is not received within a fixed time, then the process will
 * repeat the read or write OpSw access up to MAX_OPSW_ACCESS_RETRIES additional
 * times to try to get a response from the addressed board. If the board does
 * not respond, the access sequence is aborted and a failure message is
 * populated in the "status" variable.
 * <P>
 * Programming of the board is done via configuration messages, so the board
 * should not be put into programming mode via the built-in pushbutton while
 * this tool is in use.
 * <P>
 * Throughout, the terminology is "closed" == true, "thrown" == false. Variables
 * are named for their closed state.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 *
 * @author Bob Jacobsen Copyright (C) 2004, 2007
 * @version $Revision: 28771 $
 */
//abstract /*public*/ class AbstractBoardProgPanel extends jmri.jmrix.loconet.swing.LnPanel
//        implements LocoNetListener {

//    /**
//     *
//     */
//    /*private*/ static final long serialVersionUID = -8539447083900083082L;
    //java.util.ResourceBundle rb = tr("jmri.jmrix.loconet.LocoNetBundle");
void AbstractBoardProgPanel::common(int boardNum, bool readOnInit)
{
 log = new Logger("AbstractBoardProgPanel");
 setLayout(thisLayout = new QVBoxLayout);
 contents = new QWidget();
 status = new QLabel();
 readAllButton = NULL;
 writeAllButton = NULL;
 addrField = new JTextField(4);

 read = false;
 state = 0;
 awaitingReply = false;
 replyTryCount = 0;

 /* The responseTimer provides a timeout mechanism for OpSw read and write
  * requests.
  */
 responseTimer = NULL;

 /* The pacing timer is used to reduce the speed of this tool's requests to
  * LocoNet.
  */
 pacingTimer = NULL;

 /* The bool field onlyOneOperation is intended to allow accesses to
  * a single OpSw value at a time.  This is un-tested functionality.
  */
 onlyOneOperation = false;
 address = 0;
 MAX_OPSW_ACCESS_RETRIES = 2;

 /**
  * True is "closed", false is "thrown". This matches how we do the check
  * boxes also, where we use the terminology for the "closed" option. Note
  * that opsw[0] is not a legal OpSwitch.
  */
 opsw = QVector<bool>(65, false);

 // basic formatting: Create pane to hold contents
 // within a scroll box
 contents->setLayout(contentsLayout = new QVBoxLayout);//(contents, BoxLayout.Y_AXIS));
 QScrollArea* scroll = new QScrollArea();
 scroll->setWidgetResizable(true);
 scroll->setWidget(contents);
 thisLayout->addWidget(scroll);

 // and prep for display
 addrField->setText(QString::number(boardNum));
 this->readOnInit = readOnInit;
}
/*private*/ /*final static*/ int AbstractBoardProgPanel::HALF_A_SECOND = 500;
/*private*/ /*final static*/ int AbstractBoardProgPanel::FIFTIETH_OF_A_SECOND = 20; // 20 milliseconds = 1/50th of a second

/**
 * Constructor which assumes the board ID number is 1
 */
///*protected*/ AbstractBoardProgPanel() {
//    this(1, false);
//}

/*protected*/ AbstractBoardProgPanel::AbstractBoardProgPanel(bool readOnInit, QWidget *parent) : LnPanel(parent)
{
 common(1, readOnInit);
}

/*protected*/ AbstractBoardProgPanel::AbstractBoardProgPanel(int boardNum, bool readOnInit, QWidget *parent) : LnPanel(parent)
{
 //super();
 common(boardNum, readOnInit);
}

/**
 * Constructor which allows the caller to pass in the board ID number
 * <p>
 * @param boardNum
 */
/*protected*/ AbstractBoardProgPanel::AbstractBoardProgPanel(int boardNum, QWidget *parent) : LnPanel(parent)
{
 common(boardNum, false);
}

/*public*/ void AbstractBoardProgPanel::initComponents(LocoNetSystemConnectionMemo* memo)
{
 LnPanel::initComponents(memo);

 // listen for message traffic
 if (memo->getLnTrafficController() != NULL)
 {
  //memo->getLnTrafficController()->addLocoNetListener(~0, this);
  connect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
  if (readOnInit == true)
  {
   readAllButton->setSelected(true);
   //readAllButton.updateUI();
   readAll();
  }
 }
 else
 {
  log->error("No LocoNet connection available, this tool cannot function");
 }
}

/*public*/ void AbstractBoardProgPanel::initComponents()
{
 initializeResponseTimer();
 initializePacingTimer();
}

/**
 * Set the Board ID number (also known as board address number)
 * <p>
 * @param boardId
 */
/*public*/ void AbstractBoardProgPanel::setBoardIdValue(int boardId) {
    if (boardId < 1) {
        return;
    }
    if (boardId > 256) {
        return;
    }
    addrField->setText(QString::number(boardId));
    address = boardId - 1;
}

/*public*/ int AbstractBoardProgPanel::getBoardIdValue() {
 return (addrField->text().toInt());
}

/**
 * Provide GUI elements for read and write buttons and address entry field
 */
/*protected*/ QWidget* AbstractBoardProgPanel::provideAddressing(QString type) {
    QWidget* pane0 = new QWidget();
    QHBoxLayout* pane0Layout;
    pane0->setLayout(pane0Layout = new QHBoxLayout());
    pane0Layout->addWidget(new QLabel(tr("Unit address:") + " "));
    pane0Layout->addWidget(addrField);
    readAllButton = new JToggleButton(tr("Read from") + " " + type);
    writeAllButton = new JToggleButton(tr("Write to ") + " " + type);

    // make both buttons a little bit bigger, with identical (preferred) sizes
    // (width increased because some computers/displays trim the button text)
    QSize d = writeAllButton->sizeHint();
    int w = d.width();
    d = readAllButton->sizeHint();
    if (d.width() > w) {
     w = d.width();
    }
    writeAllButton->resize(QSize((int) (w * 1.1), d.height()));
    readAllButton->resize(QSize((int) (w * 1.1), d.height()));

    pane0Layout->addWidget(readAllButton);
    pane0Layout->addWidget(writeAllButton);

    // install read all, write all button handlers
//    readAllButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            if (readAllButton.isSelected()) {
//                readAll();
//            }
//        }
//    }
//    );
    connect(readAllButton, SIGNAL(clicked()), this, SLOT(On_readAllButton_selected()));
//    writeAllButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            if (writeAllButton.isSelected()) {
//                writeAll();
//            }
//        }
//    }
//    );
    connect(writeAllButton, SIGNAL(clicked()), this, SLOT(On_writeAllButton_selected()));
    return pane0;
}
void AbstractBoardProgPanel::On_readAllButton_selected()
{
 if (readAllButton->isChecked())
 {
  readAll();
 }
}
void AbstractBoardProgPanel::On_writeAllButton_selected()
{
 if (writeAllButton->isChecked())
 {
  writeAll();
 }
}

/**
 * creates the status line for the GUI
 */
/*protected*/ QWidget* AbstractBoardProgPanel::provideStatusLine() {
    return status;
}

/**
 * updates the status line
 *
 * @param msg
 */
/*protected*/ void AbstractBoardProgPanel::setStatus(QString msg) {
    status->setText(msg);
}

/**
 * Handle GUI layout details during construction.
 * <P>
 * @param c component to put on a single line
 */
/*protected*/ void AbstractBoardProgPanel::appendLine(QWidget* c)
{
 //c->setAlignmentX(0.);
 contentsLayout->addWidget(c, 0, Qt::AlignLeft);
}

/**
 * Provides a mechanism to read several OpSw values in a sequence. The
 * sequence is defined by the nextState method.
 */
/*public*/ void AbstractBoardProgPanel::readAll()
{
 // check the address
 if(!setAddress(256))
 {
  log->debug(tr("ERROR_READALL_INVALID_ADDRESS"));
  readAllButton->setSelected(false);
  writeAllButton->setSelected(false);
  status->setText(" ");
  return;
 }
 if (responseTimer == NULL)
 {
  initializeResponseTimer();
 }
 if (pacingTimer == NULL)
 {
  initializePacingTimer();
 }
 // Start the first operation
 read = true;
 state = 1;
 nextRequest();
}

/**
 * Configure the type word in the LocoNet messages.
 * <P>
 * Known values:
 * <UL>
 * <LI>0x70 - PM4
 * <LI>0x71 - BDL16
 * <LI>0x72 - SE8
 * <LI>0x73 - DS64
 * </ul>
 */
/*protected*/ void AbstractBoardProgPanel::setTypeWord(int type) {
    typeWord = type;
}

/**
 * Triggers the next read or write request. Is executed by the "pacing"
 * delay timer, which allows time between any two OpSw accesses.
 */
/*private*/ /*final*/ void AbstractBoardProgPanel::delayedNextRequest()
{
 pacingTimer->stop();
 if (read)
 {
  // read op
  status->setText(tr("STATUS_READING_OPSW") + " " + QString::number(state));
  LocoNetMessage* l = new LocoNetMessage(6);
  l->setOpCode(LnConstants::OPC_MULTI_SENSE);
  int element = 0x62;
  if ((address & 0x80) != 0)
  {
   element |= 1;
  }
  l->setElement(1, element);
  l->setElement(2, address & 0x7F);
  l->setElement(3, typeWord);
  int loc = (state - 1) / 8;
  int bit = (state - 1) - loc * 8;
  l->setElement(4, loc * 16 + bit * 2);
  memo->getLnTrafficController()->sendLocoNetMessage(l);
  awaitingReply = true;
  responseTimer->stop();
  //responseTimer->restart();
  responseTimer->start();
 }
 else
 {
  //write op
  status->setText(tr("STATUS_WRITING_OPSW") + " " + QString::number(state));
  LocoNetMessage* l = new LocoNetMessage(6);
  l->setOpCode(LnConstants::OPC_MULTI_SENSE);
  int element = 0x72;
  if ((address & 0x80) != 0)
  {
   element |= 1;
  }
  l->setElement(1, element);
  l->setElement(2, address & 0x7F);
  l->setElement(3, typeWord);
  int loc = (state - 1) / 8;
  int bit = (state - 1) - loc * 8;
  l->setElement(4, loc * 16 + bit * 2 + (opsw[state] ? 1 : 0));
  memo->getLnTrafficController()->sendLocoNetMessage(l);
  awaitingReply = true;
  responseTimer->stop();
  //responseTimer.restart();
  responseTimer->start();
 }
}

/**
 * Starts the pacing timer, which, at timeout, will begin the next OpSw
 * access request.
 */
/*private*/ /*final*/ void AbstractBoardProgPanel::nextRequest() {
    pacingTimer->stop();
    //pacingTimer.restart();
    pacingTimer->start();
    replyTryCount = 0;
}

/**
 * Converts the GUI text field containing the address into a valid integer
 * address, and handles user-input errors as needed.
 */
bool AbstractBoardProgPanel::setAddress(int maxValid) /*throws Exception*/
{
 //try {
 bool bOK;
 address = ((addrField->text().toInt(&bOK)) - 1);
 //} catch (Exception e) {
 if(!bOK)
 {
  readAllButton->setSelected(false);
  writeAllButton->setSelected(false);
  status->setText(tr("STATUS_INPUT_BAD"));
//        JOptionPane.showMessageDialog(this, tr("STATUS_INVALID_ADDRESS"),
//                tr("STATUS_TYPE_ERROR"), JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("Input Error"));
  log->error(tr("Exception when parsing Address Field:") + " " /*+ e.getMessage()*/);
  //      throw e;
  return bOK;
 }
 // parsed OK, check range
 if (address > (maxValid - 1) || address < 0)
 {
  readAllButton->setSelected(false);
  writeAllButton->setSelected(false);
  status->setText(tr("STATUS_INPUT_BAD"));
//        JOptionPane.showMessageDialog(this,
//                tr("STATUS_INVALID_ADDRESS_VALUE_BEGIN")
//                + " 1 " + tr("STATUS_INVALID_ADDRESS_VALUE_MIDDLE")
//                + " " + maxValid,
//                "Error", JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("Address out of range, must be") +" 1 " + tr("to") + " " + QString::number(maxValid));
  log->error("Invalid address value");
  throw JmriException(tr("ERROR_INVALID_ADDRESS") + " " + QString::number(address));
  return false;
 }
 return true;  // OK
}

/**
 * Copy from the GUI to the opsw array.
 * <p>
 * Used before a write operation is started.
 */
/*abstract*/ /*protected*/ void AbstractBoardProgPanel::copyToOpsw() {}

/**
 * Update the GUI based on the contents of opsw[].
 * <p>
 * This method is executed after completion of a read operation sequence.
 */
/*abstract*/ /*protected*/ void AbstractBoardProgPanel::updateDisplay() {}

/**
 * Specify which OpSws (and which sequence) need to be read/written
 */
/*abstract*/ /*protected*/ int AbstractBoardProgPanel::nextState(int state) {return 0;}

/**
 * Provides a mechanism to write several OpSw values in a sequence. The
 * sequence is defined by the nextState method.
 */
/*public*/ void AbstractBoardProgPanel::writeAll()
{
 // check the address
 if(!setAddress(256))
 {
  if (log->isDebugEnabled())
  {
   log->debug(tr("ERROR_WRITEALL_ABORTED") + " " /*+ e.getMessage()*/);
  }
  readAllButton->setSelected(false);
  writeAllButton->setSelected(false);
  status->setText(" ");
  return;
 }

 if (responseTimer == NULL)
 {
  initializeResponseTimer();
 }
 if (pacingTimer == NULL)
 {
  initializePacingTimer();
 }

 // copy over the display
 copyToOpsw();

 // Start the first operation
 read = false;
 state = 1;
 // specify as single request, not multiple
 onlyOneOperation = false;
 nextRequest();
}

/**
 * writeOne() is intended to provide a mechanism to write a single OpSw
 * value (specified by opswIndex), rather than a sequence of OpSws as done
 * by writeAll().
 * <p>
 * @param opswIndex <p>
 * @see jmri.jmrix.loconet.AbstractBoardProgPanel#writeAll()
 */
/*public*/ void AbstractBoardProgPanel::writeOne(int opswIndex)
{
 // check the address
 if(!setAddress(256))
 {
  if (log->isDebugEnabled())
  {
   log->debug(tr("ERROR_WRITEONE_ABORTED") + " " /*+ e.getMessage()*/);
  }
  readAllButton->setSelected(false);
  writeAllButton->setSelected(false);
  status->setText(" ");
  return;
 }

 // copy over the displayed value
 copyToOpsw();

 // Start the first operation
 read = false;
 state = opswIndex;

 // specify as single request, not multiple
 onlyOneOperation = true;
 nextRequest();
}

/**
 * Processes incoming LocoNet message m for OpSw responses to read and write
 * operation messages, and automatically advances to the next OpSw operation
 * as directed by nextState().
 * <p>
 * @param m
 */
/*public*/ void AbstractBoardProgPanel::message(LocoNetMessage* m) {
    if (log->isDebugEnabled()) {
        log->debug(tr("DEBUG_PARSING_LOCONET_MESSAGE") + " " + m->toString());
    }
    // are we reading? If not, ignore
    if (state == 0) {
        return;
    }
    // check for right type, unit
    if (m->getOpCode() != 0xb4
            || ((m->getElement(1) != 0x00) && (m->getElement(1) != 0x50))) {
        return;
    }

    // LACK with 0 in opcode; assume its to us.  Note that there
    // should be a 0x50 in the opcode, not zero, but this is what we
    // see...
    if (awaitingReply == true) {
        if (responseTimer != NULL) {
            if (responseTimer->isActive()) {
                // stop the response timer!
                responseTimer->stop();
            }
        }
    }

    bool value = false;
    if ((m->getElement(2) & 0x20) != 0) {
        value = true;
    }

    // update opsw array if LACK return status is not 0x7F
    if ((m->getElement(2) != 0x7f)) {
        // record this bit
        opsw[state] = value;
    }

    // show what we've got so far
    if (read) {
        updateDisplay();
    }

    // and continue through next state, if any
    doTheNextThing();
}

/**
 * Helps continue sequences of OpSw accesses.
 * <p>
 * Handles aborting a sequence of reads or writes when the GUI Read button
 * or the GUI Write button (as appropriate for the current operation) is
 * de-selected.
 */
/*public*/ void AbstractBoardProgPanel::doTheNextThing() {
    int origState;
    origState = state;
    if (origState != 0) {
        state = nextState(origState);
    }
    if ((origState == 0) || (state == 0)) {
        // done with sequence
        readAllButton->setSelected(false);
        writeAllButton->setSelected(false);
        if (origState != 0) {
            status->setText(tr("Done"));
        } else {
            status->setText(tr("ERROR_ABORTED_DUE_TO_TIMEOUT"));
        }
        // nothing more to do
        return;
    } else {
        // are not yet done, so create and send the next OpSw request message
        nextRequest();
        return;
    }
}

///*private*/ java.awt.event.ActionListener responseTimerListener = new java.awt.event.ActionListener() {

//    /*public*/ void actionPerformed(ActionEvent e) {
void AbstractBoardProgPanel::On_ResponseTimer_timeout()
{
 if (responseTimer->isActive())
 {
  // odd case - not sure why would get an event if the timer is not running.
 }
 else
 {
  if (awaitingReply == true)
  {
   // Have a case where are awaiting a reply from the device,
   // but the response timer has expired without a reply.

   if (replyTryCount < MAX_OPSW_ACCESS_RETRIES) {
       // have not reached maximum number of retries, so try
       // the access again
       replyTryCount++;
       log->debug("retrying(" + QString::number(replyTryCount) + ") access to OpSw" + QString::number(state));
       responseTimer->stop();
       delayedNextRequest();
       return;
   }

   // Have reached the maximum number of retries for accessing
   // a given OpSw.
   // Cancel the ongoing process and update the status line.
   log->warn("Reached OpSw access retry limit of " + QString::number(MAX_OPSW_ACCESS_RETRIES) + " when accessing OpSw " + QString::number(state));
   awaitingReply = false;
   responseTimer->stop();
   state = 0;
   replyTryCount = 0;
   doTheNextThing();
  }
 }
}
//};

/*private*/ void AbstractBoardProgPanel::initializeResponseTimer()
{
 if (responseTimer == NULL)
 {
//     responseTimer = new QTimer(HALF_A_SECOND, responseTimerListener);
//     responseTimer->setRepeats(false);
//     responseTimer->stop();
//     responseTimer->setInitialDelay(HALF_A_SECOND);
//     responseTimer->setDelay(HALF_A_SECOND);
  responseTimer = new QTimer();
  responseTimer->setSingleShot(true);
  connect(responseTimer, SIGNAL(timeout()), this, SLOT(On_ResponseTimer_timeout()));
  responseTimer->start(HALF_A_SECOND);
 }
 return;
}

///*private*/ java.awt.event.ActionListener pacingTimerListener = new java.awt.event.ActionListener() {

//    /*public*/ void actionPerformed(ActionEvent e) {
/*private*/ void AbstractBoardProgPanel::On_pacingTimer_timeout()
{
        if (pacingTimer->isActive()) {
            // odd case - not sure why would get an event if the timer is not running.
            log->warn("Unexpected pacing timer event while OpSw access timer is running.");
        } else {
            pacingTimer->stop();
            delayedNextRequest();
        }
    }
//};

/*private*/ void AbstractBoardProgPanel::initializePacingTimer()
{
 if (pacingTimer == NULL)
 {
//  pacingTimer = new javax.swing.Timer(FIFTIETH_OF_A_SECOND, pacingTimerListener);
//  pacingTimer->setRepeats(false);
//  pacingTimer.stop();
//  pacingTimer->setInitialDelay(FIFTIETH_OF_A_SECOND);
//  pacingTimer->setDelay(FIFTIETH_OF_A_SECOND);
  pacingTimer = new QTimer();
  pacingTimer->setSingleShot(true);
  connect(pacingTimer, SIGNAL(timeout()), this, SLOT(On_pacingTimer_timeout()));
  pacingTimer->start(FIFTIETH_OF_A_SECOND);
 }
 return;
}

/*public*/ void AbstractBoardProgPanel::dispose()
{
 // Drop loconet connection
 if (memo->getLnTrafficController() != NULL) {
     //memo->getLnTrafficController()->removeLocoNetListener(~0, this);
     disconnect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 LnPanel::dispose();

 // stop all timers (if necessary) before disposing of this class
 if (responseTimer != NULL) {
     responseTimer->stop();
 }
 if (pacingTimer != NULL) {
     pacingTimer->stop();
 }
}

