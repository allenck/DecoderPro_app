#include "vsdecodermanager.h"
#include "fileutil.h"
#include "file.h"
#include "vsdecoderpreferences.h"
#include "listeningspot.h"
#include "vsdlistener.h"
#include "vsdecodermanagerthread.h"
#include "vsdecoder.h"
#include "instancemanager.h"
#include "vsdmanagerframe.h"
#include "vsdconfig.h"
#include "locoaddress.h"
#include "namedbeanhandle.h"
#include "vsdfile.h"
#include "vsdmanagerevent.h"
#include "eventlistenerlist.h"

//VSDecoderManager::VSDecoderManager(QObject *parent) :
//  QObject(parent)
//{
//}
/*private*/ /*static*/ /*final*/ QString VSDecoderManager::vsd_property_change_name = "VSDecoder Manager"; //NOI18N
/*private*/ /*static*/ VSDecoderManagerThread* VSDecoderManager::thread = nullptr; // thread for running the manager
/*private*/ /*static*/ int VSDecoderManager::vsdecoderID = 0;


// VSDecoderFactory
//
// Builds VSDecoders as needed.  Handles loading from XML if needed.
// /*public*/ class VSDecoderManager implements PropertyChangeListener {

    ///*private*/ static final ResourceBundle rb = VSDecoderBundle.bundle();
    ///*private*/ static int listenerID = 0; // for future use

    // Unused?
    ///*private*/ PhysicalLocation listener_position;
// constructor - for kicking off by the VSDecoderManagerThread...
// WARNING: Should only be called from static instance()
/*public*/ VSDecoderManager::VSDecoderManager(QObject *parent) :
QObject(parent) {
 log = new Logger("VSDecoderManager");
 //ListenerList = new EventListenerList();
 // Setup the decoder table
 listenerTable =   QMap<QString, VSDListener*>();
 decodertable =  QMap<QString, VSDecoder*>();
 decoderAddressMap =  QMap<QString, VSDecoder*>();
 profiletable =  QMap<QString, QString>();  // key = profile name, value = path
 managerFrame = nullptr;
 reportertable =  QStringList();
 // Get preferences
 QString dirname = FileUtil::getUserFilesPath() + "vsdecoder" + File::separator; // NOI18N
 FileUtil::createDirectory(dirname);

 vsdecoderPrefs = new VSDecoderPreferences(dirname + VSDecoderPreferences::VSDPreferencesFileName);
 // Listen to ReporterManager for Report List changes
 setupReporterManagerListener();
 // Get a Listener (the only one for now)
 //VSDListener t = new VSDListener(getNextListenerID());
 VSDListener* t = new VSDListener();
 listenerTable.insert(t->getSystemName(), t);
}

/*public*/ /*static*/ VSDecoderManager* VSDecoderManager::instance()
{
 if (thread == nullptr) {
     thread = VSDecoderManagerThread::instance(true);
 }
 return (VSDecoderManagerThread::manager());
}
/*public*/ VSDecoderPreferences* VSDecoderManager::getVSDecoderPreferences()
{
 return (vsdecoderPrefs);
}

/*public*/ JmriJFrame* VSDecoderManager::provideManagerFrame()
{
 if (managerFrame == nullptr) {
     managerFrame = new VSDManagerFrame();
 }
 return (managerFrame);
}

/*private*/ QString VSDecoderManager::getNextVSDecoderID()
{
 // vsdecoderID initialized to zero, pre-incremented before return...
 // first returned ID value is 1.
 return ("IAD:VSD:VSDecoderID" + (++vsdecoderID)); // NOI18N
}

// To be used in the future
/*
 private QString VSDecoderManager::getNextListenerID() {
 // ListenerID initialized to zero, pre-incremented before return...
 // first returned ID value is 1.
 // Prefix is added by the VSDListener constructor
 return("VSDecoderID" + (++listenerID)); // NOI18N
 }
 */
