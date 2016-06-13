#ifndef AUDIO_H
#define AUDIO_H
#include "abstractnamedbean.h"
#include <QtMultimedia/qaudio.h>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT Audio :  public AbstractNamedBean
{
  Q_OBJECT
public:
 explicit Audio(QString systemName, QObject *parent = 0);
 Audio(QString systemName, QString userName, QObject *parent = 0);
    /**
     * Represent an Audio, a place to store or control sound information.
     * <P>
     * The AbstractAudio class contains a basic implementation of the state and messaging
     * code, and forms a useful start for a system-specific implementation.
     * Specific implementations in the jmrix package, e.g. for LocoNet and NCE, will
     * convert to and from the layout commands.
     * <P>
     * The states  and names are Java Bean parameters, so that listeners can be
     * registered to be notified of any changes.
     * <P>
     * Each Audio object has a two names.  The "user" name is entirely free form, and
     * can be used for any purpose.  The "system" name is provided by the system-specific
     * implementations, and provides a unique mapping to the layout control system
     * (e.g. LocoNet, NCE, etc) and address within that system.
     * <P>
     *
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
     * @author  Matthew Harris copyright (c) 2009
     * @version $Revision: 21734 $
     */
//    public interface Audio extends NamedBean {

        // Define Object sub-type constants

        /**
         * Definition of AudioSource NamedBean sub-type code
         */
        static const QChar SOURCE;//    = 'S';

        /**
         * Definition of AudioBuffer NamedBean sub-type code
         */
        static const QChar BUFFER;//    = 'B';

        /**
         * Definition of AudioListener NamedBean sub-type code
         */
        static const QChar LISTENER;//  = 'L';

        // Define orientation constants

        /**
         * Definition of Audio object orientation at vector code
         */
        const static int AT = 0x01;

        /**
         * Definition of Audio object orientation up vector code
         */
        const static int UP = 0x02;

        // Define state variables for Audio objects

        /**
         * Default state for any newly created Audio object
         */
        const static int STATE_INITIAL    =/* 0x00*/QAudio::IdleState; // 3

        // Define applicable states for Source sub-types

        /**
         * State code for an AudioSource when stopped
         */
        const static int STATE_STOPPED    = /*0x10*/QAudio::SuspendedState; // 2

        /**
         * State code for an AudioSource when playing
         */
        const static int STATE_PLAYING    = /*0x11*/QAudio::ActiveState; // 0

        // Define applicable states for Buffer sub-types

        /**
         * State code for an AudioBuffer when empty
         */
        const static int STATE_EMPTY      = 0x20;

        /**
         * State code for an AudioBuffer when loaded
         */
        const static int STATE_LOADED     = 0x21;

        // Define applicable states for Listener sub-types

        /**
         * State code for an AudioListener when positioned
         */
        const static int STATE_POSITIONED;// = 0x30;

        /**
         * State code for an AudioListener when moving
         */
        const static int STATE_MOVING;//     = 0x31;

        // Define Audio command constants

        // Constants defining Factory related commands

        /**
         * Command to initialise AudioFactory
         */
        const static int CMD_INIT_FACTORY = 0x01;

        // Constants defining Buffer related commands

        /**
         * Command to load the sound
         */
        const static int CMD_LOAD_SOUND = 0x20;

        // Constants defining Source related commands

        /**
         * Command to bind Buffer to Source
         */
        const static int CMD_BIND_BUFFER = 0x30; // (48)

        /**
         * Command to queue Buffer to Source
         */
        const static int CMD_QUEUE_BUFFERS = 0x31;

        /**
         * Command to unqueue used Buffers from Source
         */
        const static int CMD_UNQUEUE_BUFFERS = 0x32;

        /**
         * Command to play this Source from the beginning
         */
        const static int CMD_PLAY = 0x40;

        /**
         * Command to stop playing this Source and rewind to the start
         */
        const static int CMD_STOP = 0x41; // (65)

        /**
         * Command to start or stop this Source from the beginning
         */
        const static int CMD_PLAY_TOGGLE = 0x42;

        /**
         * Command to pause playback of this Source and retain the position
         */
        const static int CMD_PAUSE = 0x43;

        /**
         * Command to resume playback of this Source from the current position
         */
        const static int CMD_RESUME = 0x44;

        /**
         * Command to pause or resume this Source from the current position
         */
        const static int CMD_PAUSE_TOGGLE = 0x45;

        /**
         * Command to rewind this Source to the beginning
         */
        const static int CMD_REWIND = 0x46;

        /**
         * Command to fade in and start playback of this Source
         */
        const static int CMD_FADE_IN = 0x47;

        /**
         * Command to fade out and stop playback of this Source
         */
        const static int CMD_FADE_OUT = 0x48;

        /**
         * Command to reset the position of this Source
         */
        const static int CMD_RESET_POSITION = 0x49;

        // Define state variables for fade states

        /**
         * Fade state of Source when not fading
         */
        const static int FADE_NONE = 0x00;

        /**
         * Fade state of Source when fading out
         */
        const static int FADE_OUT = 0x01;

        /**
         * Fade state of Source when fading in
         */
        const static int FADE_IN = 0x02;

        /**
         * Maximum distance for Audio objects
         */
        /*const*/ static float MAX_DISTANCE;// = 9999.99f;

        /**
         * Number of decimal places for float values to be stored in
         */
        /*const*/ static double DECIMAL_PLACES;// = 2;

        /**
         * An Audio object can represent one of a number of subtypes of object.
         * <p>
         * This method enables us to determine which of those subtypes this
         * particular instance is and be able to process accordingly.
         * <p>
         * Current supported subtypes are:
         * <ul>
         * <li>B = Buffer
         * <li>L = Listener
         * <li>S = Source
         * </ul>
         * @return subType char
         */
        virtual QChar getSubType() {return ' ';}

        /**
         * Method used to update the current state of the Audio object
         */
        virtual void stateChanged(int /*oldState*/) {}
        virtual QString toString() {return "";}
signals:
    
public slots:
    private:
        void common();
 friend class AbstractAudioListener;
};

#endif // AUDIO_H
