#include "autoturnouts.h"
#include "instancemanager.h"
#include "turnoutmanager.h"
#include "section.h"
#include "activetrain.h"
#include "transit.h"
#include "logger.h"
#include "dispatcherframe.h"
#include "connectivityutil.h"
#include <entrypoint.h>
#include "block.h"
#include "layoutslip.h"
#include "turnout.h"

//AutoTurnouts::AutoTurnouts(QObject *parent) : QObject(parent)
//{

//}
/**
 * Handles automatic checking and setting of turnouts when Dispatcher allocates
 * a Section in a specific direction.
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author	Dave Duchamp Copyright (C) 2008-2009
 */
///*public*/ class AutoTurnouts {

//    static final ResourceBundle rb = ResourceBundle
//            .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");

/*public*/ AutoTurnouts::AutoTurnouts(DispatcherFrame* d) {
 log = new Logger("AutoTurnouts");
 closedText = InstanceManager::turnoutManagerInstance()->getClosedText();
 thrownText = InstanceManager::turnoutManagerInstance()->getThrownText();
 // operational variables
 _dispatcher = NULL;
 userInformed = false;

    _dispatcher = d;
}



/**
 * Check that all turnouts are correctly set for travel in the designated
 * Section to the next Section.
 *
 * Returns 'true' if affected turnouts are correctly set, returns 'false'
 * otherwise. If arguments are not valid for this Section, returns 'false',
 * and issues an error message. NOTE: This method requires use of the
 * connectivity stored in a Layout Editor panel.
 */
/*protected*/ bool AutoTurnouts::checkTurnoutsInSection(Section* s, int seqNum, Section* nextSection,
        ActiveTrain* at, LayoutEditor* le, Section* prevSection) {
    return turnoutUtil(s, seqNum, nextSection, at, le, false, false, prevSection);
}

/**
 * Set all turnouts for travel in the designated Section to the next
 * Section.
 *
 * Checks that all turnouts are correctly set for travel in this Section to
 * the next Section, and sets any turnouts that are not correct. The Section
 * must be FREE to set its turnouts. Testing for FREE only occurs if a
 * command needs to be issued. For a command to be issued to set a turnout,
 * the Block containing that turnout must be unoccupied. NOTE: This method
 * does not wait for turnout feedback--it assumes the turnout will be set
 * correctly if a command is issued. Returns 'true' if affected turnouts are
 * correctly set or commands have been issued to set any that aren't set
 * correctly. If a needed command could not be issued because the turnout's
 * Block is occupied, returns 'false' and sends a warn message. If arguments
 * are not valid for this Transit, returns 'false', and issues an error
 * message. NOTE: This method requires use of the connectivity stored in a
 * Layout Editor panel.
 */
/*protected*/ bool AutoTurnouts::setTurnoutsInSection(Section* s, int seqNum, Section* nextSection,
        ActiveTrain* at, LayoutEditor* le, bool trustKnownTurnouts, Section* prevSection) {
    return turnoutUtil(s, seqNum, nextSection, at, le, trustKnownTurnouts, true, prevSection);
}

/**
 * Internal method implementing the above two methods Returns 'true' if
 * turnouts are set correctly, 'false' otherwise If 'set' is 'true' this
 * routine will attempt to set the turnouts, if 'false' it reports what it
 * finds.
 */
