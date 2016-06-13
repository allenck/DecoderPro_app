#ifndef QTSOUNDAUDIOFACTORY_H
#define QTSOUNDAUDIOFACTORY_H
#include "abstractaudiofactory.h"

class Mixer;
class QtSoundAudioListener;
class QtSoundAudioFactory : public AbstractAudioFactory
{
 Q_OBJECT
public:
 explicit QtSoundAudioFactory(QObject *parent = 0);
 /*public*/ static /*synchronized*/ Mixer* getMixer();
 /*public*/ bool init();
 /*public*/ QString toString();
 /*public*/ void cleanup();
 /*public*/ AudioBuffer* createNewBuffer(QString systemName, QString userName);
 /*public*/ AudioListener* createNewListener(QString systemName, QString userName);
 /*public*/ AudioListener* getActiveAudioListener();
 /*public*/ AudioSource* createNewSource(QString systemName, QString userName);

signals:

public slots:
private:
 /*private*/ static bool _initialised;// = false;

 /*private*/ /*volatile*/ static Mixer* _mixer;

 /*private*/ QtSoundAudioListener* _activeAudioListener;
 Logger* log;
};

#endif // QTSOUNDAUDIOFACTORY_H
