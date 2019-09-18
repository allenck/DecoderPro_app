#include "proglistenerscaffold.h"

/**
 * Scaffold implementation of Programmer Listener interface for testing.
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 *
 * @see jmri.Programmer
 * @author	Paul Bender Copyright (C) 2013
 */
// /*public*/ class ProgListenerScaffold implements ProgListener {

    /*public*/ ProgListenerScaffold::ProgListenerScaffold() {
        rcvdInvoked = 0;
        rcvdValue = -1;
        rcvdStatus = -1;
        wasOnRightThread = false;
    }

    //@Override
    /*public*/ void ProgListenerScaffold::programmingOpReply(int value, int status) {
        rcvdValue = value;
        rcvdStatus = status;
        rcvdInvoked++;
        wasOnRightThread = true; //jmri.util.ThreadingUtil.isGUIThread();
    }

    /*public*/ int ProgListenerScaffold::getRcvdValue() {
        return rcvdValue;
    }

    /*public*/ int ProgListenerScaffold::getRcvdStatus() {
        return rcvdStatus;
    }

    /*public*/ int ProgListenerScaffold::getRcvdInvoked() {
        return rcvdInvoked;
    }

    /*public*/ bool ProgListenerScaffold::wasRightThread() {
        return wasOnRightThread;
    }
