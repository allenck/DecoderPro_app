#include "vsdecoder.h"
#include "vsdconfig.h"
#include "logger.h"
#include "audiomanager.h"
#include "instancemanager.h"
#include "vsdfile.h"
#include "locoaddress.h"
#include "vsdsound.h"
#include "vsdcontrol.h"
#include "vsdecoderevent.h"
#include "rosterentry.h"
#include "vsdmanagerframe.h"
#include "trigger.h"
#include "soundevent.h"
#include "momentarysoundevent.h"
#include "togglesoundevent.h"
#include "enginesoundevent.h"
#include "configurablesound.h"
#include "steamsound.h"
#include "dieselsound.h"
#include "diesel3sound.h"
#include "trainmanager.h"
#include "train.h"

//VSDecoder::VSDecoder(QObject *parent) :
//  QObject(parent)
//{
//}

/**
 * Virtual Sound Decoder
 *
 * Implements a software "decoder" that responds to throttle inputs and
 * generates sounds in responds to them.
 *
 * Each VSDecoder implements exactly one Sound Profile (describes a particular
 * type of locomtive, say, an EMD GP7).
 *
 */

/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 28771 $
 */
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import java.util.ArrayList;
//import java.util.Collection;
//import java.util.HashMap;
//import java.util.Iterator;
//import jmri.Audio;
//import jmri.DccLocoAddress;
//import jmri.InstanceManager;
//import jmri.LocoAddress;
//import jmri.jmrit.operations.locations.Location;
//import jmri.jmrit.operations.routes.RouteLocation;
//import jmri.jmrit.operations.trains.Train;
//import jmri.jmrit.operations.trains.TrainManager;
//import jmri.jmrit.vsdecoder.swing.VSDControl;
//import jmri.jmrit.vsdecoder.swing.VSDManagerFrame;
//import jmri.util.PhysicalLocation;
//import org.jdom2.Element;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

///*public*/ class VSDecoder implements PropertyChangeListener {




/**
 * public VSDecoder(String id, String name)
 *
 * Construct a VSDecoder with a given name and ID (system name)
 *
 * Parameters:
 *
 * @param id   (String) System Name of this VSDecoder
 * @param name (String) Sound Profile name for this VSDecoder
 */
//@Deprecated
/*public*/ VSDecoder::VSDecoder(QString id, QString name, QObject *parent) :
QObject(parent) {
 common();
 config = new VSDConfig();
 config->setProfileName(name);
 config->setID(id);

 sound_list =  QMap<QString, VSDSound*>();
 trigger_list =  QMap<QString, Trigger*>();
 event_list =  QMap<QString, SoundEvent*>();

 // Force re-initialization
 initialized = _init();
}

/**
 * public VSDecoder(VSDConfig cfg)
 *
 * Construct a VSDecoder with the given system name (id) and configuration
 * (config)
 *
 * Parameters:
 *
 * @param cfg (VSDConfig) Configuration
 */
/*public*/ VSDecoder::VSDecoder(VSDConfig* cfg, QObject *parent) :
  QObject(parent)
{
 common();
 config = cfg;

 sound_list =  QMap<QString, VSDSound*>();
 trigger_list =  QMap<QString, Trigger*>();
 event_list =  QMap<QString, SoundEvent*>();

 // Force re-initialization
 initialized = _init();

//        try {
 VSDFile* vsdfile = new VSDFile(config->getVSDPath());
 if (vsdfile->isInitialized()) {
     log->debug("Constructor: vsdfile init OK, loading XML...");
     this->setXml(vsdfile, config->getProfileName());
 } else {
     log->debug("Constructor: vsdfile init FAILED.");
     initialized = false;
 }
//        } catch (java.util.zip.ZipException e) {
//            log->error("ZipException loading VSDecoder from " + config->getVSDPath());
//            // would be nice to pop up a dialog here...
//        } catch (java.io.IOException ioe) {
//            log->error("IOException loading VSDecoder from " + config->getVSDPath());
//            // would be nice to pop up a dialog here...
//        }

 // Since the Config already has the address set, we need to call
 // our own setAddress() to register the throttle listener
 this->setAddress(config->getLocoAddress());
 this->enable();

 if (log->isDebugEnabled())
 {
  log->debug("VSDecoder Init Complete.  Audio Objects Created:");
  foreach (QString s, ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getSystemNameList(Audio::SOURCE))
  {
   log->debug("\tSource: " + s);
  }
  foreach (QString s, ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getSystemNameList(Audio::BUFFER))
  {
   log->debug("\tBuffer: " + s);
  }
 }
}

