#include "abstractaudiothread.h"
#include "sleeperthread.h"

//AbstractAudioThread::AbstractAudioThread(QObject *parent) :
//  AudioThread(parent)
//{
//}
/**
 * Base implementation of all common thread code for use by threads in the
 * various Audio classes.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28771 $
 */
// /*public*/ abstract class AbstractAudioThread extends Thread implements AudioThread {

long AbstractAudioThread::counter = 0;
/**
 * Default constructor that gives this thread a unique name based on the
 * value of the static counter
 */
/*public*/ AbstractAudioThread::AbstractAudioThread(QObject *parent)
 : AudioThread(parent)
{
 this->setObjectName("audio-" + QString::number(counter++));
 _alive = true;
}

/**
 * Perform necessary cleanup routines before shutting down
 */
/*protected*/ void AbstractAudioThread::cleanup()
{

    // Thread is to shutdown
    die(SET, true);

    // End of thread
    alive(SET, false);
}

//@Override
/*public*/ bool AbstractAudioThread::alive() {
    return alive(GET, NA);
}

//@Override
/*public*/ void AbstractAudioThread::die() {
    die(SET, true);
}

/**
 * Checks if the thread is in the process of shutting down
 *
 * @return true, if thread should die
 */
/*protected*/ bool AbstractAudioThread::dying() {
    return die(GET, NA);
}

/**
 * Based on the 'action' parameter, sets or returns if the thread is running
 *
 * @param action GET or SET
 * @param value  for action==SET, new value; for action==GET, NA
 * @return true, when thread is alive
 */
/*private*/ /*synchronized*/ bool AbstractAudioThread::alive(bool action, bool  value) {
    if (action == SET) {
        _alive = value;
    }
    return _alive;
}

/**
 * Based on the 'action' parameter, sets or returns if the thread should die
 *
 * @param action GET or SET
 * @param value  for action==SET, new value; for action==GET, NA
 * @return true, when thread should die
 */
/*private*/ /*synchronized*/ bool AbstractAudioThread::die(bool action, bool value) {
    if (action == SET) {
        _die = value;
    }
    return _die;
}

/**
 * Sleep for the specified number of milliseconds
 * <p>
 * (Avoids cluttering the main code with the try-catch construct)
 *
 * @param ms number of milliseconds to sleep for
 */
/*protected*/ /*static*/ void AbstractAudioThread::snooze(long ms) {
//    try {
        SleeperThread::msleep(ms);
//    } catch (InterruptedException ex) {
//    }
}
//}
