#include "vsdecoderpreferences.h"
#include <file.h>
#include "fileutil.h"
#include "vsdecodermanager.h"
#include "listeningspot.h"
#include "propertychangeevent.h"
#include "propertychangelistener.h"
#include "physicallocation.h"

VSDecoderPreferences::VSDecoderPreferences(QObject *parent) :
  QObject(parent)
{
 common();
}


///*public*/ class VSDecoderPreferences {

/*public*/ /*final*/ /*static*/ QString VSDecoderPreferences::VSDPreferencesFileName = "VSDecoderPreferences.xml";

/*static*/ /*public*/ /*final*/ QMap<VSDecoderPreferences::AudioMode, QString> VSDecoderPreferences::audioModeMap = QMap<VSDecoderPreferences::AudioMode, QString>();
#if 0
    static {
        Map<AudioMode, QString> aMap = new HashMap<AudioMode, QString>();
        aMap.put(AudioMode.ROOM_AMBIENT, "RoomAmbient");
        aMap.put(AudioMode.HEADPHONES, "Headphones");
        AudioModeMap = Collections.unmodifiableMap(aMap);
    }
#else
//VSDecoderPreferences::AudioModeMap.insert(ROOM_AMBIENT, "RoomAmbient");
#endif
/*static*/ /*public*/ /*final*/ VSDecoderPreferences::AudioMode VSDecoderPreferences::DefaultAudioMode = ROOM_AMBIENT;

void VSDecoderPreferences::common()
{
 log = new Logger("VSDecoderPreferences");
 listeners = NULL;

 _autoStartEngine = false;
 _defaultVSDFilePath = "";
 _defaultVSDFileName = "";
 _autoLoadDefaultVSDFile = true;
 if(audioModeMap.isEmpty())
 {
  audioModeMap.insert(ROOM_AMBIENT, "RoomAmbient");
  audioModeMap.insert(HEADPHONES, "Headphones");

 }
}

/*public*/ VSDecoderPreferences::VSDecoderPreferences(QString sfile,QObject *parent) :
      QObject(parent)
{
 common();
    prefFile = sfile;
    VSDecoderPrefsXml* prefs = new VSDecoderPrefsXml();
    File* file = new File(prefFile);
    QDomElement root;

    // Set default values
    _defaultVSDFilePath = FileUtil::getExternalFilename("program:resources/vsdecoder");
    _defaultVSDFileName = "example.vsd";
    _listenerPosition = new ListeningSpot(); // default to (0, 0, 0) Orientation (0,1,0)
    _audioMode = DefaultAudioMode;

    // Try to load preferences from the file
//        try {
    root = prefs->rootFromFile(file);
//        } catch (java.io.FileNotFoundException e2) {
//            log->info("Did not find VSDecoder preferences file.  This is normal if you haven't save the preferences before");
//            root = null;
//        } catch (Exception* e) {
//            log->error("Exception while loading VSDecoder preferences: " + e);
//            root = QDomElement();
//        }
 if (!root.isNull())
 {
  load(root.firstChildElement("VSDecoderPreferences"));
 }
}

//    /*public*/ VSDecoderPreferences(QObject *parent) :
//      QObject(parent) {
//    }

/*public*/ void VSDecoderPreferences::load(QDomElement e)
{
    if (e.isNull())
    {
        return;
    }
    QString a;
    QDomElement c;
    if ((a = e.attribute("isAutoStartingEngine")) != "") {
        setAutoStartEngine(a.compare("true") == 0);
    }
    if ((a = e.attribute("isAutoLoadingDefaultVSDFile")) != "") {
        setAutoLoadDefaultVSDFile(a.compare("true") == 0);
    }
    if (!(c = e.firstChildElement("DefaultVSDFilePath")).isNull()) {
        setDefaultVSDFilePath(c.text());
    }
    if (!(c = e.firstChildElement("DefaultVSDFileName")).isNull()) {
        setDefaultVSDFileName(c.text());
    }
    if (!(c = e.firstChildElement("ListenerPosition")).isNull()) {
        _listenerPosition = new ListeningSpot(c);
    } else {
        _listenerPosition = new ListeningSpot();
    }
    if (!(c = e.firstChildElement("AudioMode")).isNull()) {
        setAudioMode(c.text());
    }
}

