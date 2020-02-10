#include "lncabsignalmanager.h"
#include "loconetsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "lncabsignal.h"

/**
 * LocoNet implementation of the {@link jmri.CabSignalManager} interface.
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
 * @author Paul Bender Copyright (C) 2019
 */
// /*public*/ class LnCabSignalManager extends AbstractCabSignalManager {


    /*public*/ LnCabSignalManager::LnCabSignalManager(LocoNetSystemConnectionMemo* memo, QObject *parent)
 : AbstractCabSignalManager(parent){
         //super();
         _memo = memo;
         log->debug("LocoNet Cab Signal Manager initialized");
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ CabSignal* LnCabSignalManager::createCabSignal(LocoAddress* address){
           return new LnCabSignal(_memo,address);
    }

    /*private*/ /*final*/ /*static*/ Logger* LnCabSignalManager::log = LoggerFactory::getLogger("LnCabSignalManager");