//@Deprecated
/*public*/ VSDecoder* VSDecoderManager::getVSDecoder(QString profile_name)
{
 VSDecoder* vsd;
 QString path;
 if (profiletable.contains(profile_name))
 {
  path = profiletable.value(profile_name);
  log->debug("Profile " + profile_name + " is in table.  Path = " + path);
  vsd = new VSDecoder(getNextVSDecoderID(), profile_name, path);
  decodertable.insert(vsd->getID(), vsd);  // poss. broken for duplicate profile names
  if(vsd->getAddress() != nullptr)
   decoderAddressMap.insert(vsd->getAddress()->toString(), vsd);
  return (vsd);
 }
 else
 {
  // Don't have enough info to try to load from file.
  log->error("Requested profile not loaded: " + profile_name);
  return (nullptr);
 }
}

/*public*/ VSDecoder* VSDecoderManager::getVSDecoder(QString profile_name, QString path) {
    VSDecoder* vsd = new VSDecoder(getNextVSDecoderID(), profile_name, path);
    decodertable.insert(vsd->getID(), vsd); // poss. broken for duplicate profile names
    if (vsd->getAddress() != nullptr) {
        decoderAddressMap.insert(vsd->getAddress()->toString(), vsd);
    }
    return (vsd);
}

/**
 * Provide or build a VSDecoder based on a provided configuration
 */
/*public*/ VSDecoder* VSDecoderManager::getVSDecoder(VSDConfig* config) {
    QString path;
    QString profile_name = config->getProfileName();
    // First, check to see if we already have a VSDecoder on this Address
    //debugPrintDecoderList();
    if (decoderAddressMap.contains(config->getLocoAddress()->toString())) {
        return (decoderAddressMap.value(config->getLocoAddress()->toString()));
    }
    if (profiletable.contains(profile_name)) {
        path = profiletable.value(profile_name);
        log->debug("Profile " + profile_name + " is in table.  Path = " + path);
        config->setVSDPath(path);
        config->setID(getNextVSDecoderID());
        VSDecoder* vsd = new VSDecoder(config);
        decodertable.insert(vsd->getID(), vsd);
        decoderAddressMap.insert(vsd->getAddress()->toString(), vsd);
        //debugPrintDecoderList();
        return (vsd);
    } else {
        // Don't have enough info to try to load from file.
        log->error("Requested profile not loaded: " + profile_name);
        return (nullptr);
    }
}

/*
 public void debugPrintDecoderList() {
 log->debug("Current Decoder List by System ID:");
 Set<Map.Entry<String, VSDecoder>> ids = decodertable.entrySet();
 Iterator<Map.Entry<String, VSDecoder>> idi = ids.iterator();
 while (idi.hasNext()) {
 Map.Entry<String, VSDecoder> e = idi.next();
 log->debug("    ID = " +  e.getKey() + " Val = " + e.getValue().getAddress().toString());
 }
 log->debug("Current Decoder List by Address:");
 ids = decoderAddressMap.entrySet();
 idi = ids.iterator();
 while (idi.hasNext()) {
 Map.Entry<String, VSDecoder> e = idi.next();
 log->debug("    ID = " +  e.getKey() + " Val = " + e.getValue().getID());
 }
 }
 */
/*public*/ VSDecoder* VSDecoderManager::getVSDecoderByID(QString id) {
    VSDecoder* v = decodertable.value(id);
    if (v == nullptr) {
        log->debug("No decoder in table! ID = " +id);
    }
    return (decodertable.value(id));
}

/*public*/ VSDecoder* VSDecoderManager::getVSDecoderByAddress(QString sa) {
 if (sa == "") {
        log->debug("Decoder Address is Null");
        return (nullptr);
    }
    log->debug("Decoder Address: " + sa);
    VSDecoder* rv = decoderAddressMap.value(sa);
    if (rv == nullptr) {
        log->debug("Not found.");
    } else {
        log->debug("Found: " + rv->getAddress()->toString());
    }
    return (rv);
}

/*
 public VSDecoder getVSDecoderByAddress(String sa) {
 // First, translate the string into a DccLocoAddress
 // no object if no address
 if (sa.equals("")) return NULL;

 DccLocoAddress da = NULL;
 // ask the Throttle Manager to handle this!
 LocoAddress.Protocol protocol;
 if(InstanceManager.throttleManagerInstance()!=NULL){
 protocol = InstanceManager.throttleManagerInstance().getProtocolFromString(sa);
 da = (DccLocoAddress)InstanceManager.throttleManagerInstance().getAddress(sa, protocol);
 }

 // now look up the decoder
 if (da != NULL) {
 return getVSDecoderByAddress(da);
 }
 return(NULL);

 }
 */
