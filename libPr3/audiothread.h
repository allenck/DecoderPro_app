#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include "runnable.h"

/**
 * Interface defining public methods and variables used in AudioThread classes
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
 * @version $Revision: 28746 $
 */
/*public*/ /*interface*/ class  AudioThread : public  Runnable
{
public:
 AudioThread(QObject* parent) : Runnable(parent) {}
    /**
     * Used to return value from synchronised bool methods
     */
    /*public*/ static /*final*/ bool const GET = false;

    /**
     * Used to set value in synchronised bool methods
     */
    /*public*/ static /*final*/ bool const SET = true;

    /**
     * Used as parameter when returning value from synchronised bool methods
     */
    /*public*/ static /*final*/ bool const NA = false;

    /**
     * Checks if the thread is still alive (or in the process of shutting down)
     * <p>
     * Once cleanup has finished, this should return False
     *
     * @return true, while thread is alive; false, when all cleanup has finished
     */
    virtual /*public*/ bool alive() {return false;}

    /**
     * Method used to tell the thread that it should shutdown
     */
    virtual /*public*/ void die() {}
};
#endif // AUDIOTHREAD_H