/*private*/ bool AutoTurnouts::turnoutUtil(Section* s, int seqNum, Section* nextSection,
        ActiveTrain* at, LayoutEditor* le, bool trustKnownTurnouts, bool set, Section* prevSection) {
    // validate input and initialize
    Transit* tran = at->getTransit();
    if ((s == NULL) || (seqNum > tran->getMaxSequence()) || (!tran->containsSection(s)) || (le == NULL)) {
        log->error("Invalid argument when checking or setting turnouts in Section.");
        return false;
    }
    int direction = at->getAllocationDirectionFromSectionAndSeq(s, seqNum);
    if (direction == 0) {
        log->error("Invalid Section/sequence arguments when checking or setting turnouts");
        return false;
    }
    // Did have this set to include SignalMasts as part of the && statement
    //Sections created using Signal masts will generally only have a single entry/exit point.
    // check for no turnouts in this section
    if (_dispatcher->getSignalType() == DispatcherFrame::SIGNALHEAD && (s->getForwardEntryPointList()->size() <= 1) && (s->getReverseEntryPointList()->size() <= 1)) {
        log->debug("No entry points lists");
        // no possibility of turnouts
        return true;
    }
    // initialize connectivity utilities and beginning block pointers
    ConnectivityUtil* ct = le->getConnectivityUtil();
    EntryPoint* entryPt = NULL;
    if (prevSection != NULL) {
        entryPt = s->getEntryPointFromSection(prevSection, direction);
    } else if (!s->containsBlock(at->getStartBlock())) {
        entryPt = s->getEntryPointFromBlock(at->getStartBlock(), direction);
    }
    EntryPoint* exitPt = NULL;
    if (nextSection != NULL) {
        exitPt = s->getExitPointToSection(nextSection, direction);
    }
    Block* curBlock = NULL;    // must be in the section
    Block* prevBlock = NULL;	  // must start outside the section or be NULL
    int curBlockSeqNum = -1;   // sequence number of curBlock in Section
    if (entryPt != NULL) {
        curBlock = entryPt->getBlock();
        prevBlock = entryPt->getFromBlock();
        curBlockSeqNum = s->getBlockSequenceNumber(curBlock);
    } else if (s->containsBlock(at->getStartBlock())) {
        curBlock = at->getStartBlock();
        curBlockSeqNum = s->getBlockSequenceNumber(curBlock);
        //Get the previous block so that we can set the turnouts in the current block correctly.
        if (direction == Section::FORWARD) {
            prevBlock = s->getBlockBySequenceNumber(curBlockSeqNum - 1);
        } else if (direction == Section::REVERSE) {
            prevBlock = s->getBlockBySequenceNumber(curBlockSeqNum + 1);
        }
    } else {

        if (_dispatcher->getSignalType() == DispatcherFrame::SIGNALMAST) {
            //This can be considered normal where SignalMast Logic is used.
            return true;
        }
        log->error("Error in turnout check/set request - initial Block and Section mismatch");
        return false;
    }

    Block* nextBlock = NULL;
    // may be either in the section or the first block in the next section
    int nextBlockSeqNum = -1;   // sequence number of nextBlock in Section (-1 indicates outside Section)
    if (exitPt != NULL && curBlock == exitPt->getBlock()) {
        // next Block is outside of the Section
        nextBlock = exitPt->getFromBlock();
    } else {
        // next Block is inside the Section
        if (direction == Section::FORWARD) {
            nextBlock = s->getBlockBySequenceNumber(curBlockSeqNum + 1);
            nextBlockSeqNum = curBlockSeqNum + 1;
        } else if (direction == Section::REVERSE) {
            nextBlock = s->getBlockBySequenceNumber(curBlockSeqNum - 1);
            nextBlockSeqNum = curBlockSeqNum - 1;
        }
        if ((nextBlock == NULL) && (curBlock != at->getEndBlock())) {
            log->error("Error in block sequence numbers when setting/checking turnouts");
            return false;
        }
    }

    QVector<LayoutTurnout*>* turnoutList = new QVector<LayoutTurnout*>();
    QVector<int>* settingsList = new QVector<int>();
    // get turnouts by Block
    bool turnoutsOK = true;
    while (curBlock != NULL) {
        /*No point in getting the list if the previous block is NULL as it will return empty and generate an error,
         this will only happen on the first run.  Plus working on the basis that the turnouts in the current block would have already of
         been set correctly for the train to have arrived in the first place.
         */
        if (prevBlock != NULL) {
            turnoutList = ct->getTurnoutList(curBlock, prevBlock, nextBlock);
            settingsList = ct->getTurnoutSettingList();
        }
        // loop over turnouts checking and optionally setting turnouts
        for (int i = 0; i < turnoutList->size(); i++) {
            Turnout* to = turnoutList->at(i)->getTurnout();
            int setting = settingsList->at(i);
            //if (turnoutList->at(i) instanceof LayoutSlip) {
            if(qobject_cast<LayoutSlip*>(turnoutList->at(i)))
            {
                setting = ((LayoutSlip*) turnoutList->at(i))->getTurnoutState(settingsList->at(i));
            }
            // check or ignore current setting based on flag, set in Options
            if (!trustKnownTurnouts) {
                log->debug(tr("%1: setting turnout %2 to %3").arg(at->getTrainName()).arg( to->getFullyFormattedDisplayName()).arg(
                        (setting==Turnout::CLOSED ? closedText : thrownText)));
                to->setCommandedState(setting);
                //try { Thread.sleep(100); } catch(Exception ex) {}  //TODO: move this to separate thread
                SleeperThread::msleep(100);
            } else {
                if (to->getKnownState() != setting) {
                    // turnout is not set correctly
                    if (set) {
                        // setting has been requested, is Section free and Block unoccupied
                        if ((s->getState() == Section::FREE) && (curBlock->getState() != Block::OCCUPIED)) {
                            // send setting command
                            log->debug(tr("%1: turnout %2 commanded to %3").arg(at->getTrainName()).arg( to->getFullyFormattedDisplayName()).arg(
                                    (setting==Turnout::CLOSED ? closedText : thrownText)));
                            to->setCommandedState(setting);
                            //try { Thread.sleep(100); } catch(Exception ex) {}  //TODO: move this to separate thread
                            SleeperThread::msleep(100);
                        } else {
                            turnoutsOK = false;
                        }
                    } else {
                        turnoutsOK = false;
                    }
                } else {
                    log->debug(tr("%1: turnout %2 already %3, skipping").arg(at->getTrainName()).arg( to->getFullyFormattedDisplayName()).arg(
                            (setting==Turnout::CLOSED ? closedText : thrownText)));
                }
            }
            //if (turnoutList.get(i) instanceof LayoutSlip) {
            if(qobject_cast<LayoutSlip*>(turnoutList->at(i)))
            {
                //Look at the state of the second turnout in the slip
                setting = ((LayoutSlip*) turnoutList->at(i))->getTurnoutBState(settingsList->at(i));
                to = ((LayoutSlip*) turnoutList->at(i))->getTurnoutB();
                if (!trustKnownTurnouts) {
                    to->setCommandedState(setting);
                } else if (to->getKnownState() != setting) {
                    // turnout is not set correctly
                    if (set) {
                        // setting has been requested, is Section free and Block unoccupied
                        if ((s->getState() == Section::FREE) && (curBlock->getState() != Block::OCCUPIED)) {
                            // send setting command
                            to->setCommandedState(setting);
                        } else {
                            turnoutsOK = false;
                        }
                    } else {
                        turnoutsOK = false;
                    }
                }
            }
        }
        if (turnoutsOK) {
            // move to next Block if any
            if (nextBlockSeqNum >= 0) {
                prevBlock = curBlock;
                curBlock = nextBlock;
                curBlockSeqNum = nextBlockSeqNum;
                if ((exitPt != NULL) && (curBlock == exitPt->getBlock())) {
                    // next block is outside of the Section
                    nextBlock = exitPt->getFromBlock();
                    nextBlockSeqNum = -1;
                } else {
                    if (direction == Section::FORWARD) {
                        nextBlockSeqNum++;
                    } else {
                        nextBlockSeqNum--;
                    }
                    nextBlock = s->getBlockBySequenceNumber(nextBlockSeqNum);
                    if (nextBlock == NULL) {
                        // there is no next Block
                        nextBlockSeqNum = -1;
                    }
                }
            } else {
                curBlock = NULL;
            }
        } else {
            curBlock = NULL;
        }
    }
    return turnoutsOK;
}