/*public*/ void VSDecoderManager::setDefaultVSDecoder(VSDecoder* d) {
    default_decoder = d;
}

/*public*/ VSDecoder* VSDecoderManager::getDefaultVSDecoder() {
    return (default_decoder);
}

/*public*/ QStringList VSDecoderManager::getVSDProfileNames() {
    QStringList sl =  QStringList();
    foreach (QString p, profiletable.keys()) {
        sl.append(p);
    }
    return (sl);
}

/*public*/ QList<VSDecoder*> VSDecoderManager::getVSDecoderList() {
    return (decodertable.values());
}

/*public*/ QString VSDecoderManager::getDefaultListenerName() {
    return (VSDListener::ListenerSysNamePrefix + "ListenerID1"); // NOI18N
}

/*public*/ ListeningSpot* VSDecoderManager::getDefaultListenerLocation()
{
    VSDListener* l = listenerTable.value(getDefaultListenerName());
    if (l != nullptr) {
        return (l->getLocation());
    } else {
        return (nullptr);
    }
}

/*public*/ void VSDecoderManager::setListenerLocation(QString id, ListeningSpot* sp)
{
    VSDListener* l = listenerTable.value(id);
    if (l != nullptr)
    {
     log->debug("Set listener location " + sp->toString() + " listener: " + l->objectName());

        l->setLocation(sp);
    }
}

/*public*/ void VSDecoderManager::setDecoderPositionByID(QString id, PhysicalLocation* p) {
    VSDecoder* d = decodertable.value(id);
    if (d != nullptr) {
        d->setPosition(p);
    }
}

/*public*/ void VSDecoderManager::setDecoderPositionByAddr(LocoAddress* a, PhysicalLocation* l) {
    // Find the addressed decoder
    // This is a bit hokey.  Need a better way to index decoder by address
    // OK, this whole LocoAddress vs. DccLocoAddress thing has rendered this SUPER HOKEY.
    if (a == nullptr) {
        log->warn("Decoder Address is Null");
        return;
    }
    if (l == nullptr) {
        log->warn("PhysicalLocation is Null");
        return;
    }
    if (l==(PhysicalLocation::Origin)) {
        log->debug("Location : " + l->toString() + " ... ignoring.");
        // Physical location at origin means it hasn't been set.
        return;
    }
    log->debug("Decoder Address: " + QString::number(a->getNumber()));
    foreach (VSDecoder* d, decodertable.values()) {
        // Get the Decoder's address protocol.  If it's a DCC_LONG or DCC_SHORT, convert to DCC
        // since the LnReprter can't tell the difference and will always report "DCC".
        if (d == nullptr) {
            log->debug("VSdecoder NULL pointer!");
            return;
        }
        LocoAddress* pa = d->getAddress();
        if (pa == nullptr) {
            log->debug("Vsdecoder" + d->objectName() + " address NULL!");
            return;
        }
        LocoAddress::Protocol p = d->getAddress()->getProtocol();
        if (p == 0) {
            log->debug("Vsdecoder" + d->objectName() + " address = " + pa->toString() + " protocol NULL!");
            return;
        }
        if ((p == LocoAddress::DCC_LONG) || (p == LocoAddress::DCC_SHORT)) {
            p = LocoAddress::DCC;
        }
        if ((d->getAddress()->getNumber() == a->getNumber()) && (p == a->getProtocol())) {
            d->setPosition(l);
            // Loop through all the decoders (assumes N will be "small"), in case
            // there are multiple decoders with the same address.  This will be somewhat broken
            // if there's a DCC_SHORT and a DCC_LONG decoder with the same address number.
            //return;
        }
    }
    // decoder not found.  Do nothing.
    return;
}

// VSDecoderManager Events
/*public*/ void VSDecoderManager::addEventListener(VSDManagerListener* /*listener*/) {
  //listenerList->add("VSDManagerListener", listener);
}

/*public*/ void VSDecoderManager::removeEventListener(VSDManagerListener* /*listener*/) {
 //listenerList->remove("VSDManagerListener", listener);
}

