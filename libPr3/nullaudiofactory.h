#ifndef NULLAUDIOFACTORY_H
#define NULLAUDIOFACTORY_H
#include "abstractaudiofactory.h"

class NullAudioListener;
class NullAudioFactory : public AbstractAudioFactory
{
 Q_OBJECT
public:
 explicit NullAudioFactory(QObject *parent = 0);
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
 /*private*/ NullAudioListener* activeAudioListener;
 Logger* log;
};

#endif // NULLAUDIOFACTORY_H
