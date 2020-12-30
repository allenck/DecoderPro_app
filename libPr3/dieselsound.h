#ifndef DIESELSOUND_H
#define DIESELSOUND_H
#include "enginesound.h"
#include <QMap>

class JActionEvent;
class Logger;
class VSDFile;
class NotchTransition;
class SoundBite;
class DieselSound : public EngineSound
{
 Q_OBJECT
public:
// explicit DieselSound(QObject *parent = 0);
 /*public*/ DieselSound(QString name,QObject *parent = 0);
 /*public*/ void setXml(QDomElement e, VSDFile* vf);
 /*public*/ void play();
 /*public*/ void loop();
 /*public*/ void stop();
 /*public*/ void changeNotch(int new_notch);
 /*public*/ void startEngine();
 /*public*/ void stopEngine() ;
 /*public*/ void shutdown();
 /*public*/ void mute(bool m);
 /*public*/ void setVolume(float v);
 /*public*/ void setPosition(PhysicalLocation* p);
 /*public*/ QDomElement getXml();

signals:

public slots:
private:
 // Engine Sounds
 QMap<int, SoundBite*> notch_sounds;
 QList<NotchTransition*> transition_sounds;
 SoundBite* start_sound;
 SoundBite* shutdown_sound;
 NotchTransition* notch_transition; // used for changing notches

 int current_notch;// = 1;
 Logger* log;
 /*private*/ NotchTransition* findNotchTransient(int prev, int next);


 private slots:
 /*private*/ void startToIdleAction(JActionEvent* e = 0);

protected slots:
 /*protected*/ void handleNotchTimerPop(JActionEvent* e = 0);

};

#endif // DIESELSOUND_H