/**
 * public VSDecoder(String id, String name, String path)
 *
 * Construct a VSDecoder with the given system name (id), profile name and
 * VSD file path
 *
 * Parameters:
 *
 * @param id   (String) System name for this VSDecoder
 * @param name (String) Profile name
 * @param path (String) Path to a VSD file to pull the given Profile from
 */
/*public*/ VSDecoder::VSDecoder(QString id, QString name, QString path, QObject *parent) :
QObject(parent) {
 common();

 config = new VSDConfig();
 config->setProfileName(name);
 config->setID(id);

 sound_list =  QMap<QString, VSDSound*>();
 trigger_list =  QMap<QString, Trigger*>();
 event_list =  QMap<QString, SoundEvent*>();

 // Force re-initialization
 initialized = _init();

 config->setVSDPath(path);

 //try {
 VSDFile* vsdfile = new VSDFile(path);
 if (vsdfile->isInitialized()) {
     log->debug("Constructor: vsdfile init OK, loading XML...");
     this->setXml(vsdfile, name);
 } else {
     log->debug("Constructor: vsdfile init FAILED.");
     initialized = false;
 }
//        } catch (java.util.zip.ZipException e) {
//            log->error("ZipException loading VSDecoder from " + path);
//            // would be nice to pop up a dialog here...
//        } catch (java.io.IOException ioe) {
//            log->error("IOException loading VSDecoder from " + path);
//            // would be nice to pop up a dialog here...
//        }
}

void VSDecoder::common()
{
 initialized = false; // This decoder has been initialized
 enabled = false; // This decoder is enabled
 is_default = false; // This decoder is the default for its file
 tunnelVolume = 0.5f;
 log = new Logger("VSDecoder");
}

/*private*/ bool VSDecoder::_init() {
    // Do nothing for now
    this->enable();
    return (true);
}
/**
 * public String getID()
 *
 * Get the ID (System Name) of this VSDecoder
 *
 * @return (String) system name of this VSDecoder
 */
/*public*/ QString VSDecoder::getID() {
    return (config->getID());
}

/**
 * public bool isInitialized()
 *
 * Check whether this VSDecoder has completed initialization
 *
 * @return (bool) true if initialization is complete.
 */
/*public*/ bool VSDecoder::isInitialized() {
    return (initialized);
}

/**
 * public void setVSDFilePath(String p)
 *
 * Set the VSD File path for this VSDecoder to use
 *
 * @param p (String) path to VSD File
 */
/*public*/ void VSDecoder::setVSDFilePath(QString p) {
    config->setVSDPath(p);
}

/**
 * public String getVSDFilePath()
 *
 * Get the current VSD File path for this VSDecoder
 *
 * @return (String) path to VSD file
 */
/*public*/ QString VSDecoder::getVSDFilePath() {
    return (config->getVSDPath());
}
#if 0
    // VSDecoder Events
    /**
     * public String addEventListener(VSDecoderListener listener)
     *
     * Add a listener for this object's events
     *
     * @param listener handle
     */
    /*public*/ void addEventListener(VSDecoderListener listener) {
        listenerList.add(VSDecoderListener.class, listener);
    }

    /**
     * public String removeEventListener(VSDecoderListener listener)
     *
     * Remove a listener for this object's events
     *
     * @param listener handle
     */
    /*public*/ void removeEventListener(VSDecoderListener listener) {
        listenerList.remove(VSDecoderListener.class, listener);
    }
#endif
    /**
     * Fire an event to this object's listeners
     */
    /*private*/ void VSDecoder::fireMyEvent(VSDecoderEvent* evt) {
//        for (VSDecoderListener l : listenerList.getListeners(VSDecoderListener.class)) {
//            l.eventAction(evt);
//        }
 emit notify(evt);
    }
