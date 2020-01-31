#ifndef VSDECODER_H
#define VSDECODER_H

#include <QObject>
#include <QMap>
#include "libPr3_global.h"

class QDomElement;
class VSDecoderEvent;
class PhysicalLocation;
class PropertyChangeEvent;
class VSDFile;
class locoAddress;
class Logger;
class VSDSound;
class Trigger;
class SoundEvent;
class EventListenerList;
class VSDConfig;
class LIBPR3SHARED_EXPORT VSDecoder : public QObject
{
 Q_OBJECT
public:
 explicit VSDecoder(QObject *parent = 0);
 /*public*/ VSDecoder(QString id, QString name, QObject *parent = 0);
 /*public*/ VSDecoder(VSDConfig* cfg, QObject *parent = 0);
 /*public*/ VSDecoder(QString id, QString name, QString path, QObject *parent = 0);
 /*public*/ QString getID();
 /*public*/ bool isInitialized();
 /*public*/ void setVSDFilePath(QString p);
 /*public*/ QString getVSDFilePath();
 /*public*/ locoAddress* getAddress();
 /*public*/ void setXml(VSDFile* vf, QString pn);
 /*public*/ void enable();
 /*public*/ void disable();
 /*public*/ void releaseAddress(int number, bool isLong);
 /*public*/ void setAddress(int number, bool isLong);
 /*public*/ void setAddress(locoAddress* l);
 /*public*/ QList<SoundEvent*> getEventList();
 /*public*/ bool isDefault();
 /*public*/ void setDefault(bool d);
 /*public*/ QString getProfileName();
 /*public*/ void shutdown();
 /*public*/ float getMasterVolume();
 /*public*/ void setMasterVolume(float vol);
 /*public*/ bool isMuted();
 /*public*/ void mute(bool m);
 /*public*/ void setPosition(PhysicalLocation* p);
 /*public*/ PhysicalLocation* getPosition();
 /*public*/ QDomElement getXml();
 /*public*/ void setProfileName(QString pn);
 /*public*/ VSDSound* getSound(QString name);
 /*public*/ void toggleBell();
 /*public*/ void toggleHorn();
 /*public*/ void playHorn() ;
 /*public*/ void shortHorn();
 /*public*/ void stopHorn();


signals:
 void notify(VSDecoderEvent*);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 void common();
 bool initialized;// = false; // This decoder has been initialized
 bool enabled;// = false; // This decoder is enabled
 /*private*/ bool is_default;// = false; // This decoder is the default for its file

 /*private*/ VSDConfig* config;

 /*private*/ float tunnelVolume;// = 0.5f;
 QMap<QString, VSDSound*> sound_list; // list of sounds
 QMap<QString, Trigger*> trigger_list; // list of triggers
 QMap<QString, SoundEvent*> event_list; // list of events
 /*private*/ bool _init();

 Logger* log;
 /*private*/ void fireMyEvent(VSDecoderEvent* evt);

protected:
 // List of registered event listeners
 /*protected*/ EventListenerList* listenerList;// = new javax.swing.event.EventListenerList();
  protected slots:
 /*protected*/ void throttlePropertyChange(PropertyChangeEvent* event);

};

#endif // VSDECODER_H
