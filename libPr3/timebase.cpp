#include "timebase.h"
/**
 * Provide access to clock capabilities in hardware or software.
 * <P>
 * The Rate parameter determines how much faster than real time
 * this timebase runs.  E.g. a value of 2.0 means that the value
 * returned by getTime will advance an hour for every half-hour of
 * wall-clock time elapsed.
 * <P>
 * The Rate and Run parameters are bound, so you can listen for them
 * changing.  The Time parameters is not bound, because it changes
 * continuously.  Ask for its value when needed, or add a
 * a listener for the changes in the "minute" value using {@link #addMinuteChangeListener}
 * <P>
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
 * @author			Bob Jacobsen Copyright (C) 2004, 2007, 2008
 * @version			$Revision: 17977 $
 */

//Timebase::Timebase(QObject *parent)
//{
//}
