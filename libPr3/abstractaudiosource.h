#ifndef ABSTRACTAUDIOSOURCE_H
#define ABSTRACTAUDIOSOURCE_H
#include "audiosource.h"
#include <QVector3D>
#include "abstractaudiothread.h"
#include <QLinkedList>
#include "libPr3_global.h"

class AudioFactory;
class LIBPR3SHARED_EXPORT AbstractAudioSource : public AudioSource
{
 Q_OBJECT
public:
 //explicit AbstractAudioSource(QObject *parent = 0);
 /*public*/ AbstractAudioSource(QString systemName, QObject *parent= 0);
 /*public*/ AbstractAudioSource(QString systemName, QString userName, QObject *parent= 0);
 /*public*/ QChar getSubType();
 /*public*/ bool queueBuffers(QQueue<AudioBuffer*> audioBuffers);
 /*public*/ bool queueBuffer(AudioBuffer* audioBuffer);
 /*public*/ bool unqueueBuffers();
 /*public*/ QQueue<AudioBuffer*> getQueuedBuffers();
 /*public*/ void setAssignedBuffer(AudioBuffer* audioBuffer);
 /*public*/ void setAssignedBuffer(QString bufferSystemName);
 /*public*/ AudioBuffer* getAssignedBuffer();
 /*public*/ QString getAssignedBufferName();
 /*public*/ void setPosition(QVector3D pos) ;
 /*public*/ void setPosition(float x, float y, float z);
 /*public*/ void setPosition(float x, float y);
 /*public*/ QVector3D getPosition();
 /*public*/ QVector3D getCurrentPosition();
 /*public*/ void setPositionRelative(bool relative) ;
 /*public*/ bool isPositionRelative();
 /*public*/ void setVelocity(QVector3D vel) ;
 /*public*/ QVector3D getVelocity();
 /*public*/ void resetCurrentPosition();
 /*public*/ void setGain(float gain) ;
 /*public*/ float getGain();
 /*public*/ void setPitch(float pitch) ;
 /*public*/ float getPitch() ;
 /*public*/ void setReferenceDistance(float referenceDistance) ;
 /*public*/ float getReferenceDistance();
 /*public*/ void setMaximumDistance(float maximumDistance);
 /*public*/ float getMaximumDistance();
 /*public*/ void setRollOffFactor(float rollOffFactor);
 /*public*/ float getRollOffFactor() ;
 /*public*/ void setLooped(bool loop) ;
 /*public*/ bool isLooped();
 /*public*/ void setMinLoops(int loops);
 /*public*/ int getMinLoops();
 /*public*/ void setMaxLoops(int loops);
 /*public*/ int getMaxLoops();
 /*public*/ int getNumLoops();
 /*public*/ void setFadeIn(int fadeInTime);
 /*public*/ int getFadeIn() ;
 /*public*/ void setFadeOut(int fadeOutTime);
 /*public*/ int getFadeOut();
 /*public*/ void setDopplerFactor(float dopplerFactor);
 /*public*/ float getDopplerFactor();
 /*public*/ bool queueAudioBuffers(QQueue<AudioBuffer*> audioBuffers);
 /*public*/ bool queueAudioBuffer(AudioBuffer* audioBuffer) ;
 /*public*/ bool unqueueAudioBuffers() ;
 /*public*/ int numQueuedBuffers() ;
 /*public*/ int numProcessedBuffers();
 /*public*/ bool isBound();
 /*public*/ bool isQueued();
 /*public*/ void stateChanged(int oldState) ;
 /*public*/ void play();
 /*public*/ void stop();
 /*public*/ void togglePlay();
 /*public*/ void pause();
 /*public*/ void resume();
 /*public*/ void togglePause();
 /*public*/ void rewind();
 /*public*/ void fadeIn() ;
 /*public*/ void fadeOut();
 /*public*/ QString toString();



signals:

public slots:
private:
 void common();
 /*private*/ QVector3D _position;// = new QVector3D(0.0f, 0.0f, 0.0f);
 /*private*/ QVector3D _currentPosition;// = new QVector3D(0.0f, 0.0f, 0.0f);
 /*private*/ QVector3D _velocity;// = new QVector3D(0.0f, 0.0f, 0.0f);
 /*private*/ float _gain;// = 1.0f;
 /*private*/ float _pitch;// = 1.0f;
 /*private*/ float _referenceDistance;// = 1.0f;
 /*private*/ float _maximumDistance;// = Audio.MAX_DISTANCE;
 /*private*/ float _rollOffFactor;// = 1.0f;
 /*private*/ int _minLoops;// = LOOP_NONE;
 /*private*/ int _maxLoops;// = LOOP_NONE;
 /*private*/ int _numLoops;// = 0;
//    /*private*/ int _minLoopDelay         = 0;
//    /*private*/ int _maxLoopDelay         = 0;
//    /*private*/ int _loopDelay            = 0;
 /*private*/ int _fadeInTime;// = 1000;
 /*private*/ int _fadeOutTime;// = 1000;
 /*private*/ float _fadeGain;// = 1.0f;
 /*private*/ float _dopplerFactor;// = 1.0f;
 /*private*/ long _timeOfLastFadeCheck;// = 0;
 /*private*/ long _timeOfLastPositionCheck;// = 0;
 /*private*/ int _fading;// = Audio.FADE_NONE;
 /*private*/ bool _bound;// = false;
 /*private*/ bool _positionRelative ;//= false;
 /*private*/ bool _queued;// = false;
 /*private*/ AudioBuffer* _buffer;
//    /*private*/ AudioSourceDelayThread asdt = null;
 /*private*/ QQueue<AudioBuffer*> pendingBufferQueue;// = new LinkedList<AudioBuffer>();
// /*private*/ static /*final*/ long serialVersionUID = -984900360787361666L;

