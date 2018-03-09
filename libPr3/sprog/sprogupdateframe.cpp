#include "sprogupdateframe.h"
#include "loggerfactory.h"
#include "jfilechooser.h"
#include "fileutil.h"
#include "sprogreply.h"
#include "joptionpane.h"
#include "sproghexfile.h"

using namespace Sprog;

/**
 * Frame for SPROG firmware update utility.
 *
 * Refactored
 *
 * @author Andrew Crosland Copyright (C) 2004
 * @author Andrew Berridge - Feb 2010 - removed implementation of SprogListener - wasn't
 * being used.
 */
//abstract /*public*/ class SprogUpdateFrame
//        extends jmri.util.JmriJFrame
//        implements SprogListener {





/*static*/ /*final*/ bool SprogUpdateFrame::UNKNOWN = false;
/*static*/ /*final*/ bool SprogUpdateFrame::KNOWN = true;

/*public*/ SprogUpdateFrame::SprogUpdateFrame(SprogSystemConnectionMemo* memo, QWidget* parent)
 : JmriJFrame(parent){
    //super();
 programButton = new QPushButton ();
 openFileChooserButton = new QPushButton ();
 setSprogModeButton = new QPushButton ();

 // to find and remember the hex file
 hexFileChooser = new JFileChooser(FileUtil::getUserFilesPath());
 // member declarations

 statusBar = new QLabel();
 hexFile = NULL;
 bootState = BootState::IDLE;
 V_SHORT_TIMEOUT = 5;
 SHORT_TIMEOUT = 500;
 LONG_TIMEOUT = 4000;
 timer = NULL;


 _memo = memo;
}

/*protected*/ QString SprogUpdateFrame::title() {
    return tr("SprogX Firmware Update", "");
}

