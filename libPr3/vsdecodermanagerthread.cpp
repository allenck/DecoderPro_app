#include "vsdecodermanagerthread.h"
#include "vsdecodermanager.h"

//VSDecoderManagerThread::VSDecoderManagerThread(QObject *parent) :
//  QThread(parent)
//{
//}
/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 28746 $
 */
//class VSDecoderManagerThread extends Thread {

    /*private*/ /*static*/ VSDecoderManagerThread* VSDecoderManagerThread::_instance = NULL;
    /*private*/ /*static*/ VSDecoderManager* VSDecoderManagerThread::_manager = NULL;

/*private*/ VSDecoderManagerThread::VSDecoderManagerThread(QObject *parent) :
QThread(parent) {
    //super();
    is_running = false;
}

/*public*/ /*static*/ VSDecoderManagerThread* VSDecoderManagerThread::instance(bool create)
{
 _manager = new VSDecoderManager();

 return (instance());
}

/*public*/ /*static*/ VSDecoderManagerThread* VSDecoderManagerThread::instance() {
    if (_instance == NULL) {
        VSDecoderManagerThread* temp = new VSDecoderManagerThread();
        temp->start();
        _instance = temp; // don't allow escape of VSDecoderManagerThread object until running

    }
    return (_instance);
}

/*public*/ /*static*/ VSDecoderManager* VSDecoderManagerThread::manager() {
    return (VSDecoderManagerThread::_manager);
}

//@Override
/*public*/ void VSDecoderManagerThread::run() {
    is_running = true;
    while (is_running) {
        // just nap.
        //try {
            sleep(20);
//        } catch (InterruptedException e) {
//        }
    }
    // all done.
}

/*public*/ void VSDecoderManagerThread::kill() {
    is_running = false;
}