void VSDecoderManager::fireMyEvent(VSDManagerEvent* evt) {
    //Object[] listeners = listenerList.getListenerList();

// for (VSDManagerListener l : listenerList.getListeners("VSDManagerListener")) {
//        l.eventAction(evt);
//    }
 emit fireEvent(evt);
}
/**
 * getProfilePath()
 *
 * Retrieve the Path for a given Profile name.
 */
/*public*/ QString VSDecoderManager::getProfilePath(QString profile) {
    return (profiletable.value(profile));
}

/**
 * Load Profiles from a VSD file Not deprecated anymore. used by the new
 * ConfigDialog->
 */
/*public*/ void VSDecoderManager::loadProfiles(QString path) {
    //try {
        VSDFile* vsdfile = new VSDFile(path);
        if (vsdfile->isInitialized()) {
            this->loadProfiles(vsdfile);
        }
//    } catch (java.util.zip.ZipException e) {
//        log->error("ZipException loading VSDecoder from " + path);
//        // would be nice to pop up a dialog here...
//    } catch (java.io.IOException ioe) {
//        log->error("IOException loading VSDecoder from " + path);
//        // would be nice to pop up a dialog here...
//    }
}

/*protected*/ void VSDecoderManager::registerReporterListener(QString sysName) {
    Reporter* r = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(sysName);
    if (r == nullptr) {
        return;
    }
    NamedBeanHandle<Reporter*>* h = nbhm->getNamedBeanHandle(sysName, r);
    if (h == nullptr) {
        return;
    }
    // Make sure we aren't already registered.
    QVector<PropertyChangeListener*> ll = r->getPropertyChangeListeners(h->getName());
    if (ll.isEmpty()) {
        r->addPropertyChangeListener((PropertyChangeListener*)this, h->getName(), vsd_property_change_name);
    }
}

/*protected*/ void VSDecoderManager::registerBeanListener(Manager* beanManager, QString sysName) {
    NamedBean* b = beanManager->getBeanBySystemName(sysName);
    if (b == nullptr) {
        log->debug("No bean by name " + sysName);
        return;
    }
    NamedBeanHandle<NamedBean*>* h = nbhm->getNamedBeanHandle(sysName, b);
    if (h == nullptr) {
        log->debug("no handle for bean " + b->getDisplayName());
        return;
    }
    // Make sure we aren't already registered.
    QVector<PropertyChangeListener*> ll = b->getPropertyChangeListenersByReference(h->getName());
    if (ll.isEmpty()) {
        b->addPropertyChangeListener((PropertyChangeListener*)this, h->getName(), vsd_property_change_name);
        log->debug("Added listener to bean " + b->getDisplayName() + " type " + b->metaObject()->className());
    }
}

/*protected*/ void VSDecoderManager::registerReporterListeners() {
    // Walk through the list of reporters
    foreach (QString sysName, static_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->getSystemNameList()) {
        registerReporterListener(sysName);
    }
    foreach (QString sysname, static_cast<BlockManager*>(InstanceManager::getDefault("BlockManager"))->getSystemNameList()) {
        registerBeanListener(static_cast<BlockManager*>(InstanceManager::getDefault("BlockManager")), sysname);
    }
}

