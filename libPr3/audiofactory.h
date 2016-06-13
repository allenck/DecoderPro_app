#ifndef AUDIOFACTORY_H
#define AUDIOFACTORY_H

#include <QObject>
#include "audiobuffer.h"
#include "audiocommand.h"
#include "audiolistener.h"
#include "libPr3_global.h"

class AudioListener;
class AudioSource;
class LIBPR3SHARED_EXPORT AudioFactory : public QObject
{
    Q_OBJECT
public:
 explicit AudioFactory(QObject *parent = 0) : QObject(parent) {}
    /**
     * An AudioFactory is responsible for the initialisation of specific audio
     * system implementations, creation of audio system specific Audio objects and
     * any necessary clean-up operations required by a specific audio system
     * implementation.
     * <p>
     * Each factory varies in its capabilities with regard the faithfulness of the
     * audio rendering model (such as spatial positioning approximation), number
     * of concurrent sounds (polyphony), hardware required, etc.
     * <p>
     * Current implemented audio systems include:
     * <ul>
     * <li>JOAL
     * <li>JavaSound
     * <li>Null (a catch-all which doesn't actually play any sounds)
     * </ul>
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
     * @author Matthew Harris  copyright (c) 2009
     * @version $Revision: 17977 $
     */
//    public interface AudioFactory {

        /**
         * Perform any implementation specific initialisation routines.
         *
         * @return true, if initialisation successful
         */
        virtual bool init() {return false;}

        /**
         * Perform any implementation specific clean-up operations.
         */
        virtual void cleanup() {}

        /**
         * Provide a specific new AudioBuffer object.
         *
         * @param systemName for this object instance
         * @param userName for this object instance
         * @return a new specific AudioBuffer
         */
        virtual AudioBuffer* createNewBuffer(QString /*systemName*/, QString /*userName*/) {return NULL;}

        /**
         * Provide a specific new AudioListener object.
         *
         * @param systemName for this object instance
         * @param userName for this object instance
         * @return a new specific AudioListener
         */
        virtual AudioListener* createNewListener(QString /*systemName*/, QString /*userName*/) {return NULL;}

        /**
         * Return the currently active Listener object
         *
         * @return active AudioListener
         */
        virtual AudioListener* getActiveAudioListener() {return NULL;}

        /**
         * Provide a specific new AudioSource object.
         *
         * @param systemName for this object instance
         * @param userName for this object instance
         * @return a new specific AudioSource
         */
        virtual AudioSource* createNewSource(QString /*systemName*/, QString /*userName*/) {return NULL;}

        /**
         * Queues a new AudioCommand for subsequent execution.
         * <p>
         * If newAudioCommand is null the current queue is executed and cleaned
         *
         * @param newAudioCommand AudioCommand to queue or null to execute queue
         * @return true, if further commands exist; false, if empty
         */
        virtual bool audioCommandQueue(AudioCommand* /*newAudioCommand*/) {return false;}

        /**
         * Return the currently active Command thread
         *
         * @return active CommandThread
         */
        virtual QThread* getCommandThread() {return NULL;}

        /**
         * Sets if this AudioFactory should attenuate sources based on their
         * distance from the listener
         * <p>
         * Default = true
         *
         * @param attenuated true if distance attenuation to be used
         */
        virtual void setDistanceAttenuated(bool /*attenuated*/) {}

        /**
         * Determines if this AudioFactory attenuates sources based on their
         * distance from the Listener
         *
         * @return true if distance attenuation used
         */
        virtual bool isDistanceAttenuated() {return false;}

signals:
    
public slots:
    
};

#endif // AUDIOFACTORY_H
