#include "hexfilesystemconnectionmemo.h"

HexFileSystemConnectionMemo::HexFileSystemConnectionMemo(QObject *parent)
 : LocoNetSystemConnectionMemo(parent)
{

}
/**
 * Lightweight class to denote that a system is "active" via a LocoNet hexfile emulator.
 * <p>
 * Objects of specific subtypes are registered in the instance manager to
 * activate their particular system.
 *
 * @author Kevin Dickerson Copyright (C) 2010
 */
// /*public*/ class HexFileSystemConnectionMemo extends jmri.jmrix.loconet.LocoNetSystemConnectionMemo {

    //@Override
    /*public*/ LnSensorManager* HexFileSystemConnectionMemo::getSensorManager() {
        if (getDisabled()) {
            return nullptr;
        }
        if (sensorManager == nullptr) {
            sensorManager = new LnSensorManager(this);
        }
        return sensorManager;
    }
