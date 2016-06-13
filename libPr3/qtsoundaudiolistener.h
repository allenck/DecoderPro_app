#ifndef QTSOUNDAUDIOLISTENER_H
#define QTSOUNDAUDIOLISTENER_H
#include "abstractaudiolistener.h"

class QtSoundAudioListener : public AbstractAudioListener
{
 Q_OBJECT
public:
 //explicit QtSoundAudioListener(QObject *parent = 0);
 /*public*/ QtSoundAudioListener(QString systemName, QObject *parent = 0);
 /*public*/ QtSoundAudioListener(QString systemName, QString userName, QObject *parent  = 0);
 /*public*/ void setGain(float gain);

signals:

public slots:
private:
 Logger* log;
 void common();
 /*private*/ void recalculateSources();

protected:
 /*protected*/ void changePosition(QVector3D pos);
 /*protected*/ void cleanUp();
friend class QtSoundAudioFactory;
};

#endif // QTSOUNDAUDIOLISTENER_H