#if 0
    /**
     * public void windowChange(java.awt.event.WindowEvent e)
     *
     * Handle Window events from this VSDecoder's GUI window.
     *
     * @param e the window event to handle
     */
    /*public*/ void windowChange(java.awt.event.WindowEvent e) {
        log->debug("decoder.windowChange() - " + e.toString());
        log->debug("param string = " + e.paramString());
        // if (e.paramString()==("WINDOW_CLOSING")) {
        // Shut down the sounds.
        this->shutdown();

        // }
    }
#endif
    /**
     * public void shutdown()
     *
     * Shut down this VSDecoder and all of its associated sounds.
     *
     */
    /*public*/ void VSDecoder::shutdown() {
#if 0
        log->debug("Shutting down sounds...");
        foreach (VSDSound* vs, sound_list.values()) {
            log->debug("Stopping sound: " + vs->getName());
            vs->shutdown();
        }
#endif
    }

    /**
     * protected void throttlePropertyChange(PropertyChangeEvent event)
     *
     * Handle the details of responding to a PropertyChangeEvent from a
     * throttle.
     *
     * @param event (PropertyChangeEvent) Throttle event to respond to
     */
    /*protected*/ void VSDecoder::throttlePropertyChange(PropertyChangeEvent* event) {
        // WARNING: FRAGILE CODE
        // This will break if the return type of the event.getOld/NewValue() changes.

        QString eventName = event->getPropertyName();
        QVariant oldValue = event->getOldValue();
        QVariant newValue = event->getNewValue();

        // Skip this if disabled
        if (!enabled) {
            log->debug("VSDecoder disabled. Take no action.");
            return;
        }

        log->warn("VSDecoderPane throttle property change: " + eventName);

        if (oldValue != QVariant()) {
            log->warn("Old: " + oldValue.toString());
        }
        if (newValue != QVariant()) {
            log->warn("New: " + newValue.toString());
        }
#if 0
        // Iterate through the list of sound events, forwarding the propertyChange event.
        for (SoundEvent* t : event_list.values()) {
            t.propertyChange(event);
        }

        // Iterate through the list of triggers, forwarding the propertyChange event.
        for (Trigger t : trigger_list.values()) {
            t.propertyChange(event);
        }
#endif
    }

// DCC-specific and unused. Deprecate this->
//@Deprecated
/*public*/ void VSDecoder::releaseAddress(int number, bool isLong) {
    // remove the listener, if we can...
}

// DCC-specific. Deprecate this->
//@Deprecated
/*public*/ void VSDecoder::setAddress(int number, bool isLong) {
 this->setAddress((LocoAddress*)new DccLocoAddress(number, isLong));
}

/**
 * public void setAddress(LocoAddress l)
 *
 * Set this VSDecoder's LocoAddress, and register to follow events from the
 * throttle with this address.
 *
 * @param l (LocoAddress) LocoAddress to be followed
 */
/*public*/ void VSDecoder::setAddress(LocoAddress* l) {
    // Hack for ThrottleManager Dcc dependency
    config->setLocoAddress(l);
    // DccLocoAddress dl = new DccLocoAddress(l.getNumber(), l.getProtocol());
#if 0
   InstanceManager::throttleManagerInstance()->attachListener(config->getDccAddress(),
            new PropertyChangeListener()
   {
                /*public*/ void propertyChange(PropertyChangeEvent event) {
                    log->debug("property change name " + event.getPropertyName() + " old " + event.getOldValue()
                            + " new " + event.getNewValue());
                    throttlePropertyChange(event);
                }
            });
#endif
    log->debug("VSDecoder: Address set to " + config->getLocoAddress()->toString());
}

/**
 * public LocoAddress getAddress()
 *
 * Get the currently assigned LocoAddress
 *
 * @return the currently assigned LocoAddress
 */
