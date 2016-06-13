#ifndef ABSTRACTAUDIO_H
#define ABSTRACTAUDIO_H
#include "audiobuffer.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT AbstractAudio : public AudioBuffer
{
 Q_OBJECT
public:
 //explicit AbstractAudio(QObject *parent = 0);
 /*public*/ AbstractAudio(QString systemName, QObject *parent = 0);
 /*public*/ AbstractAudio(QString systemName, QString userName, QObject *parent = 0);
 /*public*/ int getState();
 /*public*/ void setState(int newState);
 /*public*/ QString toString();
 /*public*/ static float roundDecimal(float value, double places);
 /*public*/ static float roundDecimal(float value);
 /*public*/ QString getBeanType();

signals:

public slots:
private:
 /*private*/ int _state;// = STATE_INITIAL;
 void common();

protected:
 virtual /*abstract*/ /*protected*/ void cleanUp();

};

#endif // ABSTRACTAUDIO_H