// This listener listens to the ReporterManager for changes to the list of Reporters.
// Need to trap list length (name="length") changes and add listeners when new ones are added.
/*private*/ void VSDecoderManager::setupReporterManagerListener() {
    // Register ourselves as a listener for changes to the Reporter list.  For now, we won't do this. Just force a
    // save and reboot after reporters are added.  We'll fix this later.
    //	jmri.InstanceManager.reporterManagerInstance().addPropertyChangeListener(new PropertyChangeListener() {
    //	/*public*/ void propertyChange(PropertyChangeEvent event) {
    //		    log->debug("property change name " + event.getPropertyName() + " old " + event.getOldValue() + " new " + event.getNewValue());
    //	    reporterManagerPropertyChange(event);
    //	}
    //   });
    ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->addPropertyChangeListener((PropertyChangeListener*)this);

    // Now, the Reporter Table might already be loaded and filled out, so we need to get all the Reporters and list them.
    // And add ourselves as a listener to them.
    QSet<NamedBean*> reporterSet = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getNamedBeanSet();
    for (NamedBean* r : reporterSet) {
        if (r != nullptr) {
            registerReporterListener(((Reporter*)r)->getSystemName());
        }
    }

    QSet<NamedBean*> blockSet = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getNamedBeanSet();
    for (NamedBean* b : blockSet) {
        if (b != nullptr) {
            registerBeanListener((BlockManager*)InstanceManager::getDefault("BlockManager"), ((NamedBean*)b)->getSystemName());
        }
    }
}
#if 0
/*protected*/ void shutdownDecoders() {
    // Shut down and destroy all running VSDecoders.
    Set<String> vk = decodertable.keySet();
    Iterator<String> it = vk.iterator();
    while (it.hasNext()) {
        VSDecoder v = decodertable.get(it.next());
        v.shutdown();
    }
    // Empty the DecoderTable
    decodertable.clear();
    /*
     vk = decodertable.keySet();
     it = vk.iterator();
     while(it.hasNext()) {
     decodertable.remove(it.next());
     }
     */
    // Empty the AddressMap
    decoderAddressMap.clear();
    /*
     vk = decoderAddressMap.keySet();
     it = vk.iterator();
     while(it.hasNext()) {
     decoderAddressMap.remove(it.next());
     }
     */
}

/*public*/ void propertyChange(PropertyChangeEvent evt) {
    log->debug("property change type " + evt.getSource().getClass().getName()
            + " name " + evt.getPropertyName() + " old " + evt.getOldValue()
            + " new " + evt.getNewValue());
    if (evt.getSource() instanceof jmri.ReporterManager) {
        reporterManagerPropertyChange(evt);
    } else if (evt.getSource() instanceof jmri.Reporter) {
        reporterPropertyChange(evt);
    } else if (evt.getSource() instanceof jmri.Block) {
        log->debug("Block property change! name = " + evt.getPropertyName() + " old= " + evt.getOldValue() + " new= " + evt.getNewValue());
        blockPropertyChange(evt);
    } else if (evt.getSource() instanceof VSDManagerFrame) {
        if (evt.getPropertyName().equals(VSDManagerFrame.PCIDMap.get(VSDManagerFrame.PropertyChangeID.REMOVE_DECODER))) {
            // Shut down the requested decoder and remove it from the manager's hash maps.
            // Unless there are "illegal" handles, this should put the decoder on the garbage heap.  I think.
            String sa = (String) evt.getNewValue();
            VSDecoder d = this.getVSDecoderByAddress(sa);
            log->debug("Removing Decoder " + sa + " ... " + d.getAddress());
            d.shutdown();
            decodertable.remove(d.getID());
            decoderAddressMap.remove(sa);
            //debugPrintDecoderList();
        } else if (evt.getPropertyName().equals(VSDManagerFrame.PCIDMap.get(VSDManagerFrame.PropertyChangeID.CLOSE_WINDOW))) {
            // Note this assumes there is only one VSDManagerFrame open at a time.
            shutdownDecoders();
            managerFrame = NULL;
        }
    } else {
        // Un-Handled source. Does nothing ... yet...
    }
    return;
}

/*public*/ void blockPropertyChange(PropertyChangeEvent event) {
    // Needs to check the ID on the event, look up the appropriate VSDecoder,
    // get the location of the event source, and update the decoder's location.
    @SuppressWarnings("cast") // NOI18N
    String eventName = (String) event.getPropertyName();
    if (event.getSource() instanceof PhysicalLocationReporter) {
        Block blk = (Block) event.getSource();
        String repVal = NULL;
        // Depending on the type of Block Event, extract the needed report info from
        // the appropriate place...
        // "state" => Get loco address from Block's Reporter if present
        // "value" => Get loco address from event's newValue.
        if (eventName.equals("state")) { // NOI18N
            // Need to decide which reporter it is, so we can use different methods
            // to extract the address and the location.
            if ((Integer) event.getNewValue() == Block.OCCUPIED) {
                // Get this Block's Reporter's current/last report value.  need to fix this - it could be
                /// an idtag type reporter.
                if (blk.getReporter() == NULL) {
                    log->debug("Block " + blk.getSystemName() + " has no reporter!  Skipping state-type report.");
                    return;
                }
                if (blk.isReportingCurrent()) {
                    repVal = (String) blk.getReporter().getCurrentReport();
                } else {
                    repVal = (String) blk.getReporter().getLastReport();
                }
            } else {
                log->debug("Ignoring report. not an OCCUPIED event.");
                return;
            }
        } else if (eventName.equals("value")) {
            if (event.getNewValue() instanceof String) {
                repVal = event.getNewValue().toString();
            }
            // Else it will still be NULL from the declaration/assignment above.
        } else {
            log->debug("Not a supported Block event type.  Ignoring.");
            return;
        }  // Type of eventName.
        // Set the decoder's position.
        if (repVal == NULL) {
            log->warn("Report from Block " + blk.getUserName() + " is NULL!");
        }
        if (blk.getDirection(repVal) == PhysicalLocationReporter.Direction.ENTER) {
            setDecoderPositionByAddr(blk.getLocoAddress(repVal), blk.getPhysicalLocation());
        }
        return;
    } else {
        log->debug("Reporter doesn't support physical location reporting.");
    }  // Reporting object implements PhysicalLocationReporter
    return;
}