/**
 * An extension of the abstract XmlFile. No changes made to that class.
 *
 */

/*private*/ QDomElement VSDecoderPreferences::store()
{
    QDomElement ec;
    QDomElement e = doc.createElement("VSDecoderPreferences");
    e.setAttribute("isAutoStartingEngine", "" + isAutoStartingEngine());
    e.setAttribute("isAutoLoadingDefaultVSDFile", "" + isAutoLoadingDefaultVSDFile());
    ec = doc.createElement("DefaultVSDFilePath");
    //ec.setText("" + getDefaultVSDFilePath());
    ec.appendChild(doc.createTextNode(getDefaultVSDFilePath()));
    e.appendChild(ec);
    ec = doc.createElement("DefaultVSDFileName");
    //ec.setText("" + getDefaultVSDFileName());
    ec.appendChild(doc.createTextNode(getDefaultVSDFileName()));
    e.appendChild(ec);
    // ListenerPosition generates its own XML
    e.appendChild(_listenerPosition->getXml("ListenerPosition"));
    ec = doc.createElement("AudioMode");
    //ec.setText("" + AudioModeMap.value(_audioMode));
    ec.appendChild(doc.createTextNode(audioModeMap.value(_audioMode)));
    e.appendChild(ec);
    return e;
}

/*public*/ void VSDecoderPreferences::set(VSDecoderPreferences* tp) {
    setAutoStartEngine(tp->isAutoStartingEngine());
    setAutoLoadDefaultVSDFile(tp->isAutoLoadingDefaultVSDFile());
    setDefaultVSDFilePath(tp->getDefaultVSDFilePath());
    setDefaultVSDFileName(tp->getDefaultVSDFileName());
    setListenerPosition(tp->getListenerPosition());
    setAudioMode(tp->getAudioMode());

    if (listeners != NULL) {
        for (int i = 0; i < listeners->size(); i++) {
            PropertyChangeListener* l = listeners->value(i);
            PropertyChangeEvent* e = new PropertyChangeEvent(this, "VSDecoderPreferences", NULL, this);
            l->propertyChange(e);
        }
    }
}

/*public*/ bool VSDecoderPreferences::compareTo(VSDecoderPreferences* tp)
{
 return (isAutoStartingEngine() != tp->isAutoStartingEngine()
            || isAutoLoadingDefaultVSDFile() != tp->isAutoLoadingDefaultVSDFile()
            || (getDefaultVSDFilePath()!=(tp->getDefaultVSDFilePath()))
            || (getDefaultVSDFileName()!=(tp->getDefaultVSDFileName()))
            || (getListenerPosition()!=(tp->getListenerPosition()))
            || (getAudioMode()!=(tp->getAudioMode())));
}

/*public*/ void VSDecoderPreferences::save() {
     if (prefFile == "") {
        return;
    }
    XmlFile* xf = new XmlFile();// {
    //};   // odd syntax is due to XmlFile being abstract
    xf->makeBackupFile(prefFile);
    File* file = new File(prefFile);
    try {
        //The file does not exist, create it before writing
        File* parentDir = file->getParentFile();
        if (!parentDir->exists()) {
            if (!parentDir->mkdir()) // make directory, check result
            {
                log->error("failed to make parent directory");
            }
        }
        if (!file->createNewFile()) // create file, check result
        {
            log->error("createNewFile failed");
        }
    } catch (Exception* exp) {
        log->error("Exception while writing the new VSDecoder preferences file, may not be complete: " /*+ exp*/);
    }
    doc = xf->doc;
    try {
        QDomElement root = doc.createElement("vsdecoder-preferences");
        //Document doc = XmlFile.newDocument(root, XmlFile.dtdLocation+"vsdecoder-preferences.dtd");
        //QDomDocument doc = XmlFile::newDocument(root);
        // add XSLT processing instruction
        // <?xml-stylesheet type="text/xsl" href="XSLT/throttle.xsl"?>
/*TODO    		java.util.Map<String,String> m = new java.util.HashMap<String,String>();
         m.put("type", "text/xsl");
         m.put("href", jmri.jmrit.XmlFile.xsltLocation+"throttles-preferences.xsl");
         ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
         doc.addContent(0,p);*/
        root.appendChild(store());
        xf->writeXML(file, doc);
    } catch (Exception* ex) {
        log->warn("Exception in storing vsdecoder preferences xml: " /*+ ex*/);
    }
}

