#ifndef CABSIGNAL_H
#define CABSIGNAL_H
#include <QObject>
#include "locoaddress.h"
#include "block.h"
#include "signalmast.h"
#include "propertychangelistener.h"

/**
 * Interface for a Cab Signal Object, describing the state of the track ahead
 * relative to a locomotive with a given address.  This is effectively a mobile
 * signal mast.
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 *
 * @author Steve Young Copyright (C) 2018
 * @author Paul Bender Copyright (C) 2019
 */
/*public*/ /*interface*/class CabSignal {
public:
    /**
     * A method for cleaning up the cab signal
     */
    /*public*/ virtual void dispose() = 0;

    /**
     * Get the LocoAddress associated with the consist
     *
     * @return the cab signal address
     */
    /*public*/ virtual LocoAddress* getCabSignalAddress() = 0;

    /**
     * Set the Block of the locomotive by searching the block list.
     */
    /*public*/ virtual void setBlock() = 0;

    /**
     * Set the Block of the locomotive
     *
     * @param position is a Block the locomotive is in.
     */
    /*public*/ virtual void setBlock(Block* position) = 0;

    /**
     * Get the Block position of the locomotive associated with the cab signal.
     *
     * @return The current Block position
     */
    /*public*/ virtual Block* getBlock() = 0;

    /**
     * Get the Next Block the locomotive is expected to enter.
     * This value is calculated from the current block and direction
     * of travel.
     *
     * @return The next Block position
     */
    /*public*/ virtual Block* getNextBlock() = 0;

    /**
     * Get the Next Signal Mast the locomotive is expected to pass.
     * This value may be calculated from the current block and direction
     * of travel.
     *
     * @return The next SignalMast position
     */
    /*public*/ virtual SignalMast* getNextMast() = 0;

    /**
     * Forward the current cab signal value to the layout.
     */
    /*public*/ virtual void forwardCabSignalToLayout() = 0;

    /*
     * get whether this cab signal is on or off
     *
     * @return true if on, false if off
     */
    /*public*/ virtual bool isCabSignalActive() = 0;

    /*
     * set whether this cab signal is on or off
     *
     * @param active true if on, false if off
     */
    /*public*/ virtual void setCabSignalActive(bool active) = 0;

    /*
     * set whether a Master Cab signal button is on or off
     *
     * @param active true if on, false if off
     */
    /*public*/ virtual void setMasterCabSigPauseActive(bool active) = 0;

    /**
     * Add a listener for consist events
     *
     * @param listener is a PropertyChangeListener object
     */
    /*public*/ virtual void addPropertyChangeListener(PropertyChangeListener* listener) = 0;

    /**
     * Remove a listener for cab signal events
     *
     * @param listener is a PropertyChangeListener object
     */
    /*public*/ virtual void removePropertyChangeListener(PropertyChangeListener* listener) = 0;

    /*public*/ virtual QObject* self() =0;

};
Q_DECLARE_INTERFACE(CabSignal, "CabSignal")
#endif // CABSIGNAL_H