/*public*/ void reporterPropertyChange(PropertyChangeEvent event) {
    // Needs to check the ID on the event, look up the appropriate VSDecoder,
    // get the location of the event source, and update the decoder's location.
    @SuppressWarnings("cast") // NOI18N
    String eventName = (String) event.getPropertyName();
    if ((event.getSource() instanceof PhysicalLocationReporter) && (eventName.equals("currentReport"))) { // NOI18N
        PhysicalLocationReporter arp = (PhysicalLocationReporter) event.getSource();
        // Need to decide which reporter it is, so we can use different methods
        // to extract the address and the location.
        if (event.getNewValue() instanceof String) {
            String newValue = (String) event.getNewValue();
            if (arp.getDirection(newValue) == PhysicalLocationReporter.Direction.ENTER) {
                setDecoderPositionByAddr(arp.getLocoAddress(newValue), arp.getPhysicalLocation(newValue));
            }
        } else if (event.getNewValue() instanceof IdTag) {
            // newValue is of IdTag type.
            // Dcc4Pc, Ecos,
            // Assume Reporter "arp" is the most recent seen location
            IdTag newValue = (IdTag) event.getNewValue();
            setDecoderPositionByAddr(arp.getLocoAddress(newValue.getTagID()), arp.getPhysicalLocation(NULL));
        } else {
            log->debug("Reporter's return type is not supported.");
            // do nothing
        }

    } else {
        log->debug("Reporter doesn't support physical location reporting or isn't reporting new info.");
    }  // Reporting object implements PhysicalLocationReporter
    return;
}

/*public*/ void reporterManagerPropertyChange(PropertyChangeEvent event) {
    String eventName = event.getPropertyName();

    log->debug("VSDecoder received Reporter Manager Property Change: " + eventName);
    if (eventName.equals("length")) { // NOI18N

        // Re-register for all the reporters. The registerReporterListener() will skip
        // any that we're already registered for.
        for (String sysName : jmri.InstanceManager.reporterManagerInstance().getSystemNameList()) {
            registerReporterListener(sysName);
        }

        // It could be that we lost a Reporter.  But since we aren't keeping a list anymore
        // we don't care.
    }
}
#endif
/*public*/ void VSDecoderManager::loadProfiles(VSDFile* vf) {
    QDomElement root;
    QString pname;
    if ((root = vf->getRoot()) == QDomElement()) {
        return;
    }

    QStringList new_entries = QStringList();
#if 1
    //java.util.Iterator<Element> i = root.getChildren("profile").iterator(); // NOI18N
    QDomNodeList nl = root.childNodes();
    //while (i.hasNext()) {
    for(int i = 0; i < nl.count(); i++)
    {
        QDomElement e = nl.at(i).toElement(); //i.next();
        log->debug(e.tagName());
        if ((pname = e.attribute("name")) != nullptr) { // NOI18N
            profiletable.insert(pname, vf->getName());
            new_entries.append(pname);
        }
    }

// debug
/*
     for (String s : new_entries) {
     log->debug("New entry: " + s);
     }
     */
    // /debug
    fireMyEvent(new VSDManagerEvent(this, VSDManagerEvent::PROFILE_LIST_CHANGE, new_entries));
#endif
}


