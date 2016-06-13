#ifndef ABSTRACTAUDIOLISTENER_H
#define ABSTRACTAUDIOLISTENER_H
#include "audiolistener.h"
#include "abstractaudiothread.h"
#include <QVector3D>
#include "libPr3_global.h"

class AudioFactory;
class LIBPR3SHARED_EXPORT AbstractAudioListener : public AudioListener
{
 Q_OBJECT
public:
 //explicit AbstractAudioListener(QObject *parent = 0);
 /*public*/ AbstractAudioListener(QString systemName, QObject *parent);
 /*public*/ AbstractAudioListener(QString systemName, QString userName, QObject *parent);
 /*public*/ QChar getSubType();
 /*public*/ void setPosition(QVector3D pos);
 /*public*/ void setPosition(float x, float y, float z);
 /*public*/ void setPosition(float x, float y) ;
 /*public*/ QVector3D getPosition();
 /*public*/ QVector3D getCurrentPosition() ;
 /*public*/ void setVelocity(QVector3D vel);
 /*public*/ QVector3D getVelocity();
 /*public*/ void resetCurrentPosition();
 /*public*/ void setOrientation(QVector3D at, QVector3D up);
 /*public*/ QVector3D getOrientation(int which);
 /*public*/ QVector3D getCurrentOrientation(int which) ;
 /*public*/ void setGain(float gain) ;
 /*public*/ float getGain();
 /*public*/ void setMetersPerUnit(float metersPerUnit) ;
 /*public*/ float getMetersPerUnit() ;
 /*public*/ void stateChanged(int oldState);
 /*public*/ QString toString();

signals:

public slots:
private:
 /*private*/ QVector3D _position;// = new QVector3D(0.0f, 0.0f, 0.0f);
 /*private*/ QVector3D _currentPosition;// = new QVector3D(0.0f, 0.0f, 0.0f);
 /*private*/ QVector3D _velocity;// = new QVector3D(0.0f, 0.0f, 0.0f);
 /*private*/ QVector3D _orientationAt;// = new QVector3D(0.0f, 1.0f, 0.0f);
 /*private*/ QVector3D _orientationUp;// = new QVector3D(0.0f, 0.0f, 1.0f);
 /*private*/ QVector3D _currentOriAt;// = new QVector3D(0.0f, 1.0f, 0.0f);
 /*private*/ QVector3D _currentOriUp;// = new QVector3D(0.0f, 0.0f, 1.0f);
 /*private*/ float _gain;// = 1.0f;
 /*private*/ float _metersPerUnit;// = 1.0f;
 /*private*/ long _timeOfLastPositionCheck;// = 0;
 Logger* log;
 void common();
 /*private*/ static /*final*/ AudioFactory* activeAudioFactory;// = InstanceManager.audioManagerInstance().getActiveAudioFactory();

protected:
 /*protected*/ void calculateCurrentPosition();
 /*protected*/ void doResetCurrentPosition();
 virtual /*abstract*/ /*protected*/ void changePosition(QVector3D pos);
friend class AbstractAudioFactory;
friend class AudioListenerMoveThread;
};
/*protected*/ /*static*/ class AudioListenerMoveThread : public  AbstractAudioThread
{
Q_OBJECT
    /**
     * Reference to the AudioListener object being monitored
     */
    /*private*/ AbstractAudioListener* audioListener;
 Logger* log;
public:
    /**
     * Constructor that takes handle to AudioListener to monitor
     *
     * @param audioListener AudioListener to monitor
     */
    AudioListenerMoveThread(AbstractAudioListener* audioListener, QObject* parent = 0);
    /*public*/ void run() ;
protected:
    /*protected*/ void cleanup() ;
};
#endif // ABSTRACTAUDIOLISTENER_H
