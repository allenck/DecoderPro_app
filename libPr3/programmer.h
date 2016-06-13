#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include "commandstation.h"
#include "proglistener.h"
#include "exceptions.h"
#include "propertychangelistener.h"

/**
 * Provide access to the hardware DCC decoder programming capability.
 * <P>
 * Programmers come in multiple types:
 * <UL>
 * <LI>Global, previously Service Mode, e.g. on a programming track
 * <LI>Addressed, previously Ops Mode, e.g. "programming on the main"
 * </UL>
 * Different equipment may also require different programmers:
 * <LI>DCC CV programming, on service mode track or on the main
 * <LI>CBUS Node Variable programmers
 * <LI>LocoNet System Variable programmers
 * <LI>LocoNet Op Switch programmers
 * </UL>
 * Depending on which type you have, only certain modes can
 * be set. Valid modes are specified by the class static constants.
 * <P>
 * You get a Programmer object from a {@link ProgrammerManager},
 * which in turn can be located from the {@link InstanceManager}.
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
 * @see         jmri.ProgrammerManager
 * @author	Bob Jacobsen Copyright (C) 2001, 2008
 * @version	$Revision: 17977 $
 */

class ProgrammingMode;
class Programmer : public CommandStation
{
 Q_OBJECT
// Q_ENUMS(programmerMode)
public:
 explicit Programmer(QObject *parent = 0) : CommandStation(parent) {}
// enum programmerMode
// {
//  // mode e.g. register, direct, paged

//  /**
//   * No programming mode available
//   */
//  NONE  = 0,
//  /**
//   * NMRA "Register" mode
//   */
//  REGISTERMODE = 11,

//     /**
//      * NMRA "Paged" mode
//      */
//     PAGEMODE = 21,

//     /**
//      * NMRA "Direct" mode, using only the bit-wise operations
//      */
//     DIRECTBITMODE  = 31,

//     /**
//      * NMRA "Direct" mode, using only the byte-wise operations
//      */
//     DIRECTBYTEMODE = 32,
//     /**
//      * NMRA "Address-only" mode. Often implemented as
//      * a proper subset of "Register" mode, as the
//      * underlying operation is the same.
//      */
//     ADDRESSMODE = 41,

//     /**
//      * NMRA "Operations" or "Programming on the main" mode, using only the byte-wise operations
//      */
//     OPSBYTEMODE  = 101,
//     /**
//      * NMRA "Operations" or "Programming on the main" mode, using only the bit-wise operations
//      */
//     OPSBITMODE  = 102,
//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the byte-wise operations. Note that this is
//      * defined as using the "normal", not "extended" addressing.
//      */
//     OPSACCBYTEMODE  = 111,

//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the bit-wise operations. Note that this is
//      * defined as using the "normal", not "extended" addressing.
//      */
//     OPSACCBITMODE   = 112,
//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the byte-wise operations and "extended" addressing.
//      */
//     OPSACCEXTBYTEMODE = 121,
//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the bit-wise operations and "extended" addressing.
//      */
//     OPSACCEXTBITMODE  = 122,

//     /**
//      * CBUS mode for programming node variables.
//      */
//     CBUSNODEVARMODE  = 140
//    };

/**
 * Perform a CV write in the system-specific manner,
 * and using the specified programming mode.
 * Note that this returns before the write
 * is complete; you have to provide a ProgListener to hear about
 * completion. The exceptions will only be thrown at the start, not
 * during the actual programming sequence. A typical exception would be
 * due to an invalid mode (though that should be prevented earlier)
 */
 virtual void writeCV(int /*CV*/, int /*val*/, ProgListener* /*p*/) /*throw(ProgrammerException)*/ {}
 /**
  * Perform a CV write in the system-specific manner,
  * and using the specified programming mode.
  *<P>
  * Handles a general address space through a String address.
  * Each programmer defines the acceptable formats.
  *<P>
  * Note that this returns before the write
  * is complete; you have to provide a ProgListener to hear about
  * completion. The exceptions will only be thrown at the start, not
  * during the actual programming sequence. A typical exception would be
  * due to an invalid mode (though that should be prevented earlier)
  */
 virtual /*public*/ void writeCV(QString /*CV*/, int /*val*/, ProgListener* /*p*/) /*throw (ProgrammerException)*/ {}
 /**
 * Perform a CV read in the system-specific manner,
 * and using the specified programming mode.
 * Note that this returns before the read
 * is complete; you have to provide a ProgListener to hear about
 * completion. The exceptions will only be thrown at the start, not
 * during the actual programming sequence. A typical exception would be
 * due to an invalid mode (though that should be prevented earlier)
 */
virtual void readCV(int /*CV*/, ProgListener* /*p*/) {} // throws ProgrammerException;
 /**
  * Perform a CV read in the system-specific manner,
  * and using the specified programming mode.
  *<P>
  * Handles a general address space through a String address.
  * Each programmer defines the acceptable formats.
  *<P>
  * Note that this returns before the read
  * is complete; you have to provide a ProgListener to hear about
  * completion. The exceptions will only be thrown at the start, not
  * during the actual programming sequence. A typical exception would be
  * due to an invalid mode (though that should be prevented earlier)
  */
 virtual /*public*/ void readCV(QString /*CV*/, ProgListener* /*p*/) {} // throws ProgrammerException;
 /**
 * Confirm the value of a CV using the specified programming mode.
 * On some systems, this is faster than a read.
 * Note that this returns before the confirm
 * is complete; you have to provide a ProgListener to hear about
 * completion. The exceptions will only be thrown at the start, not
 * during the actual programming sequence. A typical exception would be
 * due to an invalid mode (though that should be prevented earlier)
 */
virtual void confirmCV(int /*CV*/, int /*val*/, ProgListener* /*p*/) {} /*throw(ProgrammerException)*/
 /**
  * Confirm the value of a CV using the specified programming mode.
  * On some systems, this is faster than a read.
  *<P>
  * Handles a general address space through a String address.
  * Each programmer defines the acceptable formats.
  *<P>
  * Note that this returns before the confirm
  * is complete; you have to provide a ProgListener to hear about
  * completion. The exceptions will only be thrown at the start, not
  * during the actual programming sequence. A typical exception would be
  * due to an invalid mode (though that should be prevented earlier)
  */
  virtual /*public*/ void confirmCV(QString /*CV*/, int /*val*/, ProgListener* /*p*/) /*throw (ProgrammerException)*/ {}
/**
 * Get the list of {@link ProgrammingMode} supported by this
 * Programmer. If the order is significant, earlier modes are better.
 */
    /*public*/ virtual QList<ProgrammingMode*> getSupportedModes() {return QList<ProgrammingMode*>();}
  virtual void setMode(ProgrammingMode* /*mode*/) {}
  virtual ProgrammingMode*  getMode() {return NULL;}
//virtual bool hasMode(int mode) {return false;}
  virtual bool getCanRead() {return false;}
/**
 * Checks the general read capability, regardless of mode,
 * for a specific address
 */
  virtual /*public*/ bool getCanRead(QString /*addr*/) {return false;}

/**
 * Checks the general write capability, regardless of mode
 */
 virtual /*public*/ bool getCanWrite() {return false;}
/**
 * Checks the general write capability, regardless of mode,
 * for a specific address
 */
 virtual /*public*/ bool getCanWrite(QString /*addr*/) {return false;}

  virtual void addPropertyChangeListener(PropertyChangeListener* /*p*/) {}
virtual void removePropertyChangeListener(PropertyChangeListener* /*p*/) {}

// error handling on request is via exceptions
// results are returned via the ProgListener callback

 virtual QString decodeErrorCode(int /*i*/) {return "";}

signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(Programmer, "Programmer interface")
#endif // PROGRAMMER_H
