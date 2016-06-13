#include "vsdsound.h"
#include <QTimer>
#include "physicallocation.h"
#include "actionlistener.h"

//VSDSound::VSDSound(QObject *parent) :
//  QObject(parent)
//{
//}
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
 * @version			$Revision: 28746 $
 */
//import java.awt.event.ActionListener;
//import javax.swing.Timer;
//import jmri.util.PhysicalLocation;
//import org.jdom2.Element;

///*abstract*/ /*public*/ class VSDSound {

    /*public*/ /*final*/ /*static*/ QString VSDSound::SrcSysNamePrefix = "IAS$VSD:";
    /*public*/ /*final*/ /*static*/ QString VSDSound::BufSysNamePrefix = "IAB$VSD:";
    /*public*/ /*final*/ /*static*/ QString VSDSound::SrcUserNamePrefix = "IVSDS_";
    /*public*/ /*final*/ /*static*/ QString VSDSound::BufUserNamePrefix = "IVSDB_";

    /*public*/ /*final*/ /*static*/ float VSDSound::default_gain = 0.8f;



    /*public*/ VSDSound::VSDSound(QString name,QObject *parent) :
      QObject(parent) {
        this->name = name;
        gain = default_gain;
        vsd_file_base = "resource:resources/sounds/vsd/";

    }

    /*public*/ bool VSDSound::isPlaying() {
        return (is_playing);
    }

    /*protected*/ QTimer* VSDSound::newTimer(int time, bool repeat, ActionListener* al) {
        time = qMax(1, time);  // make sure the time is > zero
        t = new QTimer(/*time, al*/);
        connect(t, SIGNAL(timeout()), al, SLOT(actionPerformed()));
        //t->setInitialDelay(time);
        t->setInterval(time);
        //t->setRepeats(repeat);
        t->setSingleShot(!repeat);
        return (t);
    }

    // Required methods - /*abstract*/ because all subclasses MUST implement
    /*abstract*/ /*public*/ void VSDSound::play() {}

    /*abstract*/ /*public*/ void VSDSound::loop() {}

    /*abstract*/ /*public*/ void VSDSound::stop() {}

    /*abstract*/ /*public*/ void VSDSound::fadeIn(){}

    /*abstract*/ /*public*/ void VSDSound::fadeOut() {}

    /*abstract*/ /*public*/ void VSDSound::mute(bool /*m*/) {}

    /*abstract*/ /*public*/ void VSDSound::setVolume(float /*g*/) {}

    /*abstract*/ /*public*/ void VSDSound::shutdown() {}// called on window close.  Cease playing immediately.

    /*public*/ void VSDSound::setPosition(PhysicalLocation* p) {
        myposition = p;
    }

    /*public*/ PhysicalLocation* VSDSound::getPosition() {
        return (myposition);
    }

    // Optional methods - overridden in subclasses where needed.  Do nothing otherwise
    /*public*/ void VSDSound::changeNotch(int new_notch) {
    }

    /*public*/ void VSDSound::changeThrottle(float t) {
    }

    /*public*/ void VSDSound::setName(QString n) {
        name = n;
    }

    /*public*/ QString VSDSound::getName() {
        return (name);
    }

    /*public*/ float VSDSound::getGain() {
        return (gain);
    }

    /*public*/ void VSDSound::setGain(float g) {
        gain = g;
    }

    /*public*/ QDomElement VSDSound::getXml() {
        QDomElement me = doc.createElement("Sound");

        me.setAttribute("name", name);
        me.setAttribute("type", "empty");
        return (me);
    }

    /*public*/ void VSDSound::setXml(QDomElement e) {
        // Default: do nothing
    }
