#ifndef VSDECODERMANAGER_H
#define VSDECODERMANAGER_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include "libPr3_global.h"
#include "propertychangelistener.h"

class VSDManagerListener;
class LocoAddress;
class PhysicalLocation;
class VSDManagerEvent;
class VSDFile;
class Manager;
class VSDConfig;
class Logger;
class ListeningSpot;
class VSDecoderPreferences;
class JmriJFrame;
class EventListenerList;
class VSDecoderManagerThread;
class VSDListener;
class VSDecoder;
class NamedBeanHandleManager;
class LIBPR3SHARED_EXPORT VSDecoderManager : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 explicit VSDecoderManager(QObject *parent = 0);
 ~VSDecoderManager() {}
 VSDecoderManager(const VSDecoderManager&) : QObject(){}
 /*public*/ static VSDecoderManager* instance();

 /*public*/ QString getDefaultListenerName();
 /*public*/ ListeningSpot* getDefaultListenerLocation();
 /*public*/ void setListenerLocation(QString id, ListeningSpot* sp);
 /*public*/ VSDecoderPreferences* getVSDecoderPreferences();
 /*public*/ JmriJFrame* provideManagerFrame();
 /*public*/ VSDecoder* getVSDecoder(QString profile_name);
 /*public*/ VSDecoder* getVSDecoder(QString profile_name, QString path);
 /*public*/ VSDecoder* getVSDecoder(VSDConfig* config);
 /*public*/ VSDecoder* getVSDecoderByID(QString id);
 /*public*/ VSDecoder* getVSDecoderByAddress(QString sa);
 /*public*/ void setDefaultVSDecoder(VSDecoder* d);
 /*public*/ VSDecoder* getDefaultVSDecoder();
 /*public*/ QStringList getVSDProfileNames();
 /*public*/ QList<VSDecoder*> getVSDecoderList();
 /*public*/ void loadProfiles(VSDFile* vf);
 /*public*/ QString getProfilePath(QString profile);
 /*public*/ void loadProfiles(QString path);
 /*public*/ void setDecoderPositionByID(QString id, PhysicalLocation* p);
 /*public*/ void setDecoderPositionByAddr(LocoAddress* a, PhysicalLocation* l);
 /*public*/ void addEventListener(VSDManagerListener* listener);
 /*public*/ void removeEventListener(VSDManagerListener* listener);

 QObject* self() override {return (QObject*)this;}

signals:
 void fireEvent(VSDManagerEvent*);

public slots:

private:
 /*private*/ static /*final*/ QString vsd_property_change_name;// = "VSDecoder Manager"; //NOI18N

 QMap<QString, VSDListener*> listenerTable; // list of listeners
 QMap<QString, VSDecoder*> decodertable; // list of active decoders by System ID
 QMap<QString, VSDecoder*> decoderAddressMap; // List of active decoders by address
 QMap<QString, QString> profiletable;    // list of loaded profiles key = profile name, value = path
 QStringList reportertable;        // list of Reporters we are following.

 // List of registered event listeners

 ///*private*/ static VSDecoderManager instance = null;   // sole instance of this class
 /*private*/ static VSDecoderManagerThread* thread;// = null; // thread for running the manager

 /*private*/ VSDecoderPreferences* vsdecoderPrefs; // local pointer to the preferences object

 /*private*/ JmriJFrame* managerFrame;// = null;

 /*private*/ VSDecoder* default_decoder;// = null;  // shortcut pointer to the default decoder (do we need this?)

 /*private*/ static int vsdecoderID;// = 0;
 /*private*/ QString getNextVSDecoderID();
 Logger* log;
 // /*private*/ QString getNextListenerID();
 /*private*/ void setupReporterManagerListener();
 void fireMyEvent(VSDManagerEvent* evt);

 protected:
 /*protected*/ NamedBeanHandleManager* nbhm;// = jmri.InstanceManager.getDefault(jmri.NamedBeanHandleManager.class);
 /*protected*/ EventListenerList* listenerList;// = new javax.swing.event.EventListenerList();
 /*protected*/ void registerReporterListener(QString sysName);
 /*protected*/ void registerBeanListener(Manager* beanManager, QString sysName);
 /*protected*/ void registerReporterListeners();

};
//Q_DECLARE_METATYPE(VSDecoderManager)
#endif // VSDECODERMANAGER_H
