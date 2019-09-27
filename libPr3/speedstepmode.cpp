#include "speedstepmode.h"
#include "exceptions.h"

SpeedStepMode::SpeedStepMode(QObject *parent) : QObject(parent)
{

}
/**
 * DCC Speed Step Mode.
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
 * @author Austin Hendrix Copyright (C) 2019
 */
//@javax.annotation.concurrent.Immutable
// /*public*/ enum SpeedStepMode {
//    UNKNOWN("unknown", 1, 0.0f),
//    // NMRA DCC standard speed step modes.
//    NMRA_DCC_128("128", 126), // Remember there are only 126 non-stop values in 128 speed.
//    NMRA_DCC_28("28", 28),
//    NMRA_DCC_27("27", 27),
//    NMRA_DCC_14("14", 14),
//    // Non-DCC speed step modes.
//    MOTOROLA_28("motorola_28", 28), // Motorola 28 speed step mode.
//    TMCC_32("tmcc_32", 32), // Lionel TMCC 32 speed step mode.
//    INCREMENTAL("incremental", 1, 1.0f);

    SpeedStepMode::SpeedStepMode(QString name, int numSteps, QObject *parent) : QObject(parent) {
        common(name, numSteps, 1.0f / numSteps);
    }

    SpeedStepMode::SpeedStepMode(QString name, int numSteps, float increment, QObject *parent) : QObject(parent)
    {
     common(name, numSteps, increment);
    }

    void SpeedStepMode::common(QString name, int numSteps, float increment){
        this->name = name;
        this->numSteps = numSteps;
        this->increment = increment;
    }


    /**
     * Convert a human-readable string to a DCC speed step mode.
     *
     * @param name string version of speed step mode; example "128"
     * @return matching SpeedStepMode
     * @throws IllegalArgumentException if name does not correspond to a valid speed step mode.
     */
    /*static*/ /*public*/ SpeedStepMode::SSMODDES SpeedStepMode::getByName(QString name) {
//        for(SpeedStepMode s : SpeedStepMode.values()) {
//            if(s.name.equals(name)) {
//                return s;
//            }
//        }
     if(name == "unknown")
      return UNKNOWN;
     if(name == "128")
      return NMRA_DCC_128;
     if(name == "28")
      return NMRA_DCC_28;
     if(name == "27")
      return NMRA_DCC_27;
     if(name == "14")
      return NMRA_DCC_14;
     if(name == "motorola_28")
      return MOTOROLA_28;
     if(name == "tmcc_32")
      return TMCC_32;
     if(name == "incremental")
      return INCREMENTAL;

        throw  IllegalArgumentException("Invalid speed step mode: " + name);
    }
#if 0
    static /*public*/ EnumSet<SpeedStepMode> getCompatibleModes(
            EnumSet<SpeedStepMode> command_station_modes,
            EnumSet<SpeedStepMode> decoder_modes) {
        EnumSet<SpeedStepMode> result = command_station_modes.clone();
        result.retainAll(decoder_modes);
        return result;
    }

    static /*public*/ SpeedStepMode bestCompatibleMode(
            EnumSet<SpeedStepMode> command_station_modes,
            EnumSet<SpeedStepMode> decoder_modes) {
        EnumSet<SpeedStepMode> result = getCompatibleModes(command_station_modes, decoder_modes);
        if(result.contains(NMRA_DCC_128)) {
            return NMRA_DCC_128;
        } else if(result.contains(TMCC_32)) {
            return TMCC_32;
        } else if(result.contains(NMRA_DCC_28)) {
            return NMRA_DCC_28;
        } else if(result.contains(MOTOROLA_28)) {
            return MOTOROLA_28;
        } else if(result.contains(NMRA_DCC_27)) {
            return NMRA_DCC_27;
        } else if(result.contains(NMRA_DCC_14)) {
            return NMRA_DCC_14;
        }
        return UNKNOWN;
    }
#endif
