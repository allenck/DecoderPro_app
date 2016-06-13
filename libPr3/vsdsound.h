#ifndef VSDSOUND_H
#define VSDSOUND_H

#include <QObject>
#include <QDomDocument>

class QDomElement;
class ActionListener;
class PhysicalLocation;
class QTimer;
class VSDSound : public QObject
{
 Q_OBJECT
public:
 //explicit VSDSound(QObject *parent = 0);
 /*public*/ /*final*/ static QString SrcSysNamePrefix;// = "IAS$VSD:";
 /*public*/ /*final*/ static QString BufSysNamePrefix;// = "IAB$VSD:";
 /*public*/ /*final*/ static QString SrcUserNamePrefix;// = "IVSDS_";
 /*public*/ /*final*/ static QString BufUserNamePrefix;// = "IVSDB_";
 /*public*/ /*final*/ static float default_gain;// = 0.8f;
 /*public*/ VSDSound(QString name,QObject *parent = 0);
 /*public*/ bool isPlaying();
 /*abstract*/ virtual  /*public*/ void play();
 /*abstract*/ virtual  /*public*/ void loop();
 /*abstract*/ virtual  /*public*/ void stop();
 /*abstract*/ virtual  /*public*/ void fadeIn();
 /*abstract*/ virtual  /*public*/ void fadeOut();
 /*abstract*/ virtual  /*public*/ void mute(bool m);
 /*abstract*/ virtual  /*public*/ void setVolume(float g);
 /*abstract*/ virtual  /*public*/ void shutdown(); // called on window close.  Cease playing immediately.
 /*public*/ void setPosition(PhysicalLocation* p);
 /*public*/ PhysicalLocation* getPosition();
 // Optional methods - overridden in subclasses where needed.  Do nothing otherwise
 /*public*/ void changeNotch(int new_notch);
 /*public*/ void changeThrottle(float t) ;
 /*public*/ void setName(QString n) ;
 /*public*/ QString getName();
 /*public*/ float getGain() ;
 /*public*/ void setGain(float g);
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);

signals:

public slots:
private:
 QTimer* t;

 bool is_playing;
 QString name;
 float gain;  // this is the (fixed) gain relative to the other sounds in this Profile
 float volume; // this is the (active) volume level (product of fixed gain and volume slider).

 PhysicalLocation* myposition;
 QDomDocument doc;

protected:
 /*protected*/ QString vsd_file_base;// = "resource:resources/sounds/vsd/";
 /*protected*/ QTimer* newTimer(int time, bool repeat, ActionListener* al);
 friend class ConfigurableSound;
 friend class EngineSound;
 friend class SoundBite;
 friend class SteamSound;
 friend class DieselSound;
};

#endif // VSDSOUND_H
