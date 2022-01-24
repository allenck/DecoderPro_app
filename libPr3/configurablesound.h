#ifndef CONFIGURABLESOUND_H
#define CONFIGURABLESOUND_H
#include "vsdsound.h"

class JActionEvent;
class Logger;
class VSDFile;
class SoundBite;
class ConfigurableSound : public VSDSound
{
 Q_OBJECT
public:
 //explicit ConfigurableSound(QObject *parent = 0);
 /*public*/ ConfigurableSound(QString name, QObject *parent = 0);
 /*public*/ void setXml(QDomElement e);
 /*public*/ void setXml(QDomElement e, VSDFile* vf);
 /*public*/ bool init() ;
 /*public*/ bool init(VSDFile* vf);
 /*public*/ bool isPlaying();
 /*public*/ void play();
 /*public*/ void loop();
 /*public*/ void stop();
 /*public*/ void fadeIn() ;
 /*public*/ void fadeOut();
 /*public*/ void shutdown() ;
 /*public*/ void mute(bool m);
 /*public*/ void setVolume(float v);
 /*public*/ void setPosition(PhysicalLocation* p) ;
 /*public*/ QDomElement getXml();

signals:

public slots:
private:

 SoundBite* start_sound;
 SoundBite* mid_sound;
 SoundBite* end_sound;
 SoundBite* short_sound;

 bool initialized;// = false;
 Logger* log;

 int start_sound_duration;// = 136;
protected:
 /*protected*/ QString start_file;
 /*protected*/ QString mid_file;
 /*protected*/ QString end_file;
 /*protected*/ QString short_file;
 /*protected*/ bool use_start_sound;// = false;
 /*protected*/ bool use_mid_sound;// = false;
 /*protected*/ bool use_end_sound;// = false;
 /*protected*/ bool use_short_sound;// = false;

 protected slots:
 /*protected*/ void handleTimerPop(JActionEvent* e = 0);

};

#endif // CONFIGURABLESOUND_H
