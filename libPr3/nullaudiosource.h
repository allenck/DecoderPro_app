#ifndef NULLAUDIOSOURCE_H
#define NULLAUDIOSOURCE_H
#include "abstractaudiosource.h"
#include <QVector3D>

class AudioBuffer;
class NullAudioSource : public AbstractAudioSource
{
 Q_OBJECT
public:
 //explicit NullAudioSource(QObject *parent = 0);
 /*public*/ NullAudioSource(QString systemName,  QObject *parent = 0);
 /*public*/ NullAudioSource(QString systemName, QString userName, QObject *parent = 0);

signals:

public slots:
private:
 /**
  * True if we've been initialised
  */
 /*private*/ bool _initialised;// = false;
 void common();
 bool bindAudioBuffer(AudioBuffer* audioBuffer);
 /*private*/ bool init();
 Logger* log;
protected:
 /*protected*/ void changePosition(QVector3D pos);
 /*protected*/ void doPlay();
 /*protected*/ void doStop();
 /*protected*/ void doPause();
 /*protected*/ void doResume();
 /*protected*/ void doRewind();
 /*protected*/ void doFadeIn();
 /*protected*/ void doFadeOut();
 /*protected*/ void cleanUp();
 /*protected*/ void calculateGain();
friend class NullAudioFactory;
};

#endif // NULLAUDIOSOURCE_H