/*public*/ QString VSDecoderPreferences::getDefaultVSDFilePath() {
    return (_defaultVSDFilePath);
}

/*public*/ void VSDecoderPreferences::setDefaultVSDFilePath(QString s) {
    _defaultVSDFilePath = s;
}

/*public*/ QString VSDecoderPreferences::getDefaultVSDFileName() {
    return (_defaultVSDFileName);
}

/*public*/ void VSDecoderPreferences::setDefaultVSDFileName(QString s) {
    _defaultVSDFileName = s;
}

/*public*/ bool VSDecoderPreferences::isAutoStartingEngine() {
    return (_autoStartEngine);
}

/*public*/ void VSDecoderPreferences::setAutoStartEngine(bool b) {
    _autoStartEngine = b;
}

/*public*/ bool VSDecoderPreferences::isAutoLoadingDefaultVSDFile() {
    return (_autoLoadDefaultVSDFile);
}

/*public*/ void VSDecoderPreferences::setAutoLoadDefaultVSDFile(bool b) {
    _autoLoadDefaultVSDFile = b;
}

/*public*/ ListeningSpot* VSDecoderPreferences::getListenerPosition() {
    log->debug("getListenerPosition() : " + _listenerPosition->toString());
    return (_listenerPosition);
}

/*public*/ void VSDecoderPreferences::setListenerPosition(ListeningSpot* p) {
    VSDecoderManager* vm = VSDecoderManager::instance();
    vm->setListenerLocation(vm->getDefaultListenerName(), p);
    _listenerPosition = p;
}
// Note:  No setListenerPosition(String) for ListeningSpot implementation

/*public*/ PhysicalLocation* VSDecoderPreferences::getListenerPhysicalLocation() {
    return (_listenerPosition->getPhysicalLocation());
}

/*public*/ void VSDecoderPreferences::setListenerPosition(PhysicalLocation* p) {
    VSDecoderManager* vm = VSDecoderManager::instance();
#if 1 // TODO: PhysicalLocation extends Vector3f
    vm->setListenerLocation(vm->getDefaultListenerName(), new ListeningSpot(QVector3D(p->getX(), p->getY(), p->getZ())));
#endif
    //_listenerPosition = new ListeningSpot();
    //_listenerPosition.setLocation(p);
}

/*public*/ VSDecoderPreferences::AudioMode VSDecoderPreferences::getAudioMode() {
    return (_audioMode);
}

/*public*/ void VSDecoderPreferences::setAudioMode(AudioMode am) {
    _audioMode = am;
}

/*public*/ void VSDecoderPreferences::setAudioMode(QString am) {
    // There's got to be a more efficient way to do this
#if 0
    Set<Map.Entry<AudioMode, QString>> ids = audioModeMap.entrySet();
    Iterator<Map.Entry<AudioMode, QString>> idi = ids.iterator();
    while (idi.hasNext()) {
        Map.Entry<AudioMode, QString> e = idi.next();
        log->debug("    ID = " + e.getKey() + " Val = " + e);
        if (e.equals(am)) {
            _audioMode = e.getKey();
            return;
        }
    }
#else
 QMapIterator<AudioMode, QString> itr(audioModeMap);
 while(itr.hasNext())
 {
  itr.next();
  if(itr.value() == am)
   _audioMode = itr.key();
  return;
 }
#endif
    // We fell out of the loop.  Must be an invalid string. Set default
    _audioMode = DefaultAudioMode;
}

/**
 * Add an AddressListener. AddressListeners are notified when the user
 * selects a new address and when a Throttle is acquired for that address
 *
 * @param l
 */
/*public*/ void VSDecoderPreferences::addPropertyChangeListener(PropertyChangeListener* l)
{
    if (listeners == NULL)
    {
        listeners = new QList<PropertyChangeListener*>(/*2*/);
    }
    if (!listeners->contains(l)) {
        listeners->append(l);
    }
}

/**
 * Remove an AddressListener.
 *
 * @param l
 */
/*public*/ void VSDecoderPreferences::removePropertyChangeListener(PropertyChangeListener* l) {
    if (listeners == NULL) {
        return;
    }
    if (listeners->contains(l)) {
        listeners->removeOne(l);
    }
}
//#endif