/*public*/ LocoAddress* VSDecoder::getAddress() {
    return (config->getLocoAddress());
}

    /**
     * public float getMasterVolume()
     *
     * Get the current master volume setting for this VSDecoder
     *
     * @return (float) volume level (0.0 - 1.0)
     */
    /*public*/ float VSDecoder::getMasterVolume() {
        return (config->getVolume());
    }

    /**
     * public void setMasterVolume(float vol)
     *
     * Set the current master volume setting for this VSDecoder
     *
     * @param vol (float) volume level (0.0 - 1.0)
     */
    /*public*/ void VSDecoder::setMasterVolume(float vol) {
        log->debug("VSD: float volume = " + QString::number(vol));
        config->setVolume(vol);
        foreach (VSDSound* vs, sound_list.values()) {
            vs->setVolume(vol);
        }
    }

    /**
     * public bool isMuted()
     *
     * Is this VSDecoder muted?
     *
     * @return true if muted.
     */
    /*public*/ bool VSDecoder::isMuted() {
        return (false);
    }

    /**
     * public void mute(bool m)
     *
     * Mute or un-mute this VSDecoder
     *
     * @param m (bool) true to mute, false to un-mute
     */
    /*public*/ void VSDecoder::mute(bool m) {
        foreach (VSDSound* vs, sound_list.values()) {
            vs->mute(m);
        }
    }

    /**
     * public void setPosition(PhysicalLocation p)
     *
     * set the x/y/z position in the soundspace of this VSDecoder Translates the
     * given position to a position relative to the listener for the component
     * VSDSounds.
     *
     * The idea is that the user-preference Listener Position (relative to the
     * USER's chosen origin) is always the OpenAL Context's origin.
     *
     * @param p (PhysicalLocation) location relative to the user's chosen
     *          Origin.
     */
    /*public*/ void VSDecoder::setPosition(PhysicalLocation* p) {
        // Store the actual position relative to the user's Origin locally.
        config->setPhysicalLocation(p);
        log->debug("( " + this->getAddress()->toString() + ") Set Position: " + p->toString());

        // Give all of the VSDSound objects the position translated relative to the listener position.
        // This is a workaround for OpenAL requiring the listener position to always be at (0,0,0).
  /*
         * PhysicalLocation ref = VSDecoderManager.instance().getVSDecoderPreferences().getListenerPhysicalLocation();
         * if (ref == null) ref = PhysicalLocation.Origin;
         */
        foreach (VSDSound* s, sound_list.values()) {
            // s.setPosition(PhysicalLocation.translate(p, ref));
            s->setPosition(p);
        }
        // Set (relative) volume for this location (in case we're in a tunnel)
        float tv = config->getVolume();
        if (p->isTunnel()) {
            tv *= tunnelVolume;
            log->debug("VSD: Tunnel volume: " + QString::number(tv));
        } else {
            log->debug("VSD: Not in tunnel. Volume = " + QString::number(tv));
        }
        foreach (VSDSound* vs, sound_list.values()) {
            vs->setVolume(tv);
        }
        fireMyEvent(new VSDecoderEvent(this, VSDecoderEvent::LOCATION_CHANGE, VPtr<PhysicalLocation>::asQVariant(p)));
    }

    /**
     * public PhysicalLocation getPosition()
     *
     * Get the current x/y/z position in the soundspace of this VSDecoder
     *
     * @return PhysicalLocation location of this VSDecoder
     */
    /*public*/ PhysicalLocation* VSDecoder::getPosition() {
        return (config->getPhysicalLocation());
    }

    /**
     * public void propertyChange(PropertyChangeEvent evt)
     *
     * Respond to property change events from this VSDecoder's GUI
     *
     * @param evt (PropertyChangeEvent) event to respond to
     */
    //@SuppressWarnings("cast")
    /*public*/ void VSDecoder::propertyChange(PropertyChangeEvent* evt) {
        QString property = evt->getPropertyName();
        // Respond to events from the new GUI.
        if (qobject_cast<VSDControl*>(evt->getSource())!= NULL)
        {
#if 1 // TODO:
            if (property==(VSDControl::PCIDMap.value(VSDControl::OPTION_CHANGE)))
            {
                Operations::Train* selected_train = Operations::TrainManager::instance()->getTrainByName( evt->getNewValue().toString());
                if (selected_train != NULL) {
                    //selected_train.addPropertyChangeListener(this);
                 connect(selected_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                }
            }
#endif
            return;
        }


#if 0
        else if (property==(Train.TRAIN_LOCATION_CHANGED_PROPERTY)) {
            // Train Location Move (either GUI)
            PhysicalLocation p = getTrainPosition((Train) evt.getSource());
            if (p != null) {
                this->setPosition(getTrainPosition((Train) evt.getSource()));
            } else {
                log->debug("Train has null position");
                this->setPosition(new PhysicalLocation());
            }

        } else if (property==(Train.STATUS_CHANGED_PROPERTY)) {
            // Train Status change (either GUI)
            String status = (String) evt.getNewValue();
            log->debug("Train status changed: " + status);
            log->debug("New Location: " + getTrainPosition((Train) evt.getSource()));
            if ((status.startsWith(Train.BUILT)) || (status.startsWith(Train.PARTIAL_BUILT))) {
                log->debug("Train built. status = " + status);
                PhysicalLocation p = getTrainPosition((Train) evt.getSource());
                if (p != null) {
                    this->setPosition(getTrainPosition((Train) evt.getSource()));
                } else {
                    log->debug("Train has null position");
                    this->setPosition(new PhysicalLocation());
                }
            }
        }
#endif
    }
#if 0
    // Methods for handling location tracking based on JMRI Operations
    /**
     * protected PhysicalLocation getTrainPosition(Train t)
     *
     * Get the physical location of the given Operations Train
     *
     * @param t (Train) the Train to interrogate
     * @return PhysicalLocation location of the train
     */
    /*protected*/ PhysicalLocation* getTrainPosition(Train t) {
        if (t == null) {
            log->debug("Train is null.");
            return (null);
        }
        RouteLocation rloc = t.getCurrentLocation();
        if (rloc == null) {
            log->debug("RouteLocation is null.");
            return (null);
        }
        Location loc = rloc.getLocation();
        if (loc == null) {
            log->debug("Location is null.");
            return (null);
        }
        return (loc.getPhysicalLocation());
    }
#endif
    // Methods for handling the underlying sounds
    /**
     * public VSDSound getSound(String name)
     *
     * Retrieve the VSDSound with the given system name
     *
     * @param name (String) System name of the requested VSDSound
     * @return VSDSound the requested sound
     */
    /*public*/ VSDSound* VSDecoder::getSound(QString name) {
        return (sound_list.value(name));
    }

    /**
     * public void toggleBell()
     *
     * Turn the bell sound on/off
     *
     */
    /*public*/ void VSDecoder::toggleBell() {
        VSDSound* snd = sound_list.value("BELL");
        if (snd->isPlaying()) {
            snd->stop();
        } else {
            snd->loop();
        }
    }

    /**
     * public void toggleHorn()
     *
     * Turn the horn sound on/off
     *
     */
    /*public*/ void VSDecoder::toggleHorn() {
        VSDSound* snd = sound_list.value("HORN");
        if (snd->isPlaying()) {
            snd->stop();
        } else {
            snd->loop();
        }
    }

    /**
     * public void playHorn()
     *
     * Turn the horn sound on
     *
     */
    /*public*/ void VSDecoder::playHorn() {
        VSDSound* snd = sound_list.value("HORN");
        snd->loop();
    }

    /**
     * public void shortHorn()
     *
     * Turn the horn sound on (Short burst)
     *
     */
    /*public*/ void VSDecoder::shortHorn() {
        VSDSound* snd = sound_list.value("HORN");
        snd->play();
    }

    /**
     * public void stopHorn()
     *
     * Turn the horn sound off
     *
     */
    /*public*/ void VSDecoder::stopHorn() {
        VSDSound* snd = sound_list.value("HORN");
        snd->stop();
    }

    // Java Bean set/get Functions
    /**
     * public void setProfileName(String pn)
     *
     * Set the profile name to the given string
     *
     * @param pn (String) : name of the profile to set
     */
    /*public*/ void VSDecoder::setProfileName(QString pn) {
        config->setProfileName(pn);
    }

    /**
     * public String getProfileName()
     *
     * get the currently selected profile name
     *
     * @return (String) name of the currently selected profile
     */
    /*public*/ QString VSDecoder::getProfileName() {
        return (config->getProfileName());
    }

/**
 * public void enable()
 *
 * Enable this VSDecoder
 *
 */
/*public*/ void VSDecoder::enable() {
    enabled = true;
}

/**
 * public void disable()
 *
 * Disable this VSDecoder
 *
 */
/*public*/ void VSDecoder::disable() {
    enabled = false;
}

/**
 * public Collection<SoundEvent> getEventList()
 *
 * Get a Collection of SoundEvents associated with this VSDecoder
 *
 * @return Collection<SoundEvent> collection of SoundEvents
 */
/*public*/ QList<SoundEvent*> VSDecoder::getEventList() {
    return (event_list.values());
}

    /**
     * public bool isDefault()
     *
     * True if this is the default VSDecoder
     *
     * @return bool true if this is the default VSDecoder
     */
    /*public*/ bool VSDecoder::isDefault() {
        return (is_default);
    }

    /**
     * public void isDefault(bool d)
     *
     * Set whether this is the default VSDecoder or not
     *
     * @param d (bool) True to set this as the default, False if not.
     */
    /*public*/ void VSDecoder::setDefault(bool d) {
        is_default = d;
    }

    /**
     * public Element getXML()
     *
     * Get an XML representation of this VSDecoder Includes a subtree of
     * Elements for all of the associated SoundEvents, Triggers, VSDSounds, etc.
     *
     * @return Element XML Element for this VSDecoder
     */
    /*public*/ QDomElement VSDecoder::getXml() {
        //QDomElement me = doc.createElement("vsdecoder");
 QDomElement me = QDomElement();
 me.setTagName("vsdecoder");
        //ArrayList<Element> le = new ArrayList<Element>();

        me.setAttribute("name", this->config->getProfileName());

        // If this decoder is marked as default, add the default Element.
        if (is_default)
        {
            //me.appendChild(doc.createElement("default"));
         QDomElement d = QDomElement();
         d.setTagName("default");
         me.appendChild(d);
        }

        foreach (SoundEvent* se, event_list.values()) {
            //le.add(se.getXml());;
         me.appendChild(se->getXml());
        }

        foreach (VSDSound* vs, sound_list.values()) {
            //le.add(vs.getXml());
         me.appendChild(vs->getXml());
        }

        foreach (Trigger* t, trigger_list.values()) {
            //le.add(t.getXml());
         me.appendChild(t->getXml());
        }

        //me.addContent(le);

        // Need to add whatever else here.
        return (me);
    }

/*
 * @Deprecated public void setXml(Element e) { this->setXml(e, null); }
 *
 * @Deprecated public void setXml(Element e, VSDFile vf) { this->setXml(vf); }
 *
 * @Deprecated public void setXml(VSDFile vf) { }
 */
/**
 * publi/ void setXML(VSDFile vf, String pn)
 *
 * Build this VSDecoder from an XML representation
 *
 * @param vf (VSDFile) : VSD File to pull the XML from
 * @param pn (String) : Parameter Name to find within the VSD File.
 */
//@SuppressWarnings({"cast"})
/*public*/ void VSDecoder::setXml(VSDFile* vf, QString pn)
{

    //Iterator<Element> itr;
    QDomElement e = QDomElement();
    QDomElement el = QDomElement();
    SoundEvent* se;

    if (vf == NULL) {
        log->debug("Null VSD File Name");
        return;
    }

    log->debug("VSD File Name = " + vf->getName());
    // need to choose one.
    this->setVSDFilePath(vf->getName());

    // Find the <profile/> element that matches the name pn
    // List<Element> profiles = vf.getRoot().getChildren("profile");
    // java.util.Iterator i = profiles.iterator();
    //java.util.Iterator<Element> i = vf.getRoot().getChildren("profile").iterator();
    QDomNodeList i = vf->getRoot().elementsByTagName("profile");
   // while (i.hasNext()) {
    for(int j = 0; j < i.count(); j++)
    {
        e = i.at(j).toElement();//i.next();
        if (e.attribute("name")==(pn)) {
            break;
        }
    }
    // E is now the first <profile/> in vsdfile that matches pn.

    if (e.isNull()) {
        // No matching profile name found.
        return;
    }

    // Set this decoder's name.
    this->setProfileName(e.attribute("name"));
    log->debug("Decoder Name = " + e.attribute("name"));

    // Read and create all of its components.
    // Check for default element.
    if (e.firstChildElement("default") != QDomElement()) {
        log->debug("" + getProfileName() + "is default.");
        is_default = true;
    } else {
        is_default = false;
    }

    // +++ DEBUG
    // Log and print all of the child elements.
    //itr = (e.getChildren()).iterator();
    QDomNodeList itr = e.childNodes();
    //while (itr.hasNext()) {
    for(int i = 0; i < itr.count(); i++)
    {
     // Pull each element from the XML file.
        el = itr.at(i).toElement(); //itr.next();
        log->debug("Element: " + el.tagName());
        if (el.attribute("name") != "") {
            log->debug("  Name: " + el.attribute("name"));
            log->debug("   type: " + el.attribute("type"));
        }
    }
// --- DEBUG

    // First, the sounds.
    QString prefix = "" + this->getID() + ":";
    log->debug("VSDecoder " + this->getID() + " prefix = " + prefix);
    //itr = (e.getChildren("sound")).iterator();
     itr = e.elementsByTagName("sound");
    //while (itr.hasNext()) {
     for(int i = 0; i < itr.count(); i++)
     {
        el = itr.at(i).toElement(); //Element) itr.next();
        if (el.attribute("type") == "") {
            // Empty sound. Skip.
            log->debug("Skipping empty Sound.");
            continue;
        }

        else if (el.attribute("type")==("configurable")) {
            // Handle configurable sounds.
            ConfigurableSound* cs = new ConfigurableSound(prefix + el.attribute("name"));
            cs->setXml(el, vf);
            sound_list.insert(el.attribute("name"), cs);
        }
        else if (el.attribute("type")==("diesel")) {
            // Handle a Diesel Engine sound
            DieselSound* es = new DieselSound(prefix + el.attribute("name"));
            es->setXml(el, vf);
            sound_list.insert(el.attribute("name"), es);
        }
        else if (el.attribute("type")==("diesel3")) {
            // Handle a Diesel Engine sound
            Diesel3Sound* es = new Diesel3Sound(prefix + el.attribute("name"));
            es->setXml(el, vf);
            sound_list.insert(el.attribute("name"), es);
        }
        else if (el.attribute("type")==("steam")) {
            // Handle a Steam Engine sound
            SteamSound* es = new SteamSound(prefix + el.attribute("name"));
            es->setXml(el, vf);
            sound_list.insert(el.attribute("name"), es);
        }
        else {
            // TODO: Some type other than configurable sound. Handle appropriately
        }
    }

    const QMetaObject &mo = SoundEvent::staticMetaObject;
    int index = mo.indexOfEnumerator("ButtonType");
    QMetaEnum metaEnum = mo.enumerator(index);
    // Next, grab all of the SoundEvents
    // Have to do the sounds first because the SoundEvent's setXml() will
    // expect to be able to look it up.
    itr = (e.elementsByTagName("sound-event")); //.iterator();
    //while (itr.hasNext()) {
    for(int i = 0; i < itr.count(); i++)
    {
     el = itr.at(i).toElement(); //Element) itr.next();
     QString buttonType = el.attribute("buttontype").toUpper();

     //switch (SoundEvent::ButtonType.valueOf(buttonType))
     int value = metaEnum.keyToValue(buttonType.toLatin1());
     switch(value)
     {
      case SoundEvent::MOMENTARY:
       se = new MomentarySoundEvent(el.attribute("name"));
       break;
      case SoundEvent::TOGGLE:
       se = new ToggleSoundEvent(el.attribute("name"));
       break;
      case SoundEvent::ENGINE:
       se = new EngineSoundEvent(el.attribute("name"));
       break;
      case SoundEvent::NONE:
      default:
       se = new SoundEvent(el.attribute("name"));
     }

     se->setParent(this);
     se->setXml(el, vf);
     event_list.insert(se->getName(), se);
    }

    // Handle other types of children similarly here.
    // Check for an existing throttle and update speed if it exists.
    if(config->address == NULL)
    {
     log->error("No existing throttle found. address is NULL");
     return;
    }
    float s =  InstanceManager::throttleManagerInstance()->getThrottleInfo(config->getDccAddress(),
            "SpeedSetting").toFloat();
    if (s != 0) {
        // Mimic a throttlePropertyChange to propagate the current (init) speed setting of the throttle.
        log->debug("Existing Throttle found.  Speed = " + QString::number(s));
        this->throttlePropertyChange(new PropertyChangeEvent(this, "SpeedSetting", QVariant(), s));
    } else {
        log->debug("No existing throttle found.");
    }

}


