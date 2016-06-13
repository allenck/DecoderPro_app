#ifndef ENGINESOUND_H
#define ENGINESOUND_H
#include "vsdsound.h"

class EnginePane;
class Logger;
class VSDFile;
class EngineSound : public VSDSound
{
 Q_OBJECT
public:
 //explicit EngineSound(QObject *parent = 0);
 /*public*/ EngineSound(QString name, QObject *parent=0);
 /*public*/ bool init();
 /*public*/ virtual void setXml(QDomElement e, VSDFile* vf);
 /*public*/ virtual QDomElement getXml();
 /*public*/ int getFadeInTime();
 /*public*/ int getFadeOutTime();
 /*public*/ void play() ;
 /*public*/ void loop();
 /*public*/ void stop();
 /*public*/ void fadeIn();
 /*public*/ void fadeOut();
 static /*final*/ /*public*/ int calcEngineNotch(/*final*/ float throttle) ;
 static /*final*/ /*public*/ int calcEngineNotch(/*final*/ double throttle);
 // This is the default behavior.  Subclasses can do fancier things
 // if they want.
 /*public*/ void handleSpeedChange(float s, EnginePane* e) ;
 /*public*/ virtual void startEngine();
 /*public*/ virtual void stopEngine();
 /*public*/ bool isEngineStarted();
 /*public*/ void setEngineStarted(bool es);
 /*public*/ void shutdown();
 /*public*/ void mute(bool m) ;
 /*public*/ void setVolume(float v);

signals:

public slots:
private:
 void common();
 // Engine Sounds
 bool initialized;// = false;
 bool engine_started;// = false;
 bool auto_start_engine;// = false;

 int fade_length;// = 100;
 int fade_in_time;// = 100;
 int fade_out_time;// = 100;

 QTimer* t;
 Logger* log;
protected:
 /*protected*/ float setXMLGain(QDomElement e);
 /*protected*/ void setFadeInTime(int t);
 /*protected*/ void setFadeInTime(QString s);
 /*protected*/ void setFadeOutTime(int t);
 /*protected*/ void setFadeOutTime(QString s);
 /*protected*/ QTimer* newTimer(int time, bool repeat);

 friend class Diesel3Sound;
 friend class SteamSound;
 friend class DieselSound;
};

#endif // ENGINESOUND_H
