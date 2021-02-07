#ifndef DCCTHROTTLE_H
#define DCCTHROTTLE_H
#include "throttle.h"
#include "libPr3_global.h"
#include "speedstepmode.h"

//class Throttle;
class LIBPR3SHARED_EXPORT DccThrottle : public Throttle
{
    Q_OBJECT
public:
    explicit DccThrottle(QObject *parent = 0) : Throttle(parent) {}
    ~DccThrottle() {}
    DccThrottle(const DccThrottle&) : Throttle() {}
    /**
     * Provide DCC-specific extensions to Throttle interface.
     *
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
     * @author			Bob Jacobsen Copyright (C) 2001
     * @version			$Revision: 20636 $
     * @see Throttle
     */
//    public interface DccThrottle extends Throttle {

// to handle quantized speed. Note this can change! Valued returned is
// always positive.
virtual float getSpeedIncrement() {return 0.0;}

// Handle Speed Step Information

// There are 4 valid speed step modes
static const int SpeedStepMode128 = 1;
static const int SpeedStepMode28 = 2;
static const int SpeedStepMode27 = 4;
static const int SpeedStepMode14 = 8;
static const int SpeedStepMode28Mot = 16;

/*
 * setSpeedStepMode - set the speed step value.
 * <P>
 * @param Mode - the current speed step mode - default should be 128
 *              speed step mode in most cases
 */
void virtual setSpeedStepMode(SpeedStepMode::SSMODES /*Mode*/) {}

/*
 * getSpeedStepMode - get the current speed step value.
 * <P>
 */
virtual SpeedStepMode::SSMODES getSpeedStepMode() {return   SpeedStepMode::UNKNOWN;}

// information on consisting  (how do we set consisting?)

// register for notification


signals:
    
public slots:
    
};
Q_DECLARE_METATYPE(DccThrottle)
#endif // DCCTHROTTLE_H
