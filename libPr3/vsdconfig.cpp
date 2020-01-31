#include "vsdconfig.h"
#include "dcclocoaddress.h"
#include "rosterentry.h"

//VSDConfig::VSDConfig(QObject *parent) :
//  QObject(parent)
//{
//}

/**
 * class VSDConfig
 *
 * Data capsule ("Model"?) for passing configuration between the GUI and the
 * VSDecoder itself.
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
 * @version			$Revision: 21510 $
 */
//import jmri.DccLocoAddress;
//import jmri.LocoAddress;
//import jmri.jmrit.roster.RosterEntry;
//import jmri.util.PhysicalLocation;

///*public*/ class VSDConfig {


    /*public*/ VSDConfig::VSDConfig(QObject *parent) :
  QObject(parent) {
 DEFAULT_VOLUME = 0.8f;
        // umm... do... nothing? here...
        my_id = "";
        vsd_path = "";
        profile_name = "";
        address = NULL;
        volume = DEFAULT_VOLUME;
        location = NULL;
        roster = NULL;
    }

    /*public*/ QString VSDConfig::getID() {
        return (my_id);
    }

    /*public*/ QString VSDConfig::getVSDPath() {
        return (vsd_path);
    }

    /*public*/ QString VSDConfig::getProfileName() {
        return (profile_name);
    }

    /*public*/ locoAddress* VSDConfig::getLocoAddress() {
        return (address);
    }

    /*public*/ DccLocoAddress* VSDConfig::getDccAddress() {
        return (new DccLocoAddress(address->getNumber(), address->getProtocol()));
    }

    /*public*/ float VSDConfig::getVolume() {
        return (volume);
    }

    /*public*/ PhysicalLocation* VSDConfig::getPhysicalLocation() {
        return (location);
    }

    /*public*/ RosterEntry* VSDConfig::getRosterEntry() {
        return (roster);
    }

    /*public*/ void VSDConfig::setID(QString id) {
        my_id = id;
    }

    /*public*/ void VSDConfig::setVSDPath(QString path) {
        vsd_path = path;
    }

    /*public*/ void VSDConfig::setProfileName(QString name) {
        profile_name = name;
    }

    /*public*/ void VSDConfig::setLocoAddress(locoAddress* a) {
        address = a;
    }

    /*public*/ void VSDConfig::setVolume(float v) {
        volume = v;
    }

    /*public*/ void VSDConfig::setPhysicalLocation(PhysicalLocation* p) {
        location = p;
    }

    /*public*/ void VSDConfig::setRosterEntry(RosterEntry* r) {
        roster = r;
    }

    /*public*/ QString VSDConfig::toString() {
        return ("Config: ID:" + my_id
                + " Path:" + vsd_path
                + " Profile:" + profile_name
                + " Addr:" + address->toString()
                + " Vol:" + volume
                + " Loc:" /*+ location*/);
    }

