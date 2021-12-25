#include "vsdlistener.h"
#include "audiomanager.h"
#include "instancemanager.h"
#include "listeningspot.h"

//VSDListener::VSDListener(QObject *parent) :
//  QObject(parent)
//{
//}

///*public*/ class VSDListener {
/*public*/ /*final static*/ QString VSDListener::ListenerSysNamePrefix = "IAL$VSD:";


/*public*/ VSDListener::VSDListener(QString sname,QObject *parent) :
QObject(parent)
{
 //this(sname, sname);
 _sysname = ListenerSysNamePrefix + sname;
 _username = sname;
 common();
}

/*public*/ VSDListener::VSDListener(QString sname, QString uname, QObject *parent) :
QObject(parent)
{
 _sysname = ListenerSysNamePrefix + sname;
 _username = uname;
 common();
}
void VSDListener::common()
{
 log = new Logger("VSDListener");

 AudioManager* am = (AudioManager*)InstanceManager::getDefault("AudioManager");
    //try {
 _listener = (AudioListener*) am->provideAudio(ListenerSysNamePrefix + _sysname);
 log->debug("Listener Created: " + _listener->objectName());
//    } catch (AudioException ae) {
//        log->debug("AudioException creating Listener: " + ae);
//        // Do nothing?
//    }
}

/*public*/ VSDListener::VSDListener(AudioListener* l, QObject *parent) :
QObject(parent) {
    _listener = l;
    _sysname = l->getSystemName();
    _username = l->getUserName();
}

/*public*/ VSDListener::VSDListener(QObject *parent) :
QObject(parent) {
 common();
    // Initialize the AudioManager (if it isn't already) and get the Listener.
    AudioManager* am = (AudioManager*)InstanceManager::getDefault("AudioManager");
    am->init();
    _listener = am->getActiveAudioFactory()->getActiveAudioListener();

    QStringList names = am->getSystemNameList('L');
    if (names.size() == 0) {
        log->debug("No Listener yet. Creating one.");
    } else {
        log->debug("Found name: " + names.value(0));
    }
    _sysname = _listener->getSystemName();
    _username = _listener->getUserName();
}

/*public*/ QString VSDListener::getSystemName() {
    return (_sysname);
}

/*public*/ QString VSDListener::getUserName() {
    return (_username);
}

/*public*/ ListeningSpot* VSDListener::getLocation() {
    return (_location);
}

/*public*/ void VSDListener::setSystemName(QString s) {
    _sysname = s;
}

/*public*/ void VSDListener::setUserName(QString u) {
    _username = u;
}

/*public*/ void VSDListener::setLocation(ListeningSpot* l) {
    _location = l;
#if 0
    _listener->setPosition(new Vector3f(l.getLocation()));
    _listener->setOrientation(new Vector3f(l.getLookAtVector()), new Vector3f(l.getUpVector()));
#endif
    // Set position here
}

/*public*/ void VSDListener::setPosition(PhysicalLocation* /*p*/) {
    if (_location == NULL) {
        _location = new ListeningSpot();
    }
#if 0
    _location->setLocation(p);
    _listener->setPosition(p);
#endif
}

