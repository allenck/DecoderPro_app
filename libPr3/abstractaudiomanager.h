#ifndef ABSTRACTAUDIOMANAGER_H
#define ABSTRACTAUDIOMANAGER_H
#include "audiomanager.h"
#include "libPr3_global.h"

class Audio;
class LIBPR3SHARED_EXPORT AbstractAudioManager : public AudioManager
{
 Q_OBJECT
public:
 explicit AbstractAudioManager(QObject *parent = 0);
 /*public*/ char typeLetter() const override;
 /*public*/ Audio* provideAudio(QString name) override; //throws AudioException {
 /*public*/ Audio* getAudio(QString name)override;
 /*public*/ Audio* getBySystemName(QString key) const override;
 /*public*/ Audio* getByUserName(QString key)const override;
 /*public*/ Audio* newAudio(QString systemName, QString userName) /*throws AudioException */ override;
 /*public*/ QString getBeanTypeHandled(bool plural) const override;

signals:

public slots:
private:
 Logger* log;
protected:
 virtual /*abstract*/ /*protected*/ Audio* createNewAudio(QString systemName, QString userName) /*throws AudioException*/;

};

#endif // ABSTRACTAUDIOMANAGER_H
