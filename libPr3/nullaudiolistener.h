#ifndef NULLAUDIOLISTENER_H
#define NULLAUDIOLISTENER_H
#include "abstractaudiolistener.h"

class NullAudioListener : public AbstractAudioListener
{
 Q_OBJECT
public:
 //explicit NullAudioListener(QObject *parent = 0);
 /*public*/ NullAudioListener(QString systemName, QObject *parent = 0);
 /*public*/ NullAudioListener(QString systemName, QString userName, QObject *parent = 0);

signals:

public slots:
private:
 Logger* log;
 void common();
protected:
 /*protected*/ void changePosition(QVector3D pos);
 /*protected*/ void cleanUp();
 friend class NullAudioFactory;
};

#endif // NULLAUDIOLISTENER_H
