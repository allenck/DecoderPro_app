#ifndef VSDECODERPREFERENCES_H
#define VSDECODERPREFERENCES_H

#include <QObject>
#include <QMap>
#include "xmlfile.h"
#include <QtXml>

#include "libPr3_global.h"

/*static*/ class LIBPR3SHARED_EXPORT VSDecoderPrefsXml :public XmlFile {
};
class PhysicalLocation;
class ListeningSpot;
class PropertyChangeListener;
class LIBPR3SHARED_EXPORT VSDecoderPreferences : public QObject
{
 Q_OBJECT
public:
 /*static*/ /*public*/ enum AudioMode {

     ROOM_AMBIENT, HEADPHONES
 };
 Q_ENUMS(AudioMode)
 explicit VSDecoderPreferences(QObject *parent = 0);
 /*public*/ /*final*/ static QString VSDPreferencesFileName;// = "VSDecoderPreferences.xml";
 static /*public*/ /*final*/ QMap<AudioMode, QString> audioModeMap;
 static /*public*/ /*final*/ AudioMode DefaultAudioMode;// = AudioMode.ROOM_AMBIENT;
 /*public*/ VSDecoderPreferences(QString sfile,QObject *parent = 0);
 /*public*/ void load(QDomElement e);
 /*public*/ void set(VSDecoderPreferences* tp);
 /*public*/ bool compareTo(VSDecoderPreferences* tp);
 /*public*/ void save();
 /*public*/ QString getDefaultVSDFilePath();
 /*public*/ void setDefaultVSDFilePath(QString s);
 /*public*/ QString getDefaultVSDFileName();
 /*public*/ void setDefaultVSDFileName(QString s);
 /*public*/ bool isAutoStartingEngine();
 /*public*/ void setAutoStartEngine(bool b);
 /*public*/ bool isAutoLoadingDefaultVSDFile();
 /*public*/ void setAutoLoadDefaultVSDFile(bool b);
 /*public*/ ListeningSpot* getListenerPosition();
 /*public*/ void setListenerPosition(ListeningSpot* p);
 /*public*/ PhysicalLocation* getListenerPhysicalLocation();
 /*public*/ void setListenerPosition(PhysicalLocation* p);
 /*public*/ AudioMode getAudioMode();
 /*public*/ void setAudioMode(AudioMode am);
 /*public*/ void setAudioMode(QString am) ;
 /*public*/ void addPropertyChangeListener(PropertyChangeListener* l);
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* l);

signals:

public slots:
private:
 void common();
 // Private variables to hold preference values
 /*private*/ bool _autoStartEngine;// = false; // play engine sound w/o waiting for "Engine Start" button pressed.
 /*private*/ QString _defaultVSDFilePath;// = null;
 /*private*/ QString _defaultVSDFileName;// = null;
 /*private*/ bool _autoLoadDefaultVSDFile;// = false; // Automatically load a VSD file.
 /*private*/ ListeningSpot* _listenerPosition;
 /*private*/ AudioMode _audioMode;

 // Other internal variables
 ///*private*/ Dimension _winDim = new Dimension(800,600);
 /*private*/ QString prefFile;
 /*private*/ QList<PropertyChangeListener*>* listeners;
 Logger * log;
 QDomDocument doc;
 /*private*/ QDomElement store();

};

#endif // VSDECODERPREFERENCES_H