 /*private*/ static /*final*/ AudioFactory* activeAudioFactory;// = InstanceManager.audioManagerInstance().getActiveAudioFactory();

 /*private*/ static float metersPerUnit;// = activeAudioFactory.getActiveAudioListener().getMetersPerUnit();
 Logger* log;
 /*private*/ void stop(bool interruptThread) ;

protected:
 /*protected*/ void calculateCurrentPosition();
 /*protected*/ void doResetCurrentPosition();
 virtual /*abstract*/ /*protected*/ void changePosition(QVector3D pos);
 virtual /*abstract*/ /*protected*/ void calculateGain();
 /*protected*/ void calculateLoops();
 /*protected*/ float getFadeGain();
 /*protected*/ void calculateFades();
 virtual /*abstract*/ bool bindAudioBuffer(AudioBuffer* buffer);
 /*protected*/ void setBound(bool bound);
 /*protected*/ void setQueued(bool queued);
 virtual /*abstract*/ /*protected*/ void doPlay();
 virtual /*abstract*/ /*protected*/ void doStop();
 /*protected*/ void doTogglePlay();
 virtual /*abstract*/ /*protected*/ void doPause();
 virtual /*abstract*/ /*protected*/ void doRewind();
 virtual /*abstract*/ /*protected*/ void doResume();
 virtual /*abstract*/ /*protected*/ void doFadeIn();
 virtual /*abstract*/ /*protected*/ void doFadeOut();
 /*protected*/ int getFading();
 /*protected*/ void doTogglePause();
 friend class AbstractAudioFactory;
 friend class AudioSourceMoveThread;
 friend class AudioSourceFadeThread;
 friend class QtSoundAudioListener;
 friend class AudioSourceTableDataModel;
 friend class QtSoundAudioSource;
 friend class QtSoundAudioClip;
};
/**
 * An internal class used to create a new thread to monitor and maintain
 * fade in and fade out levels.
 * <p>
 * Will exist only as long as this source is in the process of fading in or
 * out.
 */
/*protected*/ /*static*/ class AudioSourceFadeThread : public AbstractAudioThread
{
 Q_OBJECT
/**
 * Reference to the AudioSource object being monitored
 */
/*private*/ AbstractAudioSource* audioSource;

/**
 * Internal variable to hold the fade direction
 */
/*private*/ int fadeDirection;
Logger* log;
public:
/**
 * Constructor that takes handle to looping AudioSource to monitor
 *
 * @param audioSource looping AudioSource to monitor
 */
AudioSourceFadeThread(AbstractAudioSource* audioSource, QObject *parent =0);
/*public*/ void run() ;
protected:

/*protected*/ void cleanup() ;
};

/**
* An internal class used to create a new thread to monitor and maintain
* current source position with respect to velocity.
*/
/*protected*/ /*static*/ class AudioSourceMoveThread : public AbstractAudioThread {

/**
 * Reference to the AudioSource object being monitored
 */
/*private*/ AbstractAudioSource* audioSource;
 Logger* log;
public:
/**
 * Constructor that takes handle to looping AudioSource to monitor
 *
 * @param audioSource looping AudioSource to monitor
 */
AudioSourceMoveThread(AbstractAudioSource* audioSource, QObject* parent = 0);
/*public*/ void run();
protected:

/*protected*/ void cleanup();
friend class QtSoundAudioListener;
};

#endif // ABSTRACTAUDIOSOURCE_H
