#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include "audio.h"
#include "audiobuffer.h"
#include <QVector3D>
#include <QQueue>
#include "libPr3_global.h"


/**
 * Represent an AudioSource, a place to store or control sound information.
 * <P>
 * The AbstractAudio class contains a basic implementation of the state and
 * messaging code, and forms a useful start for a system-specific
 * implementation. Specific implementations in the jmrix package, e.g. for
 * LocoNet and NCE, will convert to and from the layout commands.
 * <P>
 * The states and names are Java Bean parameters, so that listeners can be
 * registered to be notified of any changes.
 * <P>
 * Each AudioSource object has a two names. The "user" name is entirely free
 * form, and can be used for any purpose. The "system" name is provided by the
 * system-specific implementations, and provides a unique mapping to the layout
 * control system (e.g. LocoNet, NCE, etc) and address within that system.
 * <P>
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
/*public*/ /*interface*/ class LIBPR3SHARED_EXPORT AudioSource : public Audio {

public:
 AudioSource(QObject* parent = 0);
 AudioSource(QString systemName, QObject* parent = 0);
 AudioSource(QString systemName, QString userName, QObject* parent = 0);
    /**
     * Constant to define that this source should loop continously when played
     */
    /*public*/ static /*final*/ int LOOP_CONTINUOUS;// = -1;

    /**
     * Constant to define that this source should not loop when played
     */
    /*public*/ static /*final*/ int LOOP_NONE;// = 0;

    /**
     * Sets the position of this AudioSource object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @param pos 3d position vector
     */
    virtual /*public*/ void setPosition(QVector3D /*pos*/) {}

    /**
     * Sets the position of this AudioSource object in x, y and z planes
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @param x x-coordinate
     * @param y y-coordinate
     * @param z z-coordinate
     */
    virtual /*public*/ void setPosition(float /*x*/, float /*y*/, float /*z*/) {}

    /**
     * Sets the position of this AudioSource object in x and y planes with z
     * plane position fixed at zero
     * <p>
     * Equivalent to setPosition(x, y, 0.0f)
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @param x x-coordinate
     * @param y y-coordinate
     */
 virtual /*public*/ void setPosition(float /*x*/, float /*y*/) {}

    /**
     * Returns the position of this AudioSource object as a 3-dimensional
     * vector.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @return 3d position vector
     */
 virtual /*public*/ QVector3D getPosition() {return QVector3D();}

    /**
     * Returns the current position of this AudioSource object as a
     * 3-dimensional vector.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @return 3d position vector
     */
 /*public*/ virtual QVector3D getCurrentPosition() {return QVector3D();}

    /**
     * Method to reset the current position of this AudioSource object to the
     * initial position as defined by setPosition.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void resetCurrentPosition() {}

    /**
     * Sets the position of this AudioSource object to be relative to the
     * position of the AudioListener object or absolute.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param relative position relative or absolute
     */
    /*public*/ virtual void setPositionRelative(bool /*relative*/) {}

    /**
     * Returns a boolean value that determines if the position of this
     * AudioSource object is relative to the position of the AudioListener
     * object or absolute.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return boolean position relative
     */
    virtual /*public*/ bool isPositionRelative() { return false;}

    /**
     * Sets the velocity of this AudioSource object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @param vel 3d velocity vector
     */
    virtual /*public*/ void setVelocity(QVector3D /*vel*/) {}

    /**
     * Returns the velocity of this AudioSource object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @return 3d velocity vector
     */
 virtual /*public*/ QVector3D getVelocity() { return QVector3D();}

    /**
     * Returns linked AudioBuffer object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return AudioBuffer the AudioBuffer object bound to this AudioSource
     */
    virtual /*public*/ AudioBuffer* getAssignedBuffer() {return NULL;}

    /**
     * Return system name of linked AudioBuffer object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return sysName the SystemName of the AudioBuffer bound to this
     *         AudioSource
     */
  virtual /*public*/ QString getAssignedBufferName() {return "";}

    /**
     * Sets the linked AudioBuffer object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param audioBuffer the AudioBuffer object to bind to this AudioSource
     */
    virtual /*public*/ void setAssignedBuffer(AudioBuffer* /*audioBuffer*/) {}

    /**
     * Sets the system name of the linked AudioBuffer object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param sysName the SystemName of the AudioBuffer (i.e. IAB1) to bind to
     *                this AudioSource
     */
    virtual /*public*/ void setAssignedBuffer(QString /*sysName*/) {}

//    /**
//     * Binds this AudioSource with the specified AudioBuffer
//     * <p>
//     * Applies only to sub-types:
//     * <ul>
//     * <li>Source
//     * </ul>
//     * @param audioBuffer the AudioBuffer to bind to this AudioSource
//     * @return true if successful
//     */
//    @Deprecated
//    /*public*/ boolean bindAudioBuffer(AudioBuffer audioBuffer);
    /**
     * Queues the linked AudioBuffer object to this Source's buffer queue
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param audioBuffers the AudioBuffer object to enqueue to this AudioSource
     */
    /*public*/ virtual bool queueBuffers(QQueue<AudioBuffer*> /*audioBuffers*/) {return false;}

    /*public*/ virtual bool queueBuffer(AudioBuffer* /*audioBuffer*/) {return false;}

    /*public*/ virtual bool unqueueBuffers() {return false;}

    /*public*/ virtual int numQueuedBuffers() {return 0;}

    /*public*/ virtual int numProcessedBuffers() {return 0;}

    /**
     * Method to return if this AudioSource has been bound to an AudioBuffer
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return True if bound to an AudioBuffer
     */
    /*public*/ virtual bool isBound() {return false;}

    /**
     * Method to return if this AudioSource has AudioBuffers queued to it
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return True if AudioBuffers are queued.
     */
    /*public*/ virtual bool isQueued() {return false;}

    /**
     * Return the currently stored gain setting
     * <p>
     * Default value = 1.0f
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * </ul>
     *
     * @return gain setting of this AudioSource
     */
    /*public*/ virtual float getGain() {return 0;}

    /**
     * Set the gain of this AudioSource object
     * <p>
     * Default value = 1.0f
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Listener
     * <li>Source
     * <ul>
     *
     * @param gain the gain of this AudioSource
     */
    /*public*/ virtual void setGain(float /*gain*/) {}

    /**
     * Return the current pitch setting
     * <p>
     * Values are restricted from 0.5f to 2.0f, i.e. half to double
     * <p>
     * Default value = 1.0f
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return pitch of this AudioSource
     */
    /*public*/ virtual float getPitch() {return 0;}

    /**
     * Set the pitch of this AudioSource object
     * <p>
     * Values are restricted from 0.5f to 2.0f, i.e. half to double
     * <p>
     * Default value = 1.0f
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param pitch the pitch of this AudioSource
     */
    /*public*/ virtual void setPitch(float /*pitch*/) {}

    /**
     * Return the current reference distance setting
     * <p>
     * Default value = 1.0f
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return Reference Distance of this AudioSource
     */
    /*public*/ virtual float getReferenceDistance()  {return 0;}

    /**
     * Set the reference distance of this AudioSource object.
     * <p>
     * Default value = 1.0f
     * <p>
     * The Reference Distance is one of the main parameters you have for
     * controlling the way that sounds attenutate with distance. A Source with
     * Reference Distance set to 5 (meters) will be at maximum volume while it
     * is within 5 metere of the listener, and start to fade out as it moves
     * further away. At 10 meters it will be at half volume, and at 20 meters at
     * a quarter volume, etc ...
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param referenceDistance the Reference Distance for this AudioSource
     */
    /*public*/ virtual void setReferenceDistance(float /*referenceDistance*/) {}

    /**
     * Return the current maximum distance setting
     * <p>
     * Default value = Audio.MAX_DISTANCE
     * <p>
     * The maximum distance is that where the volume of the sound would normally
     * be zero.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual float getMaximumDistance()  {return 0;}

    /**
     * Set the current maximum distance setting
     * <p>
     * Default value = Audio.MAX_DISTANCE
     * <p>
     * The maximum distance is that where the volume of the sound would normally
     * be zero.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param maximumDistance maximum distance of this source
     */
    /*public*/ virtual void setMaximumDistance(float /*maximumDistance*/) {}

    /**
     * Set the roll-off factor of this AudioSource object
     * <p>
     * Default value = 1.0f
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param rollOffFactor roll-off factor
     */
    virtual /*public*/ void setRollOffFactor(float /*rollOffFactor*/) {}

    /**
     * Return the roll-off factor of this AudioSource object
     * <p>
     * Default value = 1.0f
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    virtual /*public*/ float getRollOffFactor() {return 0;}

    /**
     * Returns a boolean if this AudioSource object will loop or not
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return boolean loop
     */
    /*public*/ virtual bool isLooped() {return false;}

    /**
     * Sets this AudioSource object to loop infinitely or not.
     * <p>
     * When loop == false, sets the min and max number of loops to zero.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param loop infinite loop setting
     */
    /*public*/ virtual void setLooped(bool /*loop*/) {}

    /**
     * Returns the minimum number of times that this AudioSource will loop, or
     * LOOP_CONTINUOUS for infinite looping.
     * <p>
     * Default value = 0
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return number of loops
     */
    /*public*/ virtual int getMinLoops()  {return 0;}

    /**
     * The minimum number of times that this AudioSource should loop.
     * <p>
     * When set to 1, the sound will loop once (i.e. play through twice).
     * <p>
     * When set to LOOP_CONTINUOUS, determines that this AudioSource object
     * should loop indefinitely until explicitly stopped.
     * <p>
     * Default value = 0
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param loops minimum number of loops
     */
    /*public*/ virtual void setMinLoops(int /*loops*/) {}

    /**
     * Returns the maximum number of times that this AudioSource will loop, or
     * LOOP_CONTINUOUS for infinite looping.
     * <p>
     * Default value = 0
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return maximum number of loops
     */
    /*public*/ virtual int getMaxLoops()  {return 0;}

    /**
     * The maximum number of times that this AudioSource should loop.
     * <p>
     * When set to 1, the sound will loop once (i.e. play through twice).
     * <p>
     * When set to LOOP_CONTINUOUS, determines that this AudioSource object
     * should loop indefinitely until explicitly stopped.
     * <p>
     * Default value = 0
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param loops maximum number of loops
     */
    /*public*/ virtual void setMaxLoops(int /*loops*/) {}

    /**
     * The number of times that this AudioSource should loop, or LOOP_CONTINUOUS
     * for infinite looping.
     * <p>
     * When the minimum and maximum number of loops are different, each call to
     * this method will return a different random number that lies between the
     * two settings:
     * <pre>
     * minimum &lt= number of loops &lt= maximum
     * </pre> Default value = 0
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return number of loops
     */
    /*public*/ virtual int getNumLoops()  {return 0;}

//    /**
//     * Set the minimum length of time in milliseconds to wait before
//     * playing a subsequent loop of this source.
//     * <p>
//     * Not applicable when number of loops is LOOP_NONE or LOOP_CONTINUOUS
//     * <p>
//     * Default value = 0
//     * <p>
//     * Applies only to sub-types:
//     * <ul>
//     * <li>Source
//     * </ul>
//     * @param loopDelay minimum time in milliseconds to wait
//     */
//    /*public*/ void setMinLoopDelay(int loopDelay);
//
//    /**
//     * Retrieve the minimum length of time in milliseconds to wait before
//     * playing a subsequent loop of this source.
//     * <p>
//     * Not applicable when number of loops is LOOP_NONE or LOOP_CONTINUOUS
//     * <p>
//     * Default value = 0
//     * <p>
//     * Applies only to sub-types:
//     * <ul>
//     * <li>Source
//     * </ul>
//     * @return minimum time in milliseconds to wait
//     */
//    /*public*/ int getMinLoopDelay();
//
//    /**
//     * Set the maximum length of time in milliseconds to wait before
//     * playing a subsequent loop of this source.
//     * <p>
//     * Not applicable when number of loops is LOOP_NONE or LOOP_CONTINUOUS
//     * <p>
//     * Default value = 0
//     * <p>
//     * Applies only to sub-types:
//     * <ul>
//     * <li>Source
//     * </ul>
//     * @param loopDelay maximum time in milliseconds to wait
//     */
//    /*public*/ void setMaxLoopDelay(int loopDelay);
//
//    /**
//     * Set the maximum length of time in milliseconds to wait before
//     * playing a subsequent loop of this source.
//     * <p>
//     * Not applicable when number of loops is LOOP_NONE or LOOP_CONTINUOUS
//     * <p>
//     * Default value = 0
//     * <p>
//     * Applies only to sub-types:
//     * <ul>
//     * <li>Source
//     * </ul>
//     * @return maximum time in milliseconds to wait
//     */
//    /*public*/ int getMaxLoopDelay();
//
//    /**
//     * The length of time in milliseconds that this source should wait
//     * before playing a subsequent loop.
//     * <p>
//     * Not applicable when number of loops is LOOP_NONE or LOOP_CONTINUOUS
//     * <p>
//     * When the minimum and maximum delay times are different, each call
//     * to this method will return a different random number that lies between
//     * the two settings:
//     * <pre>
//     * minimum &lt= delay time &lt= maximum
//     * </pre>
//     * Default value = 0
//     * <p>
//     * Applies only to sub-types:
//     * <ul>
//     * <li>Source
//     * </ul>
//     * @return time in milliseconds to wait
//     */
//    /*public*/ int getLoopDelay();
    /**
     * Set the length of time in milliseconds to fade this source in
     * <p>
     * Default value = 1000
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param fadeInTime fade-in time in milliseconds
     */
    /*public*/ virtual void setFadeIn(int /*fadeInTime*/) {}

    /**
     * Retrieve the length of time in milliseconds to fade this source in
     * <p>
     * Default value = 1000
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return fade-in time in milliseconds
     */
    /*public*/ virtual int getFadeIn()  {return 0;}

    /**
     * Set the length of time in milliseconds to fade this source in
     * <p>
     * Default value = 1000
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param fadeOutTime fade-out time in milliseconds
     */
    /*public*/ virtual void setFadeOut(int /*fadeOutTime*/) {}

    /**
     * Retrieve the length of time in milliseconds to fade this source in
     * <p>
     * Default value = 1000
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return fade-in time in milliseconds
     */
    /*public*/ virtual int getFadeOut() {return 0;}

    /**
     * Set the doppler factor of this source
     * <p>
     * Default value = 1.0f
     * <p>
     * Only calculated for JoalAudioSources
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @param dopplerFactor factor to apply in doppler calculations
     */
    //@Deprecated
    /*public*/ Q_DECL_DEPRECATED virtual void setDopplerFactor(float /*dopplerFactor*/) {}

    /**
     * Retrieve the doppler factor of this source
     * <p>
     * Default value = 1.0f
     * <p>
     * Only calculated for JoalAudioSources
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     *
     * @return factor to apply in doppler calculations
     */
    //@Deprecated
    /*public*/ Q_DECL_DEPRECATED virtual float getDopplerFactor()  {return 0;}

    /**
     * Method to start playing this AudioSource Object
     * <p>
     * If this AudioSource is already playing, this command is ignored.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void play() {}

    /**
     * Method to stop playing this AudioSource Object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void stop(){}

    /**
     * Method to toggle playback of this AudioSource Object reseting position
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void togglePlay(){}

    /**
     * Method to pause playing this AudioSource Object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void pause(){}

    /**
     * Method to resume playing this AudioSource Object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void resume(){}

    /**
     * Method to toggle playback of this AudioSource Object retaining postition
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void togglePause(){}

    /**
     * Method to rewind this AudioSource Object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void rewind() {}

    /**
     * Method to fade in and then play this AudioSource Object
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void fadeIn() {}

    /**
     * Method to fade out and then stop this AudioSource Object only when it is
     * already playing.
     * <p>
     * If not playing, command is ignored.
     * <p>
     * Applies only to sub-types:
     * <ul>
     * <li>Source
     * </ul>
     */
    /*public*/ virtual void fadeOut() {}
};

#endif // AUDIOSOURCE_H
