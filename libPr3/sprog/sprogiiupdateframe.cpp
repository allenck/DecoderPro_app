#include "sprogiiupdateframe.h"
#include "loggerfactory.h"
#include "fileutil.h"
#include "sprogversionquery.h"
#include "sleeperthread.h"
#include "sprogreply.h"
#include "joptionpane.h"
#include "sproghexfile.h"
#include "sprogtype.h"

using namespace Sprog;

/**
 * Frame for SPROG II firmware update utility.
 *
 * Extended to cover SPROG 3 which uses the same bootloader protocol Refactored
 *
 * @author	Andrew Crosland Copyright (C) 2004
 */
///*public*/ class SprogIIUpdateFrame
//        extends SprogUpdateFrame
//        implements SprogVersionListener {

/*public*/ SprogIIUpdateFrame::SprogIIUpdateFrame(SprogSystemConnectionMemo* memo, QWidget* parent )
  : SprogUpdateFrame(memo, parent)
{
    //super(memo);
 bootVer = 0;
 log->setDebugEnabled(true);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void SprogIIUpdateFrame::initComponents() {
    SprogUpdateFrame::initComponents();
    resize(300,300);

    // add help menu to window
    addHelpMenu("package.jmri.jmrix.sprog.update.SprogIIUpdateFrame", true);

    // Get the SPROG version
    _memo->getSprogVersionQuery()->requestVersion((SprogVersionListener*)this);
}


/**
 * {@inheritDoc}
 */
//@SuppressFBWarnings(value = "SWL_SLEEP_WITH_LOCK_HELD")
//@Override
/*synchronized*/ /*public*/ void SprogIIUpdateFrame::notifyVersion(SprogVersion* v)
{
 sv = v;
 if (sv->sprogType->isSprog() == false)
 {
  // Didn't recognize a SPROG so check if it is in boot mode already
  if (log->isDebugEnabled()) {
      log->debug("SPROG not found - looking for bootloader");
  }
  statusBar->setText(tr("SPROG not found - looking for bootloader"));
  blockLen = -1;
  requestBoot();
 }
 else
 {
  // Check that it's not a V4
  if (sv->sprogType ->_sprogType > SprogType::SPROGV4)
  {
   statusBar->setText(tr("Found %1").arg(sv->toString()));
   blockLen = sv->sprogType->getBlockLen();
   // Put SPROG in boot mode
   if (log->isDebugEnabled()) {
       log->debug("Putting SPROG in boot mode");
   }
   msg = new SprogMessage("b 1 1 1", 0);
   tc->sendSprogMessage(msg, (SprogListener*)this);
   // SPROG II and 3 will not reply to this so just wait a while
   tc->setSprogState(SprogConstants::SprogState::SIIBOOTMODE);
   try {
       //Thread.sleep(500);
    SleeperThread::msleep(500);
   } catch (InterruptedException e) {
// TODO:                Thread.currentThread().interrupt(); // retain if needed later
   }
   // Look for bootloader version
   requestBoot();
  }
  else
  {
   log->error("Incorrect SPROG Type detected");
   statusBar->setText(tr("Incorrect SPROG Type detected"));
   bootState = BootState::IDLE;
  }
 }
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::frameCheck()
{
 // If SPROG II is in boot mode, check message framing and checksum
 if ((bootState != BootState::RESETSENT) && tc->isSIIBootMode() && !reply->strip())
 {
     stopTimer();
     JOptionPane::showMessageDialog(this, tr("Malformed  bootloader reply.\nDid you remember to unlock the firmware?"),
             tr("Connect to Bootloader"), JOptionPane::ERROR_MESSAGE);
     log->error("Malformed bootloader reply");
     statusBar->setText(tr("Malformed bootloader reply"));
     bootState = BootState::IDLE;
     tc->setSprogState(SprogConstants::SprogState::NORMAL);
     return;
 }
 if ((bootState != BootState::RESETSENT) && tc->isSIIBootMode() && !reply->getChecksum()) {
     log->error("Bad bootloader checksum");
     statusBar->setText(tr("StatusBadBootloaderChecksum"));
     bootState = BootState::IDLE;
     tc->setSprogState(SprogConstants::SprogState::NORMAL);
 }
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::stateBootVerReqSent() {
    stopTimer();
    if (log->isDebugEnabled()) {
        log->debug("reply in VERREQSENT state");
    }
    // see if reply is the version
    if ((reply->getOpCode() == SprogMessage::RD_VER) && (reply->getElement(1) == 2)) {
        bootVer = reply->getElement(2);
        if (log->isDebugEnabled()) {
            log->debug("Found bootloader version " + bootVer);
        }
        statusBar->setText(tr("Connected to bootloader version %1").arg(bootVer));
        // Enable the file chooser button
        setSprogModeButton->setEnabled(true);
        openFileChooserButton->setEnabled(true);
        if (blockLen > 0) {
            // We think we already know the version
            if (blockLen != SprogType::getBlockLen(bootVer)) {
                log->error("Bootloader version does not match SPROG type");
                bootState = BootState::IDLE;
                return;
            }
        } else {
            // Don't yet have correct SPROG version
            if (bootVer <= 11) {
                // Force SPROG version SPROG II 1.x or 2.x
                sv = new SprogVersion(new SprogType(SprogType::SPROGII), "");
            } else {
                // Force SPROG version SPROG SPROG II v3.x (also covers IIv4, SPROG 3 and Nano)
                sv = new SprogVersion(new SprogType(SprogType::SPROGIIv3), "");
            }
            blockLen = sv->sprogType->getBlockLen();
            // We remain in this state until program button is pushed
        }
    } else {
        log->error("Bad reply to RD_VER request");
        bootState = BootState::IDLE;
        tc->setSprogState(SprogConstants::SprogState::NORMAL);
        JOptionPane::showMessageDialog(this, tr("Unable to connect to bootloader"),
                tr("SPROG%1 Firmware Update").arg(" II"), JOptionPane::ERROR_MESSAGE);
        statusBar->setText(tr("Unable to connect to bootloader"));
        return;
    }
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::stateWriteSent() {
    stopTimer();
    if (log->isDebugEnabled()) {
        log->debug("reply in WRITESENT state");
    }
    // Check for correct response to type of write that was sent
    if ((reply->getOpCode() == msg->getElement(2)) && (reply->getNumDataElements() == 1)
            || (reply->getElement(reply->getNumDataElements() - 1) == '.')) {
        if (hexFile->read() > 0) {
            // More data to write
            sendWrite();
        } else {
            doneWriting();
        }
    } else {
        // Houston, we have a problem
//            JOptionPane.showMessageDialog(this, tr("StatusBadReplyWriteRequest"),
//                                        tr("SprogXFirmwareUpdate", " II"), JOptionPane.ERROR_MESSAGE);
        log->error("Bad reply to write request");
        statusBar->setText(tr("StatusBadReplyWriteRequest"));
        bootState = BootState::IDLE;
        tc->setSprogState(SprogConstants::SprogState::NORMAL);
        return;
    }
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::stateEraseSent() {
    stopTimer();
    if (log->isDebugEnabled()) {
        log->debug("reply in ERASESENT state");
    }
    // Check for correct response to erase that was sent
    if ((reply->getOpCode() == msg->getElement(2)) && (reply->getNumDataElements() == 1)) {
        // Don't erase ICD debug executive if in use
        if ((sv->sprogType->_sprogType < SprogType::SPROGIIv3) && (eraseAddress < 0x7c00)
                || (sv->sprogType->_sprogType >= SprogType::SPROGIIv3) && (eraseAddress < 0x3F00)) {
            // More data to erase
            sendErase();
        } else {
            if (log->isDebugEnabled()) {
                log->debug("Finished erasing");
            }
            statusBar->setText(tr("StatusEraseComplete"));
            // Read first line from hexfile
            if (hexFile->read() > 0) {
                // Program line and wait for reply
                if (log->isDebugEnabled()) {
                    log->debug(tr("First write %1 %2").arg(hexFile->getLen()).arg(hexFile->getAddress()));
                }
                sendWrite();
            } else {
                doneWriting();
            }
        }
    } else {
        // Houston, we have a problem
//        JOptionPane.showMessageDialog(this, tr("StatusBadReplyErase"),
//                                        tr("SprogXFirmwareUpdate", " II"), JOptionPane.ERROR_MESSAGE);
        log->error("Bad reply to erase request");
        bootState = BootState::IDLE;
        tc->setSprogState(SprogConstants::SprogState::NORMAL);
        return;
    }
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::stateSprogModeSent() {
    stopTimer();
    if (log->isDebugEnabled()) {
        log->debug("reply in SROGMODESENT state");
    }
    // Check for correct response to type of write that was sent
    if ((reply->getOpCode() == msg->getElement(2)) && (reply->getNumDataElements() == 1)) {
        if (log->isDebugEnabled()) {
            log->debug("Reset SPROG");
        }
        msg = SprogMessage::getReset();
        bootState = BootState::RESETSENT;
        tc->sendSprogMessage(msg, (SprogListener*)this);
        startLongTimer();
    } else {
        // Houston, we have a problem
//        JOptionPane.showMessageDialog(this, tr("StatusBadReplyModeRequest"),
//                                        tr("SprogXFirmwareUpdate", " II"), JOptionPane.ERROR_MESSAGE);
        log->error("Bad reply to SPROG Mode request");
        bootState = BootState::IDLE;
        tc->setSprogState(SprogConstants::SprogState::NORMAL);
        return;
    }
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::stateResetSent() {
    stopTimer();
    if (log->isDebugEnabled()) {
        log->debug("reply in RESETSENT state");
    }
    // Check for correct response to type of write that was sent

    statusBar->setText(tr("DefaultStatusText")); // Ready, is in jmrixBundle

    tc->setSprogState(SprogConstants::SprogState::NORMAL);
    bootState = BootState::IDLE;
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::requestBoot() {
    // Look for SPROG in boot mode by requesting bootloader version.
    if (log->isDebugEnabled()) {
        log->debug("Request bootloader version");
    }
    // allow parsing of bootloader replies
    tc->setSprogState(SprogConstants::SprogState::SIIBOOTMODE);
    bootState = BootState::VERREQSENT;
    msg = SprogMessage::getReadBootVersion();
    tc->sendSprogMessage(msg, (SprogListener*)this);
    startLongTimer();
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::sendWrite() {
    if ((hexFile->getAddressU()&0xFF) >= 0xF0) {
        // Write to EEPROM
        if (log->isDebugEnabled()) {
            log->debug("Send write EE " + hexFile->getAddress());
        }
        msg = SprogMessage::getWriteEE(hexFile->getAddress(), hexFile->getData());
    } else if ((hexFile->getAddressU()&0xFF) >= 0x20) {
        // Write to user data or config data not supported
        if (log->isDebugEnabled()) {
            log->debug("NULL write " + hexFile->getAddress());
        }
        msg = NULL;
    } else if (sv->sprogType->isValidFlashAddress(hexFile->getAddress())) {
        // Program code address is above bootloader range and below debug executive
        if (log->isDebugEnabled()) {
            log->debug("Send write Flash " + hexFile->getAddress());
        }
        msg = SprogMessage::getWriteFlash(hexFile->getAddress(), hexFile->getData(), blockLen);
        if (log->isDebugEnabled()) {
            log->debug(msg->toString(true));
        }
    } else {
        // Do nothing
        if (log->isDebugEnabled()) {
            log->debug("NULL write " + hexFile->getAddress());
        }
        msg = NULL;
    }
    if (msg != NULL) {
        bootState = BootState::WRITESENT;
        statusBar->setText(tr("Write %1").arg(hexFile->getAddress()));
        tc->sendSprogMessage(msg, (SprogListener*)this);
        if (log->isDebugEnabled()) {
            log->debug("Sent write command to address " + hexFile->getAddress());
        }
        startLongTimer();
    } else {
        // use timeout to kick off the next write
        bootState = BootState::NULLWRITE;
        statusBar->setText(tr("Skip %1").arg(hexFile->getAddress()));
        startVShortTimer();
    }
}

/*synchronized*/ /*private*/ void SprogIIUpdateFrame::sendErase() {
    if (log->isDebugEnabled()) {
        log->debug("Erase Flash " + eraseAddress);
    }
    int rows = 8; // 512 bytes
    msg = SprogMessage::getEraseFlash(eraseAddress, rows);
    bootState = BootState::ERASESENT;
    statusBar->setText(tr("Erase %1").arg(eraseAddress));
    tc->sendSprogMessage(msg, (SprogListener*)this);
    if (log->isDebugEnabled()) {
        log->debug("Sent erase command to address " + eraseAddress);
    }
    eraseAddress += (rows * 64);
    startLongTimer();
}

//@Override
/*synchronized*/ /*protected*/ void SprogIIUpdateFrame::doneWriting() {
    // Finished
    if (log->isDebugEnabled()) {
        log->debug("Done writing");
    }
    statusBar->setText(tr("StatusWriteComplete"));
    openFileChooserButton->setEnabled(false);
    programButton->setEnabled(false);

    setSprogModeButton->setEnabled(true);
    bootState = BootState::IDLE;
}

//@Override
/*synchronized*/ /*public*/ void SprogIIUpdateFrame::programButtonActionPerformed(/*ActionEvent* e*/) {
    if (hexFile != NULL) {
        openFileChooserButton->setEnabled(false);
        programButton->setEnabled(false);
        setSprogModeButton->setEnabled(false);
        eraseAddress = sv->sprogType->getEraseStart();
        if (eraseAddress > 0) {
            if (log->isDebugEnabled()) {
                log->debug("Start erasing @" + eraseAddress);
            }
            sendErase();
        }
    }
}

//@Override
/*synchronized*/ /*public*/ void SprogIIUpdateFrame::setSprogModeButtonActionPerformed(/*ActionEvent e*/) {
    if (log->isDebugEnabled()) {
        log->debug("Set SPROG mode");
    }
    msg = SprogMessage::getWriteEE(0xff, QVector<int>());
    bootState = BootState::SPROGMODESENT;
    tc->sendSprogMessage(msg, (SprogListener*)this);
    startLongTimer();
}

/*public*/ QString SprogIIUpdateFrame::getClassName()
{
 return "jmri.jmrix.sprog.SprogIIUpdateFrame";
}

/*private*/ /*final*/ /*static*/ Logger* SprogIIUpdateFrame::log = LoggerFactory
        ::getLogger("SprogIIUpdateFrame");
