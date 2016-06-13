#ifndef ABSTRACTAUDIOFACTORY_H
#define ABSTRACTAUDIOFACTORY_H
#include "audiofactory.h"
#include "libPr3_global.h"

class AbstractAudioThread;
class LIBPR3SHARED_EXPORT AbstractAudioFactory : public AudioFactory
{
 Q_OBJECT
public:
 explicit AbstractAudioFactory(QObject *parent = 0);
 /*public*/ bool init();
 /*public*/ void cleanup();
 /*public*/ QThread* getCommandThread();
 /*public*/ void setDistanceAttenuated(bool attenuated);
 /*public*/ bool isDistanceAttenuated();

signals:
 void queue_updated();

public slots:
 /*public*/ /*synchronized*/ bool audioCommandQueue(AudioCommand* queueAudioCommand = 0);

private:
 /**
 * List of queued audio commands to process
 */
/*private*/ static QList<AudioCommand*>* commandQueue;// = null;

/**
 * Boolean used to determine if this AudioFactory has been initialised
 */
/*private*/ static bool _initialised;// = false;

/**
 * Boolean used to determine if this AudioFactory should attenuate sources
 * based on their distance from the Listener
 */
/*private*/ static bool _distanceAttenuated;// = true;

/**
 * Reference to the separate thread used to process all AudioCommands
 */
/*private*/ static AbstractAudioThread* audioCommandThread;// = null;
 Logger* log;
};

#endif // ABSTRACTAUDIOFACTORY_H