/*protected*/ void SprogUpdateFrame::init() {
    // connect to the TrafficManager
    tc = _memo->getSprogTrafficController();
    tc->setSprogState(SprogConstants::SprogState::NORMAL);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void SprogUpdateFrame::dispose() {
    tc = NULL;
    _memo = NULL;
    JmriJFrame::dispose();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void SprogUpdateFrame::initComponents() {
    // the following code sets the frame's initial state
    programButton->setText(tr("Program"));
    programButton->setVisible(true);
    programButton->setEnabled(false);
    programButton->setToolTip(tr("Re-program the SPROG with new firmware"));

    openFileChooserButton->setText(tr("Select HexFile"));
    openFileChooserButton->setVisible(true);
    openFileChooserButton->setEnabled(false);
    openFileChooserButton->setToolTip(tr("Click here to select a hex file on disk to be loaded onto your SPROG"));

    setSprogModeButton->setText(tr("Set to SPROG Mode"));
    setSprogModeButton->setVisible(true);
    setSprogModeButton->setEnabled(false);
    setSprogModeButton->setToolTip(tr("Click here to set the SPROG II in SPROG mode"));

    statusBar->setVisible(true);
    statusBar->setText(" ");
//    statusBar->setHorizontalTextPosition(SwingConstants.LEFT);

    setTitle(title());
//    getContentPane()->setLayout(new BoxLayout(getContentPane(),
//            BoxLayout.Y_AXIS));
    contentPaneLayout = new QVBoxLayout(getContentPane());

    QWidget* paneA = new QWidget();
    //paneA->setLayout(new BoxLayout(paneA, BoxLayout.Y_AXIS));
    QVBoxLayout* paneALayout = new QVBoxLayout(paneA);

    QWidget* buttons1 = new QWidget();
    //buttons1->setLayout(new BoxLayout(buttons1, BoxLayout.X_AXIS));
    FlowLayout* buttons1Layout = new FlowLayout(buttons1);
    buttons1Layout->addWidget(openFileChooserButton);
    buttons1Layout->addWidget(programButton);

    QWidget* buttons2 = new QWidget();
   // buttons2->setLayout(new BoxLayout(buttons2, BoxLayout.X_AXIS));
    FlowLayout* buttons2Layout = new FlowLayout(buttons2);
    buttons2Layout->addWidget(setSprogModeButton);

    QWidget* status = new QWidget();
    //status->setLayout(new BoxLayout(status, BoxLayout.X_AXIS));
    QHBoxLayout* statusLayout = new QHBoxLayout(status);
    statusLayout->addWidget(statusBar);

    paneALayout->addWidget(buttons1);
    paneALayout->addWidget(buttons2);
    paneALayout->addWidget(status);

    contentPaneLayout->addWidget(paneA);

//    openFileChooserButton.addActionListener(new java.awt.event.ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            openFileChooserButtonActionPerformed(e);
//        }
//    });
    connect(openFileChooserButton, SIGNAL(clicked(bool)), this, SLOT(openFileChooserButtonActionPerformed()));

//    programButton.addActionListener(new java.awt.event.ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            programButtonActionPerformed(e);
//        }
//    });
    connect(programButton, SIGNAL(clicked(bool)), this, SLOT(programButtonActionPerformed()));

//    setSprogModeButton.addActionListener(new java.awt.event.ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            setSprogModeButtonActionPerformed(e);
//        }
//    });
    connect(setSprogModeButton, SIGNAL(clicked(bool)), this, SLOT(setSprogModeButtonActionPerformed()));

    // connect to data source
    init();

    // Don't connect to help here, let the subclasses do it
    // prevent button areas from expanding
    pack();
    paneA->setMaximumSize(paneA->size());
//        pack();
}

//@Override
/*public*/ void SprogUpdateFrame::notifyMessage(SprogMessage* m) {
}

/**
 * State machine to catch replies that calls functions to handle each state.
 * <p>
 * These functions can be overridden for each SPROG type.
 *
 * @param m the SprogReply received from the SPROG
 */
//@Override
/*synchronized*/ /*public*/ void SprogUpdateFrame::notifyReply(SprogReply* m) {
    reply = m;
    frameCheck();
    replyString = m->toString();
    switch (bootState) {
        case IDLE:
            stateIdle();
            break;
        case SETBOOTSENT:           // awaiting reply from bootloader
            stateSetBootSent();
            break;
        case VERREQSENT:            // awaiting reply to version request
            stateBootVerReqSent();
            break;
        case WRITESENT:             // write flash command sent, waiting reply
            stateWriteSent();
            break;
        case ERASESENT:             // erase sent
            stateEraseSent();
            break;
        case SPROGMODESENT:         // enable sprog mode sent
            stateSprogModeSent();
            break;
        case RESETSENT:             // reset sent
            stateResetSent();
            break;
        case EOFSENT:               // v4 end of file sent
            stateEofSent();
            break;
        case V4RESET:               // wait for v4 to reset
            stateV4Reset();
            break;
        default:
            stateDefault();
            break;
    }
}

/*protected*/ void SprogUpdateFrame::frameCheck() {
}

/*protected*/ void SprogUpdateFrame::stateIdle() {
    if (log->isDebugEnabled()) {
        log->debug("reply in IDLE state");
    }
}

/*protected*/ void SprogUpdateFrame::stateSetBootSent() {
}

/*protected*/ void SprogUpdateFrame::stateBootVerReqSent() {
}

/*protected*/ void SprogUpdateFrame::stateWriteSent() {
}

/*protected*/ void SprogUpdateFrame::stateEraseSent() {
}

/*protected*/ void SprogUpdateFrame::stateSprogModeSent() {
}

/*protected*/ void SprogUpdateFrame::stateResetSent() {
}

/*protected*/ void SprogUpdateFrame::stateEofSent() {
}

/*protected*/ void SprogUpdateFrame::stateV4Reset() {
}

/*synchronized*/ /*protected*/ void SprogUpdateFrame::stateDefault() {
    // Houston, we have a problem
    if (log->isDebugEnabled()) {
        log->debug("Reply in unknown state");
    }
    bootState = BootState::IDLE;
    tc->setSprogState(SprogConstants::SprogState::NORMAL);
}

// Normally this happens well before the transfer thread
// is kicked off, but it's synchronized anyway to control
// access to shared hexFile variable.
/*synchronized*/ /*public*/ void SprogUpdateFrame::openFileChooserButtonActionPerformed(/*ActionEvent e*/) {
    // start at current file, show dialog
    int retVal = hexFileChooser->showOpenDialog(this);

    // handle selection or cancel
    if (retVal == JFileChooser::APPROVE_OPTION) {
        hexFile = new SprogHexFile(hexFileChooser->getSelectedFile()->getPath());
        if (log->isDebugEnabled()) {
            log->debug("hex file chosen: " + hexFile->getName());
        }
        if ((hexFile->getName().indexOf("sprog") < 0)) {
            JOptionPane::showMessageDialog(this, tr("HexFileSelectDialogString"),
                    tr("Hex File Select"), JOptionPane::ERROR_MESSAGE);
            hexFile = NULL;
        } else {
            hexFile->openRd();
            programButton->setEnabled(true);
        }
    }
}

/*public*/ /*synchronized*/ void SprogUpdateFrame::programButtonActionPerformed(/*ActionEvent e*/) {
}

/*public*/ void SprogUpdateFrame::setSprogModeButtonActionPerformed(/*ActionEvent e*/) {
}

///*abstract*/ /*protected*/ void SprogUpdateFrame::requestBoot() = 0;

///*abstract*/ /*protected*/ void SprogUpdateFrame::sendWrite() = 0;

///*abstract*/ /*protected*/ void SprogUpdateFrame::doneWriting() = 0;

/**
 * Internal routine to handle a timeout.
 */
/*synchronized*/ /*protected*/ void SprogUpdateFrame::timeout() {
    if (bootState == BootState::CRSENT) {
        if (log->isDebugEnabled()) {
            log->debug("timeout in CRSENT - assuming boot mode");
            // we were looking for a SPROG in normal mode but have had no reply
            // so maybe it was already in boot mode.
            // Try looking for bootloader
        }
        requestBoot();
    } else if (bootState == BootState::VERREQSENT) {
        log->error("timeout in VERREQSENT!");
        JOptionPane::showMessageDialog(this, tr("Unable to connect to bootloader."),
                tr("Fata lError"), JOptionPane::ERROR_MESSAGE);
        statusBar->setText(tr("Fatal error - unable to connect"));
        bootState = BootState::IDLE;
        tc->setSprogState(SprogConstants::SprogState::NORMAL);
    } else if (bootState == BootState::WRITESENT) {
        log->error("timeout in WRITESENT!");
        // This is fatal!
        JOptionPane::showMessageDialog(this, tr("Timeout during write to SPROG."),
                tr("FatalErrorTitle"), JOptionPane::ERROR_MESSAGE);
        statusBar->setText(tr("ErrorTimeoutStatus"));
        bootState = BootState::IDLE;
        tc->setSprogState(SprogConstants::SprogState::NORMAL);
    } else if (bootState == BootState::NULLWRITE) {
        if (hexFile->read() > 0) {
            // More data to write
            sendWrite();
        } else {
            doneWriting();
        }
    }
}


/**
 * Internal routine to start very short timer for NULL writes.
 */
/*protected*/ void SprogUpdateFrame::startVShortTimer() {
    restartTimer(V_SHORT_TIMEOUT);
}

/**
 * Internal routine to start timer to protect the mode-change.
 */
/*protected*/ void SprogUpdateFrame::startShortTimer() {
    restartTimer(SHORT_TIMEOUT);
}

/**
 * Internal routine to restart timer with a long delay.
 */
/*synchronized*/ /*protected*/ void SprogUpdateFrame::startLongTimer() {
    restartTimer(LONG_TIMEOUT);
}

/**
 * Internal routine to stop timer, as all is well.
 */
/*synchronized*/ /*protected*/ void SprogUpdateFrame::stopTimer() {
    if (timer != NULL) {
        timer->stop();
    }
}

/**
 * Internal routine to handle timer starts {@literal &} restarts.
 */
/*synchronized*/ /*protected*/ void SprogUpdateFrame::restartTimer(int delay) {
    if (timer == NULL) {
        timer = new QTimer(); //delay, new java.awt.event.ActionListener() {
//            //@Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                timeout();
//            }
//        });
        connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    }
    timer->stop();
//    timer->setInitialDelay(delay);
    timer->setSingleShot(true);//setRepeats(false);
    timer->start(delay);
}

/*private*/ /*final*/ /*static*/ Logger* SprogUpdateFrame::log = LoggerFactory
        ::getLogger("SprogUpdateFrame");
