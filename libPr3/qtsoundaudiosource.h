#ifndef QTSOUNDAUDIOSOURCE_H
#define QTSOUNDAUDIOSOURCE_H
#include "abstractaudiosource.h"
#include <QAudio>

class QEventLoop;
class QBuffer;
class QAudioOutput;
class QtSoundAudioSource;
class FloatControl;
class Clip;
class QtSoundAudioChannel;
class AudioListener;
class Mixer;
/*private*/ /*static*/ class QtSoundAudioChannel : public QObject
{
 Q_OBJECT
    /**
     * Control for changing the gain of this AudioSource
     */
    /*private*/ FloatControl* _gainControl;// = NULL;

    /**
     * Control for changing the pan of this AudioSource
     */
    /*private*/ FloatControl* _panControl;// = NULL;

    /**
     * Control for changing the sample rate of this AudioSource
     */
    /*private*/ FloatControl* _sampleRateControl;// = NULL;

    /**
     * Holds the initial sample rate setting
     */
    /*private*/ float _initialSampleRate;// = 0.0f;

    /**
     * Holds the initial gain setting
     */
    /*private*/ float _initialGain;// = 0.0f;

    /**
     * Holds reference to the parent AudioSource object
     */
    /*private*/ QtSoundAudioSource* _audio;

    /**
     * Holds reference to the QtSound clip
     */
    /*private*/ Clip* _clip;
 Logger* log;

public:
    /**
     * Constructor for creating an AudioChannel for a specific
     * QtSoundAudioSource
     *
     * @param audio the specific QtSoundAudioSource
     */
    /*public*/ QtSoundAudioChannel(QtSoundAudioSource* audio);
protected:
    /*protected*/ void setGain(float gain);
    /*protected*/ void setPan(float pan);
    /*protected*/ void setPitch(float pitch);
 friend class QtSoundAudioSource;
};
class QtSoundAudioSource : public AbstractAudioSource
{
 Q_OBJECT
public:
 //explicit QtSoundAudioSource(QObject *parent = 0);
 /*public*/ QtSoundAudioSource(QString systemName, QObject *parent = 0);
 /*public*/ QtSoundAudioSource(QString systemName, QString userName, QObject *parent = 0);
 /*public*/ void setGain(float gain);
 /*public*/ void setPitch(float pitch);
 /*public*/ void setReferenceDistance(float referenceDistance);
 /*public*/ int getState();

signals:

public slots:
 /*public*/ void stateChanged(QAudio::State oldState);

private:
 Logger* log;
 void common();
 /**
  * Reference to QtSound mixer object
  */
 /*private*/ static Mixer* _mixer;// = QtSoundAudioFactory.getMixer();

 /**
  * Reference to current active AudioListener
  */
 /*private*/ AudioListener* _activeAudioListener;// = InstanceManager::audioManagerInstance().getActiveAudioFactory().getActiveAudioListener();

 /**
  * True if we've been initialised
  */
 /*private*/ bool _initialised;// = false;

 /**
  * Used for playing back sound source
  */
 /*private*/ /*transient*/ Clip* _clip;// = NULL;

 /**
  * Holds reference to the QtSoundAudioChannel object
  */
 /*private*/ /*transient*/ QtSoundAudioChannel* _audioChannel;// = NULL;

 /*private*/ bool _jsState;
 /*private*/ bool init();
 bool bindAudioBuffer(AudioBuffer* audioBuffer);
 QAudioOutput* audioOut;
 QBuffer* buf;
 QEventLoop* loop;

protected:
 /*protected*/ void changePosition(QVector3D pos);
 /*protected*/ void doPlay();
 /*protected*/ void doStop();
 /*protected*/ void doPause();
 /*protected*/ void doResume() ;
 /*protected*/ void doRewind();
 /*protected*/ void doFadeIn();
 /*protected*/ void doFadeOut();
 /*protected*/ void cleanUp();
 /*protected*/ void calculatePan();
 /*protected*/ void calculateGain();
 /*protected*/ void calculatePitch();
 friend class QtSoundAudioChannel;
 friend class QtSoundAudioListener;
 friend class QtSoundAudioFactory;
};

#endif // QTSOUNDAUDIOSOURCE_H
