#ifndef CABSIGNALMANAGER_H
#define CABSIGNALMANAGER_H
#include "locoaddress.h"
#include "cabsignal.h"
#include "cabsignallistlistener.h"

/**
 * Interface for CabSignal Manager objects, which provide access to the existing
 * CabSignals and allows for creation and destruction.
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Paul Bender Copyright (C) 2019
 */
/*public*/ /*interface*/ class CabSignalManager
{
 public:
    /**
     * Find a CabSignal with the given address, and return it. If the CabSignal
     * doesn't exit, create it.
     *
     * @param address the cab signal for the address
     * @return an existing or new cab signal
     */
    /*public*/ virtual  CabSignal* getCabSignal(LocoAddress* address) = 0;

    /**
     * Remove an old CabSignal.
     *
     * @param address the address associated with the cab signal
     */
    /*public*/ virtual  void delCabSignal(LocoAddress* address) = 0;

    /**
     * Get a list of known cab signal addresses.
     *
     * @return list of cab signal addresses
     */
    /*public*/ virtual  QSet<LocoAddress*> getCabSignalList() = 0;

    /**
     * Get an array of known cab signals.
     *
     * @return array of cab signals
     */
    /*public*/ virtual  QVector<CabSignal*> getCabSignalArray() = 0;

    /**
     * Register a CabSignalListListener object with this CabSignalManager
     *
     * @param listener a CabSignal List Listener object.
     */
    /*public*/ virtual  void addCabSignalListListener(CabSignalListListener* listener) = 0;

    /**
     * Remove a CabSignalListListener object with this CabSignalManager
     *
     * @param listener a CabSignal List Listener object.
     */
    /*public*/ virtual  void removeCabSignalListListener(CabSignalListListener* listener) = 0;

    /**
     * Notify the registered CabSignalListListener objects that the CabSignalList
     * has changed.
     */
    /*public*/ virtual  void notifyCabSignalListChanged() = 0;
 virtual QObject* self() =0;


};
Q_DECLARE_INTERFACE(CabSignalManager, "CabSignalManager")
#endif // CABSIGNALMANAGER_H
